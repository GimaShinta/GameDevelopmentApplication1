#include "EnemyBase.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

#define D_ENEMY_SPEED (50.0f / enemy_speed)
#define D_IZIKE_TIME (12.0f)

EnemyBase::EnemyBase():
	direction(0.0f),
	enemy_state(eEnemyState::TERRITORY),
	now_direction(eEnemyDirectionState::UP),
	old_direction(eEnemyDirectionState::UP),
	old_panel(ePanelID::NONE),
	animation_time(0.0f),
	izike_time(0.0f),
	track_time(0.0f),
	enemy_speed(0.0f),
	animation_count(0),
	eye(NULL),
	in_tunnel(false),
	izike(false),
	player_powerd(false),
	end_anim(false)
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

	//�i�s�����ݒ�
	direction = Vector2D(2.5f, 0.0f);

	//���x�ݒ�
	enemy_speed = 1;

	//�C�W�P���Ԃ�ݒ�
	izike_time = D_IZIKE_TIME;
}

//�X�V����
void EnemyBase::Update(float delta_second)
{
	//enemy_state�̒��g�ŏ�����ς���
	switch (enemy_state)
	{
	case eEnemyState::IZIKE:
		enemy_speed = 2;
		MovementBase(delta_second);
		// �ړ����̃A�j���[�V����
		animation_time += delta_second;
		if (animation_time >= (1.0f / 16.0f))
		{
			animation_time = 0.0f;
			animation_count++;

			//�A�j���[�V�����t���O
			if (end_anim == false)
			{
				if (animation_count >= 2)
				{
					animation_count = 0;
				}
				// �摜�̐ݒ�
				image = move_animation[izike_order[animation_count]];
			}
			else
			{
				if (animation_count >= 4)
				{
					animation_count = 0;
				}
				// �摜�̐ݒ�
				image = move_animation[izikeend_order[animation_count]];
			}
		}
		break;
	case eEnemyState::EYE:
		enemy_speed = 0.5;
		MovementBase(delta_second);
		AnimationBase(delta_second);
		break;
	}

	//�C�W�P��Ԃ�������
	if (izike == true)
	{
		//�C�W�P�ɂ���
		enemy_state = eEnemyState::IZIKE;
		//�C�W�P���Ԃ����炷
		izike_time -= delta_second;

		//�C�W�P���Ԃ��R�b�ȉ��ɂȂ�����
		if (izike_time <= 3)
		{
			//�A�j���[�V������ω�������
			end_anim = true;
		}
		//�C�W�P���Ԃ��O�b�ȉ��ɂȂ�����
		if (izike_time <= 0)
		{
			//�ǐՏ�Ԃɖ߂�
			enemy_state = eEnemyState::TRACK;
			//�C�W�P��Ԃ�����
			izike = false;
			//�v���C���[�p���[�_�E���t���O
			player_powerd = true;
		}
	}
	//�C�W�P��Ԃ���Ȃ�������
	else
	{
		//�l�̍ď�����
		end_anim = false;
		player_powerd = false;
		izike_time = D_IZIKE_TIME;
	}

	// ���͏�Ԃ̎擾
	InputManager* input = InputManager::GetInstance();

	if (input->GetKeyDown(KEY_INPUT_B) && enemy_state == eEnemyState::EYE)
	{
		enemy_state = eEnemyState::TRACK;
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
	eye_animation.clear();
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
		direction *= -1;
	}

	//�C�W�P��Ԃ̂܂܃v���C���[�Ɠ���������
	if (hit_object->GetCollision().object_type == eObjectType::player && enemy_state==eEnemyState::IZIKE)
	{
		//�C�W�P��Ԃ�����
		izike = false;
		//�ڂ̏�Ԃɂ���
		enemy_state = eEnemyState::EYE;
	}
}

//�G�l�~�[�̏�Ԃ��擾
eEnemyState EnemyBase::GetEnemyState() const
{
	return enemy_state;
}

//�v���C���[�p���[�_�E���t���O���擾
bool EnemyBase::GetPlayerDown() const
{
	return player_powerd;
}

//�i�s�����̐ݒ�
void EnemyBase::SetDirection(const Vector2D& direction)
{
	this->direction = direction;
}

//�C�W�P��ԃt���O���I��
void EnemyBase::SetIzikeState()
{
	izike = true;
}

//���ʈړ�����
void EnemyBase::MovementBase(float delta_second)
{
	location += direction * D_ENEMY_SPEED * delta_second;

	//�i�s�����ɂ���Đi�s������Ԃ�ύX����
	if (direction.x > 0)
	{
		now_direction = eEnemyDirectionState::RIGHT;
	}
	else if (direction.x < 0)
	{
		now_direction = eEnemyDirectionState::LEFT;
	}
	else if (direction.y < 0)
	{
		now_direction = eEnemyDirectionState::UP;
	}
	else if (direction.y > 0)
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
