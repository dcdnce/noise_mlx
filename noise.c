#include "noise.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	valueNoise1D(long seed) {
	srand48(seed);
	for (int i = 0 ; i < D_kMaxVertices ; i++) {
		g_n.r[i] = drand48();
	}
}

float	lerp(const float lo, const float hi, const float t) {
	return (lo * (1 - t) + hi * t);
}

float	eval(const float x) {
	int	xMin = (int)x;
	int	xMax = xMin + 1;
	if (xMin == D_kMaxVertices - 1)
		xMax = 0;
	float	t = x - xMin;
	return (lerp(g_n.r[xMin], g_n.r[xMax], t));
}