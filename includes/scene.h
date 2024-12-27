#ifndef SCENE_H
# define SCENE_H

typedef struct s_camera
{
	t_vector	pos;
	t_vector	orientation;
	double		fov;
}	t_camera;

typedef struct s_light
{
	t_vector	pos;
	double		brightness;
	t_color		color;
	double		radius;
}	t_light;

typedef struct s_plane
{
	t_vector	point;
	t_vector	normal;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	orientation;
	double		diameter;
	double		height;
	double		radius;
	t_color		color;
}	t_cylinder;

typedef struct s_disc
{
	double		diameter;
	double		height;
	t_vector	orientation;
	t_vector	center;
	t_vector	normal;
	double		radius;
	t_color		color;
}	t_disc;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		lights[10];
	t_plane		planes[10];
	t_sphere	spheres[10];
	t_cylinder	cylinders[10];
	t_disc		discs[10];
	int			num_spheres;
	int			num_planes;
	int			num_cylinders;
	int			num_discs;
	int			num_lights;
	int			has_ambient;
	int			has_camera;
	int			has_light;
}	t_scene;

typedef struct s_disc_params
{
	t_disc	*disc;
	double	*t;
	t_color	*final_color;
	t_scene	*scene;
}	t_disc_params;

typedef struct s_plane_params
{
	t_plane	*plane;
	double	*t;
	t_color	*final_color;
	t_scene	*scene;
}	t_plane_params;

typedef struct s_render_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
	int			current_row;
	bool		render_complete;
}	t_render_data;

#endif // SCENE_H
