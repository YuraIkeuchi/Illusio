#include<Windows.h>
#include<d3d12.h>
#include<d3dx12.h>
#include<dxgi1_6.h>
#include<vector>
#include<string>
#include<DirectXMath.h>
#include<d3dcompiler.h>
#define DIRECTiNPUT_VERSION 
#include<DirectXTex.h>
#include<wrl.h>
#include <stdio.h>
#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Sprite.h"
#include "Audio.h"
#include "Block.h"
#include "PlayerLeftWalk.h"
#include "PlayerLeftWalk2.h"
#include "PlayerLeftWalk3.h"
#include "PlayerLeftWalk4.h"
#include "PlayerRightWalk.h"
#include "PlayerRightWalk2.h"
#include "PlayerRightWalk3.h"
#include "PlayerRightWalk4.h"
#include "PlayerJump.h"
#include "PlayerJumpLeft.h"
#include "backGround.h"
#include "Light.h"
#include "Screen.h"
#include "Projector.h"
#include "Collision.h"
#include "LightSource.h"
#include "Item.h"
#include "Goal.h"
#include "Lever.h"
#include "Gear.h"
#include "under.h"
#include "Area.h"
#include "vinet.h"
#include "DirectXTex/d3dx12.h"
#include "RealBlock.h"

#include "imgui\imgui.h"
#include <cassert>

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"d3d12.lib")

#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
using namespace DirectX;
using namespace Microsoft::WRL;
#pragma region//WinMain
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ポインタ置き場
	Input* input = nullptr;
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	winApp = new WinApp();
	winApp->Initialize();
	//DirectXの初期化
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	MSG msg{};
	//でバッグレイヤーのやつ
#ifdef _DEBUG
#endif
	//directx初期化
#pragma region//構造体
	const int Block_NUM = 10;
	const int Block_Area_NUM = 40;
#pragma endregion
#pragma region//行列
	//射影変換行列の作り
	XMMATRIX matprojection = XMMatrixPerspectiveFovLH(XMConvertToRadians(60.0f), (float)WinApp::window_width / WinApp::window_height, 0.1f, 1000.0f);

	//ビュー変換行列
	XMMATRIX matview;
	XMFLOAT3 eye(0, 0, -100);
	XMFLOAT3 target(0, 0, 0);
	XMFLOAT3 up(0, 1, 0);
	matview = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	//ワールド変換行列
	XMMATRIX matworld0;
	matworld0 = XMMatrixIdentity();
	XMFLOAT3 position;
	position = { 0.0f,0.0f,0.0f };
	//2
	XMMATRIX matRot1;
	XMMATRIX matTrans1;
	XMMATRIX matworld1;
	matRot1 = XMMatrixRotationY(XMConvertToRadians(90.0f));
	matTrans1 = XMMatrixTranslation(-20.0f, 0, 0);
	matworld1 = matRot1 * matTrans1;
	//カメラの回転角
	float angle = 0.0f;
#pragma endregion
#pragma region//スプライト共通データ
	if (!Sprite::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 0;
	}

	const int SpriteMax = 30;
	const int SpriteNumberMax = 10;
	Sprite* sprite[SpriteMax] = { nullptr };
	// スプライト共通テクスチャ読み込み
	/*SpriteCommonLoadTexture(spriteCommon, 0, L"Resources/texture.png", dxCommon->GetDev());
	SpriteCommonLoadTexture(spriteCommon, 1, L"Resources/house.png", dxCommon->GetDev());*/
	Sprite::LoadTexture(0, L"Resources/180_20220130123604.png");
	Sprite::LoadTexture(1, L"Resources/END.png");
	Sprite::LoadTexture(2, L"Resources/UI/ItemUI.png");
	Sprite::LoadTexture(3, L"Resources/Number/0.png");
	Sprite::LoadTexture(4, L"Resources/Number/1.png");
	Sprite::LoadTexture(5, L"Resources/Number/2.png");
	Sprite::LoadTexture(6, L"Resources/Number/3.png");
	Sprite::LoadTexture(7, L"Resources/Number/4.png");
	Sprite::LoadTexture(8, L"Resources/Number/5.png");
	Sprite::LoadTexture(9, L"Resources/Number/6.png");
	Sprite::LoadTexture(10, L"Resources/Number/7.png");
	Sprite::LoadTexture(11, L"Resources/Number/8.png");
	Sprite::LoadTexture(12, L"Resources/Number/9.png");
	Sprite::LoadTexture(13, L"Resources/STAGECLEAR.png");
	Sprite::LoadTexture(14, L"Resources/GAMECLEAR.png");
	Sprite::LoadTexture(15, L"Resources/GAMEOVER.png");
	Sprite::LoadTexture(16, L"Resources/EXPLATION.png");
	Sprite::LoadTexture(17, L"Resources/EXPLATION2.png");
	Sprite::LoadTexture(18, L"Resources/UI/TextUI.png");
	Sprite::LoadTexture(19, L"Resources/UI/Text1.png");
	Sprite::LoadTexture(20, L"Resources/UI/Text2.png");
	Sprite::LoadTexture(21, L"Resources/UI/Text3.png");
	Sprite::LoadTexture(22, L"Resources/UI/Text4.png");
	Sprite::LoadTexture(23, L"Resources/Film.png");
	Sprite::LoadTexture(24, L"Resources/SceneCut/NewSceneCut4.png");
	Sprite::LoadTexture(25, L"Resources/SceneCut/NewSceneCut3.png");
	Sprite::LoadTexture(26, L"Resources/SceneCut/NewSceneCut2.png");
	Sprite::LoadTexture(27, L"Resources/SceneCut/NewSceneCut1.png");
	Sprite::LoadTexture(28, L"Resources/UI/Text5.png");
	Sprite::LoadTexture(29, L"Resources/UI/Text6.png");
	Sprite::LoadTexture(30, L"Resources/SceneCut/SceneCutNumber1.png");
	Sprite::LoadTexture(31, L"Resources/SceneCut/SceneCutNumber2.png");
	Sprite::LoadTexture(32, L"Resources/SceneCut/SceneCutNumber3.png");
	Sprite::LoadTexture(33, L"Resources/SceneCut/SceneCutNumber4.png");
	Sprite::LoadTexture(34, L"Resources/SceneCut/SceneCutNumber5.png");
	Sprite::LoadTexture(35, L"Resources/SceneCut/SceneCutNumber6.png");
	Sprite::LoadTexture(36, L"Resources/SceneCut/SceneCutNumber7.png");
	Sprite::LoadTexture(37, L"Resources/SceneCut/SceneCutNumber8.png");
	Sprite::LoadTexture(38, L"Resources/SceneCut/SceneCutNumber9.png");
	Sprite::LoadTexture(39, L"Resources/SceneCut/SceneCutNumber10.png");
	Sprite::LoadTexture(40, L"Resources/SceneCut/SceneCutNumber11.png");
	Sprite::LoadTexture(41, L"Resources/SceneCut/SceneCutNumber12.png");
	Sprite::LoadTexture(42, L"Resources/UI/PlayerHPUI1.png");
	Sprite::LoadTexture(43, L"Resources/UI/PlayerHPUI2.png");
	Sprite::LoadTexture(44, L"Resources/UI/PlayerHPUI3.png");
	Sprite::LoadTexture(45, L"Resources/UI/PlayerHPUI4.png");
	Sprite::LoadTexture(46, L"Resources/UI/PlayerHPUI5.png");
	Sprite::LoadTexture(47, L"Resources/UI/ResetUI.png");
	Sprite::LoadTexture(48, L"Resources/SceneCut/LastSceneCutNumber.png");
	sprite[0] = Sprite::Create(0, { 0.0f,0.0f });
	sprite[1] = Sprite::Create(1, { 0.0f,0.0f });
	sprite[2] = Sprite::Create(2, { 0.0f,0.0f });
	sprite[3] = Sprite::Create(13, { 0.0f,0.0f });
	sprite[4] = Sprite::Create(14, { 0.0f,0.0f });
	sprite[5] = Sprite::Create(15, { 0.0f,0.0f });
	sprite[6] = Sprite::Create(16, { 0.0f,0.0f });
	sprite[7] = Sprite::Create(17, { 0.0f,0.0f });
	sprite[8] = Sprite::Create(18, { 0.0f,0.0f });
	sprite[9] = Sprite::Create(19, { 0.0f,0.0f });
	sprite[10] = Sprite::Create(20, { 0.0f,0.0f });
	sprite[11] = Sprite::Create(21, { 0.0f,0.0f });
	sprite[12] = Sprite::Create(22, { 0.0f,0.0f });
	sprite[13] = Sprite::Create(23, { 0.0f,0.0f });
	sprite[14] = Sprite::Create(23, { 0.0f,0.0f });
	sprite[15] = Sprite::Create(28, { 0.0f,0.0f });
	sprite[16] = Sprite::Create(29, { 0.0f,0.0f });
	sprite[17] = Sprite::Create(42, { 0.0f,0.0f });
	sprite[18] = Sprite::Create(43, { 0.0f,0.0f });
	sprite[19] = Sprite::Create(44, { 0.0f,0.0f });
	sprite[20] = Sprite::Create(45, { 0.0f,0.0f });
	sprite[21] = Sprite::Create(46, { 0.0f,0.0f });
	sprite[22] = Sprite::Create(47, { 0.0f,0.0f });
	Sprite* spriteNumber[SpriteNumberMax] = { nullptr };
	spriteNumber[0] = Sprite::Create(3, { 0.0f,0.0f });
	spriteNumber[1] = Sprite::Create(4, { 0.0f,0.0f });
	spriteNumber[2] = Sprite::Create(5, { 0.0f,0.0f });
	spriteNumber[3] = Sprite::Create(6, { 0.0f,0.0f });
	spriteNumber[4] = Sprite::Create(7, { 0.0f,0.0f });
	spriteNumber[5] = Sprite::Create(8, { 0.0f,0.0f });
	spriteNumber[6] = Sprite::Create(9, { 0.0f,0.0f });
	spriteNumber[7] = Sprite::Create(10, { 0.0f,0.0f });
	spriteNumber[8] = Sprite::Create(11, { 0.0f,0.0f });
	spriteNumber[9] = Sprite::Create(12, { 0.0f,0.0f });
	const int SceneCutMax = 4;
	Sprite* SpriteSceneCut[SceneCutMax] = { nullptr };
	SpriteSceneCut[0] = Sprite::Create(24, { 0.0f,0.0f });
	SpriteSceneCut[1] = Sprite::Create(25, { 0.0f,0.0f });
	SpriteSceneCut[2] = Sprite::Create(26, { 0.0f,0.0f });
	SpriteSceneCut[3] = Sprite::Create(27, { 0.0f,0.0f });
	const int SceneCutNumberMax = 13;
	Sprite* SpriteSceneCutNumber[SceneCutNumberMax] = { nullptr };
	SpriteSceneCutNumber[0] = Sprite::Create(30, { 0.0f,0.0f });
	SpriteSceneCutNumber[1] = Sprite::Create(31, { 0.0f,0.0f });
	SpriteSceneCutNumber[2] = Sprite::Create(32, { 0.0f,0.0f });
	SpriteSceneCutNumber[3] = Sprite::Create(33, { 0.0f,0.0f });
	SpriteSceneCutNumber[4] = Sprite::Create(34, { 0.0f,0.0f });
	SpriteSceneCutNumber[5] = Sprite::Create(35, { 0.0f,0.0f });
	SpriteSceneCutNumber[6] = Sprite::Create(36, { 0.0f,0.0f });
	SpriteSceneCutNumber[7] = Sprite::Create(37, { 0.0f,0.0f });
	SpriteSceneCutNumber[8] = Sprite::Create(38, { 0.0f,0.0f });
	SpriteSceneCutNumber[9] = Sprite::Create(39, { 0.0f,0.0f });
	SpriteSceneCutNumber[10] = Sprite::Create(40, { 0.0f,0.0f });
	SpriteSceneCutNumber[11] = Sprite::Create(41, { 0.0f,0.0f });
	SpriteSceneCutNumber[12] = Sprite::Create(48, { 0.0f,0.0f });
	sprite[2]->SetPosition({ 200.0f,0.0f });
	for (int i = 0; i < SpriteNumberMax; i++) {
		//spriteNumber[i]->SetColor({ 0.0f,0.0f,0.0f,1.0f });
		spriteNumber[i]->SetSize({ 120.0f,120.0f });
		spriteNumber[i]->SetPosition({ 290,0 });
	}

	sprite[8]->SetPosition({ 0.0f,605.0f });
	//sprite[8]->SetSize({ 1000.0f,200.0f });
	for (int i = 9; i < 13; i++) {
		sprite[i]->SetPosition({ 0.0f,605.0f });
	}

	sprite[22]->SetPosition({ 0.0f,605.0f });
	sprite[15]->SetPosition({ 0.0f,605.0f });
	sprite[16]->SetPosition({ 0.0f,605.0f });
	XMFLOAT2 FilmPos[2];
	FilmPos[0] = { 0,-720 };
	FilmPos[1] = { 0,0 };
	sprite[13]->SetPosition(FilmPos[0]);
	sprite[14]->SetPosition(FilmPos[1]);
	int ExplanationNumber = 0;
	int TextNumber = 0;
	XMFLOAT2 SceneCutPos = { 1280,0 };
	for (int i = 0; i < SceneCutMax; i++) {
		SpriteSceneCut[i]->SetPosition(SceneCutPos);
	}

	for (int i = 0; i < SceneCutNumberMax; i++) {
		SpriteSceneCutNumber[i]->SetPosition(SceneCutPos);
	}

	for (int i = 17; i < 22; i++) {
		sprite[i]->SetPosition({120.0f,30.0f });
	}
	int SceneCutFlag = 1;
