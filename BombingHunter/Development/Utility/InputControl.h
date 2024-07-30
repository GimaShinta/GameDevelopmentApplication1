#pragma once

//�L�[�R�[�h�ő�l
#define D_KEYCODE_MAX (256)

class InputControl
{
private:
	//�L�[�{�[�h���͒l
	static char now_key[D_KEYCODE_MAX];
	static char old_key[D_KEYCODE_MAX];

public:
	//�X�V����
	static void Update();

	//�L�[���͏�Ԃ��擾����
	static bool GetKey(int key_code);         //�����Ă����
	static bool GetKeyDown(int key_code);     //�������u��
	static bool GetKeyUp(int key_code);       //�������u��

private:
	//�L�[���͈͂̔͂��m�F����
	static bool CheckKeyCodeRange(int key_code);
};