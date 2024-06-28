#include "GoldEnemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�^�ϊ��p
#include "../Bomb/Bomb.h"

GoldEnemy::GoldEnemy() :animation_count(0)
{
	//������
	for (int i = 0; i < 5; i++)
	{
		animation[i] = NULL;
	}
}

GoldEnemy::~GoldEnemy()
{
}

//����������
void GoldEnemy::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
	animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
	animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
	animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");

	//�G���[�`�F�b�N
	for (int i = 0; i < 5; i++)
	{
		if (animation[i] == -1)
		{
			throw("�L���e�L�̉摜������܂���\n");
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
void GoldEnemy::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();

	//������Ƃ��̃A�j���[�V�������s��
	if (animation_flag == TRUE)
	{
		//�����x���グ��
		anim_a += anim_b;

		//�J�E���g���Z
		a_count++;
		if (a_count >= 15)
		{
			//a_count��15�ɂȂ�����1�����Z
			b_count += 1;
			//�����ł����
			if (b_count % 2 == 0)
			{
				location.x += -20;
			}
			//��ł����
			else
			{
				location.x += 20;
			}
			//�J�E���g���Z�b�g
			a_count = 0;
		}
		//���S�ɓ����ɂȂ�����폜
		if (anim_a <= 0)
		{
			//�폜�t���O
			delete_flag = TRUE;
		}
	}
}

//�`�揈��
void GoldEnemy::Draw() const
{
	//������ɃL���e�L�摜��`�悷��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, anim_a);
	DrawRotaGraphF(location.x, location.y, image_size, radian, image, TRUE, flip_flag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void GoldEnemy::Finalize()
{
	//�g�p�����摜���������
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//�����蔻��ʒm����
void GoldEnemy::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	//�q�b�g���ʒm
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		//������
		animation_flag = TRUE;

		//�X�R�A
		score = 1500;
	}
}

//�ړ�����
void GoldEnemy::Movement()
{
	//�E����o��
	if (flip_flag == FALSE)
	{
		direction.x = 2;
	}
	//������o��
	else
	{
		direction.x = -2;
	}

	//������Ƃ��������~�߂�
	if (animation_flag == TRUE)
	{
		direction = 0;
	}

	//��ʊO�ō폜
	if (location.x < 0 || location.x>640)
	{
		//��ʊO�t���O
		out_flag = TRUE;
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

//�A�j���[�V��������
void GoldEnemy::AnimationControl()
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
		else if(image == animation[1])
		{
			image = animation[2];
		}
		else if (image == animation[2])
		{
			image = animation[3];
		}
		else if (image == animation[3])
		{
			image = animation[4];
		}
		else if (image == animation[4])
		{
			image = animation[1];
		}
	}
}
