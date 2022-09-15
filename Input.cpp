#include "Input.h"
#pragma comment(lib,"dinput8.lib") 
#pragma comment(lib,"dxguid.lib") 

void Input::Initialize(WinApp* winApp)
{
	this->winApp = winApp;
	HRESULT result;
	//////キーボードの初期化
	ComPtr<IDirectInput8>dinput = nullptr;
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	////
	//キーボードデバイスの作成
	////
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);

	//////にゅうりょくデータ形式のセット
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);

	//排他制御レベルのセット
	result = devkeyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update()
{
	HRESULT result;
	memcpy(keyPre, key, sizeof(key));
	result = devkeyboard->Acquire();
	//BYTE key[256] = {};
	result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
	//指定キーを押していればtrueを返す
	if (key[keyNumber]) {
		return true;
	}
	//そうでなければfalseを返す
	return false;
}

bool Input::TriggerKey(BYTE keyNumber) {

	// 前回が0で、今回が0でなければトリガー
	if (!keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}

	// トリガーでない
	return false;
}

//マウス関係
bool Input::PushMouseLeft()
{
	//0でなければ押している
	if (mouseState.rgbButtons[0]) {
		return true;
	}

	return false;
}

bool Input::PushMouseMiddle()
{
	//0でなければ押している
	if (mouseState.rgbButtons[2]) {
		return true;
	}

	return false;
}

bool Input::TriggerMouseLeft()
{	// 前回が0で、今回が0でなければトリガー
	if (!mouseStatePre.rgbButtons[0] && mouseState.rgbButtons[0]) {
		return true;
	}

	return false;
}

bool Input::TriggerMouseMiddle()
{	// 前回が0で、今回が0でなければトリガー
	if (!mouseStatePre.rgbButtons[2] && mouseState.rgbButtons[2]) {
		return true;
	}

	return false;
}

Input::MouseMove Input::GetMouseMove()
{
	MouseMove tmp;
	tmp.lX = mouseState.lX;
	tmp.lY = mouseState.lY;
	tmp.lZ = mouseState.lZ;

	return tmp;
}