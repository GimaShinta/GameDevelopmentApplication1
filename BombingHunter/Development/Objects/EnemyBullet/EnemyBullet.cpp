#include "EnemyBullet.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�^�ϊ��p
#include "../Player/Player.h"

EnemyBullet::EnemyBullet() :animation_count(0)
{
	//������
	for (int i = 0; i < 4; i++)
	{
		animation[i] = NULL;
	}
	for (int i = 0; i < 4; i++)
	{
		number[i] = NULL;
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

	number[0] = LoadGraph("Resource/Images/FlyText/-.png");
	number[1] = LoadGraph("Resource/Images/Score/1.png");
	number[2] = LoadGraph("Resource/Images/Score/0.png");
	number[3] = LoadGraph("Resource/Images/Score/0.png");

	//�G���[�`�F�b�N
	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("�e�L�e�̉摜������܂���\n");
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (number[i] == -1)
		{
			throw("�����̉摜������܂���\n");
		}
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = (64.0f/5)*2;

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

	//������Ƃ��A�j���[�V�������s��
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
	if (animation_flag == TRUE)
	{
		DrawRotaGraphF(location.x + 45, location.y - 30, number_size, radian, number[0], TRUE, FALSE);
		DrawRotaGraphF(location.x + 55, location.y - 30, number_size, radian, number[1], TRUE, FALSE);
		DrawRotaGraphF(location.x + 65, location.y - 30, number_size, radian, number[2], TRUE, FALSE);
		DrawRotaGraphF(location.x + 75, location.y - 30, number_size, radian, number[3], TRUE, FALSE);
	}

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void EnemyBullet::Finalize()
{
	//�g�p�����摜���������
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(animation[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(number[i]);
	}
}

//�����蔻��ʒm����
void EnemyBullet::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	//�q�b�g���ʒm
	if (dynamic_cast<Player*>(hit_object) != nullptr)
	{
		//������
		animation_flag = TRUE;

		//�X�R�A
		score = -100;
	}
}

//�ړ�����
void EnemyBullet::Movement()
{
	//������Ƃ��������~�߂�
	if (animation_flag == TRUE)
	{
		direction = 0;
	}

	//��ʊO�ō폜
	if (location.x < 0 || location.x>640 || location.y < 0)
	{
		//�폜�t���O
		delete_flag = TRUE;
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
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
			//�폜�t���O
			delete_flag = TRUE;
		}
	}
}
