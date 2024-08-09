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

//����������
void RedEnemy::Initialize()
{
	__super::Initialize();

	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	image = move_animation[0];
}

//�X�V����
void RedEnemy::Update(float delta_second)
{
	__super::Update(delta_second);

	//�G�l�~�[��Ԃɂ���āA�����ς���
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

//�`�揈��
void RedEnemy::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

//�I��������
void RedEnemy::Finalize()
{
	move_animation.clear();
	eye_animation.clear();
}

//�ړ�����
void RedEnemy::Movement(float delta_second)
{
	//�e�N���X�̈ړ��������Ăяo��
	__super::MovementBase(delta_second);
}

//�A�j���[�V��������
void RedEnemy::AnimationControl(float delta_second)
{
	//�e�N���X�̈ړ��������Ăяo��
	__super::AnimationBase(delta_second);
	
	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		// �摜�̐ݒ�
		image = move_animation[move_order[animation_count]];
	}
}
