#include "BoxEnemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"
#include "../../Scene/Scene.h"
#include "../Bomb/Bomb.h"
#include "../Player/Player.h"

BoxEnemy::BoxEnemy():animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

BoxEnemy::~BoxEnemy()
{
}

void BoxEnemy::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�{�b�N�X�G�l�~�[�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(1.0f, 0);

}

void BoxEnemy::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimetionControl();
}

void BoxEnemy::Draw() const
{
	//�摜���]�t���O
	int flip_flag = FALSE;

	//�i�s�����ɂ���āA���]��Ԃ����肷��
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//������Ƀn�R�e�L�摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

void BoxEnemy::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void BoxEnemy::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	if (dynamic_cast<BoxEnemy*>(hit_object) != nullptr)
	{
		delete_flag = FALSE;
	}
	else
	{
		delete_flag = TRUE;
	}
}

void BoxEnemy::Movement()
{
	//��ʒ[�ɓ��B������A�i�s�����𔽓]����
	if (((location.x + direction.x) < box_size.x)
		|| (640.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}

	if (((location.y + direction.y) < box_size.y) || (480.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}
	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

void BoxEnemy::AnimetionControl()
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
