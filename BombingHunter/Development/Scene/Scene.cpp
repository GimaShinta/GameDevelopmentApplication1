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

//コンストラクタ
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

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
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

	//エラーチェック
	for (int i = 0; i < 5; i++)
	{
		if (number_animation[i] == -1)
		{
			throw("数字の画像がありません\n");
		}
	}

	if (number_animation[0] == -1|| number_animation[1] == -1 || number_animation[2] == -1 )
	{
		throw("シーンUIの画像がありません\n");
	}


	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 50.0f));
}

//更新処理
void Scene::Update()
{
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//一定時間で生成する
	if (ctime_count >= 250)
	{
		RandamCreate();
		ctime_count = 0;
	}
	else
	{
		ctime_count++;
	}

	//爆弾を生成する
	BombCreate();

	//画面外のオブジェクトを削除
	ScreenOut();

	//ヒットオブジェクトの削除
	HitDelete();

	gametime--;
}

//描画処理
void Scene::Draw() const
{
	//背景描画
	int bgimage = LoadGraph("Resource/Images/BackGround.png");
	DrawGraph(0, 0, bgimage, FALSE);

	//int time;
	//LONGLONG timelimit = GetNowHiPerformanceCount() + 120000000;
	//time = int(timelimit - GetNowHiPerformanceCount());
	//DrawFormatString(5, 5, f_color, "%02d'%02d'%d%d", time / 60000000);

	//スコア表示
	DrawFormatString(150, 450, f_color, "スコア %d", object_score);
	DrawGraph(40, 450, number_animation[gametime / 150 / 10],FALSE);
	DrawGraph(60, 450, number_animation[gametime / 150 % 10],FALSE);
	DrawRotaGraphF(20, 460, 0.5, 0.0,number_animation[0], TRUE, TRUE);

	DrawRotaGraphF(20, 460, 0.5, 0.0, scene_image[0], TRUE, TRUE);
	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了処理
void Scene::Finalize()
{
	//使用した画像を解放する
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(number_animation[i]);
	}

	DeleteGraph(scene_image[0]);
	DeleteGraph(scene_image[1]);
	DeleteGraph(scene_image[2]);

	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();
}

//ランダムに敵を生成する
void Scene::RandamCreate()
{
	//生成位置ランダム(1～10を出す)
	//x座標の生成位置ランダムと画像の反転
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
	//y座標の生成位置ランダム
	if (rand() % 10 + 1 <= 5)
	{
		create_location.y = 200.0f;
	}
	else
	{
		create_location.y = 300.0f;
	}

	//オブジェクトランダム(1～100を出す)
	int obj_rd = rand() % 100 + 1;
	if (obj_rd <= 30)
	{ 
		BoxEnemy* a = CreateObject<BoxEnemy>(Vector2D(create_location.x,400.0f));
		//画像反転フラグの設定
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

//画面外のオブジェクトを削除
void Scene::ScreenOut()
{
	for (int i = 0; i < objects.size(); i++)
	{
		//爆弾
		if (dynamic_cast<Bomb*>(objects[i]) != nullptr)
		{
			//オブジェクトの位置情報を取得
			obj_location = objects[i]->GetLocation();
			if (obj_location.y > 480)
			{
				//オブジェクトを配列から削除
				this->objects.erase(objects.begin() + i);
				//爆弾生成可能
				b_flag = FALSE;
			}
		}
		//ハコテキ
		else if (dynamic_cast<BoxEnemy*>(objects[i]) != nullptr)
		{
			//オブジェクトの位置情報を取得
			obj_location = objects[i]->GetLocation();
			if (obj_location.x > 640)
			{
				//オブジェクトを配列から削除
				this->objects.erase(objects.begin() + i);
			}
			if (obj_location.x < 0)
			{
				this->objects.erase(objects.begin() + i);
			}
		}
		//ハーピー
		else if (dynamic_cast<Harpy*>(objects[i]) != nullptr)
		{
			//オブジェクトの位置情報を取得
			obj_location = objects[i]->GetLocation();
			if (obj_location.x > 640)
			{
				//オブジェクトを配列から削除
				this->objects.erase(objects.begin() + i);
			}
			if (obj_location.x < 0)
			{
				this->objects.erase(objects.begin() + i);
			}
		}
		//ハネテキ
		else if (dynamic_cast<WingEnemy*>(objects[i]) != nullptr)
		{
			//オブジェクトの位置情報を取得
			obj_location = objects[i]->GetLocation();
			if (obj_location.x > 640)
			{
				//オブジェクトを配列から削除
				this->objects.erase(objects.begin() + i);
			}
			if (obj_location.x < 0)
			{
				this->objects.erase(objects.begin() + i);
			}
		}
		//金テキ
		else if (dynamic_cast<GoldEnemy*>(objects[i]) != nullptr)
		{
			//オブジェクトの位置情報を取得
			obj_location = objects[i]->GetLocation();
			if (obj_location.x > 640)
			{
				//オブジェクトを配列から削除
				this->objects.erase(objects.begin() + i);
			}
			if (obj_location.x < 0)
			{
				this->objects.erase(objects.begin() + i);
			}
		}
	}
}

//ヒットオブジェクトの削除
void Scene::HitDelete()
{
	for (int i = 0; i < objects.size(); i++)
	{
		//オブジェクトのDeleteFlag関数へ
		if (objects[i]->GetDeleteFlag() == TRUE)
		{
			//スコアを足していく
			object_score += objects[i]->GetScore();
			//オブジェクトを配列から削除
			this->objects.erase(objects.begin() + i);
			//爆弾生成可能
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
	//爆弾が存在していなければ生成
	if (b_flag == FALSE)
	{
		//スペースキーを押したら、爆弾を生成する
		if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (dynamic_cast<Player*>(objects[i]) != nullptr)
				{
					//爆弾をPlayerの位置から生成   
					CreateObject<Bomb>(objects[i]->GetLocation());
					//爆弾生成不可能
					b_flag = TRUE;
				}
			}
		}
	}
}

#ifdef D_PIVOT_CENTER

//当たり判定チェック処理（矩形の中心で当たり判定を取る）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//２つのオブジェクトの処理を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//２つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = ((a->GetBoxSize() + b->GetBoxSize()) / 2.0f);

	//距離より大きさが大きい場合、Hit判定をする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#else

//当たり判定チェック処理（左上頂点の座標から当たり判定計算を行う）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//右下頂点座標を取得する
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//矩形Aと矩形Bの位置関係を調べる
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//オブジェクトに対してHit判定を通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif //D_PIBOT＿CNETER