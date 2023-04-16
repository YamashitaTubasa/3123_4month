#include "Line.hlsli"

//float4 main() : SV_TARGET
//{
//	return color;
//}

//-----04_01_UVÀ•W-----//
float4 main(VSOutput input) : SV_TARGET
{
	return float4(input.uv,0,1);
}

