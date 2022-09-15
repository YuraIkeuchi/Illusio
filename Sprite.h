#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>


/// �X�v���C�g

class Sprite
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �T�u�N���X

	/// ���_�f�[�^�\����
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT2 uv;  // uv���W
	};


	/// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		XMFLOAT4 color;	// �F (RGBA)
		XMMATRIX mat;	// �R�c�ϊ��s��
	};

public: // �ÓI�����o�֐�
	static bool StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	/// �e�N�X�`���ǂݍ���
	static bool LoadTexture(UINT texnumber, const wchar_t* filename);


	/// �`��O����
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);


	/// �`��㏈��
	static void PostDraw();

	/// �X�v���C�g����
	static Sprite* Create(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1, 1, 1, 1 }, XMFLOAT2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);

private: // �ÓI�����o�ϐ�
	// �e�N�X�`���̍ő喇��
	static const int srvCount = 512;
	// ���_��
	static const int vertNum = 4;
	static ID3D12Device* device;
	static UINT descriptorHandleIncrementSize;
	static ID3D12GraphicsCommandList* cmdList;
	static ComPtr<ID3D12RootSignature> rootSignature;
	static ComPtr<ID3D12PipelineState> pipelineState;
	static XMMATRIX matProjection;
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	static ComPtr<ID3D12Resource> texBuff[srvCount];

public: // �����o�֐�
	/// �R���X�g���N�^
	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);

	/// ������
	bool Initialize();

	/// �p�x�̐ݒ�
	void SetRotation(float rotation);

	/// ���W�̐ݒ�
	void SetPosition(XMFLOAT2 position);

	/// ���W�̎擾
	const XMFLOAT2& GetPosition() { return position; }

	/// �T�C�Y�̐ݒ�
	void SetSize(XMFLOAT2 size);

	/// �J���[�̐ݒ�
	void Sprite::SetColor(XMFLOAT4 color);

	/// �A���J�[�|�C���g�̐ݒ�
	void SetAnchorPoint(XMFLOAT2 anchorpoint);


	/// ���E���]�̐ݒ�
	void SetIsFlipX(bool isFlipX);

	/// �㉺���]�̐ݒ�
	void SetIsFlipY(bool isFlipY);

	/// �e�N�X�`���͈͐ݒ�
	void SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize);

	/// �`��
	void Draw();

private: // �����o�ϐ�
	ComPtr<ID3D12Resource> vertBuff;
	ComPtr<ID3D12Resource> constBuff;
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	UINT texNumber = 0;
	float rotation = 0.0f;
	XMFLOAT2 position{};
	XMFLOAT2 size = { 100.0f, 100.0f };
	XMFLOAT2 anchorpoint = { 0, 0 };
	XMMATRIX matWorld{};
	// �F
	XMFLOAT4 color = { 1, 1, 1, 1 };
	// ���E���]
	bool isFlipX = false;
	// �㉺���]
	bool isFlipY = false;
	// �e�N�X�`���n�_
	XMFLOAT2 texBase = { 0, 0 };
	// �e�N�X�`�����A����
	XMFLOAT2 texSize = { 100.0f, 100.0f };

private: // �����o�֐�
	/// ���_�f�[�^�]��
	void TransferVertices();
};