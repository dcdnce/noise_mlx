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

static inline float	interpolation(const float x) {
	int	xMin = (int)x;
	int	xMax = xMin + 1;
	xMax &= D_kMaxVerticesMask;
	//if (xMin == D_kMaxVertices)
	//	xMax = 0;
	float	t = x - xMin;
	t = (1 - cos(t * M_PI)) * 0.5; // cos curve
	return (lerp(g_n.r[xMin], g_n.r[xMax], t));
}

/**
 * @brief Main loop of the noise1D tool.
 * 
 */
void	noise1D(int seed)
{
	valueNoise1D(seed);

	const int	numSteps = W;

	t_vec2f		a = {0};
	t_vec2f		v = {0};
	t_vec2f		v_old = {0};
	int			color = ft_create_trgb(0, 50, 100, 255);

	//Main loop
	for (int i = 0 ; i < numSteps; ++i) {
		a.x = (float)i / ((float)numSteps - 1) * D_kMaxVertices;

		float	scale = 100.0f;
		float	frequency = 0.03125f;

		const int numLayers = 5;
		a.y = 0;
		for (int j = 0 ; j < numLayers ; j++) {
			a.y += interpolation(a.x * frequency) * scale;
			frequency *= 2;
			scale *= 0.5f;
		}

		v_old = v;
		/* V.X RENDERING */
		v.x = i * (W / numSteps);  //fullscreen
		/* V.Y RENDERING */
		v.y = H / 2 - a.y;
		if (v_old.x + v_old.y != 0)
			dda(v_old, v, 2, color);
	}
}
