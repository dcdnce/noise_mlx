#ifndef NOISE_H
#define NOISE_H
#include <mlx.h>

#define W 400
#define H 400
#define D_kMaxVertices	4 
#define D_kMaxVerticesMask 4 - 1

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
}			 	t_noise;

extern t_noise	g_n;

/*	dda.c	*/
void	dda(t_vec2f a, t_vec2f b, const int size, const int color);

/*	mlx.c	*/
int		ft_create_trgb(int t, int r, int g, int b);
void	initMlx(void);
void	pixelPut(t_imgdata *img, int x, int y, int color, int size);

/*	noise1D.c	*/
void	noise1D(void);

/*	noise2D.c	*/
void	noise2D(void);

/* utils.c	*/
float	lerp(const float lo, const float hi, const float t);

#endif
