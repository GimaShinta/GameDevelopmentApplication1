#pragma once

#include "../GameObject.h"

class BoxEnemy :public GameObject
{
private:
	int animation[2];
	int animation_count;
	int flip_flag;

public:
	BoxEnemy();
	~BoxEnemy();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�A�j���[�V��������
	void AnimeControl();
};