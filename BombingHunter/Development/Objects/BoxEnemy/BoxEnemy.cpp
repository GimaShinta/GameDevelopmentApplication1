#include "BoxEnemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

BoxEnemy::BoxEnemy():animation_count(0),flip_flag(FALSE)
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

}

void BoxEnemy::Update()
{
	location.x += 1.0f;

	//�E�̉�ʒ[���獶�̉�ʒ[�Ɉړ�����
	if (location.x >= 700.0f)
	{
		location.x = 0.0f;
	}
}

void BoxEnemy::Draw() const
{
	DrawRotaGraph(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D t1 = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif

}

void BoxEnemy::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void BoxEnemy::OnHitCollision(GameObject* hit_object)
{
}

void BoxEnemy::AnimeControl()
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
