#pragma once

#include "../EnemyBase.h"
#include "../../Utility/StageData.h"

class RedEnemy : public EnemyBase
{
private:

public:
	RedEnemy();
	~RedEnemy();

	//初期化処理
	virtual void Initialize() override;
	//更新処理
	virtual void Update(float delta_second) override;
	//描画処理
	virtual void Draw(const Vector2D& screen_offset) const override;
	//終了時処理
	virtual void Finalize() override;

private:
	//移動処理
	void Movement(float delta_second);
	//アニメーション制御
	void AnimationControl(float delta_second);
};