#pragma once
#include <wrl.h>
#include <windows.h>
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include <dinput.h>
#include "WinApp.h"
class Input
{
public:
	struct MouseMove {
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};
	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//初期化
	void Initialize(WinApp* winApp);
	//更新
	void Update();
	bool PushKey(BYTE keyNumber);
	bool TriggerKey(BYTE keyNumber);
	bool PushMouseLeft();
	bool PushMouseMiddle();
	bool TriggerMouseLeft();
	bool TriggerMouseMiddle();
	MouseMove GetMouseMove();
private://メンバ変数
	//キーボードのデパイス
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};
	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 mouseStatePre = {};
private:
	WinApp* winApp = nullptr;
};