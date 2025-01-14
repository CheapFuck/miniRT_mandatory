#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

typedef struct s_sphere
{
	t_vector	center;
	double		radius;
	t_color		color;
	int			checker;
	double		shininess; //moet dit?
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		sqrt_discriminant;
	double		t1;
	double		t2;
}	t_sphere;

#endif // OBJECTS_H
