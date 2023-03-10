#pragma once

#include "DirectXCommon.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <string>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

//==================//
// スプライト共通部 //
//==================//
class SpriteCommon final
{
public:
	void Initialize();

public:
	static SpriteCommon* Instance();

private:
	SpriteCommon() = default;
	~SpriteCommon() = default;
	SpriteCommon(const SpriteCommon&) = delete;
	SpriteCommon& operator=(const SpriteCommon&) = delete;

private:
	ComPtr<ID3D12Device> device;
	ComPtr<ID3D12Resource> vertBuff;
};