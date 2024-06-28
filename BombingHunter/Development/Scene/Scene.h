#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"

#define TIMELIMIT 3000*3

class Scene
{
private:

	std::vector<GameObject*>objects;

	int f_color;                 //フォントカラー（黒）
	int object_score;            //スコア結果
	int gametime;                // 時間制限
	int ctime_count;             //一定時間
	int image_count;             //フレームレートカウント
	int image;                   //描画する画像
	int scene_image[8];          //UI画像
	int number_animation[10];    //数字画像
	bool b_flag;                 //爆弾生成フラグ
	bool object_flip;            //画像反転フラグ
	Vector2D obj_location;       //オブジェクト比較用位置情報
	Vector2D create_location;    //オブジェクト生成位置

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();
	void RandamCreate();          //ランダムに敵を生成する
	void DeleteObject();          //オブジェクトを削除する
	void BombCreate();            //爆弾を生成する
	void ResultScene();           //リザルト結果を表示する

private:
	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);

	//オブジェクト生成処理
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定したクラスを生成する
		T* new_instance = new T();
		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("ゲームオブジェクトが生成できませんでした");
		}

		//初期化処理
		new_object->Initialize();

		//位置情報の設定
		new_object->SetLocation(location);

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}

};