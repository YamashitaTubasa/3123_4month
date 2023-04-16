#include "Line.hlsli"
//float4 main(float4 pos : POSITION) : SV_POSITION
//{
//    return pos/* * float4(2,2,1,1)*/;
//}

//-----04_01_UVç¿ïW-----//
VSOutput main(float4 pos : POSITION, float2 uv : TEXCOORD) {
	VSOutput output;
	output.svpos = pos;
	output.uv = uv;
	return output;
}




