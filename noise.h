#ifndef NOISE_H
#define NOISE_H
#include <mlx.h>

#define W 1920
#define H 960
#define D_kMaxVertices	10 

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
	float		r[100];
}			 	t_noise;

t_noise	g_n;

/*	dda.c	*/
void	dda(t_vec2f a, t_vec2f b);

/*	mlx.c	*/
int		ft_create_trgb(int t, int r, int g, int b);
void	initMlx(void);
void	pixelPut(t_imgdata *img, int x, int y, int color, int size);

/*	noise.c	*/
void	valueNoise1D(long seed);
float	lerp(const float lo, const float hi, const float t);
float	eval(const float x);
#endif
