#pragma once
#include "../GameObject.h"

class Bomb :public GameObject
{
private:
	int animation[2];
	int animation_count;
	Vector2D direction;     //is•ûŒü

public:
	Bomb();
	~Bomb();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	//“–‚½‚è”»’è’Ê’mˆ—
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//ˆÚ“®ˆ—
	void Movement();
};