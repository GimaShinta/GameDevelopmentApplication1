#pragma once

#include "../EnemyBase.h"
#include "../../Utility/StageData.h"

class PinkEnemy : public EnemyBase
{
private:
	const int move_num[2] = { 2, 3 };                     //移動アニメーションの順番
public:
	PinkEnemy();
	~PinkEnemy();

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