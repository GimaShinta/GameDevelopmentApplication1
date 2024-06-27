#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER    //���W�̌��_���摜�̒��S�ɂ���

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
public:
	int a;
	int b;

protected:
	Vector2D location;           //�ʒu���
	Vector2D box_size;           //�傫��
	Vector2D direction;
	double radian;               //����
	double image_size;
	int score;
	int image;                   //�`�悷��摜
	int sound;                   //�Đ����鉹��
	bool delete_flag;            //�폜�t���O
	bool flip_flag;              //���]�t���O
	bool animation_flag;

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();   //����������
	virtual void Update();       //�X�V����
	virtual void Draw() const;   //�`�揈��
	virtual void Finalize();     //�I��������
    bool GetDeleteFlag();     //�I�u�W�F�N�g�폜����

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�����蔻��̑傫�����擾����
	Vector2D GetBoxSize() const;

	//�X�R�A���擾
	int GetScore();

	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//�i�s�����ύX����
	void SetDirection(const Vector2D& direction);

	//�摜���]�t���O�ݒ菈��
	void SetFlipFlag(bool flag);

};