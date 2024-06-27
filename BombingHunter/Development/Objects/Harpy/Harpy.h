#pragma once

#include "../GameObject.h"

class Harpy :public GameObject
{
private:
	int animation[2];
	int animation_count;

public:
	Harpy();
	~Harpy();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimationControl();
};