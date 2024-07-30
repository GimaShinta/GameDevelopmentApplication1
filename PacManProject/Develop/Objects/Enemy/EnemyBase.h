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
	Vector2D velocity;                       //速さ
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

protected:
	int animation_count;                     //アニメーションカウント
	int izike_animcount;                        //イジケのアニメーションカウント
	int izike_reachcount;                        //イジケのアニメーションカウントの到達回数カウント
	int eye;                                 //目の画像

protected:
	bool in_tunnel;                          //トンネルに入っているか
	bool izike;

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize();
	virtual void Update(float delta_secound) ;
	virtual void Draw(const Vector2D& screen_offset) const;
	virtual void Finalize() ;

	virtual void OnHitCollision(GameObjectBase*hit_object)override;

public:
	eEnemyState GetEnemyState() const;
	float GetIzikeTime() const;

public:
	void SetDirection(const Vector2D& direction);
	void SetEnemyState();
	void MovementBase(float delta_second);
	void AnimationBase(float delta_second);
};