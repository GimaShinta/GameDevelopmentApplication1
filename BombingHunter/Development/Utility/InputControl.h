#pragma once

//キーコード最大値
#define D_KEYCODE_MAX (256)

class InputControl
{
private:
	//キーボード入力値
	static char now_key[D_KEYCODE_MAX];
	static char old_key[D_KEYCODE_MAX];

public:
	//更新処理
	static void Update();

	//キー入力状態を取得する
	static bool GetKey(int key_code);         //押している間
	static bool GetKeyDown(int key_code);     //押した瞬間
	static bool GetKeyUp(int key_code);       //離した瞬間

private:
	//キー入力の範囲を確認する
	static bool CheckKeyCodeRange(int key_code);
};