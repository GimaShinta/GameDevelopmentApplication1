#include "WingEnemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�^�ϊ��p
#include "../Bomb/Bomb.h"

WingEnemy::WingEnemy():animation_count(0)
{
	//������
	animation[0] = NULL;
	animation[1] = NULL;
	number[0] = NULL;
	number[1] = NULL;
}

WingEnemy::~WingEnemy()
{
}

//����������
void WingEnemy::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");

	number[0] = LoadGraph("Resource/Images/Score/3.png");
	number[1] = LoadGraph("Resource/Images/Score/0.png");


	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�l�e�L�̉摜������܂���\n");
	}
	if (number[0] == -1 || number[1] == -1)
	{
		throw("�����̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = (64.0f / 5) * 3;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(0, 0);

}

//�X�V����
void WingEnemy::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();

	//������Ƃ��̃A�j���[�V�������s��
	if (animation_flag == TRUE)
	{
		//�����x���グ��
		transparent += gradually;

		//�J�E���g���Z
		anim_count++;
		if (anim_count >= 5)
		{
			//anim_count��15�ɂȂ�����1�����Z
			 reach_count+= 1;
			//�����ł����
			if (reach_count % 2 == 0)
			{
				location.x += -5;
			}
			//��ł����
			else
			{
				location.x += 5;
			}
			//�J�E���g���Z�b�g
			anim_count = 0;
		}
		//���S�ɓ����ɂȂ�����폜
		if (transparent <= 0)
		{
			//�폜�t���O
			delete_flag = TRUE;
		}
	}
}

//�`�揈��
void WingEnemy::Draw() const
{
	//������Ƀn�l�e�L�摜��`�悷��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparent);
	DrawRotaGraphF(location.x, location.y, image_size, radian, image, TRUE, flip_flag);
	//�l���X�R�A�̕\��
	if (transparent < 255)
	{
		DrawRotaGraphF(location.x+45, location.y-30, number_size, radian, number[0], TRUE, FALSE);
		DrawRotaGraphF(location.x+55, location.y-30, number_size, radian, number[1], TRUE, FALSE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void WingEnemy::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(number[0]);
	DeleteGraph(number[1]);
}

//�����蔻��ʒm����
void WingEnemy::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	//�q�b�g���ʒm
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		//����
		animation_flag = TRUE;
		//�X�R�A
		score = 30;
	}
}

//�ړ�����
void WingEnemy::Movement()
{
	int we_rd = rand() % 10 + 1;
	//�E����o��
	if (flip_flag == FALSE)
	{
		//�X�s�[�h�̊m���i�E�i�s�j
		if (we_rd < 7)
		{
			direction.x = 1;
		}
		else
		{
			direction.x = 2;
		}
	}
	//������o��
	else
	{
		//�X�s�[�h�̊m���i���i�s�j
		if (we_rd < 7)
		{
			direction.x = -1;
		}
		else
		{
			direction.x = -2;
		}
	}

	//������Ƃ��������~�߂�
	if (animation_flag == TRUE)
	{
		direction = 0;
	}

	//��ʊO�ō폜
	if (location.x < 0 || location.x>640)
	{
		//�폜�t���O
		delete_flag = TRUE;
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

//�A�j���[�V��������
void WingEnemy::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}
