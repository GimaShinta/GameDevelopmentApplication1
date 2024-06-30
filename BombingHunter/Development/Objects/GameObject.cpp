#include "GameObject.h"
#include "DxLib.h"

//�R���X�g���N�^
GameObject::GameObject() :
	location(0.0f),
	box_size(0.0f),
	image_size(0.7),
	number_size(1.0),
	radian(0.0f),
	image(NULL),
	sound(NULL),
	delete_flag(FALSE),
	flip_flag(FALSE),
	animation_flag(FALSE),
	anumber_flag(FALSE),
	score(0),
	transparent(255),
	gradually(-5),
	anim_count(0),
	reach_count(0)
{
}

//�f�X�g���N�^
GameObject::~GameObject()
{

}

//����������
void GameObject::Initialize()
{

}

//�X�V����
void GameObject::Update()
{

}

//�`�揈��
void GameObject::Draw() const
{
	//�����蔻��̉���
	//Vector2D t1 = location - (box_size / 2.0f);
	//Vector2D br = location + (box_size / 2.0f);

	//DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
}

//�I��������
void GameObject::Finalize()
{

}

//�e�I�u�W�F�N�g�̍폜�t���O�擾
bool GameObject::GetDeleteFlag()
{
	return this->delete_flag;
}

//�����蔻��ʒm����
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//�����������ɍs������
}

//�ʒu���擾����
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//�X�R�A�̒l���擾
int GameObject::GetScore()
{
	return this->score;
}

//�ʒu���ݒ菈��
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//�i�s�����ݒ菈��
void GameObject::SetDirection(const Vector2D& direction)
{
	this->direction = direction;
}

//�摜���]�t���O�̎擾
void GameObject::SetFlipFlag(bool flag)
{
	this->flip_flag = flag;
}

//�����蔻��̑傫�����擾����
Vector2D GameObject::GetBoxSize() const
{
	return box_size;
}
