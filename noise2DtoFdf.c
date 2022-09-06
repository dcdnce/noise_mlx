#include "noise.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

void toFdf(void) {
	FILE*	f;

	//open accordingly
	f = fopen("noise.fdf", "w");

	//write properly
	for (int i = 0 ; i < H ; i++) {
		for (int j = 0 ; j < W ; j++) {
			if (j)
				fprintf(f, " ");
			fprintf(f, "%d", (int)lerp(0, 100, g_n.noiseMap[j + i * W]));
		}
		fprintf(f, "\n");
	}

	fclose(f);
}
