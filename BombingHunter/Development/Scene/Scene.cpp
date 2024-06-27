#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/BoxEnemy/BoxEnemy.h"
#include "../Objects/Harpy/Harpy.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Objects/WingEnemy/WingEnemy.h"
#include "../Objects/GoldEnemy/GoldEnemy.h"
#include "../Objects/EnemyBullet/EnemyBullet.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include <math.h>

//�R���X�g���N�^
Scene::Scene() :objects(),b_flag(FALSE),object_flip(FALSE),object_score(0)
{
	ctime_count = 0;
	gametime = TIMELIMIT;
	f_color = GetColor(255, 255, 255);

	for (int i = 0; i < 10; i++)
	{
		number_animation[i] = NULL;
	}
	scene_image[0] = NULL;
	scene_image[1] = NULL;
	scene_image[2] = NULL;
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
	number_animation[0] = LoadGraph("Resource/Images/Score/0.png");
	number_animation[1] = LoadGraph("Resource/Images/Score/1.png");
	number_animation[2] = LoadGraph("Resource/Images/Score/2.png");
	number_animation[3] = LoadGraph("Resource/Images/Score/3.png");
	number_animation[4] = LoadGraph("Resource/Images/Score/4.png");
	number_animation[5] = LoadGraph("Resource/Images/Score/5.png");
	number_animation[6] = LoadGraph("Resource/Images/Score/6.png");
	number_animation[7] = LoadGraph("Resource/Images/Score/7.png");
	number_animation[8] = LoadGraph("Resource/Images/Score/8.png");
	number_animation[9] = LoadGraph("Resource/Images/Score/9.png");

	scene_image[0] = LoadGraph("Resource/Images/TimeLimit/timer-03.png");
	scene_image[1] = LoadGraph("Resource/Images/Score/font-21.png");
	scene_image[2] = LoadGraph("Resource/Images/Score/hs.png");

	//�G���[�`�F�b�N
	for (int i = 0; i < 5; i++)
	{
		if (number_animation[i] == -1)
		{
			throw("�����̉摜������܂���\n");
		}
	}

	if (number_animation[0] == -1|| number_animation[1] == -1 || number_animation[2] == -1 )
	{
		throw("�V�[��UI�̉摜������܂���\n");
	}


	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 50.0f));
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
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//��莞�ԂŐ�������
	if (ctime_count >= 250)
	{
		RandamCreate();
		ctime_count = 0;
	}
	else
	{
		ctime_count++;
	}

	//���e�𐶐�����
	BombCreate();

	//��ʊO�̃I�u�W�F�N�g���폜
	ScreenOut();

	//�q�b�g�I�u�W�F�N�g�̍폜
	HitDelete();

	gametime--;
}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�`��
	int bgimage = LoadGraph("Resource/Images/BackGround.png");
	DrawGraph(0, 0, bgimage, FALSE);

	//int time;
	//LONGLONG timelimit = GetNowHiPerformanceCount() + 120000000;
	//time = int(timelimit - GetNowHiPerformanceCount());
	//DrawFormatString(5, 5, f_color, "%02d'%02d'%d%d", time / 60000000);

	//�X�R�A�\��
	DrawFormatString(150, 450, f_color, "�X�R�A %d", object_score);
	DrawGraph(40, 450, number_animation[gametime / 150 / 10],FALSE);
	DrawGraph(60, 450, number_animation[gametime / 150 % 10],FALSE);
	DrawRotaGraphF(20, 460, 0.5, 0.0,number_animation[0], TRUE, TRUE);

	DrawRotaGraphF(20, 460, 0.5, 0.0, scene_image[0], TRUE, TRUE);
	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I������
void Scene::Finalize()
{
	//�g�p�����摜���������
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(number_animation[i]);
	}

	DeleteGraph(scene_image[0]);
	DeleteGraph(scene_image[1]);
	DeleteGraph(scene_image[2]);

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

//�����_���ɓG�𐶐�����
void Scene::RandamCreate()
{
	//�����ʒu�����_��(1�`10���o��)
	//x���W�̐����ʒu�����_���Ɖ摜�̔��]
	if(rand() % 10 + 1 <= 5)
	{
		create_location.x = 0.0f;
		object_flip = FALSE;
	}
	else
	{
		create_location.x = 640.0f;
		object_flip = TRUE;
	}
	//y���W�̐����ʒu�����_��
	if (rand() % 10 + 1 <= 5)
	{
		create_location.y = 200.0f;
	}
	else
	{
		create_location.y = 300.0f;
	}

	//�I�u�W�F�N�g�����_��(1�`100���o��)
	int obj_rd = rand() % 100 + 1;
	if (obj_rd <= 30)
	{ 
		BoxEnemy* a = CreateObject<BoxEnemy>(Vector2D(create_location.x,400.0f));
		//�摜���]�t���O�̐ݒ�
		a->SetFlipFlag(object_flip);
		for (int i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<Player*>(objects[i]) != nullptr)
			{
				Vector2D b = objects[i]->GetLocation() - a->GetLocation();
				float c = sqrt(pow(b.x, 2) + pow(b.y, 2));
				CreateObject<EnemyBullet>(a->GetLocation())->SetDirection(Vector2D(b.x/c,b.y/c));
			}
		}
	}
	else if (obj_rd <= 60)
	{
		Harpy* a = CreateObject<Harpy>(Vector2D(create_location.x, create_location.y));
		a->SetFlipFlag(object_flip);
	}
	else if (obj_rd <= 90)
	{
		WingEnemy* a = CreateObject<WingEnemy>(Vector2D(create_location.x, create_location.y));
		a->SetFlipFlag(object_flip);
	}
	else if (obj_rd <= 100)
	{
		GoldEnemy* a = CreateObject<GoldEnemy>(Vector2D(create_location.x, 400.0f));
		a->SetFlipFlag(object_flip);
	}

}

