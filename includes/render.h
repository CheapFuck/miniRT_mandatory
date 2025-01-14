#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

void			render_scene(mlx_t *mlx, t_scene *scene);
int				intersect_sphere(t_ray *ray, t_sphere *sphere, double *t);
int				intersect_cylinder(t_ray *ray, t_cylinder *cylinder, double *t);
int				intersect_plane(t_ray *ray, t_plane *plane, double *t);
t_color			apply_lighting(t_vector hit_point, t_vector normal,
					t_color object_color, t_scene *scene);
t_color			combine_color(t_color light_color, t_color object_color);
t_vector		random_point_on_light(t_light light);
int				handle_spheres(t_ray *ray, t_scene *scene, double *t,
					t_color *final_color);
t_render_data	*init_render_data(mlx_t *mlx, t_scene *scene, mlx_image_t *img);
void			render_next_row(void *param);
void			calculate_cylinder_quadratic(t_ray *ray, t_cylinder *cylinder,
					double *components);
t_ray			generate_shadow_ray(t_vector hit_point, t_light light);
double			compute_distance(t_vector a, t_vector b);
int				is_in_shadow(t_ray *shadow_ray, t_scene *scene,
					double light_distance);
t_ray			create_ray(int x, int y, t_camera *camera);
t_vector		world_to_local(t_vector point, t_vector orientation,
					t_vector center);
t_vector		scale(t_vector v, double s);
int				intersect_disc(t_ray *ray, t_disc *disc, double *t);
void			parse_discs(char *line, t_scene *scene);
int				parse_disc_properties(char **tokens, t_disc *disc);
t_vector		cross(t_vector a, t_vector b);
void			ft_hook(void *param);

#endif // RENDER_H
