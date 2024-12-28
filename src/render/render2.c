/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 15:40:19 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/09 16:02:15 by diwang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Create and initialize an MLX image
static mlx_image_t	*create_image(mlx_t *mlx)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		exit_with_error("Error creating image");
	return (img);
}

// Main render scene function
void	render_scene(mlx_t *mlx, t_scene *scene)
{
	mlx_image_t		*img;
	t_render_data	*data;

	img = create_image(mlx);
	data = init_render_data(mlx, scene, img);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, ft_hook, data);
	mlx_loop_hook(mlx, render_next_row, data);
	mlx_loop(mlx);
	free(data);
}