//��ʊO�̃I�u�W�F�N�g���폜
void Scene::ScreenOut()
{
	for (int i = 0; i < objects.size(); i++)
	{
		//���e
		if (dynamic_cast<Bomb*>(objects[i]) != nullptr)
		{
			//�I�u�W�F�N�g�̈ʒu�����擾
			obj_location = objects[i]->GetLocation();
			if (obj_location.y > 480)
			{
				//�I�u�W�F�N�g��z�񂩂�폜
				this->objects.erase(objects.begin() + i);
				//���e�����\
				b_flag = FALSE;
			}
		}
		//�n�R�e�L
		else if (dynamic_cast<BoxEnemy*>(objects[i]) != nullptr)
		{
			//�I�u�W�F�N�g�̈ʒu�����擾
			obj_location = objects[i]->GetLocation();
			if (obj_location.x > 640)
			{
				//�I�u�W�F�N�g��z�񂩂�폜
				this->objects.erase(objects.begin() + i);
			}
			if (obj_location.x < 0)
			{
				this->objects.erase(objects.begin() + i);
			}
		}
		//�n�[�s�[
		else if (dynamic_cast<Harpy*>(objects[i]) != nullptr)
		{
			//�I�u�W�F�N�g�̈ʒu�����擾
			obj_location = objects[i]->GetLocation();
			if (obj_location.x > 640)
			{
				//�I�u�W�F�N�g��z�񂩂�폜
				this->objects.erase(objects.begin() + i);
			}
			if (obj_location.x < 0)
			{
				this->objects.erase(objects.begin() + i);
			}
		}
		//�n�l�e�L
		else if (dynamic_cast<WingEnemy*>(objects[i]) != nullptr)
		{
			//�I�u�W�F�N�g�̈ʒu�����擾
			obj_location = objects[i]->GetLocation();
			if (obj_location.x > 640)
			{
				//�I�u�W�F�N�g��z�񂩂�폜
				this->objects.erase(objects.begin() + i);
			}
			if (obj_location.x < 0)
			{
				this->objects.erase(objects.begin() + i);
			}
		}
		//���e�L
		else if (dynamic_cast<GoldEnemy*>(objects[i]) != nullptr)
		{
			//�I�u�W�F�N�g�̈ʒu�����擾
			obj_location = objects[i]->GetLocation();
			if (obj_location.x > 640)
			{
				//�I�u�W�F�N�g��z�񂩂�폜
				this->objects.erase(objects.begin() + i);
			}
			if (obj_location.x < 0)
			{
				this->objects.erase(objects.begin() + i);
			}
		}
	}
}

//�q�b�g�I�u�W�F�N�g�̍폜
void Scene::HitDelete()
{
	for (int i = 0; i < objects.size(); i++)
	{
		//�I�u�W�F�N�g��DeleteFlag�֐���
		if (objects[i]->GetDeleteFlag() == TRUE)
		{
			//�X�R�A�𑫂��Ă���
			object_score += objects[i]->GetScore();
			//�I�u�W�F�N�g��z�񂩂�폜
			this->objects.erase(objects.begin() + i);
			//���e�����\
			b_flag = FALSE;

			if (object_score <= 0)
			{
				object_score = 0;
			}
		}
	}
}

void Scene::BombCreate()
{
	//���e�����݂��Ă��Ȃ���ΐ���
	if (b_flag == FALSE)
	{
		//�X�y�[�X�L�[����������A���e�𐶐�����
		if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (dynamic_cast<Player*>(objects[i]) != nullptr)
				{
					//���e��Player�̈ʒu���琶��   
					CreateObject<Bomb>(objects[i]->GetLocation());
					//���e�����s�\
					b_flag = TRUE;
				}
			}
		}
	}
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