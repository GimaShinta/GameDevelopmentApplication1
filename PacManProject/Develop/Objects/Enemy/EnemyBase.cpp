#include "EnemyBase.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

#define D_ENEMY_SPEED (50.0f)

EnemyBase::EnemyBase():
	velocity(0.0f),
	direction(0.0f),
	enemy_state(eEnemyState::TERRITORY),
	now_direction(eEnemyDirectionState::UP),
	old_direction(eEnemyDirectionState::UP),
	old_panel(ePanelID::NONE),
	animation_time(0.0f),
	izike_time(8.0f),
	track_time(0.0f),
	animation_count(0),
	izike_animcount(0),
	izike_reachcount(0),
	eye(NULL),
	in_tunnel(false),
	izike(false)
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

	//速度設定
	velocity = Vector2D(2.5f, 0.0f);
}

//更新処理
void EnemyBase::Update(float delta_second)
{
	//enemy_stateの中身で処理を変える
	switch (enemy_state)
	{
	case eEnemyState::IZIKE:
		MovementBase(delta_second);
		// 移動中のアニメーション
		animation_time += delta_second;
		if (animation_time >= (1.0f / 16.0f))
		{
			animation_time = 0.0f;
			// 画像の設定
			if (image != move_animation[17])
			{
				image = move_animation[17];
			}
			else if (image == move_animation[17])
			{
				image = move_animation[16];
			}
		}
		break;
	case eEnemyState::EYE:
		MovementBase(delta_second);
		AnimationBase(delta_second);
		break;
	}

	//イジケ状態かつ目の状態では無かったら
	if (izike == true && enemy_state != eEnemyState::EYE)
	{
		enemy_state = eEnemyState::IZIKE;
		//カウントを減らす
		izike_time -= delta_second;
	}

	if (izike_time <= 2)
	{
		if (animation_time >= (1.0f / 4.0f))
		{
			animation_time = 0.0f;
			// 画像の設定
			if (image != move_animation[18])
			{
				image = move_animation[18];
			}
			else if (image == move_animation[18])
			{
				image = move_animation[19];
			}
		}
	}
	else if (izike_time <= 0)
	{
		izike_time = 8;
		izike = false;
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
		velocity *= -1;
	}

	//イジケ状態のままプレイヤーと当たったら
	if (hit_object->GetCollision().object_type == eObjectType::player&&enemy_state==eEnemyState::IZIKE)
	{
		enemy_state = eEnemyState::EYE;
	}
}

//エネミーの状態を取得
eEnemyState EnemyBase::GetEnemyState() const
{
	return enemy_state;
}

float EnemyBase::GetIzikeTime() const
{
	return izike_time;
}

//進行方向の設定
void EnemyBase::SetDirection(const Vector2D& direction)
{
	this->direction = direction;
}

//イジケ状態にする
void EnemyBase::SetEnemyState()
{
	izike = true;
}

//共通移動処理
void EnemyBase::MovementBase(float delta_second)
{
	location += velocity * D_ENEMY_SPEED * delta_second;

	//進行方向によって進行方向状態を変更する
	if (velocity.x > 0)
	{
		now_direction = eEnemyDirectionState::RIGHT;
	}
	else if (velocity.x < 0)
	{
		now_direction = eEnemyDirectionState::LEFT;
	}
	else if (velocity.y < 0)
	{
		now_direction = eEnemyDirectionState::UP;
	}
	else if (velocity.y > 0)
	{
		now_direction = eEnemyDirectionState::DOWN;
	}

}

//共通アニメーション制御
void EnemyBase::AnimationBase(float delta_second)
{
	//進行方向によって目の向きが変わる
	switch (now_direction)
	{
	case eEnemyDirectionState::UP:
		eye = eye_animation[0];
		break;
	case eEnemyDirectionState::RIGHT:
		eye = eye_animation[1];
		break;
	case eEnemyDirectionState::DOWN:
		eye = eye_animation[2];
		break;
	case eEnemyDirectionState::LEFT:
		eye = eye_animation[3];
		break;
	default:
		break;
	}
}
