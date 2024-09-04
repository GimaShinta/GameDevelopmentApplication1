#include "../EnemyBase.h"
#include "RedEnemy.h"
#include "../../../Utility/InputManager.h"
#include "../../../Utility/ResourceManager.h"
#include "../../Player/Player.h"
#include "DxLib.h"
#include <fstream>

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
void RedEnemy::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

//終了時処理
void RedEnemy::Finalize()
{
	__super::Finalize();
	move_animation.clear();
}

//移動処理
void RedEnemy::Movement(float delta_second)
{
	//親クラスの移動処理を呼び出す
	__super::MovementBase(delta_second);

	//比較用の隣接パネル情報
	std::map<eAdjacentDirection, ePanelID> next_panel = StageData::GetAdjacentPanelData(location);

	std::map<eEnemyDirectionState, int> e_state;
	std::map<int, int> open;
	std::map<int, int> close;

	//現在パネルの位置座標
	distance = PanelDistance(panel_x, panel_y);
	//プレイヤーまでの距離の分だけ回す
	for (int step_number = 0; step_number < distance; step_number++)
	{
		//隣接パネルの評価の開示
		for (int i = 0; i < 4; i++)
		{
			//右パネルの評価
			if (i == 0)
			{
				panel_x += 1;
				open[i] = PanelDistance(panel_x, panel_y);
				e_state[eEnemyDirectionState::RIGHT] = open[i];
				//隣のパネルが壁の場合配列に入れないようにする
				if (next_panel[eAdjacentDirection::RIGHT] == ePanelID::WALL)
				{
					open[i] = 100;
					e_state[eEnemyDirectionState::RIGHT] = open[i];
				}
				panel_x += -1;
			}
			//左パネルの評価
			else if (i== 1)
			{
				panel_x += -1;
				open[i] = PanelDistance(panel_x, panel_y);
				e_state[eEnemyDirectionState::LEFT] = open[i];
				//隣のパネルが壁の場合配列に入れないようにする
				if (next_panel[eAdjacentDirection::LEFT] == ePanelID::WALL)
				{
					open[i] = 100;
					e_state[eEnemyDirectionState::LEFT] = open[i];
				}
				panel_x += 1;
			}
			//上パネルの評価
			else if (i == 2)
			{
				panel_y += -1;
				open[i] = PanelDistance(panel_y, panel_y);
				e_state[eEnemyDirectionState::UP] = open[i];
				//隣のパネルが壁の場合配列に入れないようにする
				if (next_panel[eAdjacentDirection::UP] == ePanelID::WALL)
				{
					open[i] = 100;
					e_state[eEnemyDirectionState::UP] = open[i];
				}
				panel_y += 1;
			}
			//下パネルの評価
			else if (i == 3)
			{
				panel_y += 1;
				open[i] = PanelDistance(panel_x, panel_y);
				e_state[eEnemyDirectionState::DOWN] = open[i];
				//隣のパネルが壁の場合配列に入れないようにする
				if (next_panel[eAdjacentDirection::DOWN] == ePanelID::WALL)
				{
					open[i] = 100;
					e_state[eEnemyDirectionState::DOWN] = open[i];
				}
				panel_y += -1;
			}
		}
		//評価の比較を配列の数-1の数だけ繰り返す
		for (int j = 0; j < 3; j++)
		{
			//隣接パネルの評価の比較
			if (open[j] < open[j + 1])
			{
				//評価の小さいパネルを既に見たパネル配列に入れる
				close[step_number] = open[j];
			}
			//評価が同じだった場合
			else if (open[j] == open[j + 1])
			{
				//比べる一個前の値を入れる
				close[step_number] = open[j - 1];
			}
			else
			{
				//評価の小さいパネルを既に見たパネル配列に入れる
				close[step_number] = open[j + 1];
			}
		}
		//一番評価の小さかったパネルが右だったら、右のパネル視点へ
		if (e_state[eEnemyDirectionState::RIGHT] == close[step_number])
		{
			panel_x += 1;
		}
		//一番評価の小さかったパネルが右だったら、右のパネル視点へ
		if (e_state[eEnemyDirectionState::LEFT] == close[step_number])
		{
			panel_x -= 1;
		}
		//一番評価の小さかったパネルが右だったら、右のパネル視点へ
		if (e_state[eEnemyDirectionState::UP] == close[step_number])
		{
			panel_y += -1;
		}
		//一番評価の小さかったパネルが右だったら、右のパネル視点へ
		if (e_state[eEnemyDirectionState::RIGHT] == close[step_number])
		{
			panel_y += 1;
		}
	}

	for (int i = 0; i < close.size(); i++)
	{
		printf("%d", close[i]);
	}


	//open[d] == close[c - 1]



	//now_direction = next_direction;

	//// 進行方向の移動量を追加
	//switch (now_direction)
	//{
	//case eEnemyDirectionState::UP:
	//	direction.y = -2.5;
	//	break;
	//case eEnemyDirectionState::DOWN:
	//	direction.y = 2.5;
	//	break;
	//case eEnemyDirectionState::LEFT:
	//	direction.x = -2.5;
	//	break;
	//case eEnemyDirectionState::RIGHT:
	//	direction.x = 2.5;
	//	break;
	//default:
	//	break;
	//}

	//配列に進行方向をいれてプレイヤーまでの方向を決める


}

//アニメーション制御
void RedEnemy::AnimationControl(float delta_second)
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