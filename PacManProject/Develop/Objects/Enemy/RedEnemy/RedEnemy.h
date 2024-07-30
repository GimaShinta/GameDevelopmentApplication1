#pragma once

#include "../EnemyBase.h"
#include "../../Utility/StageData.h"

class RedEnemy : public EnemyBase
{
private:

public:
	RedEnemy();
	~RedEnemy();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

private:
	void Movement(float delta_second);
	void AnimationControl(float delta_second);
};