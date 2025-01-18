/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 15:56:19 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/09 15:56:20 by diwang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	close_window(mlx_t *mlx)
{
	if (mlx)
		mlx_terminate(mlx);
	exit(0);
}

static void	init_scene(t_scene *scene)
{
	scene->num_spheres = 0;
	scene->num_cylinders = 0;
	scene->num_lights = 0;
	scene->num_planes = 0;
	scene->num_discs = 0;
	scene->has_ambient = 0;
	scene->has_camera = 0;
	scene->has_light = 0;
}

void	ft_hook(void *param)
{
	t_render_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
		free(data);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_scene	scene;

	scene = (t_scene){0};
	if (argc != 2)
		exit_with_error("Usage: ./miniRT <scene.rt>");
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		exit_with_error("Error initializing MLX42");
	init_scene(&scene);
	parse_file(argv[1], &scene);
	render_scene(mlx, &scene);
	close_window(mlx);
	return (0);
}
