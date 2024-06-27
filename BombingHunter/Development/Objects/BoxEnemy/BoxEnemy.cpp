#include "BoxEnemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//型変換用
#include "../Bomb/Bomb.h"

BoxEnemy::BoxEnemy():animation_count(0)
{
	//初期化
	animation[0] = NULL;
	animation[1] = NULL;
}

BoxEnemy::~BoxEnemy()
{
}

//初期化処理
void BoxEnemy::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハコテキの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	box_size = (64.0f / 5) * 4;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(0, 0);

}

//更新処理
void BoxEnemy::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();

	//消えるときのアニメーションを行う
	if (animation_flag == TRUE)
	{
		//透明度を上げる
		anim_a += anim_b;

		//カウント加算
		a_count++;
		if (a_count >= 15)
		{
			//a_countが15になったら1ずつ加算
			b_count += 1;
			//奇数であれば
			if (b_count % 2 == 0)
			{
				location.x += -20;
			}
			//偶数であれば
			else
			{
				location.x += 20;
			}
			//カウントリセット
			a_count = 0;
		}
		//完全に透明になったら削除
		if (anim_a <= 0)
		{
			//削除フラグ
			delete_flag = TRUE;
		}
	}
}

//描画処理
void BoxEnemy::Draw() const
{
	//情報を基にハコテキ画像を描画する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, anim_a);
	DrawRotaGraphF(location.x, location.y, image_size, radian, image, TRUE, flip_flag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void BoxEnemy::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void BoxEnemy::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	//ヒット時通知
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		//消す
		animation_flag = TRUE;

		//スコア
		score = 200;
	}
}

//移動処理
void BoxEnemy::Movement()
{
	//右から出現
	if (flip_flag == FALSE)
	{
		direction.x = 1;
	}
	//左から出現
	else
	{
		direction.x = -1;
	}

	//消えるとき動きを止める
	if (animation_flag == TRUE)
	{
		direction = 0;
	}

	//画面外で削除
	if (location.x < 0 || location.x>640)
	{
		//削除フラグ
		delete_flag = TRUE;
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void BoxEnemy::AnimationControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}
