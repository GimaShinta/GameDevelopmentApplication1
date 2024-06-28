#include "Bomb.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"
#include <math.h>

//�^�ϊ��p
#include "../Player/Player.h"
#include "../EnemyBullet/EnemyBullet.h"

Bomb::Bomb() :animation_count(0)
{
	//������
	for (int i = 0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

Bomb::~Bomb()
{

}

//����������
void Bomb::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Images/Blast/1.png");
	animation[2] = LoadGraph("Resource/Images/Blast/2.png");
	animation[3] = LoadGraph("Resource/Images/Blast/3.png");

	//�G���[�`�F�b�N
	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("���e�̉摜������܂���\n");
		}
	}

	//�����̐ݒ�
	radian = 0;

	//�傫���̐ݒ�
	box_size = (64.0f/5)*4;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(0.0f, 1.3f);
}

//�X�V����
void Bomb::Update()
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
void Bomb::Draw() const
{	
	//������ɔ��e�̉摜��`�悷��
	DrawRotaGraphF(location.x, location.y, image_size, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Bomb::Finalize()
{
	//�g�p�����摜���������
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//�����蔻��ʒm����
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	//�q�b�g���ʒm
	if (dynamic_cast<Player*>(hit_object) != nullptr)
	{
		//�����Ȃ�
		animation_flag = FALSE;
	}
	else if (dynamic_cast<EnemyBullet*>(hit_object) != nullptr)
	{
		//�����Ȃ�
		animation_flag = FALSE;
	}
	else if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		//�����Ȃ�
		animation_flag = FALSE;
	}
	else
	{
		//������
		animation_flag = TRUE;
	}
}

//�ړ�����
void Bomb::Movement()
{
	//location.y = pow(-location.x,2);


	//������Ƃ��������~�߂�
	if (animation_flag == TRUE)
	{
		direction = 0;
	}

	//��ʊO�ɍs������폜
	if (location.y > 480)
	{
		//��ʊO�t���O
		out_flag = TRUE;
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

//�A�j���[�V��������
void Bomb::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;
    //60�t���[���ڂɓ��B������
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
		else if(image==animation[2])
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
