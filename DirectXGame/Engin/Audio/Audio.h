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

//�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
struct ConstBufferDataMaterial {
	Vector4 color;//�F(RGBA)
};

//�萔�o�b�t�@�p�f�[�^�\����(3D�ϊ��s��)
struct ConstBufferDataTransform {
	Matrix4 mat; //3D�ϊ��s��
};

// �`�����N�w�b�_
struct ChunkHeader
{
	char id[4]; // �`�����N�O��ID
	int32_t size; // �`�����N�T�C�Y
};

// RIFF�w�b�_�`�����N
struct RiffHeader
{
	ChunkHeader chunk; // "RIFF"
	char type[4]; // "WAVE"
};

// FMT�`�����N
struct FormatChunk {
	ChunkHeader chunk; // "fmt"
	WAVEFORMATEX fmt; // �g�`�t�H�[�}�b�g
};

// �����f�[�^
struct SoundData {
	// �g�`�t�H�[�}�b�g
	WAVEFORMATEX wfex;
	// �o�b�t�@�̐擪�A�h���X
	BYTE* pBuffer;
	// �o�b�t�@�̃T�C�Y
	unsigned int bufferSize;
};

// =============
// �I�[�f�B�I�N���X
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

	// �C���X�^���X�𐶐�
	static Audio* GetInstance();

	// ������
	void Initialize(const std::string& directoryPath = "Resources/sound/");
	// ���
	void Finalize();
	/// �����f�[�^�̓ǂݍ���
	void LoadWave(const std::string& filename);
	/// �����f�[�^���
	void Unload(SoundData* soundData);
	/// �����Đ�
	void PlayWave(const std::string& filename);
	/// �����̃��[�v�Đ�
	void LoopPlayWave(const std::string& filename);
	/// ������~
	void StopWave(const std::string& filename);
	/// ���ʒ���
	void SetVolume(const std::string& filename, float volume);

public:
	IXAudio2* GetxAudio2() { return xAudio2.Get(); }
	float GetVolume()const { return mVolume; }

private:
	HRESULT result;
	ComPtr<IXAudio2> xAudio2; // XAudio2�C���^�[�t�F�C�X
	IXAudio2MasteringVoice* mVoice; // �}�X�^�[�{�C�X
	IXAudio2SourceVoice* sVoice; // �\�[�X�{�C�X
	XAUDIO2_BUFFER buf{};

	// �T�E���h�f�[�^�̘A�z�z��
	std::map<std::string, SoundData> soundDatas_;
	// �T�E���h�i�[�f�B���N�g��
	std::string directoryPath_;

	float mVolume;
};

