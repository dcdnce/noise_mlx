#include "noise.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

static inline void	valueNoise2D(long seed) { 
	srand48(seed);
	for (int i = 0 ; i < D_kMaxVertices * D_kMaxVertices ; i++) {
		g_n.r2[i] = drand48();
	}
}

static inline void	eval(const t_vec2f v) {
	int	xMin = (int)v.x;
	int	yMin = (int)v.y;

	float	tx = v.x - xMin;
	float	ty = v.y - yMin;
}