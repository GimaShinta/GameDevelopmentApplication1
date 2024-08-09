#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

//エネミー状態
enum eEnemyState
{
	TRACK,
	TERRITORY,
	IZIKE,
	EYE,
};

//エネミーベースクラス
class EnemyBase : public GameObject
{
protected:
	// 進行方向状態
	enum eEnemyDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

protected:
	std::vector<int> move_animation;     //本体の画像
	std::vector<int> eye_animation;      //目の画像

protected:
	Vector2D direction;                      //進行方向
	eEnemyState enemy_state;                 //エネミーの状態

protected:
	eEnemyDirectionState now_direction;      //今の進行方向
	eEnemyDirectionState old_direction;      //前の進行方向
	ePanelID old_panel;                      //前のパネル

protected:
	float animation_time;                    //アニメーションを一定間隔で
	float izike_time;                        //イジケの時間設定
	float track_time;                        //追跡モードの時間設定
	float enemy_speed;                       //エネミーの速度

protected:
	int animation_count;                     //アニメーションカウント
	int eye;                                 //目の画像

protected:
	bool in_tunnel;                          //トンネルに入っているか
	bool izike;                              //イジケ状態か
	bool player_powerd;                      //プレイヤーをパワーダウンさせるか
	bool end_anim;                           //アニメーションを変更させる

	const int move_order[2] = { 0, 1 };                     //移動アニメーションの順番
	const int izike_order[2] = { 16, 17 };                  //イジケ状態アニメーションの順番
	const int izikeend_order[4] = { 16, 17, 18, 19 };       //イジケ終了状態アニメーション順番

public:
	EnemyBase();
	virtual ~EnemyBase();

	//初期化処理
	virtual void Initialize();
	//更新処理
	virtual void Update(float delta_secound);
	//描画処理
	virtual void Draw(const Vector2D& screen_offset) const;
	//終了時処理
	virtual void Finalize() ;

	//ヒット時処理
	virtual void OnHitCollision(GameObjectBase*hit_object)override;

public:
	//エネミー状態の取得
	eEnemyState GetEnemyState() const;
	//プレイヤーパワーダウンフラグの取得
	bool GetPlayerDown() const;

public:
	//進行方向の設定
	void SetDirection(const Vector2D& direction);
	//イジケ状態の設定
	void SetIzikeState();
	//移動処理
	void MovementBase(float delta_second);
	//アニメーション制御
	void AnimationBase(float delta_second);
};