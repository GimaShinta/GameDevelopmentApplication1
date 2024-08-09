#pragma once

#include "../EnemyBase.h"
#include "../../Utility/StageData.h"

class RedEnemy : public EnemyBase
{
private:

public:
	RedEnemy();
	~RedEnemy();

	//����������
	virtual void Initialize() override;
	//�X�V����
	virtual void Update(float delta_second) override;
	//�`�揈��
	virtual void Draw(const Vector2D& screen_offset) const override;
	//�I��������
	virtual void Finalize() override;

private:
	//�ړ�����
	void Movement(float delta_second);
	//�A�j���[�V��������
	void AnimationControl(float delta_second);
};