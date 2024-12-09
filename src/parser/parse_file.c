/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 15:47:00 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/09 15:47:02 by diwang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

char	*read_line(int fd)
{
	char	*buffer;
	int		i;
	char	c;

	buffer = malloc(10000);
	if (!buffer)
		return (NULL);
	i = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n' || c == '\0')
			break ;
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	if (i == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

void	open_file(const char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		exit_with_error("Error opening file");
}

char	*get_next_line_from_file(int fd)
{
	char	*line;

	line = read_line(fd);
	return (line);
}

void	parse_scene_element(char *line, t_scene *scene)
{
	if (ft_strncmp(line, "A ", 2) == 0)
		parse_ambient(line, scene);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_camera(line, scene);
	else if (ft_strncmp(line, "L ", 2) == 0)
		parse_light(line, scene);
	else if (ft_strncmp(line, "sp ", 3) == 0)
		parse_sphere(line, scene);
	else if (ft_strncmp(line, "pl ", 3) == 0)
		parse_plane(line, scene);
	else if (ft_strncmp(line, "cy ", 3) == 0)
		parse_cylinder(line, scene);
	else if (ft_strncmp(line, "#", 1) != 0)
	{
		printf("line is: %s\n", line);
		exit_with_error("Invalid line in scene file");
	}
}

void	parse_file(const char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	open_file(filename, &fd);
	line = get_next_line_from_file(fd);
	while (line != NULL)
	{
		parse_scene_element(line, scene);
		free(line);
		line = get_next_line_from_file(fd);
	}
	free(line);
	close(fd);
}
