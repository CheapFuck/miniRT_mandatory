/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 15:46:41 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/20 13:36:51 by thivan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	parse_camera(char *line, t_scene *scene)
{
	char	**tokens;
	char	**pos;
	char	**orient;

	validate_unique_element(scene, 'C');
	tokens = ft_split(line, ' ');
	if (!tokens || ft_arraylen(tokens) != 4)
		exit_with_error("Invalid camera format");
	pos = ft_split(tokens[1], ',');
	if (!pos || ft_arraylen(pos) != 3)
	{
		ft_free_split(tokens);
		exit_with_error("Invalid camera position format");
	}
	scene->camera.pos.x = ft_atof(pos[0]);
	scene->camera.pos.y = ft_atof(pos[1]);
	scene->camera.pos.z = ft_atof(pos[2]);
	orient = ft_split(tokens[2], ',');
	if (!orient || ft_arraylen(orient) != 3)
	{
		ft_free_split(tokens);
		ft_free_split(pos);
		exit_with_error("Invalid camera orientation format");
	}
	scene->camera.orientation.x = ft_atof(orient[0]);
	scene->camera.orientation.y = ft_atof(orient[1]);
	scene->camera.orientation.z = ft_atof(orient[2]);
	if (!validate_nrmlzd_vector(&scene->camera.orientation, "Camera"))
	{
		ft_free_split(tokens);
		ft_free_split(pos);
		ft_free_split(orient);
		exit_with_error("Invalid camera orientation vector");
	}
	scene->camera.fov = ft_atoi(tokens[3]);
	if (!validate_fov(scene->camera.fov))
	{
		ft_free_split(tokens);
		ft_free_split(pos);
		ft_free_split(orient);
		exit_with_error("FOV must be between 0 and 180 degrees");
	}
	scene->has_camera = 1;
	ft_free_split(tokens);
	ft_free_split(pos);
	ft_free_split(orient);
}