#pragma endregion
#pragma region//オーディオ
	const int AudioMax = 3;
	Audio* audio = new Audio;
	float GameVolume = 0.0f;
	float ProjectorVolume = 0.3f;
	if (!audio->Initialize()) {
		assert(0);
		return 1;
	}
	audio->LoadSound(0, "Resources/Sound/BGM/loop3.wav");
	audio->LoadSound(1, "Resources/Sound/BGM/nc63527.wav");
	audio->LoadSound(2, "Resources/Sound/BGM/fc.wav");
	audio->LoopWave(0, 0.3);
#pragma endregion
#pragma region//キー処理
	//入力の初期化
	input = new Input();
	input->Initialize(winApp);
#pragma endregion
#pragma region//障害物変数
	//影を作るためのブロック
	RealBlock* ImageBlock[Block_NUM];
	for (int i = 0; i < _countof(ImageBlock); i++) {
		if (!ImageBlock[i]->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
			assert(0);
			return 1;
		}
		ImageBlock[i] = RealBlock::Create();
		ImageBlock[i]->Update(matview);
	}

	XMFLOAT3 ImageBlockPosition[Block_NUM];
	XMFLOAT4 ImageBlockColor[Block_NUM];
	for (int i = 0; i < _countof(ImageBlock); i++) {
		ImageBlockPosition[i] = ImageBlock[i]->GetPosition();
		ImageBlockPosition[i] = { 0.0f,0.0f,70.0f };
		ImageBlock[i]->SetPosition(ImageBlockPosition[i]);
	}

	//セットしたかどうかのフラグ
	int SetFlag[Block_NUM] = { 0 };
	//ゲーム画面のブロック
	Block* SetBlock[Block_NUM];
	for (int i = 0; i < _countof(SetBlock); i++) {
		if (!SetBlock[i]->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
			assert(0);
			return 1;
		}
		SetBlock[i] = Block::Create();
		SetBlock[i]->Update(matview);
	}

	XMFLOAT3 SetBlockPosition[Block_NUM];
	XMFLOAT4 SetBlockColor[Block_NUM];
	for (int i = 0; i < _countof(SetBlock); i++) {
		SetBlockPosition[i] = { 0.0f,400.0f,0.0f };
		SetBlockColor[i] = SetBlock[i]->GetColor();
		SetBlock[i]->SetPosition(SetBlockPosition[i]);
	}

	//目印のマーク
	Block* MarkBlock[Block_NUM];
	for (int i = 0; i < _countof(MarkBlock); i++) {
		if (!MarkBlock[i]->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
			assert(0);
			return 1;
		}
		MarkBlock[i] = Block::Create();
		MarkBlock[i]->Update(matview);
	}

	XMFLOAT3 MarkBlockPosition[Block_NUM];
	XMFLOAT4 MarkBlockColor[Block_NUM];
	for (int i = 0; i < _countof(MarkBlock); i++) {
		MarkBlockColor[i] = ImageBlock[i]->GetColor();
		MarkBlockPosition[i] = { 0.0f,0.0f,134.0f };
	}
	for (int i = 0; i < _countof(MarkBlock); i++) {
		MarkBlock[i]->SetPosition(MarkBlockPosition[i]);
	}

	//普通のブロック
	const int FIELD_NUM = 80;
	Block* FieldBlock[FIELD_NUM];
	XMFLOAT3 FieldBlockPosition[FIELD_NUM];
	XMFLOAT4 FieldBlockColor[FIELD_NUM];
	for (int i = 0; i < _countof(FieldBlock); i++) {
		if (!FieldBlock[i]->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
			assert(0);
			return 1;
		}
		FieldBlock[i] = Block::Create();
		FieldBlock[i]->Update(matview);
	}

	for (int i = 0; i < 14; i++) {
		FieldBlockPosition[i] = { -135 + ((float)i * 10),0,134 };
		FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
	}

	for (int i = 14; i < 20; i++) {
		FieldBlockPosition[i] = { -60 + ((float)i * 10),0,134 };
		FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
	}

	for (int i = 20; i < 80; i++) {
		FieldBlockPosition[i] = { -80 + ((float)i * 10),-700,134 };
		FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
	}

	//スイッチで消えるブロック
	int AreaFlag = 0;
	Block* AreaBlock[Block_Area_NUM];
	for (int i = 0; i < _countof(AreaBlock); i++) {
		if (!AreaBlock[i]->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
			assert(0);
			return 1;
		}
		AreaBlock[i] = Block::Create();
		AreaBlock[i]->Update(matview);
	}

	XMFLOAT3 AreaBlockPosition[Block_Area_NUM];
	XMFLOAT4 AreaBlockColor[Block_Area_NUM];
	for (int i = 0; i < _countof(AreaBlock); i++) {
		AreaBlockPosition[i] = { 0.0f,400.0f,0.0f };
		AreaBlockColor[i] = AreaBlock[i]->GetColor();
		AreaBlock[i]->SetPosition(AreaBlockPosition[i]);
	}
