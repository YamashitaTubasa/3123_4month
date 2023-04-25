#include "Line.hlsli"

VSOutput main(float4 pos : POSITION)
{
	VSOutput output; // ピクセルシェーダーに渡す値
	output.svpos = mul(mul(mul(projection, view), matWorld), pos);
	return output;
}