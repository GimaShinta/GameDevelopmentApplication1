#include "Bomb.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"
#include <math.h>

//型変換用
#include "../Player/Player.h"
#include "../EnemyBullet/EnemyBullet.h"

Bomb::Bomb() :animation_count(0)
{
	//初期化
	for (int i = 0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

Bomb::~Bomb()
{

}

//初期化処理
void Bomb::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Images/Blast/1.png");
	animation[2] = LoadGraph("Resource/Images/Blast/2.png");
	animation[3] = LoadGraph("Resource/Images/Blast/3.png");

	//エラーチェック
	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("爆弾の画像がありません\n");
		}
	}

	//向きの設定
	radian = 0;

	//大きさの設定
	box_size = (64.0f/5)*4;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(0.0f, 1.3f);
}

//更新処理
void Bomb::Update()
{
	//移動処理
	Movement();

	//消えるときアニメーションを行う
	if (animation_flag == TRUE)
	{
		//アニメーション制御
		AnimationControl();
	}
}

//描画処理
void Bomb::Draw() const
{	
	//情報を基に爆弾の画像を描画する
	DrawRotaGraphF(location.x, location.y, image_size, radian, image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Bomb::Finalize()
{
	//使用した画像を解放する
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//当たり判定通知処理
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	//ヒット時通知
	if (dynamic_cast<Player*>(hit_object) != nullptr)
	{
		//消えない
		animation_flag = FALSE;
	}
	else if (dynamic_cast<EnemyBullet*>(hit_object) != nullptr)
	{
		//消えない
		animation_flag = FALSE;
	}
	else if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		//消えない
		animation_flag = FALSE;
	}
	else
	{
		//消える
		animation_flag = TRUE;
	}
}

//移動処理
void Bomb::Movement()
{
	//location.y = pow(-location.x,2);


	//消えるとき動きを止める
	if (animation_flag == TRUE)
	{
		direction = 0;
	}

	//画面外に行ったら削除
	if (location.y > 480)
	{
		//画面外フラグ
		out_flag = TRUE;
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void Bomb::AnimationControl()
{
	//フレームカウントを加算する
	animation_count++;
    //60フレーム目に到達したら
	if (animation_count >= 15)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else if(image==animation[1])
		{
			image = animation[2];
		}
		else if(image==animation[2])
		{
			image = animation[3];
		}
		else
		{
			//削除フラグ
			delete_flag = TRUE;
		}
	}
}
