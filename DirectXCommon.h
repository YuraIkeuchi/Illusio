#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include<wrl.h>
#include <d3dx12.h>
#include<cstdlib>
#include <imgui.h>
#include "WinApp.h"

//DirectX�ėp
class DirectXCommon
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public:

	void Finalize();
	//������
	void Initialize(WinApp* winApp);

	//�`��O����
	void PreDraw();

	//�`��㏈��
	void PostDraw();

	//�f�o�C�X������
	bool InitializeDevice();

	//�X���b�v�`�F�[������
	bool CreateSwapChain();

	//�R�}���h�֘A������
	bool InitializeCommand();

	//�����_�[�^�[�Q�b�g����
	bool InitializeRenderTargetView();

	//�[�x�o�b�t�@����
	bool InitializeDepthBuffer();

	//�t�F���X����
	bool CreateFence();

	//Imgui������
	bool InitImgui();

	ID3D12Device* GetDev() { return dev.Get(); }

	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }
private:
	//�����o�ϐ�
		// Direct3D�֘A
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<ID3D12Device> dev;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<IDXGISwapChain4> swapchain;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
	ComPtr<ID3D12DescriptorHeap> imguiHeap;
	WinApp* winApp = nullptr;
};