#pragma once
#pragma once

#include "../GameObject.h"

class GoldEnemy :public GameObject
{
private:
	int animation[5];
	int number[4];
	int animation_count;

public:
	GoldEnemy();
	~GoldEnemy();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();	//�A�j���[�V��������
	void AnimationControl();
};