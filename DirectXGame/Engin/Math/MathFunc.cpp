#include "MathFunc.h"

float MathFunc::easeInSine(float a)
{ 
	const double PI = 3.141592;
	return 1 - cos((a * PI) / 2);
}

float MathFunc::easeOutSine(float a)
{
	const double PI = 3.141592;
	return sin((a * PI) / 2);
}

float MathFunc::easeInOutSine(float a)
{
	const double PI = 3.141592;
	return cos((PI * a) - 1) / 2;
}
