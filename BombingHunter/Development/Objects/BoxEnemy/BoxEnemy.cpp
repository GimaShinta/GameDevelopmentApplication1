#include "BoxEnemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�^�ϊ��p
#include "../Bomb/Bomb.h"

BoxEnemy::BoxEnemy():animation_count(0)
{
	//������
	animation[0] = NULL;
	animation[1] = NULL;
}

BoxEnemy::~BoxEnemy()
{
}

//����������
void BoxEnemy::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�R�e�L�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = (64.0f / 5) * 4;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(0, 0);

}

//�X�V����
void BoxEnemy::Update()
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
			//��ł����
			if (b_count % 2 == 0)
			{
				location.x += -20;
			}
			//�����ł����
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
void BoxEnemy::Draw() const
{
	//������Ƀn�R�e�L�摜��`�悷��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, anim_a);
	DrawRotaGraphF(location.x, location.y, image_size, radian, image, TRUE, flip_flag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void BoxEnemy::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void BoxEnemy::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	//�q�b�g���ʒm
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		//����
		animation_flag = TRUE;

		//�X�R�A
		score = 200;
	}
}

//�ړ�����
void BoxEnemy::Movement()
{
	//�E����o��
	if (flip_flag == FALSE)
	{
		direction.x = 1;
	}
	//������o��
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
void BoxEnemy::AnimationControl()
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
