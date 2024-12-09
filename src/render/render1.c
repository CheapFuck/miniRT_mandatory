/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render1.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 15:40:15 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/09 16:03:52 by diwang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Handle cylinder intersections and update color
static int	handle_cylinders(t_ray *ray, t_scene *scene, double *t,
					t_color *final_color)
{
	int			i;
	int			hit;
	double		t_cylinder;
	t_vector	hit_point;
	t_vector	normal;

	hit = 0;
	i = 0;
	while (i < scene->num_cylinders)
	{
		t_cylinder = *t;
		if (intersect_cylinder(ray, &scene->cylinders[i], &t_cylinder)
			&& t_cylinder < *t)
		{
			*t = t_cylinder;
			hit_point = add(ray->origin, multiply_scalar(ray->direction, *t));
			normal = normalize(subtract(hit_point, scene->cylinders[i].center));
			*final_color = apply_lighting(hit_point, normal,
					scene->cylinders[i].color, scene);
			hit = 1;
		}
		i++;
	}
	return (hit);
}

// Handle plane intersections and update color
static int	handle_planes(t_ray *ray, t_scene *scene, double *t,
					t_color *final_color)
{
	int			i;
	int			hit;
	double		t_plane;
	t_vector	hit_point;

	hit = 0;
	i = 0;
	while (i < scene->num_planes)
	{
		t_plane = *t;
		if (intersect_plane(ray, &scene->planes[i], &t_plane)
			&& t_plane < *t)
		{
			*t = t_plane;
			hit_point = add(ray->origin, multiply_scalar(ray->direction, *t));
			*final_color = apply_lighting(hit_point, scene->planes[i].normal,
					scene->planes[i].color, scene);
			hit = 1;
		}
		i++;
	}
	return (hit);
}

// Trace ray and determine pixel color
static uint32_t	trace_ray(t_ray ray, t_scene *scene)
{
	double		t;
	t_color		final_color;
	int			hit;

	t = INFINITY;
	hit = 0;
	final_color = (t_color){0, 0, 0};
	if (handle_spheres(&ray, scene, &t, &final_color))
		hit = 1;
	if (handle_cylinders(&ray, scene, &t, &final_color))
		hit = 1;
	if (handle_planes(&ray, scene, &t, &final_color))
		hit = 1;
	if (hit)
		return ((final_color.r << 24) | (final_color.g << 16)
			| (final_color.b << 8) | 0xFF);
	return (0x000000FF);
}

// Main function for rendering the next row
void	render_next_row(void *param)
{
	t_render_data	*data;
	int				x;
	t_ray			ray;
	uint32_t		color;

	data = (t_render_data *)param;
	if (data->current_row >= HEIGHT)
	{
		data->render_complete = true;
		printf("Rendering complete!\n");
		mlx_terminate(data->mlx);
		free(data);
		exit(EXIT_SUCCESS);
		return ;
	}
	x = 0;
	while (x < WIDTH)
	{
		ray = create_ray(x, data->current_row, &data->scene->camera);
		color = trace_ray(ray, data->scene);
		mlx_put_pixel(data->img, x, data->current_row, color);
		x++;
	}
	data->current_row++;
}

// Allocate and initialize render data
t_render_data	*init_render_data(mlx_t *mlx, t_scene *scene,
										mlx_image_t *img)
{
	t_render_data	*data;

	data = malloc(sizeof(t_render_data));
	if (!data)
		exit_with_error("Failed to allocate render data");
	data->mlx = mlx;
	data->img = img;
	data->scene = scene;
	data->current_row = 0;
	data->render_complete = false;
	return (data);
}
