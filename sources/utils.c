#include "noise.h"

float	lerp(const float lo, const float hi, const float t) {
	return (lo * (1 - t) + hi * t);
}