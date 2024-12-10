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

// static void close_window(mlx_t *mlx)
// {
//     if (mlx) mlx_terminate(mlx);
//     exit(0);
// }
// Initialize MLX42
static mlx_t	*init_mlx(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		exit_with_error("Error initializing MLX42");
	return (mlx);
}

// Initialize scene structure
static void	init_scene(t_scene *scene)
{
	scene->num_spheres = 0;
	scene->num_cylinders = 0;
	scene->num_lights = 0;
	scene->num_planes = 0;
	scene->num_discs = 0;
}

// Main function
int	main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_scene	scene;

	if (argc != 2)
		exit_with_error("Usage: ./miniRT <scene.rt>");
	mlx = init_mlx();
	init_scene(&scene);
	parse_file(argv[1], &scene);
	render_scene(mlx, &scene);
	mlx_loop(mlx);
	return (0);
}
