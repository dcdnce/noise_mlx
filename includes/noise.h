#ifndef NOISE_H
#define NOISE_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <mlx.h>


#define W 1000 
#define H 1000
#define D_kMaxVertices	256 
#define D_kMaxVerticesMask 255

typedef struct s_vec2
{
	int	x;
	int	y;
}				t_vec2;

typedef struct s_vec2f
{
	double	x;
	double	y;
}				t_vec2f;

typedef struct s_vec3f
{
	double	x;
	double	y;
	double	z;
}				t_vec3f;

typedef struct s_vec3
{
	int	x;
	int	y;
	int	z;
}				t_vec3;

typedef struct s_mlxdata
{
	void	*body;
	void	*win;
}				t_mlxdata;

typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}				t_imgdata;

typedef struct	s_noise
{
	t_imgdata 	img;
	t_mlxdata	mlx;
	float		r[D_kMaxVertices];
	float		r2[D_kMaxVertices * D_kMaxVertices];
	float		noiseMap[H * W];
}			 	t_noise;

extern t_noise	g_n;

// .
float	lerp(const float lo, const float hi, const float t);
int		ft_create_trgb(int t, int r, int g, int b);
void	initMlx(void);
void	pixelPut(t_imgdata *img, int x, int y, int color, int size);
void	dda(t_vec2f a, t_vec2f b, const int size, const int color);

//	NOISE1D/
void	noise1D(int seed);

//	NOISE2D/
void	noise2D(int seed);
void	toFdf(void);
float	billinearInterpolation(const t_vec2f v);
void	basicFractalSum(t_vec2f	v, int h,  int w);


#endif
