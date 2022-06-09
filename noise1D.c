#include "noise.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

static inline void	valueNoise1D(long seed) {
	srand48(seed);
	for (int i = 0 ; i < D_kMaxVertices ; i++) {
		g_n.r[i] = drand48();
	}
}

static inline float	eval(const float x) {
	int	xMin = (int)x;
	int	xMax = xMin + 1;
	//xMax &= D_kMaxVerticesMask;
	if (xMin == D_kMaxVertices)
		xMax = 0;
	float	t = x - xMin;
	t = (1 - cos(t * M_PI)) * 0.5; // cos curve
	return (lerp(g_n.r[xMin], g_n.r[xMax], t));
}

void	noise1D(void) {
	valueNoise1D(2011);

	const int	amplitude = 50;
	const float	frequency = 0.5f;
	const int	numSteps = W / 4;

	t_vec2f		a = {0};
	t_vec2f		v = {0};
	t_vec2f		v_old = {0};
	int			color = ft_create_trgb(0, 50, 100, 255);

	for (int i = 0 ; i < numSteps; ++i) {
		a.x = ((float)i / ((float)numSteps - 1) * D_kMaxVertices);
		a.y = eval(a.x * frequency);

		v_old = v;

		/* V.X RENDERING */
		v.x = a.x;
		
		/* V.Y RENDERING */
		v.y = (H + amplitude) / 2 - a.y * amplitude;

		if (v_old.x + v_old.y != 0)
			dda(v_old, v, 2, color);
		//pixelPut(&g_n.img, v.x, v.y, color, 10);
	}
}
