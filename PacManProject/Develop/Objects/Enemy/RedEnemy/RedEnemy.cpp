#include "../EnemyBase.h"
#include "RedEnemy.h"
#include "../../../Utility/InputManager.h"
#include "../../../Utility/ResourceManager.h"
#include "DxLib.h"


RedEnemy::RedEnemy()
{
}

RedEnemy::~RedEnemy()
{
}

//初期化処理
void RedEnemy::Initialize()
{
	__super::Initialize();

	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	image = move_animation[0];
}

//更新処理
void RedEnemy::Update(float delta_second)
{
	__super::Update(delta_second);

	//エネミー状態によって、動作を変える
	switch (enemy_state)
	{
		case eEnemyState::TRACK:
			Movement(delta_second);
			AnimationControl(delta_second);
			break;
		case eEnemyState::TERRITORY:
			Movement(delta_second);
			AnimationControl(delta_second);
			break;
	}
}

//描画処理
void RedEnemy::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

//終了時処理
void RedEnemy::Finalize()
{
	move_animation.clear();
	eye_animation.clear();
}

//移動処理
void RedEnemy::Movement(float delta_second)
{
	//親クラスの移動処理を呼び出す
	__super::MovementBase(delta_second);
}

//アニメーション制御
void RedEnemy::AnimationControl(float delta_second)
{
	//親クラスの移動処理を呼び出す
	__super::AnimationBase(delta_second);
	
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		// 画像の設定
		image = move_animation[move_order[animation_count]];
	}
}
