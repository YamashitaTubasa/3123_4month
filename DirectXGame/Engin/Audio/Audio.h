#pragma once

#include <xaudio2.h>
#include <fstream>
#include <wrl.h>
#include <DirectXMath.h>
#include <map>
#include <string>
#include "Matrix4.h"
#include "Vector4.h"

#pragma comment(lib, "xaudio2.lib")

//定数バッファ用データ構造体(マテリアル)
struct ConstBufferDataMaterial {
	Vector4 color;//色(RGBA)
};

//定数バッファ用データ構造体(3D変換行列)
struct ConstBufferDataTransform {
	Matrix4 mat; //3D変換行列
};

// チャンクヘッダ
struct ChunkHeader
{
	char id[4]; // チャンク前のID
	int32_t size; // チャンクサイズ
};

// RIFFヘッダチャンク
struct RiffHeader
{
	ChunkHeader chunk; // "RIFF"
	char type[4]; // "WAVE"
};

// FMTチャンク
struct FormatChunk {
	ChunkHeader chunk; // "fmt"
	WAVEFORMATEX fmt; // 波形フォーマット
};

// 音声データ
struct SoundData {
	// 波形フォーマット
	WAVEFORMATEX wfex;
	// バッファの先頭アドレス
	BYTE* pBuffer;
	// バッファのサイズ
	unsigned int bufferSize;
};

// =============
// オーディオクラス
// =============
class Audio final
{
public:
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	Audio() = default;
	~Audio() = default;

public:
	Audio(const Audio& obj) = delete;
	Audio& operator=(const Audio& obj) = delete;

	// インスタンスを生成
	static Audio* GetInstance();

	// 初期化
	void Initialize(const std::string& directoryPath = "Resources/sound/");
	// 解放
	void Finalize();
	/// 音声データの読み込み
	void LoadWave(const std::string& filename);
	/// 音声データ解放
	void Unload(SoundData* soundData);
	/// 音声再生
	void PlayWave(const std::string& filename);
	/// 音声のループ再生
	void LoopPlayWave(const std::string& filename);
	/// 音声停止
	void StopWave(const std::string& filename);
	/// 音量調節
	void SetVolume(const std::string& filename, float volume);

public:
	IXAudio2* GetxAudio2() { return xAudio2.Get(); }
	float GetVolume()const { return mVolume; }

private:
	HRESULT result;
	ComPtr<IXAudio2> xAudio2; // XAudio2インターフェイス
	IXAudio2MasteringVoice* mVoice; // マスターボイス
	IXAudio2SourceVoice* sVoice; // ソースボイス
	XAUDIO2_BUFFER buf{};

	// サウンドデータの連想配列
	std::map<std::string, SoundData> soundDatas_;
	// サウンド格納ディレクトリ
	std::string directoryPath_;

	float mVolume;
};

