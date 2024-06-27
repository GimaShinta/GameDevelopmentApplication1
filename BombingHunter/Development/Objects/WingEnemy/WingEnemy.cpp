#include "WingEnemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�^�ϊ��p
#include "../Bomb/Bomb.h"

WingEnemy::WingEnemy():animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
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

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�l�e�L�̉摜������܂���\n");
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
void WingEnemy::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void WingEnemy::Draw() const
{
	//������Ƀn�l�e�L�摜��`�悷��
	DrawRotaGraphF(location.x, location.y, image_size, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void WingEnemy::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void WingEnemy::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	//�q�b�g���ʒm
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		//����
		delete_flag = TRUE;
		//�X�R�A
		score += 30;
	}
	else
	{
		//�����Ȃ�
		delete_flag = FALSE;
	}
}

//�ړ�����
void WingEnemy::Movement()
{
	int we_rd = rand() % 10 + 1;
	//�E����o��
	if (flip_flag == FALSE)
	{
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
		if (we_rd < 7)
		{
			direction.x = -1;
		}
		else
		{
			direction.x = -2;
		}
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
