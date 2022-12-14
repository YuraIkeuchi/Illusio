#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

/// 3Dオブジェクト
class PlayerJumpLeft {
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	// 頂点データ構造体
	struct VertexPosNormalUv {
		XMFLOAT3 pos; // xyz座標
		XMFLOAT3 normal; // 法線ベクトル
		XMFLOAT2 uv;  // uv座標
	};

	// 定数バッファ用データ構造体
	struct ConstBufferData {
		XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
	};

private: // 定数
	static const int division = 50;					// 分割数
	static const float radius;				// 底面の半径
	static const float prizmHeight;			// 柱の高さ
	static const int planeCount = division * 2 + division * 2;		// 面の数
	static const int vertexCount = planeCount * 3;		// 頂点数

public: // 静的メンバ関数
	/// 静的初期化
	static bool StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	/// 描画前処理
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// 描画後処理
	static void PostDraw();

	/// 3Dオブジェクト生成
	static PlayerJumpLeft* Create();

	/// 視点座標の取得
	static const XMFLOAT3& GetEye() { return eye; }

	/// 視点座標の設定
	static void SetEye(XMFLOAT3 eye);

	/// 注視点座標の取得
	static const XMFLOAT3& GetTarget() { return target; }

	/// 注視点座標の設定
	static void SetTarget(XMFLOAT3 target);

	/// ベクトルによる移動
	static void CameraMoveVector(XMFLOAT3 move);

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	// デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// デスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// 頂点バッファ
	static ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	static ComPtr<ID3D12Resource> indexBuff;
	// テクスチャバッファ
	static ComPtr<ID3D12Resource> texbuff;
	// シェーダリソースビューのハンドル(CPU)
	static CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	static CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// ビュー行列
	static XMMATRIX matView;
	// 射影行列
	static XMMATRIX matProjection;
	// 視点座標
	static XMFLOAT3 eye;
	// 注視点座標
	static XMFLOAT3 target;
	// 上方向ベクトル
	static XMFLOAT3 up;
	// 頂点バッファビュー
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	static D3D12_INDEX_BUFFER_VIEW ibView;
	// 頂点データ配列
	static VertexPosNormalUv vertices[vertexCount];
	static unsigned short indices[planeCount * 3];
private:// 静的メンバ関数
	/// デスクリプタヒープの初期化
	static bool InitializeDescriptorHeap();

	/// カメラ初期化
	static void InitializeCamera(int window_width, int window_height);

	/// グラフィックパイプライン生成
	static bool InitializeGraphicsPipeline();

	/// テクスチャ読み込み
	static bool LoadTexture();

	/// モデル作成
	static void CreateModel();

	/// ビュー行列を更新
	static void UpdateViewMatrix();

public: // メンバ関数
	bool Initialize();
	/// 毎フレーム処理
	void Update(XMMATRIX& matView);

	/// 描画
	void Draw();
	// bool collide(EnemyBullet *enebullet);
	/// 座標の取得
	const XMFLOAT3& GetPosition() { return position; }
	const XMFLOAT3& GetRotaition() { return rotation; }
	const int& GetHitFlag() { return HitFlag; }
	const int& GetDamageCount() { return damageCount; }

	const int& GetHp() { return hp; }

	/// 座標の設定
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	void SetRotaition(XMFLOAT3 rotaition) { this->rotation = rotaition; }
	void SetHitFlag(int HitFlag) { this->HitFlag = HitFlag; }
	void SetHp(int hp) { this->hp = hp; }
	//カメラをその位置に移動させる処理
	static void SetCameraPosition(XMFLOAT3 position, XMFLOAT3 targetposition);
private: // メンバ変数
	ComPtr<ID3D12Resource> constBuff; // 定数バッファ
	float speed = 0.2f;
	int HitFlag = 0;
	int hp = 5;
	int damageCount = 0;
	// 色
	XMFLOAT4 color = { 1,1,1,1 };
	// ローカルスケール
	XMFLOAT3 scale = { 0.5f,0.5f,0 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,20,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,20,135 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	// 親オブジェクト
	PlayerJumpLeft* parent = nullptr;
};
