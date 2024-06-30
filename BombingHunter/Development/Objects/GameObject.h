#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER    //���W�̌��_���摜�̒��S�ɂ���

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location;           //�ʒu���
	Vector2D box_size;           //�傫��
	Vector2D direction;          //�i�s����
	double radian;               //����
	double image_size;           //�摜�T�C�Y
	double number_size;
	int transparent;             //�����x�A�j���[�V�����ϐ�
	int gradually;               //�����x�A�j���[�V�������Z�p�ϐ�
	int anim_count;              //�A�j���[�V�����J�E���g
	int reach_count;             //�A�j���[�V�����J�E���g�̓��B�񐔃J�E���g
	int score;                   //�X�R�A
	int image;                   //�`�悷��摜
	int sound;                   //�Đ����鉹��
	bool delete_flag;            //�폜�t���O
	bool flip_flag;              //���]�t���O
	bool animation_flag;         //�A�j���[�V�����t���O
	bool anumber_flag;

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();   //����������
	virtual void Update();       //�X�V����
	virtual void Draw() const;   //�`�揈��
	virtual void Finalize();     //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�����蔻��̑傫�����擾����
	Vector2D GetBoxSize() const;

	//�X�R�A���擾
	int GetScore();

	//�I�u�W�F�N�g�폜����
    bool GetDeleteFlag();     

	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//�i�s�����ύX����
	void SetDirection(const Vector2D& direction);

	//�摜���]�t���O�ݒ菈��
	void SetFlipFlag(bool flag);

};