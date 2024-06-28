#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER    //座標の原点を画像の中心にする

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D location;           //位置情報
	Vector2D box_size;           //大きさ
	Vector2D direction;          //進行方向
	double radian;               //向き
	double image_size;           //画像サイズ
	int anim_a;                  //透明度アニメーション変数
	int anim_b;                  //透明度アニメーション加算用変数
	int a_count;                 //アニメーションカウント
	int b_count;                 //アニメーションカウントの到達回数カウント
	int score;                   //スコア
	int image;                   //描画する画像
	int sound;                   //再生する音源
	bool delete_flag;            //削除フラグ
	bool flip_flag;              //反転フラグ
	bool animation_flag;         //アニメーションフラグ
	bool out_flag;

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();   //初期化処理
	virtual void Update();       //更新処理
	virtual void Draw() const;   //描画処理
	virtual void Finalize();     //終了時処理
    bool GetDeleteFlag();     //オブジェクト削除処理
	bool GetOutDeleteFlag();

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

	//位置情報取得処理
	Vector2D GetLocation() const;

	//当たり判定の大きさを取得する
	Vector2D GetBoxSize() const;

	//スコアを取得
	int GetScore();

	//位置情報変更処理
	void SetLocation(const Vector2D& location);

	//進行方向変更処理
	void SetDirection(const Vector2D& direction);

	//画像反転フラグ設定処理
	void SetFlipFlag(bool flag);

};