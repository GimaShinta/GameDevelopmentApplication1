#include "Bomb.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"
#include "../../Scene/Scene.h"
#include "../Player/Player.h"

Bomb::Bomb() :animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Bomb::~Bomb()
{
}

void Bomb::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1)
	{
		throw("�{�b�N�X�G�l�~�[�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = -1.6f;

	//�傫���̐ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(0, 1.0f);
}

void Bomb::Update()
{
	//�ړ�����
	Movement();
}

void Bomb::Draw() const
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

void Bomb::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Bomb::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		delete_flag = FALSE;
	}
	else
	{
		delete_flag = TRUE;
	}
}

void Bomb::Movement()
{
	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}
