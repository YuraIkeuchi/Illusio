#pragma once

#include <Windows.h>
#include <xaudio2.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>

//オーディオのコールバック
class XAudio2VoiceCallBack : public IXAudio2VoiceCallback {
public:
	void OnVoiceProcessingPassStart(UINT32 BytesRequired) {};
	// ボイス処理パスの終了時
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
	//バッファストリームの再生終了時
	STDMETHOD_(void, OnStreamEnd) (THIS) {};

	//バッファの使用次
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};
	//バッファの末尾に達したとき
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext) {
		delete[] pBufferContext;//バッファ開放
	};
	//ループの達したとき
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
	//ボイスのエラー時
	STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
};

class Audio {
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//構造体の定義
	//チャンクヘッダ
	struct ChunkHeader
	{
		char id[4];//チャンク毎のID
		int32_t size;//チャンクサイズ
	};

	//RIFFヘッダチャンク
	struct RiffHeader
	{
		ChunkHeader chunk;//RIFF
		char type[4];//WAVE
	};
	
	//FMTチャンク
	struct FormatChunk
	{
		ChunkHeader chunk;//fmt
		WAVEFORMAT fmt;//波形フォーマット
	};

public://メンバ関数

	//初期化
	bool Initialize();

	//サウンドファイルの読み込み
	void LoadSound(int texnumber, const char* filename);
	//サウンドの再生
	void PlayWave(const char* filename,const float Volume);
	//サウンドのループ
	void LoopWave(int texnumber, float Volume);
	//サウンドの停止
	void StopWave(int texnumber);

private://メンバ変数
	static const int SrvCount = 50;
	int texNumber = 0;
	RiffHeader riff[SrvCount] = {};
	FormatChunk format[SrvCount] = {};
	ChunkHeader data[SrvCount] = {};
	char* pBuffer[SrvCount] = {};
	WAVEFORMATEX wfex[SrvCount]{};
	IXAudio2SourceVoice* pSourceVoice[SrvCount] = { nullptr };
	XAUDIO2_BUFFER buf[SrvCount]{};
	char fileStamp[SrvCount][50]{};
	ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;
	 XAudio2VoiceCallBack voiceCallback;
};