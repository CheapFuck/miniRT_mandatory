#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

// Function to render the scene
void		render_scene(mlx_t *mlx, t_scene *scene);

// Ray-Object intersection functions
int			intersect_sphere(t_ray *ray, t_sphere *sphere, double *t);
int			intersect_cylinder(t_ray *ray, t_cylinder *cylinder, double *t);
int			intersect_plane(t_ray *ray, t_plane *plane, double *t);
t_color		apply_lighting(t_vector hit_point, t_vector normal,
				t_color object_color, t_scene *scene);
t_vector	random_point_on_light(t_light light);
double		compute_shadow_factor(t_vector hit_point, t_light light,
				t_scene *scene, int num_samples);
// static t_color	compute_light_contribution(t_vector hit_point, t_vector normal, 
// 	t_light light, t_scene *scene);
// static t_color	compute_ambient_light(t_color light_contribution,
// 	double ambient_ratio);
t_color	combine_color(t_color light_color, t_color object_color);
t_vector	random_point_on_light(t_light light);
// static t_ray	generate_shadow_ray(t_vector hit_point, t_light light);
// static double	compute_distance(t_vector a, t_vector b);
// static int	is_in_shadow(t_ray *shadow_ray, t_scene *scene,
	// double light_distance);
t_vector	compute_reflection(t_vector light_dir, t_vector normal);



#endif // RENDER_H
