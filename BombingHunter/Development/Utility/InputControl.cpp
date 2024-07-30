#include "InputControl.h"
#include "DxLib.h"

char InputControl::now_key[D_KEYCODE_MAX] = {};
char InputControl::old_key[D_KEYCODE_MAX] = {};

//�X�V����
void InputControl::Update()
{
	//�O��̃L�[���͒l���X�V
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));

	//���݂̃L�[���͒l���擾
	GetHitKeyStateAll(now_key);
}

//�����Ă����
bool InputControl::GetKey(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) && (old_key[key_code] == TRUE));
}

//�������u��
bool InputControl::GetKeyDown(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) && (old_key[key_code] == FALSE));
}

//�������u��
bool InputControl::GetKeyUp(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == FALSE) && (old_key[key_code] == TRUE));
}
//�L�[���͈͂̔͂��m�F����
bool InputControl::CheckKeyCodeRange(int key_code)
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}