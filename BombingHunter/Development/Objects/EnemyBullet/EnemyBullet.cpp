#include "EnemyBullet.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�^�ϊ��p
#include "../Player/Player.h"

EnemyBullet::EnemyBullet() :animation_count(0)
{
	for (int i = 0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

EnemyBullet::~EnemyBullet()
{
}

//����������
void EnemyBullet::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");
	animation[1] = LoadGraph("Resource/Images/EnemyBullet/eff1.png");
	animation[2] = LoadGraph("Resource/Images/EnemyBullet/eff2.png");
	animation[3] = LoadGraph("Resource/Images/EnemyBullet/eff3.png");

	//�G���[�`�F�b�N
	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("�e�L�e�̉摜������܂���\n");
		}
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = (64.0f/3)*2;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(0, 0);

}

//�X�V����
void EnemyBullet::Update()
{
	//�ړ�����
	Movement();

	if (animation_flag == TRUE)
	{
		//�A�j���[�V��������
		AnimationControl();
	}
}

//�`�揈��
void EnemyBullet::Draw() const
{
	//������Ƀe�L�e�̉摜��`�悷��
	DrawRotaGraphF(location.x, location.y, image_size, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void EnemyBullet::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

//�����蔻��ʒm����
void EnemyBullet::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	//�q�b�g���ʒm
	if (dynamic_cast<Player*>(hit_object) != nullptr)
	{
		//�����i�A�j���[�V�����\�j
		animation_flag = TRUE;

		//�X�R�A
		score += -100;
	}
	else
	{
		//�����Ȃ�
		animation_flag = FALSE;
	}
}

//�ړ�����
void EnemyBullet::Movement()
{
	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	if (animation_flag == TRUE)
	{
		direction = 0;
	}
	location += direction;
}

//�A�j���[�V��������
void EnemyBullet::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//15�t���[���ڂɓ��B������
	if (animation_count >= 15)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else if(image==animation[1])
		{
			image = animation[2];
		}
		else if (image == animation[2])
		{
			image = animation[3];
		}
		else
		{
			//����
			delete_flag = TRUE;
		}
	}
}