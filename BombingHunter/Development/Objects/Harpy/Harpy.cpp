#include "Harpy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�^�ϊ��p
#include "../Bomb/Bomb.h"

Harpy::Harpy() :animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
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

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�[�s�[�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = 64.0f;

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

	// �A���t�@�l��ω�
	a += b;
}

//�`�揈��
void Harpy::Draw() const
{
	//������Ƀn�[�s�[�摜��`�悷��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
	DrawRotaGraphF(location.x, location.y, image_size, radian, image, TRUE, flip_flag);
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
}

//�����蔻��ʒm����
void Harpy::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	//�q�b�g������
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		//����
		delete_flag = TRUE;

		//�X�R�A
		score += -100;
	}
	else
	{
		//�����Ȃ�
		delete_flag = FALSE;
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
