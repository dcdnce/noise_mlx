#include "noise.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

/**
 * @brief Print squares linking the different 
 * vertices of the noiseMap, for debugging.
 * 
 */
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

/**
 * @brief Get random values for the 2D vertices.
 * 
 * @param seed 
 */
static inline void	valueNoise2D(long seed) { 
	srand48(seed);
	for (int i = 0 ; i < D_kMaxVertices * D_kMaxVertices ; i++) {
		g_n.r2[i] = drand48();
	}
}

/**
 * @brief Main function of the noise2D tool.
 * 
 * @param seed 
 */
void	noise2D(int seed) {
	valueNoise2D(seed);

	t_vec2f		v = {0};
	const int 	numSteps = H;
	int 		color = 0xff000000;
	float 		noiseValueMax = 0;

	//Main loop to compute noiseMap
	for (int h = 0 ; h < H ; h++) {
		for (int w = 0 ; w < W ; w++) {
			//Evaluate corresponding pixel
			v.x = ((float)w / (float)numSteps) * D_kMaxVertices;
			v.y = ((float)h / (float)numSteps) * D_kMaxVertices;
			//Basic fractal sum function
			basicFractalSum(v, h, w);	
			//Saving higher value of the noiseMap for normalization
			if (g_n.noiseMap[w + h * W] > noiseValueMax)
				noiseValueMax = g_n.noiseMap[w + h * W];
		}
	}

	//Normalization - to keep values in range [0-1]
	//Lerp between [0-255] for the output color
	for (int h = 0 ; h < H ; h++) {
		for (int w = 0 ; w < W ; w++) {
			g_n.noiseMap[w + h * W] /= noiseValueMax;
			int lr = (int)lerp(0, 255, g_n.noiseMap[w + h * W]);
			color = ft_create_trgb(0, 255 - lr, 255 - lr, 255 - lr); 
			pixelPut(&g_n.img, w, h, color, 1);
		}
	}

	//to file
	toFdf();
	//Print Squares
	//printSquares();	

}
