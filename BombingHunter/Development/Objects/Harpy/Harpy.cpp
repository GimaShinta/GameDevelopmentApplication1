#include "Harpy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�^�ϊ��p
#include "../Bomb/Bomb.h"

Harpy::Harpy() :animation_count(0)
{
	//������
	animation[0] = NULL;
	animation[1] = NULL;

	for (int i = 0; i < 4; i++)
	{
		number[i] = NULL;
	}
}

Harpy::~Harpy()
{
}

//����������
void Harpy::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Harpy/1.png");
	animation[1] = LoadGraph("Resource/Images/Harpy/2.png");

	number[0] = LoadGraph("Resource/Images/FlyText/-.png");
	number[1] = LoadGraph("Resource/Images/Score/1.png");
	number[2] = LoadGraph("Resource/Images/Score/0.png");
	number[3] = LoadGraph("Resource/Images/Score/0.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�[�s�[�̉摜������܂���\n");
	}

	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1 )
		{
			throw("�����̉摜������܂���\n");
		}
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
void Harpy::Update()
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
			reach_count += 1;
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
void Harpy::Draw() const
{
	//������Ƀn�[�s�[�摜��`�悷��
	//anim_a�œ����x���グ��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparent);
	DrawRotaGraphF(location.x, location.y, image_size, radian, image, TRUE, flip_flag);
	//�l���X�R�A�̕\��
	if (transparent < 255)
	{
		DrawRotaGraphF(location.x + 45, location.y - 30, number_size, radian, number[0], TRUE, FALSE);
		DrawRotaGraphF(location.x + 55, location.y - 30, number_size, radian, number[1], TRUE, FALSE);
		DrawRotaGraphF(location.x + 65, location.y - 30, number_size, radian, number[2], TRUE, FALSE);
		DrawRotaGraphF(location.x + 75, location.y - 30, number_size, radian, number[3], TRUE, FALSE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Harpy::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);

	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(number[i]);
	}
}

//�����蔻��ʒm����
void Harpy::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	//�q�b�g������
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		//������
		animation_flag = TRUE;

		//�X�R�A
		score = -100;
	}
}

//�ړ�����
void Harpy::Movement()
{
	//������o��
	if (flip_flag == FALSE)
	{
		direction.x = 1;
	}
	//�E����o��
	else
	{
		direction.x = -1;
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
void Harpy::AnimationControl()
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
