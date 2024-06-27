#include "Harpy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//型変換用
#include "../Bomb/Bomb.h"

Harpy::Harpy() :animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Harpy::~Harpy()
{
}

//初期化処理
void Harpy::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Harpy/1.png");
	animation[1] = LoadGraph("Resource/Images/Harpy/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハーピーの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(0, 0);
}

//更新処理
void Harpy::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimationControl();

	// アルファ値を変化
	a += b;
}

//描画処理
void Harpy::Draw() const
{
	//情報を基にハーピー画像を描画する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
	DrawRotaGraphF(location.x, location.y, image_size, radian, image, TRUE, flip_flag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Harpy::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Harpy::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	//ヒット時処理
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		//消す
		delete_flag = TRUE;

		//スコア
		score += -100;
	}
	else
	{
		//消さない
		delete_flag = FALSE;
	}
}

//移動処理
void Harpy::Movement()
{
	//左から出現
	if (flip_flag == FALSE)
	{
		direction.x = 1;
	}
	//右から出現
	else
	{
		direction.x = -1;
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void Harpy::AnimationControl()
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
