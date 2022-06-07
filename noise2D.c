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
	int	c10 = c00 + 1;
	int c01 = c00 + D_kMaxVertices;
	int	c11 = c10 + D_kMaxVertices;

	//printf("for v.x:%f v.y:%f -> c00:%d\n", v.x, v.y, c00);
	
	//get nx0 and nx1
	float tx = v.x - (int)v.x;
	float nx0 = lerp(g_n.r2[c00], g_n.r2[c10], tx);
	float nx1 = lerp(g_n.r2[c01], g_n.r2[c11], tx);

	//return pnoise
	float ty = v.y - (int)v.y;
	float pNoise = lerp(nx0, nx1, ty);
	return (pNoise);
}

void	noise2D(void) {
	valueNoise2D(2011);

	
	t_vec2f	v = {0};
	const int numSteps = H;
	float value;
	int color = 0xff000000;

	for (int h = 0 ; h < H ; h++) {
		for (int w = 0 ; w < W ; w++) {

			//eval coords
			v.x = ((float)w / (float)numSteps) * D_kMaxVertices;
			v.y = ((float)h / (float)numSteps) * D_kMaxVertices;
			value = eval(v);
			//printf("value at x.%f y.%f -> %f\n", v.x, v.y, value);
			
			//color lerp
			int lr = (int)lerp(0, 255, value);
			color = ft_create_trgb(255, lr, 255, 255); 
			pixelPut(&g_n.img, w, h, color, 1);
		}
	}

	/* Print Squares */
	printSquares();	

}
