#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"

#define TIMELIMIT 3000*3

class Scene
{
private:

	std::vector<GameObject*>objects;

	int f_color;                 //�t�H���g�J���[�i���j
	int object_score;            //�X�R�A����
	int gametime;                // ���Ԑ���
	int ctime_count;             //��莞��
	int image_count;             //�t���[�����[�g�J�E���g
	int image;                   //�`�悷��摜
	int scene_image[8];          //UI�摜
	int number_animation[10];    //�����摜
	bool b_flag;                 //���e�����t���O
	bool object_flip;            //�摜���]�t���O
	Vector2D obj_location;       //�I�u�W�F�N�g��r�p�ʒu���
	Vector2D create_location;    //�I�u�W�F�N�g�����ʒu

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();
	void RandamCreate();          //�����_���ɓG�𐶐�����
	void DeleteObject();          //�I�u�W�F�N�g���폜����
	void BombCreate();            //���e�𐶐�����
	void ResultScene();           //���U���g���ʂ�\������

private:
	//�����蔻��`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b);

	//�I�u�W�F�N�g��������
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();
		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
		}

		//����������
		new_object->Initialize();

		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}

};