#include "EnemyBase.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

#define D_ENEMY_SPEED (50.0f)

EnemyBase::EnemyBase():
	velocity(0.0f),
	direction(0.0f),
	enemy_state(eEnemyState::TERRITORY),
	now_direction(eEnemyDirectionState::UP),
	old_direction(eEnemyDirectionState::UP),
	old_panel(ePanelID::NONE),
	animation_time(0.0f),
	izike_time(8.0f),
	track_time(0.0f),
	animation_count(0),
	izike_animcount(0),
	izike_reachcount(0),
	eye(NULL),
	in_tunnel(false),
	izike(false)
{
}

EnemyBase::~EnemyBase()
{
}

//����������
void EnemyBase::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	//�����摜�̐ݒ�
	eye = eye_animation[1];

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;

	//�G�l�~�[��Ԃ̐ݒ�
	enemy_state = eEnemyState::TRACK;

	//���x�ݒ�
	velocity = Vector2D(2.5f, 0.0f);
}

//�X�V����
void EnemyBase::Update(float delta_second)
{
	//enemy_state�̒��g�ŏ�����ς���
	switch (enemy_state)
	{
	case eEnemyState::IZIKE:
		MovementBase(delta_second);
		// �ړ����̃A�j���[�V����
		animation_time += delta_second;
		if (animation_time >= (1.0f / 16.0f))
		{
			animation_time = 0.0f;
			// �摜�̐ݒ�
			if (image != move_animation[17])
			{
				image = move_animation[17];
			}
			else if (image == move_animation[17])
			{
				image = move_animation[16];
			}
		}
		break;
	case eEnemyState::EYE:
		MovementBase(delta_second);
		AnimationBase(delta_second);
		break;
	}

	//�C�W�P��Ԃ��ڂ̏�Ԃł͖���������
	if (izike == true && enemy_state != eEnemyState::EYE)
	{
		enemy_state = eEnemyState::IZIKE;
		//�J�E���g�����炷
		izike_time -= delta_second;
	}

	if (izike_time <= 2)
	{
		if (animation_time >= (1.0f / 4.0f))
		{
			animation_time = 0.0f;
			// �摜�̐ݒ�
			if (image != move_animation[18])
			{
				image = move_animation[18];
			}
			else if (image == move_animation[18])
			{
				image = move_animation[19];
			}
		}
	}
	else if (izike_time <= 0)
	{
		izike_time = 8;
		izike = false;
	}
}

//�`�揈��
void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;

	//EYE��ԈȊO�̂Ƃ��{�̂�`��
	if (enemy_state != eEnemyState::EYE)
	{
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.5, 0.0, image, TRUE);
	}

	//�C�W�P�ȊO�̂Ƃ��ڂ�`��
	if (enemy_state != eEnemyState::IZIKE)
	{
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.5, 0.0, eye, TRUE);
	}
}

//�I��������
void EnemyBase::Finalize()
{
}

//�q�b�g������
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	// ���������A�I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// �ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Player����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// �߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diff�̕������߂�
		location += dv.Normalize() * diff;

		//�ǂɓ��������甽�]
		velocity *= -1;
	}

	//�C�W�P��Ԃ̂܂܃v���C���[�Ɠ���������
	if (hit_object->GetCollision().object_type == eObjectType::player&&enemy_state==eEnemyState::IZIKE)
	{
		enemy_state = eEnemyState::EYE;
	}
}

//�G�l�~�[�̏�Ԃ��擾
eEnemyState EnemyBase::GetEnemyState() const
{
	return enemy_state;
}

float EnemyBase::GetIzikeTime() const
{
	return izike_time;
}

//�i�s�����̐ݒ�
void EnemyBase::SetDirection(const Vector2D& direction)
{
	this->direction = direction;
}

//�C�W�P��Ԃɂ���
void EnemyBase::SetEnemyState()
{
	izike = true;
}

//���ʈړ�����
void EnemyBase::MovementBase(float delta_second)
{
	location += velocity * D_ENEMY_SPEED * delta_second;

	//�i�s�����ɂ���Đi�s������Ԃ�ύX����
	if (velocity.x > 0)
	{
		now_direction = eEnemyDirectionState::RIGHT;
	}
	else if (velocity.x < 0)
	{
		now_direction = eEnemyDirectionState::LEFT;
	}
	else if (velocity.y < 0)
	{
		now_direction = eEnemyDirectionState::UP;
	}
	else if (velocity.y > 0)
	{
		now_direction = eEnemyDirectionState::DOWN;
	}

}

//���ʃA�j���[�V��������
void EnemyBase::AnimationBase(float delta_second)
{
	//�i�s�����ɂ���Ėڂ̌������ς��
	switch (now_direction)
	{
	case eEnemyDirectionState::UP:
		eye = eye_animation[0];
		break;
	case eEnemyDirectionState::RIGHT:
		eye = eye_animation[1];
		break;
	case eEnemyDirectionState::DOWN:
		eye = eye_animation[2];
		break;
	case eEnemyDirectionState::LEFT:
		eye = eye_animation[3];
		break;
	default:
		break;
	}
}
