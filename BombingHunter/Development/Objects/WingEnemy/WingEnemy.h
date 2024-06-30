#pragma once

#include "../GameObject.h"

class WingEnemy :public GameObject
{
private:
	int animation[2];
	int number[2];
	int animation_count;

public:
	WingEnemy();
	~WingEnemy();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimationControl();
};