#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/BoxEnemy/BoxEnemy.h"
#include "../Objects/Harpy/Harpy.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"


//�R���X�g���N�^
Scene::Scene() :objects()
{

}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 100.0f));
}

//�X�V����
void Scene::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 1; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//Z�L�[����������A�G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<BoxEnemy>(Vector2D(100.0f, 400.0f));
	}

	//�X�y�[�X�L�[����������A���e�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<Player*>(objects[i]) != nullptr)
			{
				CreateObject<Bomb>(objects[i]->GetLocation());
			}
		}
	}

	//��ʊO�̔��e���폜
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<Bomb*>(objects[i]) != nullptr)
		{
 			Vector2D bl;
			bl = objects[i]->GetLocation();
			if (bl.y > 480)
			{ 
				this->objects.erase(objects.begin()+i);
			}
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->DeleteObjectFanc() == TRUE)
		{
			this->objects.erase(objects.begin()+i);
		}
	}
}

//�`�揈��
void Scene::Draw() const
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I������
void Scene::Finalize()
{
	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̉��
	objects.clear();
}

#ifdef D_PIVOT_CENTER

//�����蔻��`�F�b�N�����i��`�̒��S�œ����蔻������j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�Q�̃I�u�W�F�N�g�̏������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//�Q�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = ((a->GetBoxSize() + b->GetBoxSize()) / 2.0f);

	//�������傫�����傫���ꍇ�AHit���������
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);

	}
}

#else

//�����蔻��`�F�b�N�����i���㒸�_�̍��W���瓖���蔻��v�Z���s���j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�E�����_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//��`A�Ƌ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//�I�u�W�F�N�g�ɑ΂���Hit�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif //D_PIBOT�QCNETER