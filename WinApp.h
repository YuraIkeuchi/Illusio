#pragma once
#include <windows.h>
#include "imgui.h"
//ウィンドウズアプリケーション
class WinApp
{
	//定数
public:
	static const int window_width = 1280;
	static const int window_height = 720;
	// 汎用機能
	//WinApp* win = nullptr;
	//ポインタ置き場

public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:
	//初期化
	void Initialize();
	//更新
	void Update();

	//終了
	void Finalize();

	//メッセージの処理
	bool ProcessMessage();
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetHInstance() { return w.hInstance; }
private:
	HWND hwnd = nullptr;
	WNDCLASSEX w{};
};