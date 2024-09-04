#include "EnemyBase.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../Player/Player.h"
#include "DxLib.h"

#define D_ENEMY_SPEED (50.0f * enemy_speed)
#define D_IZIKE_TIME (9.0f)

EnemyBase::EnemyBase():
	direction(0.0f),
	enemy_state(eEnemyState::TERRITORY),
	now_direction(eEnemyDirectionState::UP),
	next_direction(eEnemyDirectionState::UP),
	old_panel(ePanelID::NONE),
	animation_time(0.0f),
	izike_time(0.0f),
	track_time(0.0f),
	enemy_speed(0.0f),
	animation_count(0),
	eye(NULL),
	distance(0),
	step_number(0),
	panel_x(0),
	panel_y(0),
	in_tunnel(false),
	izike(false),
	player_powerd(false),
	end_anim(false),
	object(nullptr)
{
}

EnemyBase::~EnemyBase()
{
}

//初期化処理
void EnemyBase::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	//初期画像の設定
	eye = eye_animation[1];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	//エネミー状態の設定
	enemy_state = eEnemyState::TRACK;

	//進行方向設定
	direction = Vector2D(2.5f, 0.0f);

	//速度設定
	enemy_speed = 0.75;

	//イジケ時間を設定
	izike_time = D_IZIKE_TIME;
}

//更新処理
void EnemyBase::Update(float delta_second)
{
	//エネミー状態によって、動作を変える
	switch (enemy_state)
	{
	case eEnemyState::IZIKE:
		//移動速度の変更
		//enemy_speed = 0.75 * 0.9;
		enemy_speed = 0.5;
		//移動処理
		MovementBase(delta_second);
		// 移動中のアニメーション
		animation_time += delta_second;
		if (animation_time >= (1.0f / 7.0f))
		{
			animation_time = 0.0f;
			animation_count++;

			//アニメーション変更フラグ
			if (end_anim == false)
			{
				if (animation_count >= 2)
				{
					animation_count = 0;
				}
				// 画像の設定
				image = move_animation[izike_num[animation_count]];
			}
			else
			{
				if (animation_count >= 4)
				{
					animation_count = 0;
				}
				// 画像の設定
				image = move_animation[izikeend_num[animation_count]];
			}
		}
		break;
	case eEnemyState::EYE:
		//移動速度の変更
		enemy_speed = 3;
		//移動処理
		MovementBase(delta_second);
		//アニメーション制御
		AnimationBase(delta_second);
		break;
	}

	//イジケ状態だったら
	if (izike == true)
	{
		//イジケにする
		enemy_state = eEnemyState::IZIKE;
		//イジケ時間を減らす
		izike_time -= delta_second;

		//イジケ時間が３秒以下になったら
		if (izike_time <= 3)
		{
			//アニメーションを変化させる
			end_anim = true;
		}
		//イジケ時間が０秒以下になったら
		if (izike_time <= 0)
		{
			//追跡状態に戻す
			enemy_state = eEnemyState::TRACK;
			//イジケ状態を解除
			izike = false;
			//プレイヤーをパワーダウンさせる
			player_powerd = true;
		}
	}
	//イジケ状態じゃなかったら
	else
	{
		//値のリセット
		end_anim = false;
		player_powerd = false;
		izike_time = D_IZIKE_TIME;
	}

	// 入力状態の取得
	InputManager* input = InputManager::GetInstance();

	//Bキーを押したら通常モードに変更
	if (input->GetKeyDown(KEY_INPUT_B) && enemy_state == eEnemyState::EYE)
	{
		//プレイヤーをパワーダウンさせる
		player_powerd = true;
		//追跡状態にする
		enemy_state = eEnemyState::TRACK;
	}
}

//描画処理
void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;

	//EYE状態以外のとき本体を描画
	if (enemy_state != eEnemyState::EYE)
	{
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.5, 0.0, image, TRUE);
	}

	//イジケ以外のとき目を描画
	if (enemy_state != eEnemyState::IZIKE)
	{
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.5, 0.0, eye, TRUE);
	}
}

//終了時処理
void EnemyBase::Finalize()
{
	eye_animation.clear();
}

//ヒット時処理
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// 当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// 最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Playerからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// めり込んだ差分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diffの分だけ戻る
		location += dv.Normalize() * diff;

		//壁に当たったら反転
		direction *= -1;
	}

	//イジケ状態のままプレイヤーと当たったら
	if (hit_object->GetCollision().object_type == eObjectType::player && enemy_state==eEnemyState::IZIKE)
	{
		//イジケ状態を解除
		izike = false;
		//目の状態にする
		enemy_state = eEnemyState::EYE;
	}
}

//エネミーの状態を取得
eEnemyState EnemyBase::GetEnemyState() const
{
	return enemy_state;
}

//プレイヤーパワーダウンフラグを取得
bool EnemyBase::GetPlayerDown() const
{
	return player_powerd;
}

ePanelID EnemyBase::GetEPanel() const
{
	return old_panel;
}

//進行方向の設定
void EnemyBase::SetDirection(const Vector2D& direction)
{
	this->direction = direction;
}

//イジケ状態に設定
void EnemyBase::SetIzikeState()
{
	this->izike = true;  
}

//共通移動処理
void EnemyBase::MovementBase(float delta_second)
{
	//移動する
	location += direction * D_ENEMY_SPEED * delta_second;
}

//共通アニメーション制御
void EnemyBase::AnimationBase(float delta_second)
{
	//進行方向によって目の向きを変える
	if (direction.x > 0)
	{
		//右を向く
		eye = eye_animation[1];
	}
	else if (direction.x < 0)
	{
		//左を向く
		eye = eye_animation[3];
	}
	else if (direction.y < 0)
	{
		//上を向く
		eye = eye_animation[0];
	}
	else if (direction.y > 0)
	{
		//下を向く
		eye = eye_animation[2];
	}
}

void EnemyBase::SetPlayerControl(Player* player)
{
	object = player;
}

int EnemyBase::PanelDistance(int a, int b)
{
	int p_x, p_y;
	StageData::ConvertToIndex(object->GetLocation(), p_y, p_x);
	int e_x, e_y;
	StageData::ConvertToIndex(GetLocation(), e_y, e_x);
	int distance = (((abs(p_x - e_x)) + a) + ((abs(p_y - e_y)) + b));
	return distance;
}
