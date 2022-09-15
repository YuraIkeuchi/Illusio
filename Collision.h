#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

class Collision {
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	//当たり判定関数
	bool BoxCollision_Down(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2);

	bool BoxCollision_Up(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2);

	bool BoxCollision_Left(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2);

	bool BoxCollision_Right(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2);

	bool CircleCollision(const float& X1, const float& Y1, const float& R1, const float& X2, const float& Y2, const float& R2);
};