#pragma endregion
#pragma region//後ろ
	Screen* screen;
	if (!screen->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	screen = Screen::Create();
	screen->Update(matview);
	XMFLOAT3 screenPos = screen->GetPosition();
#pragma endregion
#pragma region//プロジェクター
	Projector* projector;
	if (!projector->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	projector = Projector::Create();
	projector->Update(matview);

	XMFLOAT3 projectorPos;
	projectorPos = { 0,-20.0f,-70.0f };
	projector->SetPosition(projectorPos);

	Lever* lever;
	if (!lever->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	lever = Lever::Create();
	lever->Update(matview);

	XMFLOAT3 leverPos;
	leverPos = { -4.0,-5.0f,-70.0f };
	lever->SetPosition(leverPos);

	Under* under;
	if (!under->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	under = Under::Create();
	under->Update(matview);

	XMFLOAT3 underPos;
	underPos = { -100,-50.0f,-70.0f };
	under->SetPosition(underPos);

	Vinet* vinet;
	if (!vinet->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	vinet = Vinet::Create();
	vinet->Update(matview);

	XMFLOAT3 vinetPos;
	vinetPos = { -100,-50.0f,-70.0f };
	vinet->SetPosition(vinetPos);

	XMFLOAT3 leverRota = lever->GetRotaition();
	Gear* gear[2];
	XMFLOAT3 gearPos[2];
	gearPos[0] = { 0.7f,0.0f,-72.0f };
	gearPos[1] = { 0.7f,-6.0f,-76.0f };
	XMFLOAT3 gearRota[2];
	for (int i = 0; i < 2; i++) {
		if (!gear[i]->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
			assert(0);
			return 1;
		}
		gear[i] = Gear::Create();
		gear[i]->Update(matview);
		gearRota[i] = gear[i]->GetRotaition();
		gear[i]->SetPosition(gearPos[i]);
	}

#pragma endregion
#pragma region//光源
	LightSource* lightSource;
	if (!lightSource->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	lightSource = LightSource::Create();
	lightSource->Update(matview);

	XMFLOAT3 lightSourcePos = lightSource->GetPosition();
#pragma endregion
#pragma region//プレイヤー変数
#pragma region//左向きのプレイヤー変数
	//各プレイヤーの初期化
	PlayerLeftWalk* playerleftwalk;
	if (!playerleftwalk->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	playerleftwalk = PlayerLeftWalk::Create();
	playerleftwalk->Update(matview);
	PlayerLeftWalk2* playerleftwalk2;
	if (!playerleftwalk2->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	playerleftwalk2 = PlayerLeftWalk2::Create();
	playerleftwalk2->Update(matview);
	PlayerLeftWalk3* playerleftwalk3;
	if (!playerleftwalk3->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	playerleftwalk3 = PlayerLeftWalk3::Create();
	playerleftwalk3->Update(matview);
	PlayerLeftWalk4* playerleftwalk4;
	if (!playerleftwalk4->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	playerleftwalk4 = PlayerLeftWalk4::Create();
	playerleftwalk4->Update(matview);

	PlayerJump* playerJump;
	if (!playerJump->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	playerJump = PlayerJump::Create();
	playerJump->Update(matview);

	PlayerJumpLeft* playerJumpLeft;
	if (!playerJumpLeft->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	playerJumpLeft = PlayerJumpLeft::Create();
	playerJumpLeft->Update(matview);
#pragma endregion
#pragma region//右向きのプレイヤー変数
	//各プレイヤーの初期化
	PlayerRightWalk* playerrightwalk;
	if (!playerrightwalk->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	playerrightwalk = PlayerRightWalk::Create();
	playerrightwalk->Update(matview);
	PlayerRightWalk2* playerrightwalk2;
	if (!playerrightwalk2->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	playerrightwalk2 = PlayerRightWalk2::Create();
	playerrightwalk2->Update(matview);
	PlayerRightWalk3* playerrightwalk3;
	if (!playerrightwalk3->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	playerrightwalk3 = PlayerRightWalk3::Create();
	playerrightwalk3->Update(matview);
	PlayerRightWalk4* playerrightwalk4;
	if (!playerrightwalk4->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	playerrightwalk4 = PlayerRightWalk4::Create();
	playerrightwalk4->Update(matview);
#pragma endregion
	XMFLOAT3 PlayerPosition;
	PlayerPosition = { -140.0f,20.0f,135.0f };
	XMFLOAT3 OldPlayerPosition;
	XMFLOAT3 PlayerRotation;
	PlayerRotation = playerleftwalk->GetRotaition();
	playerleftwalk->SetPosition(PlayerPosition);
	XMFLOAT2 SpritePosition = sprite[0]->GetPosition();
	//ジャンプ変数
	int JumpFlag = 0;
	float JumpG = 0.0f;

	XMFLOAT3 targetcamerapos = { 0,0,0 };
	int mode = 0;//0:ゲームモード 1:設置モード
	int modeflag = 0;

	//アニメーション
	int AnimetionTimer = 0;
	int AnimetionCount = 0;
	int PlayerAlive = 1;
	int PlayerDirectionNumber = 0;
	int PlayerHitFlag = 0;
	int PlayerHP = 240;
#pragma endregion
#pragma region//ライト変数
	const int Light_NUM = 10;

	Light* light[Light_NUM];
	XMFLOAT3 LightPosition[Light_NUM];
	int LightMoveNumber[Light_NUM] = { 0 };
	int LightMoveCount[Light_NUM] = { 50 };
	for (int i = 0; i < Light_NUM; i++) {
		if (!light[i]->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
			assert(0);
			return 1;
		}
		light[i] = Light::Create();
		light[i]->Update(matview);
		LightPosition[i] = { 0,300.0f,0.0f };
		light[i]->SetPosition(LightPosition[i]);
	}
#pragma endregion
#pragma region//アイテム変数
	const int Item_NUM = 10;
	Item* item[Item_NUM];
	XMFLOAT3 ItemPosition[Item_NUM];
	int ItemAlive[Item_NUM];
	int ItemCount = 0;

	for (int i = 0; i < Item_NUM; i++) {
		if (!item[i]->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
			assert(0);
			return 1;
		}
		item[i] = Item::Create();
		item[i]->Update(matview);
		ItemPosition[i] = { 0,300,134 };
		ItemAlive[i] = 1;
		item[i]->SetPosition(ItemPosition[i]);
	}

	ItemPosition[0] = { -30,10,134 };
#pragma endregion
#pragma region//ゴール
	Goal* goal;
	if (!goal->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	goal = Goal::Create();
	goal->Update(matview);
	XMFLOAT3 GoalPosition = { 110.0f,10.0f,134.0f };
	goal->SetPosition(GoalPosition);
#pragma endregion
#pragma region//スイッチ的なやつ
	Area* area;
	if (!area->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	area = Area::Create();
	area->Update(matview);
	XMFLOAT3 AreaPosition = { 50.0f,400.0f,134.0f };
	area->SetPosition(AreaPosition);
#pragma endregion
#pragma region//背景
	BackGround* background;
	if (!background->StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	//XMFLOAT3 BackPosition;
	//BackPosition = background->GetPosition();

	background = BackGround::Create();
	background->Update();
#pragma endregion
#pragma region//シーン変数
	int Scene = 0;
	int StageNumber = 1;
	int ResetFlag = 0;
	int SpaceCount = 0;
	int CutTimer = 0;
	int CutCount = 0;
	int LightCount = 0;
	int LightFlag = 0;
	int AppearanceCount = 0;
	int GameClearCount = 0;
	enum Scene {
		title,
		explation,
		appearance,
		gamePlay,
		gameOver,
		stageClear,
		gameClear
	};
#pragma endregion
#pragma region//カメラ
	XMVECTOR v0 = { 50,60,-140,0 };
	XMMATRIX rotM;// = XMMatrixIdentity();
	XMVECTOR eye2;
	XMVECTOR target2 = { PlayerPosition.x, 0,0,0 };
	XMVECTOR up2 = { 0,0.0f,0,0 };
	XMFLOAT3 targetPosition = { 0.0f,0.0f,0.0f };
#pragma endregion
#pragma region//当たり判定
	Collision* Boxcollision = nullptr;
	int HitNumber = 0;
#pragma endregion
#pragma region//ループ処理
	XMFLOAT3 kage[4];
	while (true) {
		//ウィンドウメッセージ処理
		if (winApp->ProcessMessage()) {
			break;
		}
		for (int i = 0; i < _countof(ImageBlock); i++) {
			ImageBlockPosition[i] = ImageBlock[i]->GetPosition();
			if ((ItemCount != 0) || (SetFlag[i] == 1)) {
				ImageBlock[i]->SetColor({ 1.0f,1.0f,1.0f,1.0 });
			} else {
				ImageBlock[i]->SetColor({ 1.0f,0.0f,0.0f,1.0 });
			}
		}

		for (int i = 0; i < _countof(SetBlock); i++) {
			SetBlockColor[i] = SetBlock[i]->GetColor();
		}

		for (int i = 0; i < _countof(MarkBlock); i++) {
			MarkBlock[i]->SetColor({ 1.0f,0.0f,0.0f,1.0 });
		}

		for (int i = 0; i < _countof(AreaBlock); i++) {
			if (AreaFlag == 0) {
				AreaBlock[i]->SetColor({ 0.7f,0.7f,0.7f,1.0 });
			} else {
				AreaBlock[i]->SetColor({ 0.0f,0.0f,0.0f,0.0 });
			}
		}
		area->SetColor({ 1.0f,0.0f,0.0f,1.0f });
		for (int i = 0; i < _countof(FieldBlock); i++) {
			FieldBlock[i]->SetColor({ 0.3f,0.3f,0.3f,1.0f });
		}
		SpritePosition = sprite[0]->GetPosition();
#pragma region//更新処理
		//キーの更新
		input->Update();
#pragma region//タイトル
		if (Scene == title) {
			if (input->TriggerKey(DIK_SPACE)) {
				Scene = appearance;
				targetPosition = { projectorPos.x,projectorPos.y,projectorPos.z };
				v0.m128_f32[0] = -20;
				v0.m128_f32[1] = 0;
				v0.m128_f32[2] = -90;
				audio->StopWave(0);
			}
		}
#pragma endregion
#pragma region//導入
		if (Scene == appearance) {
			AppearanceCount++;

			if (AppearanceCount == 99) {
				audio->LoopWave(1, 0.3);
			}
			if (AppearanceCount >= 100) {
				LightFlag = 1;
			}

			if (LightFlag == 1) {
				LightCount++;
				leverRota.z -= 3.0f;
				for (int i = 0; i < 2; i++) {
					gearRota[i].x += 3.0f;
				}
			}

			if (LightCount == 100) {
				LightCount = 0;
			}

			if (AppearanceCount >= 200) {
				if (v0.m128_f32[0] != 0.0f) {
					v0.m128_f32[0] += 1.0f;
				} else {
					Scene = gamePlay;
					LightFlag = 0;
					AppearanceCount = 0;
					audio->LoopWave(2, 0.3f);
					audio->StopWave(1);
				}
			}

		}
#pragma endregion
#pragma region//ゲームプレイ中
		if (Scene == gamePlay) {
			LightCount++;
			//カメラ
			if (input->TriggerKey(DIK_M) && mode == 0 && modeflag == 1)
			{
				mode = 1;
				audio->LoopWave(1, 0.3);
				audio->StopWave(2);
			}
			else if (input->TriggerKey(DIK_M) && mode == 1 && modeflag == 0)
			{
				mode = 0;
				audio->StopWave(1);
				audio->LoopWave(2, ProjectorVolume);
			}
#pragma region//プレイ画面
			if (mode == 0) {
				v0.m128_f32[1] -= 2.0f;
				v0.m128_f32[2] += 1.7f;
				if (v0.m128_f32[2] >= -20.0f) {
					v0.m128_f32[2] = -20.0f;
				}
				if (v0.m128_f32[1] <= 0.0f) {
					v0.m128_f32[1] = 0.0f;

				}

				if (v0.m128_f32[2] == -20.0f && v0.m128_f32[1] == 0.0f) {
					modeflag = 1;
				}

			}
			if (mode == 1) {
				v0.m128_f32[2] -= 3.5f;
				v0.m128_f32[1] += 0.5f;
				if (v0.m128_f32[2] <= -135.0f) {
					v0.m128_f32[2] = -135.0f;

				}
				if (v0.m128_f32[1] >= 33.0f) {
					v0.m128_f32[1] = 33.0f;
				}
				if (v0.m128_f32[2] == -135.0f && v0.m128_f32[1] == 33.0f) {
					modeflag = 0;
				}
			}
			//位置情報保存
			OldPlayerPosition.x = PlayerPosition.x;
			OldPlayerPosition.y = PlayerPosition.y;
			OldPlayerPosition.z = PlayerPosition.z;
			
				//プレイ中のプレイヤー移動
			if ((mode == 0) && (modeflag == 1) && (SceneCutFlag == 0)) {
				if ((input->PushKey(DIK_LEFT)) || (input->PushKey(DIK_RIGHT))) {
					//移動処理
					if (input->PushKey(DIK_LEFT) && (PlayerPosition.x >= -135.0f)) {
						PlayerPosition.x -= 0.8f;
						AnimetionTimer++;
						PlayerDirectionNumber = 1;
					}
					if (input->PushKey(DIK_RIGHT) && (PlayerPosition.x <= 135.0f)) {
						PlayerPosition.x += 0.8f;
						AnimetionTimer++;
						PlayerDirectionNumber = 0;
					}
					if (JumpFlag == 1) {
						if (input->PushKey(DIK_RIGHT) && (PlayerPosition.x <= 135.0f)) {
							PlayerPosition.x += 0.1f;
						}
						if (input->PushKey(DIK_LEFT) && (PlayerPosition.x >= -135.0f)) {
							PlayerPosition.x -= 0.1f;
						}
					}

				}
				else {
					AnimetionTimer = 0;
					AnimetionCount = 0;
				}
				//ジャンプ処理
				if (input->TriggerKey(DIK_SPACE) && (JumpFlag == 0) && (JumpG >= 0.0f) && (JumpG <= 0.1f)) {
					JumpG = -1.5f;
					JumpFlag = 1;
				}

				//ジャンプ処理
				PlayerPosition.y -= JumpG;
				JumpG += 0.045f;
			}

			
			//アニメーションタイマー
			if (AnimetionTimer >= 8) {
				AnimetionCount++;
				AnimetionTimer = 0;
			}
			if (AnimetionCount == 4) {
				AnimetionCount = 0;
			}

			if (input->TriggerKey(DIK_R)) {
				ResetFlag = 1;
				audio->StopWave(1);
				audio->LoopWave(2, ProjectorVolume);
			}

			//画面外で死
			if ((PlayerPosition.y <= -135) || (PlayerHP <= 0)) {
				PlayerAlive = 0;
				audio->StopWave(1);
				audio->LoopWave(2, ProjectorVolume);
			}

			if (PlayerAlive == 0) {
				ResetFlag = 1;
			}

			//光動く
			for (int i = 0; i < Light_NUM; i++) {
				if (LightMoveNumber[i] == 1) {
					LightPosition[i].y += 0.8f;
					LightMoveCount[i]++;
					if (LightMoveCount[i] >= 100) {
						LightMoveNumber[i] = 2;
					}
				}else if (LightMoveNumber[i] == 2) {
					LightPosition[i].y -= 0.8f;
					LightMoveCount[i]--;
					if (LightMoveCount[i] <= 0) {
						LightMoveNumber[i] = 1;
					}
				}else if (LightMoveNumber[i] == 3) {
					LightPosition[i].x += 1.0f;
					LightMoveCount[i]++;
					if (LightMoveCount[i] >= 100) {
						LightMoveNumber[i] = 4;
					}
				} else if (LightMoveNumber[i] == 4) {
					LightPosition[i].x -= 1.0f;
					LightMoveCount[i]--;
					if (LightMoveCount[i] <= 0) {
						LightMoveNumber[i] = 3;
					}
				}
			}
			for (int i = 0; i < 2; i++) {
				FilmPos[i].y += 3.0f;

				if (FilmPos[i].y >= 720) {
					FilmPos[i].y = -720;
				}
				sprite[13]->SetPosition(FilmPos[0]);
				sprite[14]->SetPosition(FilmPos[1]);
			}

			for (int i = 0; i < SceneCutMax; i++) {
				SpriteSceneCut[i]->SetPosition(SceneCutPos);
			}

			for (int i = 0; i < SceneCutNumberMax; i++) {
				SpriteSceneCutNumber[i]->SetPosition(SceneCutPos);
			}
#pragma endregion
#pragma region//設置画面
			if (mode == 1) {
				XMFLOAT3 temp[4];
				for (int i = 0; i < 4; i++) {
					temp[i] = { 0.0f,0.0f,screenPos.z };
					kage[i] = { 0.0f,0.0f,screenPos.z };
				}

				for (int i = 0; i < Block_NUM; i++) {
					float a1;
					float a2;
					float b;
					float c;

					float A;
					float B;
					float C;
					float boxRadius = 1.0f;
					a1 = (ImageBlockPosition[i].z - boxRadius) - projectorPos.z;
					a2 = (ImageBlockPosition[i].z + boxRadius) - projectorPos.z;

					b = boxRadius + (projectorPos.y - ImageBlockPosition[i].y);

					c = (ImageBlockPosition[i].y + boxRadius) - projectorPos.y;

					A = screenPos.z - projectorPos.z;

					if (abs(ImageBlockPosition[i].y - projectorPos.y) <= boxRadius) {
						B = (b * A) / a1;
						C = (c * A) / a1;
						float lineY = projectorPos.y - B;
						float lineLength = B + C;
						temp[0].y = lineY;
						temp[1].y = lineLength;
					}

					else if (ImageBlockPosition[i].y < projectorPos.y) {
						B = (b * A) / a1;
						C = (c * A) / a2;
						float lineY = projectorPos.y - B;
						float lineLength = B + C;
						temp[0].y = lineY;
						temp[1].y = lineLength;
					} else if (ImageBlockPosition[i].y > projectorPos.y) {
						B = (b * A) / a2;
						C = (c * A) / a1;
						float lineY = projectorPos.y - B;
						float lineLength = B + C;
						temp[0].y = lineY;
						temp[1].y = lineLength;
					}

					a1 = (ImageBlockPosition[i].z - boxRadius) - projectorPos.z;
					a2 = (ImageBlockPosition[i].z + boxRadius) - projectorPos.z;

					b = boxRadius + (projectorPos.x - ImageBlockPosition[i].x);

					c = (ImageBlockPosition[i].x + boxRadius) - projectorPos.x;

					A = screenPos.z - projectorPos.z;

					if (abs(ImageBlockPosition[i].x - projectorPos.x) <= boxRadius) {
						B = (b * A) / a1;
						C = (c * A) / a1;
						float lineY = projectorPos.x - B;
						float lineLength = B + C;
						temp[2].x = lineY;
						temp[3].x = lineLength;
					} else if (ImageBlockPosition[i].x < projectorPos.x) {
						B = (b * A) / a1;
						C = (c * A) / a2;
						float lineY = projectorPos.x - B;
						float lineLength = B + C;
						temp[2].x = lineY;
						temp[3].x = lineLength;
					} else if (ImageBlockPosition[i].x > projectorPos.x) {
						B = (b * A) / a2;
						C = (c * A) / a1;
						float lineY = projectorPos.x - B;
						float lineLength = B + C;
						temp[2].x = lineY;
						temp[3].x = lineLength;
					}
				}
				kage[0] = { temp[2].x,temp[0].y,screenPos.z - 10.0f };
				kage[1] = { temp[3].x,temp[0].y,screenPos.z - 10.0f };
				kage[2] = { temp[3].x,temp[1].y,screenPos.z - 10.0f };
				kage[3] = { temp[2].x,temp[1].y,screenPos.z - 10.0f };

				float kageXR = (kage[1].x - kage[0].x) / 2;
				float kageYR = (kage[3].y - kage[0].y) / 2;
				kage[0].x = kage[0].x + kageXR;
				kage[0].y = kage[0].y + kageYR;
				for (int i = 0; i < Block_NUM; i++) {
					if (SetFlag[i] == 0) {
						//移動処理
						if (input->PushKey(DIK_UP) && (ImageBlockPosition[i].y <= 27.0f)) {
							ImageBlockPosition[i].y += 1.0f;
						}

						if (input->PushKey(DIK_DOWN) && (ImageBlockPosition[i].y >= -63.0f)) {
							ImageBlockPosition[i].y -= 1.0f;
						}

						if (input->PushKey(DIK_LEFT) && (ImageBlockPosition[i].x >= -95.0f)) {
							ImageBlockPosition[i].x -= 1.0f;
							//PlayerRotation.z = 270;
						}
						if (input->PushKey(DIK_RIGHT) && (ImageBlockPosition[i].x <= 75.0f)) {
							ImageBlockPosition[i].x += 1.0f;
						}
						MarkBlockPosition[i].x = kage[0].x;
						MarkBlockPosition[i].y = kage[0].y;
						MarkBlockPosition[i].z = 134.0f;
					}

					//ブロックを置く処理
					if (input->TriggerKey(DIK_SPACE) && (SetFlag[i] == 0) && (ItemCount != 0) && (PlayerHitFlag == 0)) {
						ItemCount--;
						SetFlag[i] = 1;
						SetBlockPosition[i].x = kage[0].x;
						SetBlockPosition[i].y = kage[0].y;
						SetBlockPosition[i].z = 134.0f;
						TextNumber++;
						audio->PlayWave("Resources/Sound/Makibisi_Roll.wav", 0.7f);
						break;
					}
				}
				//ジャンプ処理
				PlayerPosition.y -= JumpG;
				JumpG += 0.045f;
				leverRota.z -= 3.0f;
				for (int i = 0; i < 2; i++) {
					gearRota[i].x += 3.0f;
				}
			}
#pragma endregion
#pragma region//当たり判定
			//障害物との当たり判定
			for (int i = 0; i < Block_NUM; i++) {
				if (SetFlag[i] == 1) {
					if (SetBlockColor[i].w > 0.0f) {
						//playerとブロック左辺の当たり判定
						if (Boxcollision->BoxCollision_Left(PlayerPosition, { 7.6,4.9,4 }, SetBlockPosition[i], { 7.6,4.9,4 }) == TRUE) {
							PlayerPosition.x = OldPlayerPosition.x;
							HitNumber = 1;
						}
						//playerとブロック右辺の当たり判定
						if (Boxcollision->BoxCollision_Right(PlayerPosition, { 7.6,4.9,4 }, SetBlockPosition[i], { 7.6,4.9,4 }) == TRUE) {
							PlayerPosition.x = OldPlayerPosition.x;
							HitNumber = 2;
						}

						//playerとブロック下辺の当たり判定
						if (Boxcollision->BoxCollision_Down(PlayerPosition, { 3.0,4.8,4 }, SetBlockPosition[i], { 3.0,4.8,4 }) == TRUE) {
							PlayerPosition.y = OldPlayerPosition.y;
							JumpG = 0.0f;
							HitNumber = 3;
						}

						//playerとブロック上辺の当たり判定(高いところからだと死)
						if (Boxcollision->BoxCollision_Up(PlayerPosition, { 3.0,4.8,4 }, SetBlockPosition[i], { 3.0,4.8,4 }) == TRUE) {
							PlayerPosition.y = OldPlayerPosition.y;
							JumpG = 0.0f;
							JumpFlag = 0;
							HitNumber = 4;
						}
					}
				}
			}

			for (int i = 0; i < FIELD_NUM; i++) {
				//playerとブロック左辺の当たり判定
				if (Boxcollision->BoxCollision_Left(PlayerPosition, { 7.6,4.9,4 }, FieldBlockPosition[i], { 7.6,4.9,4 }) == TRUE) {
					PlayerPosition.x = OldPlayerPosition.x;
				}
				//playerとブロック右辺の当たり判定
				if (Boxcollision->BoxCollision_Right(PlayerPosition, { 7.6,4.9,4 }, FieldBlockPosition[i], { 7.6,4.9,4 }) == TRUE) {
					PlayerPosition.x = OldPlayerPosition.x;
				}

				//playerとブロック下辺の当たり判定
				if (Boxcollision->BoxCollision_Down(PlayerPosition, { 3.0,4.8,4 }, FieldBlockPosition[i], { 3.0,4.8,4 }) == TRUE) {
					PlayerPosition.y = OldPlayerPosition.y;
					JumpG = 0.0f;
				}

				//playerとブロック上辺の当たり判定(高いところからだと死)
				if (Boxcollision->BoxCollision_Up(PlayerPosition, { 3.0,4.8,4 }, FieldBlockPosition[i], { 3.0,4.8,4 }) == TRUE) {
					PlayerPosition.y = OldPlayerPosition.y;
					JumpG = 0.0f;
					JumpFlag = 0;
				}
			}

			for (int i = 0; i < Block_Area_NUM; i++) {
				if (AreaFlag == 0) {
					//playerとブロック左辺の当たり判定
					if (Boxcollision->BoxCollision_Left(PlayerPosition, { 7.6,4.9,4 }, AreaBlockPosition[i], { 7.6,4.9,4 }) == TRUE) {
						PlayerPosition.x = OldPlayerPosition.x;
					}
					//playerとブロック右辺の当たり判定
					if (Boxcollision->BoxCollision_Right(PlayerPosition, { 7.6,4.9,4 }, AreaBlockPosition[i], { 7.6,4.9,4 }) == TRUE) {
						PlayerPosition.x = OldPlayerPosition.x;
					}

					//playerとブロック下辺の当たり判定
					if (Boxcollision->BoxCollision_Down(PlayerPosition, { 3.0,4.8,4 }, AreaBlockPosition[i], { 3.0,4.8,4 }) == TRUE) {
						PlayerPosition.y = OldPlayerPosition.y;
						JumpG = 0.0f;
					}

					//playerとブロック上辺の当たり判定(高いところからだと死)
					if (Boxcollision->BoxCollision_Up(PlayerPosition, { 3.0,4.8,4 }, AreaBlockPosition[i], { 3.0,4.8,4 }) == TRUE) {
						PlayerPosition.y = OldPlayerPosition.y;
						JumpG = 0.0f;
						JumpFlag = 0;
					}
				}
			}

			//アイテム取得判定
			for (int i = 0; i < Item_NUM; i++) {
				if (ItemAlive[i] == 1) {
					if (Boxcollision->CircleCollision(PlayerPosition.x, PlayerPosition.y, 3, ItemPosition[i].x, ItemPosition[i].y, 3) == 1) {
						ItemCount++;
						ItemAlive[i] = 0;
						TextNumber++;
					}
				}
			}

			//ゴール判定
			if (Boxcollision->CircleCollision(PlayerPosition.x, PlayerPosition.y, 3, GoalPosition.x, GoalPosition.y, 3) == 1) {
				if (SceneCutFlag == 0) {
					SceneCutFlag = 1;
					StageNumber++;
				}
			}


			//光とブロックの当たり判定
			for (int i = 0; i < Block_NUM; i++) {
				for (int j = 0; j < Light_NUM; j++) {
					if (SetFlag[i] == 1) {
						if (Boxcollision->CircleCollision(SetBlockPosition[i].x, SetBlockPosition[i].y, 7.5, LightPosition[j].x, LightPosition[j].y, 7.5) == 1) {
							if (LightMoveNumber[j] == 0) {
								SetBlockColor[i].w -= 0.0010;
							} else {
								SetBlockColor[i].w -= 0.0025;
							}
						}
					}
				}
			}

			//光とプレイヤーの当たり判定
			for (int j = 0; j < Light_NUM; j++) {
				if (Boxcollision->CircleCollision(PlayerPosition.x, PlayerPosition.y, 7.5, LightPosition[j].x, LightPosition[j].y, 7.5) == 1) {
					PlayerHP--;
				}
			}

			for (int i = 17; i < 22; i++) {
				if ((PlayerHP % 60 == 0) && (PlayerHP != 240)) {
					sprite[i]->SetColor({ 1.0f,0.0f,0.0f,1.0f }); 
					audio->PlayWave("Resources/Sound/action1, damage1.wav", 0.4f);
					PlayerHP--;
				} else {
					sprite[i]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
				}
			}

			//スイッチ判定
			for (int i = 0; i < _countof(SetBlock); i++) {
				if (Boxcollision->CircleCollision(SetBlockPosition[i].x, SetBlockPosition[i].y, 4, AreaPosition.x, AreaPosition.y, 4) == 1) {
					if (SetBlockColor[i].w > 0.0f) {
						AreaFlag = 1;
					} else {
						AreaFlag = 0;
					}
				}
			}
			//プレイヤーとカゲの当たり判定
			for (int i = 0; i < _countof(MarkBlock); i++) {
				if (Boxcollision->CircleCollision(MarkBlockPosition[i].x, MarkBlockPosition[i].y, 4, PlayerPosition.x, PlayerPosition.y, 4) == 1) {
					PlayerHitFlag = 1;
				} else {
					PlayerHitFlag = 0;
				}
			}

			//プレイヤーとエリアブロックの当たり判定
			for (int i = 0; i < _countof(AreaBlock); i++) {
				if ((Boxcollision->CircleCollision(AreaBlockPosition[i].x, AreaBlockPosition[i].y, 3, PlayerPosition.x, PlayerPosition.y, 3) == 1)
					&& (AreaFlag == 0)) {
					ResetFlag = 1;
				}
			}

			if (SceneCutFlag == 1) {
				if (SceneCutPos.x != 0.0f) {
					SceneCutPos.x -= 16.0f;
				}

				else if (SceneCutPos.x == 0.0f) {
					CutTimer++;
				
				}

				if (CutTimer == 6 && CutCount != 4) {
					CutCount++;
					CutTimer = 0;
				}
				if (CutCount == 4) {
					audio->PlayWave("Resources/Sound/nc44551.wav", 0.4f);
					SceneCutFlag = 0;
					ResetFlag = 1;
					CutCount = 0;
					SceneCutPos = { 1280.0f,0.0f };
					if (StageNumber == 13) {
						Scene = gameClear;
						audio->StopWave(2);
					}
				}
			}

			if ((TextNumber == 1) && input->TriggerKey(DIK_M)) {
				TextNumber++;
			}
#pragma endregion
		}
#pragma region//ステージクリア
		if (Scene == stageClear) {
			ResetFlag = 1;
			if (input->TriggerKey(DIK_SPACE)) {
				Scene = title;
				GameClearCount = 0;
				ResetFlag = 0;
			}
		}
#pragma endregion
#pragma region//ゲームオーバー
		if (Scene == gameOver) {
			ResetFlag = 1;
			if (input->TriggerKey(DIK_SPACE)) {
				Scene = gamePlay;
				ResetFlag = 0;
			}
		}
#pragma endregion
#pragma endregion
#pragma region//クリア
		if (Scene == gameClear) {
			StageNumber = 1;
			ResetFlag = 1;
			GameClearCount++;
			if (GameClearCount == 1) {
				audio->PlayWave("Resources/Sound/ME007-090401-clear03-wav.wav", 0.4f);
			}
			if (input->TriggerKey(DIK_SPACE)) {
				Scene = title;
				audio->LoopWave(0, 0.3);
				ResetFlag = 0;
				SceneCutFlag = 1;
				GameClearCount = 0;
				SpaceCount = 0;
			}
		}
		if (ResetFlag == 1) {
			//各変数初期化
			ExplanationNumber = 0;
			JumpG = 0.0f;
			PlayerAlive = 1;
			PlayerHP = 240;
			PlayerDirectionNumber = 0;
			ItemCount = 0;
			mode = 0;
			TextNumber = 0;
			AreaFlag = 0;
			for (int i = 0; i < Light_NUM; i++) {
				LightPosition[i] = { 0.0f,700.0f,0.0f };
				LightMoveNumber[i] = 0;
				LightMoveCount[i] = 50;
			}
			for (int i = 0; i < _countof(SetBlock); i++) {
				SetBlockPosition[i] = { 0.0f,400.0f,0.0f };
				SetBlockColor[i].w = 1.0f;
				SetFlag[i] = 0;
			}

			for (int i = 0; i < _countof(MarkBlock); i++) {
				MarkBlockPosition[i] = { 0.0f,0.0f,134.0f };
			}
			for (int i = 0; i < Item_NUM; i++) {
				ItemPosition[i] = { 0,300,134 };
				ItemAlive[i] = 1;
				item[i]->SetPosition(ItemPosition[i]);
			}
			for (int i = 0; i < _countof(ImageBlock); i++) {
				ImageBlockPosition[i] = { 0.0f,0.0f,70.0f };
			}
			for (int i = 0; i < _countof(FieldBlock); i++) {
				FieldBlockPosition[i] = { 0.0f,400.0f,0.0f };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}
			for (int i = 0; i < _countof(AreaBlock); i++) {
				AreaBlockPosition[i] = { 0.0f,400.0f,0.0f };
				AreaBlockColor[i] = AreaBlock[i]->GetColor();
				AreaBlock[i]->SetPosition(AreaBlockPosition[i]);
			}
			if (StageNumber == 1) {
				AreaPosition = { 0.0f,400.0f,134.0f };
				GoalPosition = { 110.0f,10.0f,134.0f };
				PlayerPosition = { -130.0f,20.0f,135.0f };

				for (int i = 0; i < 14; i++) {
					FieldBlockPosition[i] = { -135 + ((float)i * 10),0,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 14; i < 20; i++) {
					FieldBlockPosition[i] = { -60 + ((float)i * 10),0,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				ItemPosition[0] = { -40,10,134 };
			}
			else if (StageNumber == 2) {
				GoalPosition = { 110.0f, 30.0f, 134.0f };
				PlayerPosition = { -130.0f,-20.0f,135.0f };
				for (int i = 0; i < 10; i++) {
					FieldBlockPosition[i] = { -135 + ((float)i * 10),-40,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 10; i < 19; i++) {
					FieldBlockPosition[i] = { -20 + ((float)i * 10),20,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				ItemPosition[0] = { -120,-30,134 };
				ItemPosition[1] = { -100,-30,134 };
				ItemPosition[2] = { -80,-30,134 };
			}
			else if (StageNumber == 3) {
				GoalPosition = { 100.0f, 10.0f, 134.0f };
				PlayerPosition = { -130.0f,-50.0f,135.0f };
				for (int i = 0; i < 10; i++) {
					FieldBlockPosition[i] = { -135 + ((float)i * 10),-80,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 10; i < 19; i++) {
					FieldBlockPosition[i] = { -40 + ((float)i * 10),0,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 19; i < 28; i++) {
					FieldBlockPosition[i] = { -330 + ((float)i * 10),-30,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 28; i < 35; i++) {
					FieldBlockPosition[i] = { -40,-360 + ((float)i * 10),134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}


				for (int i = 35; i < 39; i++) {
					FieldBlockPosition[i] = { -60,-410 + ((float)i * 10),134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				ItemPosition[0] = { -120,-70,134 };
				ItemPosition[1] = { -100,-70,134 };
				ItemPosition[2] = { -120,-20,134 };
				ItemPosition[3] = { -100,-20,134 };
				ItemPosition[4] = { -80,-20,134 };
			}
			else if (StageNumber == 4) {
				PlayerPosition = { -130.0f,20.0f,135.0f };
				GoalPosition = { 120.0f,10.0f,134.0f };
				for (int i = 0; i < 8; i++) {
					FieldBlockPosition[i] = { -135 + ((float)i * 10),0,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				for (int i = 8; i < 10; i++) {
					FieldBlockPosition[i] = { -60 + ((float)i * 10),0,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				for (int i = 10; i < 13; i++) {
					FieldBlockPosition[i] = { 10 + ((float)i * 10),0,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				ItemPosition[0] = { -100,10,134 };
				ItemPosition[1] = { 20,10,134 };
				LightPosition[0] = { -25, 5 , 134 };
				LightPosition[1] = { 75, 5, 134 };
			}
			else if (StageNumber == 5) {
				PlayerPosition = { -130.0f,-60.0f,135.0f };
				GoalPosition = { 110.0f,10.0f,134.0f };
				for (int i = 0; i < 6; i++) {
					FieldBlockPosition[i] = { -135 + ((float)i * 10),-80,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 6; i < 12; i++) {
					FieldBlockPosition[i] = { -110 + ((float)i * 10),-80,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 12; i < 20; i++) {
					FieldBlockPosition[i] = { -90 + ((float)i * 10),-80,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 20; i < 45; i++) {
					FieldBlockPosition[i] = { -350 + ((float)i * 10),-40,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 45; i < 70; i++) {
					FieldBlockPosition[i] = { -550 + ((float)i * 10),0,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				ItemPosition[0] = { -10,-70,134 };
				ItemPosition[1] = { 20,-30,134 };
				LightPosition[0] = { 115, -60 ,134 };
				LightPosition[1] = { -120, -20 ,134 };
				LightPosition[2] = { -65, -40 ,134 };
				LightPosition[3] = { 15, -40 ,134 };
				LightMoveNumber[2] = 1;
				LightMoveNumber[3] = 2;
			}
			else if (StageNumber == 6) {
				PlayerPosition = { -130.0f,-60.0f,135.0f };
				GoalPosition = { 105.0f,-60.0f,134.0f };
				for (int i = 0; i < 6; i++) {
					FieldBlockPosition[i] = { -135 + ((float)i * 10),-80,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 6; i < 8; i++) {
					FieldBlockPosition[i] = { -135 + ((float)i * 10),-60,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				for (int i = 10; i < 12; i++) {
					FieldBlockPosition[i] = { -120 + ((float)i * 10),-30,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 12; i < 20; i++) {
					FieldBlockPosition[i] = { -20,-220 + ((float)i * 10),134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 20; i < 35; i++) {
					FieldBlockPosition[i] = { 20,-250 + ((float)i * 10),134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 35; i < 45; i++) {
					FieldBlockPosition[i] = { -320 + ((float)i * 10),-50,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				ItemPosition[0] = { -110,-70,134 };
				ItemPosition[1] = { -100,-70,134 };
				ItemPosition[2] = { -90,-70,134 };
				ItemPosition[3] = { -40,-10,134 };
				ItemPosition[4] = { -30,-10,134 };
				LightPosition[0] = { -50, -30 ,134 };
				LightPosition[1] = { 5, -75 ,134 };
				LightPosition[2] = { 55, -65 ,134 };
				LightPosition[3] = { 100, -65 ,134 };
				LightMoveNumber[0] = 1;
				LightMoveNumber[2] = 1;
				LightMoveNumber[3] = 2;
			}
			else if (StageNumber == 7) {
				GoalPosition = { 100.0f,10.0f,134.0f };
				PlayerPosition = { -130.0f,20.0f,135.0f };
				for (int i = 0; i < 25; i++) {
					FieldBlockPosition[i] = { -135 + ((float)i * 10),0,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				for (int i = 0; i < 10; i++) {
					AreaBlockPosition[i] = { 0,0 + ((float)i * 10),134 };
					AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
				}
				ItemPosition[0] = { -80,10,134 };
				AreaPosition = { -80.0f,40.0f,134 };
			}
			else if (StageNumber == 8) {
				GoalPosition = { -110.0f,20.0f,134.0f };
				PlayerPosition = { -130.0f,-50.0f,135.0f };
				for (int i = 0; i < 8; i++) {
					FieldBlockPosition[i] = { -135 + ((float)i * 10),-70,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				for (int i = 8; i < 15; i++) {
					FieldBlockPosition[i] = { -20 + ((float)i * 10),-70,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				for (int i = 15; i < 25; i++) {
					FieldBlockPosition[i] = { -280 + ((float)i * 10),10,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				for (int i = 0; i < 10; i++) {
					AreaBlockPosition[i] = { 60,-70 + ((float)i * 10),134 };
					AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
				}

				for (int i = 10; i < 18; i++) {
					AreaBlockPosition[i] = { -40,-80 + ((float)i * 10),134 };
					AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
				}
				ItemPosition[0] = { -100.0f,-60.0f,134.0f };
				ItemPosition[1] = { -80.0f,-60.0f,134.0f };
				ItemPosition[2] = {  80.0f,-60.0f,134.0f };
				ItemPosition[3] = {  100.0f,-60.0f,134.0f };
				ItemPosition[4] = { 120.0f,-60.0f,134.0f };
				LightPosition[0] = { 40.0f, -40.0f ,134 };
				LightPosition[1] = { 10.0f, -20.0f ,134 };
				LightPosition[2] = { -20.0f, 0.0f ,134 };
				LightMoveNumber[0] = 1;
				LightMoveNumber[1] = 2;
				LightMoveNumber[2] = 1;
				LightMoveCount[0] = 30;
				LightMoveCount[1] = 50;
				LightMoveCount[2] = 70;
				AreaPosition = { -120.0f,-55.0f,134.0f };
			}
			else if (StageNumber == 9) {
				GoalPosition = { -100.0f,-10.0f,134.0f };
				PlayerPosition = { -100.0f,-50.0f,135.0f };
				for (int i = 0; i < 8; i++) {
					FieldBlockPosition[i] = { -135 + ((float)i * 10),-70,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				for (int i = 8; i < 15; i++) {
					FieldBlockPosition[i] = { -20 + ((float)i * 10),-70,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				for (int i = 15; i < 28; i++) {
					FieldBlockPosition[i] = { -290 + ((float)i * 10),-20,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				for (int i = 0; i < 10; i++) {
					AreaBlockPosition[i] = { 60,-70 + ((float)i * 10),134 };
					AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
				}

				for (int i = 10; i < 18; i++) {
					AreaBlockPosition[i] = { -20,-110 + ((float)i * 10),134 };
					AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
				}
				ItemPosition[0] = { -100.0f,-60.0f,134.0f };
				ItemPosition[1] = { -80.0f,-60.0f,134.0f };
				ItemPosition[2] = { 80.0f,-60.0f,134.0f };
				ItemPosition[3] = { 100.0f,-60.0f,134.0f };
				ItemPosition[4] = { 120.0f,-60.0f,134.0f };
				LightPosition[0] = { -35.0f, -58.0f ,134 };
				LightPosition[1] = { 40.0f, -40.0f ,134 };
				LightPosition[2] = { 0.0f, -20.0f ,134 };
				LightPosition[3] = { -120.0f, -55.0f ,134 };
				LightMoveNumber[0] = 1;
				LightMoveNumber[1] = 2;
				LightMoveNumber[2] = 1;
				LightMoveCount[0] = 30;
				LightMoveCount[1] = 50;
				LightMoveCount[2] = 70;
				AreaPosition = { -120.0f,-55.0f,134.0f };
			}
			else if (StageNumber == 10) {
			GoalPosition = { 80.0f, -20.0f, 134.0f };
			PlayerPosition = { -100.0f,15.0f,135.0f };
			for (int i = 0; i < 10; i++) {
				FieldBlockPosition[i] = { -135 + ((float)i * 10),0,134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}

			for (int i = 10; i < 19; i++) {
				FieldBlockPosition[i] = { -90 + ((float)i * 10),-30,134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}

			for (int i = 19; i < 28; i++) {
				FieldBlockPosition[i] = { -330 + ((float)i * 10),30,134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}

			for (int i = 28; i < 38; i++) {
				FieldBlockPosition[i] = { -40,-340 + ((float)i * 10),134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}


			for (int i = 38; i < 40; i++) {
				FieldBlockPosition[i] = { -60,-360 + ((float)i * 10),134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}

			for (int i = 40; i < 50; i++) {
				FieldBlockPosition[i] = { -430 + ((float)i * 10),30,134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}

			/*for (int i = 50; i < 52; i++) {
				FieldBlockPosition[i] = { 10,-460 + ((float)i * 10),134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}*/

			for (int i = 52; i < 55; i++) {
				FieldBlockPosition[i] = { 60,-480 + ((float)i * 10),134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}

			for (int i = 55; i < 65; i++) {
				FieldBlockPosition[i] = { -550 + ((float)i * 10),0,134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}
			for (int i = 65; i < 75; i++) {
				FieldBlockPosition[i] = { 100,-710 + ((float)i * 10),134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}
			for (int i = 75; i < 77; i++) {
				FieldBlockPosition[i] = { 60,-660 + ((float)i * 10),134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}

			ItemPosition[0] = { -70,10,134 };
			ItemPosition[1] = { -60,10,134 };
			//ItemPosition[2] = { -100,40,134 };
			ItemPosition[3] = {  80,40,134 };
			ItemPosition[4] = {  50,10,134 };
			LightPosition[0] = { -50.0f, 33.0f ,134 };
			LightPosition[1] = { -130.0f, 20.0f ,134 };
			LightMoveNumber[0] = 3;
			AreaBlockPosition[0] = { -50.0f,30.0f,134.0f };
			AreaBlock[0]->SetPosition({ AreaBlockPosition[0] });
			for (int i = 1; i < 5; i++) {
				AreaBlockPosition[i] = { 60.0f + ((float)i * 10),30.0f,134.0f };
				AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
			}
			for (int i = 5; i < 10; i++) {
				AreaBlockPosition[i] = { -30.0f,-10.0f + ((float)i * 10),134.0f };
				AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
			}
			for (int i = 10; i < 16; i++) {
				AreaBlockPosition[i] = { 10.0f,-130.0f + ((float)i * 10),134.0f };
				AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
			}

			for (int i = 16; i < 18; i++) {
				AreaBlockPosition[i] = { 10.0f,-120.0f + ((float)i * 10),134.0f };
				AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
			}
			AreaPosition = { -130.0f,10.0f,134.0f };
			} 
		
			else if (StageNumber == 11) {
				GoalPosition = { 120.0f, 10.0f, 134.0f };
				PlayerPosition = { -110.0f,-60.0f,135.0f };
				for (int i = 0; i < 10; i++) {
					FieldBlockPosition[i] = { -135 + ((float)i * 10),-80,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 10; i < 13; i++) {
					FieldBlockPosition[i] = { 10 + ((float)i * 10),0,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 19; i < 28; i++) {
					FieldBlockPosition[i] = { -330 + ((float)i * 10),-50,134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 28; i < 42; i++) {
					FieldBlockPosition[i] = { -40,-360 + ((float)i * 10),134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 42; i < 44; i++) {
					FieldBlockPosition[i] = { -60,-480 + ((float)i * 10),134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}
				for (int i = 46; i < 51; i++) {
					FieldBlockPosition[46] = { -135.0f,-30.0f,134.0f };
					FieldBlockPosition[47] = { -50.0f,-30.0f,134.0f };
					FieldBlockPosition[48] = { -90.0f,-10.0f,134.0f };
					FieldBlockPosition[49] = { -135.0f,10.0f,134.0f };
					FieldBlockPosition[50] = { -50.0f,10.0f,134.0f };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 51; i < 65; i++) {
					FieldBlockPosition[i] = { 30,-560 + ((float)i * 10),134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 65; i < 74; i++) {
					FieldBlockPosition[i] = { 100,-730 + ((float)i * 10),134 };
					FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
				}

				for (int i = 0; i < 8; i++) {
					AreaBlockPosition[i] = { -130.0f + ((float)i * 10),-30.0f,134.0f };
					AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
				}
				for (int i = 8; i < 10; i++) {
					AreaBlockPosition[8] = { -90.0f,20.0f,134.0f };
					AreaBlockPosition[9] = { -80.0f,30.0f,134.0f };
					AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
				}
				for (int i = 10; i < 17; i++) {
					AreaBlockPosition[i] = { -140.0f + ((float)i * 10),50.0f,134.0f };
					AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
				}
				for (int i = 17; i < 30; i++) {
					AreaBlockPosition[i] = { -200.0f + ((float)i * 10),-80.0f,134.0f };
					AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
				}
				ItemPosition[0] = { -80,-70,134 };
				ItemPosition[1] = { -100,-40,134 };
				ItemPosition[2] = { -30,60,134 };
				ItemPosition[3] = { -20,60,134 };
				ItemPosition[4] = { -10,60,134 };
				ItemPosition[5] = { 0,60,134 };
				ItemPosition[6] = { 30,-70,134 };
				ItemPosition[7] = { 50,-70,134 };
				ItemPosition[8] = { 70,-70,134 };
				LightPosition[0] = { -130.0f, -60.0f ,134 };
				LightPosition[1] = { -125.0f, -30.0f ,134 };
				LightPosition[2] = { -90.0f, 20.0f ,134 };
				LightPosition[3] = { -100.0f, 10.0f ,134 };
				LightPosition[4] = { 30.0f, -30.0f ,134 };
				LightPosition[5] = { 30.0f, 10.0f ,134 };
				LightPosition[6] = { -10.0f, 20.0f ,134 };
				LightPosition[7] = { 70.0f, 10.0f ,134 };
				LightMoveNumber[1] = 4;
				LightMoveNumber[2] = 1;
				LightMoveNumber[3] = 3;
				LightMoveNumber[4] = 3;
				LightMoveNumber[5] = 4;
				LightMoveNumber[6] = 1;
				LightMoveNumber[7] = 2;
				LightMoveCount[1] = 20;
				LightMoveCount[2] = 70;
				LightMoveCount[3] = 50;
				AreaPosition = { -130.0f,-70.0f,134.0f };
			}

			else if (StageNumber == 12) {
			GoalPosition = { 110.0f,80.0f,134.0f };
			PlayerPosition = { -130.0f,60.0f,135.0f };
			for (int i = 0; i < 4; i++) {
				FieldBlockPosition[i] = { -135 + ((float)i * 10),40,134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}
			for (int i = 4; i < 15; i++) {
				FieldBlockPosition[i] = { -100,-100 + ((float)i * 10),134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}
			for (int i = 15; i < 30; i++) {
				FieldBlockPosition[i] = { -20,-190 + ((float)i * 10),134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}
			for (int i = 30; i < 32; i++) {
				FieldBlockPosition[i] = { -1280 + ((float)i * 40),-30,134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}
			for (int i = 32; i < 45; i++) {
				FieldBlockPosition[i] = { 90,-380 + ((float)i * 10),134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}
			for (int i = 45; i < 49; i++) {
				FieldBlockPosition[i] = { -360 + ((float)i * 10),70,134 };
				FieldBlock[i]->SetPosition({ FieldBlockPosition[i] });
			}

			ItemPosition[0] = { -110.0f,50.0f,134.0f };
			ItemPosition[1] = { -50.0f,-50.0f,134.0f };
			ItemPosition[2] = { -40.0f,-50.0f,134.0f };
			ItemPosition[3] = { -30.0f,-50.0f,134.0f };
			ItemPosition[4] = { -20.0f,-50.0f,134.0f };
			ItemPosition[5] = { -10.0f,-50.0f,134.0f };
			ItemPosition[6] = { 0.0f,-50.0f,134.0f };
			ItemPosition[7] = { 10.0f,-50.0f,134.0f };
			ItemPosition[8] = { 20.0f,-50.0f,134.0f };
			LightPosition[0] = { -80.0f, -58.0f ,134 };
			LightPosition[1] = { -40.0f, -20.0f ,134 };
			LightPosition[2] = { 45.0f, -20.0f ,134 };
			LightPosition[3] = { 35.0f, 20.0f ,134 };
			LightPosition[4] = { 45.0f, 40.0f ,134 };
			LightPosition[5] = { -120.0f, -55.0f ,134 };
			LightMoveNumber[0] = 1;
			LightMoveNumber[1] = 1;
			LightMoveNumber[2] = 3;
			LightMoveNumber[3] = 2;
			LightMoveNumber[4] = 4;
			LightMoveCount[0] = 10;
			LightMoveCount[1] = 70;
			LightMoveCount[2] = 50;
			LightMoveCount[3] = 50;
			LightMoveCount[4] = 50;
			for (int i = 0; i < 9; i++) {
				AreaBlockPosition[i] = { -100.0f,40.0f + ((float)i * 10),134.0f };
				AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
			}
			for (int i = 9; i < 28; i++) {
				AreaBlockPosition[i] = { -180.0f + ((float)i * 10),-60.0f,134.0f };
				AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
			}

			for (int i = 28; i < 37; i++) {
				AreaBlockPosition[i] = { -380.0f + ((float)i * 10),20.0f,134.0f };
				AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
			}
			/*	for (int i = 1; i < 5; i++) {
					AreaBlockPosition[i] = { 60.0f + ((float)i * 10),30.0f,134.0f };
					AreaBlock[i]->SetPosition({ AreaBlockPosition[i] });
				}*/
			AreaPosition = { -120.0f,-55.0f,134.0f };
			}
		
			ResetFlag = 0;
		}
#pragma endregion
#pragma region//Update
		for (int i = 0; i < _countof(SetBlock); i++) {
			SetBlock[i]->Update(matview);
			//ルートシグネチャの設定コマンド
			SetBlock[i]->SetPosition(SetBlockPosition[i]);
			SetBlock[i]->SetColor(SetBlockColor[i]);
		}

		for (int i = 0; i < _countof(ImageBlock); i++) {
			ImageBlock[i]->Update(matview);
			//ルートシグネチャの設定コマンド
			ImageBlock[i]->SetPosition(ImageBlockPosition[i]);
			ImageBlock[i]->SetColor(ImageBlockColor[i]);
		}

		for (int i = 0; i < _countof(MarkBlock); i++) {
			MarkBlock[i]->Update(matview);
			//ルートシグネチャの設定コマンド
			MarkBlock[i]->SetPosition(MarkBlockPosition[i]);
			MarkBlock[i]->SetColor(MarkBlockColor[i]);
		}

		for (int i = 0; i < _countof(FieldBlock); i++) {
			FieldBlock[i]->Update(matview);
		}

		for (int i = 0; i < _countof(AreaBlock); i++) {
			AreaBlock[i]->Update(matview);
		}

		for (int i = 0; i < Item_NUM; i++) {
			item[i]->Update(matview);
			item[i]->SetPosition(ItemPosition[i]);
		}

		for (int i = 0; i < Light_NUM; i++) {
			light[i]->SetPosition(LightPosition[i]);
			light[i]->Update(matview);
		}

		for (int i = 0; i < 2; i++) {
			gear[i]->SetRotaition(gearRota[i]);
			gear[i]->Update(matview);
		}
		//移動のやつ
		//カメラの注視点をプレイヤーの位置に固定
		target2.m128_f32[2] = 0;
		//カメラ追従用の処理
		target2.m128_f32[0] = 0;
		target2.m128_f32[1] = 0;
		//行列を作り直す
		rotM = XMMatrixRotationX(XMConvertToRadians(angle));
		XMVECTOR v;
		v = XMVector3TransformNormal(v0, rotM);
		eye2 = target2 + v;
		matview = XMMatrixLookAtLH((eye2), (target2), XMLoadFloat3(&up));
		background->Update();
		playerleftwalk->Update(matview);
		playerleftwalk2->Update(matview);
		playerleftwalk3->Update(matview);
		playerleftwalk4->Update(matview);
		playerJump->Update(matview);
		playerJumpLeft->Update(matview);
		playerrightwalk->Update(matview);
		playerrightwalk2->Update(matview);
		playerrightwalk3->Update(matview);
		playerrightwalk4->Update(matview);
		screen->Update(matview);
		projector->Update(matview);
		under->Update(matview);
		vinet->Update(matview);
		lever->Update(matview);
		goal->Update(matview);
		area->Update(matview);
		lightSource->Update(matview);
		playerleftwalk->SetPosition(PlayerPosition);
		playerleftwalk2->SetPosition(PlayerPosition);
		playerleftwalk3->SetPosition(PlayerPosition);
		playerleftwalk4->SetPosition(PlayerPosition);
		playerJump->SetPosition(PlayerPosition);
		playerJumpLeft->SetPosition(PlayerPosition);
		playerrightwalk->SetPosition(PlayerPosition);
		playerrightwalk2->SetPosition(PlayerPosition);
		playerrightwalk3->SetPosition(PlayerPosition);
		playerrightwalk4->SetPosition(PlayerPosition);
		screen->SetPosition({ 0,0,135 });
		projector->SetPosition({ 0,-20,-70 });
		under->SetPosition({ -32,135,150 });
		vinet->SetPosition({ 0,-60,-110 });
		lever->SetPosition(leverPos);
		lever->SetRotaition(leverRota);
		goal->SetPosition(GoalPosition);
		lightSource->SetPosition({ 0,0,190 });
		area->SetPosition(AreaPosition);
#pragma endregion
#pragma endregion
#pragma region//描画
		//描画コマンド
		dxCommon->PreDraw();
		////4.描画コマンドここから
		dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//ImGui::Begin("test");
		//if (ImGui::TreeNode("Debug"))
		//{
		//	if (ImGui::TreeNode("Film"))
		//	{
		//		ImGui::SliderFloat("Position.x", &SetBlockColor[0].w, 50, -50);
		//		ImGui::Text("HP,%d", PlayerHP);
		//		ImGui::Unindent();
		//		ImGui::TreePop();
		//	}

		//	//if (ImGui::TreeNode("Field"))
		//	//{
		//	//	ImGui::SliderFloat("Position.x", &ImageBlockPosition[0].x, 50, -50);
		//	//	ImGui::SliderFloat("Position.y", &ImageBlockPosition[0].y, 50, -50);
		//	//	ImGui::SliderFloat("JumpG", &JumpG, 50, -50);
		//	//	ImGui::Unindent();
		//	//	ImGui::TreePop();
		//	//}
		//	ImGui::TreePop();
		//}
		//ImGui::End();
		//背景スプライト描画前処理
		Sprite::PreDraw(dxCommon->GetCmdList());
		Sprite::PostDraw();
		Block::PreDraw(dxCommon->GetCmdList());
		RealBlock::PreDraw(dxCommon->GetCmdList());
		PlayerLeftWalk::PreDraw(dxCommon->GetCmdList());
		PlayerLeftWalk2::PreDraw(dxCommon->GetCmdList());
		PlayerLeftWalk3::PreDraw(dxCommon->GetCmdList());
		PlayerLeftWalk4::PreDraw(dxCommon->GetCmdList());
		PlayerJump::PreDraw(dxCommon->GetCmdList());
		PlayerJumpLeft::PreDraw(dxCommon->GetCmdList());
		PlayerRightWalk::PreDraw(dxCommon->GetCmdList());
		PlayerRightWalk2::PreDraw(dxCommon->GetCmdList());
		PlayerRightWalk3::PreDraw(dxCommon->GetCmdList());
		PlayerRightWalk4::PreDraw(dxCommon->GetCmdList());
		Light::PreDraw(dxCommon->GetCmdList());
		BackGround::PreDraw(dxCommon->GetCmdList());
		Screen::PreDraw(dxCommon->GetCmdList());
		Projector::PreDraw(dxCommon->GetCmdList());
		Under::PreDraw(dxCommon->GetCmdList());
		Vinet::PreDraw(dxCommon->GetCmdList());
		Lever::PreDraw(dxCommon->GetCmdList());
		Gear::PreDraw(dxCommon->GetCmdList());
		Goal::PreDraw(dxCommon->GetCmdList());
		Area::PreDraw(dxCommon->GetCmdList());
		LightSource::PreDraw(dxCommon->GetCmdList());
		Item::PreDraw(dxCommon->GetCmdList());
		vinet->Draw();
		if ((Scene == appearance) || (Scene == gamePlay)) {
			//スクリーン関係
			screen->Draw();
			under->Draw();
			if ((mode == 1) || (LightFlag == 1) && (LightCount != 80)) {
				lightSource->Draw();
			}
	
			//プロジェクター関係
	
			projector->Draw();
			lever->Draw();
			for (int i = 0; i < 2; i++) {
				gear[i]->Draw();
			}
			if (LightFlag == 1) {
				//プレイヤー
				if (AnimetionCount == 0) {
					if (PlayerDirectionNumber == 0) {
						playerrightwalk->Draw();
					} else if (PlayerDirectionNumber == 1) {
						playerleftwalk->Draw();
					}
				} else if (AnimetionCount == 1) {
					if (PlayerDirectionNumber == 0) {
						playerrightwalk2->Draw();
					} else if (PlayerDirectionNumber == 1) {
						playerleftwalk2->Draw();
					}
				} else if (AnimetionCount == 2) {
					if (PlayerDirectionNumber == 0) {
						playerrightwalk3->Draw();
					} else if (PlayerDirectionNumber == 1) {
						playerleftwalk3->Draw();
					}
				} else if (AnimetionCount == 3) {
					if (PlayerDirectionNumber == 0) {
						playerrightwalk4->Draw();
					} else if (PlayerDirectionNumber == 1) {
						playerleftwalk4->Draw();
					}
				}
				for (int i = 0; i < _countof(FieldBlock); i++) {
					FieldBlock[i]->Draw();
				}
			}
		}
		//背景
		if (Scene == gamePlay) {
			if (AnimetionCount == 0 && JumpFlag == 0) {
				if (PlayerDirectionNumber == 0) {
					playerrightwalk->Draw();
				} else if (PlayerDirectionNumber == 1) {
					playerleftwalk->Draw();
				}
			} else if (AnimetionCount == 1 && JumpFlag == 0) {
				if (PlayerDirectionNumber == 0) {
					playerrightwalk2->Draw();
				} else if (PlayerDirectionNumber == 1) {
					playerleftwalk2->Draw();
				}
			} else if (AnimetionCount == 2 && JumpFlag == 0) {
				if (PlayerDirectionNumber == 0) {
					playerrightwalk3->Draw();
				} else if (PlayerDirectionNumber == 1) {
					playerleftwalk3->Draw();
				}
			} else if (AnimetionCount == 3&&JumpFlag==0) {
				if (PlayerDirectionNumber == 0) {
					playerrightwalk4->Draw();
				} else if (PlayerDirectionNumber == 1) {
					playerleftwalk4->Draw();
				}
			}
			else if (PlayerDirectionNumber == 0 && JumpFlag == 1) {
				playerJump->Draw();
			}
			else if (PlayerDirectionNumber == 1 && JumpFlag == 1) {
				playerJumpLeft->Draw();
			}

			//アイテム
			for (int i = 0; i < Item_NUM; i++) {
				if (ItemAlive[i] == 1) {
					item[i]->Draw();
				}
			}
			//ゴール
			goal->Draw();
			//スイッチ
			area->Draw();
			for (int i = 0; i < _countof(light); i++) {
				light[i]->Draw();
			}
			//ブロック
			for (int i = 0; i < _countof(FieldBlock); i++) {
				FieldBlock[i]->Draw();
			}
			for (int i = 0; i < _countof(SetBlock); i++) {
				if (SetFlag[i] == 1) {
					if (SetBlockColor[i].w > 0.0f) {
						SetBlock[i]->Draw();
					}
				} else if ((SetFlag[i] == 0) && (mode == 1) && (ItemCount != 0)) {
					MarkBlock[i]->Draw();
				}
			}

			for (int i = 0; i < _countof(AreaBlock); i++) {
				AreaBlock[i]->Draw();
			}

			if (mode == 1) {
				for (int i = 0; i < Block_NUM; i++) {
					if (SetBlockColor[i].w > 0.0f) {
						ImageBlock[i]->Draw();
					}
				}
				lightSource->Draw();
			}
		}

		Sprite::PreDraw(dxCommon->GetCmdList());
		if (Scene == title) {
			sprite[0]->Draw();
		}
		else if (Scene == explation) {
			if (ExplanationNumber == 0) {
				sprite[6]->Draw();
			} else {
				sprite[7]->Draw();
			}
		}
		else if (Scene == gamePlay) {
			
			if (modeflag == 1 && mode == 0) {
				sprite[13]->Draw();
				sprite[14]->Draw();
			}

			if (SceneCutFlag == 0) {
				if (StageNumber == 1) {
					//sprite[8]->Draw();
					if (TextNumber == 0) {
						sprite[9]->Draw();
					} else if (TextNumber == 1) {
						sprite[10]->Draw();
					} else if (TextNumber == 2) {
						sprite[11]->Draw();
					} else {
						sprite[12]->Draw();
					}
				} else if (StageNumber == 2) {
					sprite[22]->Draw();
				} else if (StageNumber == 4) {
					sprite[15]->Draw();
				} else if (StageNumber == 7) {
					sprite[16]->Draw();
				}
				sprite[2]->Draw();
				spriteNumber[ItemCount]->Draw();
				if (PlayerHP > 180) {
					sprite[17]->Draw();
				} else if ((PlayerHP <= 180) && (PlayerHP > 120)) {
					sprite[18]->Draw();
				} else if ((PlayerHP <= 120) && (PlayerHP > 60)) {
					sprite[19]->Draw();
				} else if ((PlayerHP <= 60) && (PlayerHP > 0)) {
					sprite[20]->Draw();
				} else {
					sprite[21]->Draw();
				}
			}
			else if (SceneCutFlag == 1) {
				SpriteSceneCut[CutCount]->Draw();
				SpriteSceneCutNumber[StageNumber - 1]->Draw();
			}
		}

		else if (Scene == stageClear) {
			sprite[3]->Draw();
		}

		else if (Scene == gameClear) {
			sprite[4]->Draw();
		}

		else if (Scene == gameOver) {
			sprite[5]->Draw();
		}
		Sprite::PostDraw();
		// 3Dオブジェクト描画後処理
		Block::PostDraw();
		RealBlock::PostDraw();
		PlayerLeftWalk::PostDraw();
		PlayerLeftWalk2::PostDraw();
		PlayerLeftWalk3::PostDraw();
		PlayerLeftWalk4::PostDraw();
		PlayerJump::PostDraw();
		PlayerJumpLeft::PostDraw();
		PlayerRightWalk::PostDraw();
		PlayerRightWalk2::PostDraw();
		PlayerRightWalk3::PostDraw();
		PlayerRightWalk4::PostDraw();
		Light::PostDraw();
		BackGround::PostDraw();
		Screen::PostDraw();
		Projector::PostDraw();
		Under::PostDraw();
		Vinet::PostDraw();
		Lever::PostDraw();
		Gear::PostDraw();
		Goal::PostDraw();
		LightSource::PostDraw();
		Area::PostDraw();
		Item::PostDraw();
		dxCommon->PostDraw();
	}
#pragma endregion
#pragma endregion
#pragma region//開放処理
	winApp->Finalize();
	for (int i = 0; i < SpriteMax; i++) {
		delete sprite[i];
	}
	//入力開放
	delete input;
	delete audio;
	delete winApp;
	delete dxCommon;
	delete playerleftwalk;
	delete playerleftwalk2;
	delete playerleftwalk3;
	delete playerleftwalk4;
	delete playerJump;
	delete playerJumpLeft;
	delete playerrightwalk;
	delete playerrightwalk2;
	delete playerrightwalk3;
	delete playerrightwalk4;
	for (int i = 0; i < Light_NUM; i++) {
		delete light[i];
	}
	for (int i = 0; i < Item_NUM; i++) {
		delete item[i];
	}
	for (int i = 0; i < 2; i++) {
		delete gear[i];
	}
	delete screen;
	delete projector;
	delete under;
	delete vinet;
	delete lever;
	delete lightSource;
	delete goal;
	delete area;
	for (int i = 0; i < _countof(ImageBlock); i++) {
		delete ImageBlock[i];
	}
	for (int i = 0; i < _countof(MarkBlock); i++) {
		delete MarkBlock[i];
	}

	for (int i = 0; i < _countof(SetBlock); i++) {
		delete SetBlock[i];
	}
	for (int i = 0; i < _countof(FieldBlock); i++) {
		delete FieldBlock[i];
	}
	for (int i = 0; i < _countof(AreaBlock); i++) {
		delete AreaBlock[i];
	}
	winApp = nullptr;
	return 0;
#pragma endregion
}
#pragma endregion