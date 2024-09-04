#include "../EnemyBase.h"
#include "PinkEnemy.h"
#include "../../../Utility/InputManager.h"
#include "../../../Utility/ResourceManager.h"
#include "../../Player/Player.h"
#include "DxLib.h"
#include <fstream>

PinkEnemy::PinkEnemy()
{
}

PinkEnemy::~PinkEnemy()
{
}

//初期化処理
void PinkEnemy::Initialize()
{
	__super::Initialize();

	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	image = move_animation[2];
}

//更新処理
void PinkEnemy::Update(float delta_second)
{
	__super::Update(delta_second);

	//エネミー状態によって、動作を変える
	switch (enemy_state)
	{
	case eEnemyState::TRACK:
		//移動速度の変更
		enemy_speed = 0.75;
		//移動処理
		Movement(delta_second);
		//アニメーション制御
		AnimationControl(delta_second);
		break;
	case eEnemyState::TERRITORY:
		//移動速度の変更
		enemy_speed = 0.75;
		//移動処理
		Movement(delta_second);
		//アニメーション制御
		AnimationControl(delta_second);
		break;
	}
}

//描画処理
void PinkEnemy::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

//終了時処理
void PinkEnemy::Finalize()
{
	__super::Finalize();
	move_animation.clear();
}

//移動処理
void PinkEnemy::Movement(float delta_second)
{
	//親クラスの移動処理を呼び出す
	__super::MovementBase(delta_second);
}

//アニメーション制御
void PinkEnemy::AnimationControl(float delta_second)
{
	//親クラスの移動処理を呼び出して目を描画する
	__super::AnimationBase(delta_second);

	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		// 画像の設定
		image = move_animation[move_num[animation_count]];
	}
}