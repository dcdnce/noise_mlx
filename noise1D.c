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
	xMax &= D_kMaxVerticesMask;
	float	t = x - xMin;
	t = (1 - cos(t * M_PI)) * 0.5; // cos curve
	return (lerp(g_n.r[xMin], g_n.r[xMax], t));
}

void	noise1D(void) {
	valueNoise1D(2011);

	const int	amplitude = 20;
	const int	numSteps = W / 2;
	t_vec2f		a = {0};
	t_vec2f		v = {0};
	t_vec2f		v_old = {0};
	int			color;
	color = ft_create_trgb(0, 50, 100, 255);

	for (int j = 0 ; j < 2; j++) {
		for (int i = 0 ; i < numSteps; ++i) {
			a.x = ((float)i / ((float)numSteps - 1) * D_kMaxVertices);
			a.y = eval(a.x);

			v_old = v;
			//v.x = (i * W / numSteps); // fullscreen
			v.x = i + (numSteps * j);
			v.y = (H + amplitude) / 2 - a.y * amplitude;
			if (v_old.x + v_old.y != 0)
				dda(v_old, v, 2, color);
			//pixelPut(&g_n.img, v.x, v.y, color, 10);
		}
		color = ft_create_trgb(0, 255, 0, 55);
	}
}