#include "noise.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

static inline void	printSquares(void) {
	t_vec2f	v1;
	t_vec2f	v2;
	for (int i = 1 ; i <= D_kMaxVertices ; i++) {
		v1.y = H / D_kMaxVertices * i;
		v2.y = H / D_kMaxVertices * i;
		v1.x = 0; 
		v2.x = W; 
		dda(v1, v2, 1, 0xffff0000);
		v1.x = v1.y;
		v2.x = v2.y;
		v1.y = 0;
		v2.y = H;
		dda(v1, v2, 1, 0xffff0000);
	}
}

static inline float pSmoothstep(float t) {
	return (t * t * (3 - 2 * t));
}

static inline void	valueNoise2D(long seed) { 
	srand48(seed);
	for (int i = 0 ; i < D_kMaxVertices * D_kMaxVertices ; i++) {
		g_n.r2[i] = drand48();
	}
}

static inline float	eval(const t_vec2f v) {
	//get c00 / c10
	//get c01 / c11
	int	c00 = (int)v.x + (int)v.y * (int)D_kMaxVertices;
	if (c00 >= D_kMaxVertices * D_kMaxVertices)
		c00 = 0;
	int	c10 = c00 + 1;
	int c01 = c00 + D_kMaxVertices;
	int	c11 = c10 + D_kMaxVertices;

	
	//get nx0 and nx1
	float tx = v.x - (int)v.x;
	tx = pSmoothstep(tx);
	float nx0 = lerp(g_n.r2[c00], g_n.r2[c10], tx);
	float nx1 = lerp(g_n.r2[c01], g_n.r2[c11], tx);

	//return pnoise
	float ty = v.y - (int)v.y;
	ty = pSmoothstep(ty);
	float pNoise = lerp(nx0, nx1, ty);
	return (pNoise);
}

void	noise2D(void) {
	valueNoise2D(1998);

	
	t_vec2f		v = {0};
	const int 	numSteps = H;
	int 		color = 0xff000000;
	float 		noiseValueMax = 0;
	float		noiseMap[H * W] = {0};

	for (int h = 0 ; h < H ; h++) {
		for (int w = 0 ; w < W ; w++) {

			//eval coords
			v.x = ((float)w / (float)numSteps) * D_kMaxVertices;
			v.y = ((float)h / (float)numSteps) * D_kMaxVertices;

			//fBm
			const int	layers = 5;
			float		scale = 1.0f;
			float		frequency = 0.015f;
			float		lacunarity = 1.8f;
			float		gain = 0.35f;

			v.x *= frequency;
			v.y *= frequency;
			for (int j = 0 ; j < layers ; j++) {
				noiseMap[w + h * W] += eval(v) * scale;
				scale *= gain;
				v.x *= lacunarity;
				v.y *= lacunarity;
			}
			//for normalization
			if (noiseMap[w + h * W] > noiseValueMax)
				noiseValueMax = noiseMap[w + h * W];
		}
	}

	//color lerp & normalization
	for (int h = 0 ; h < H ; h++) {
		for (int w = 0 ; w < W ; w++) {
			noiseMap[w + h * W] /= noiseValueMax;
			int lr = (int)lerp(0, 255, noiseMap[w + h * W]);
			color = ft_create_trgb(255, 255 - lr, 255 - lr, 255 - lr); 
			pixelPut(&g_n.img, w, h, color, 1);
		}
	}

	/* Print Squares */
	//printSquares();	

}
