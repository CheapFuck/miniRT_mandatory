/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 15:04:25 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/13 15:05:30 by diwang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"

// Parsing functions
void		parse_file(const char *filename, t_scene *scene);
void		handle_parse_error(char **tokens, const char *error_message);
char		**split_and_validate(char *str, int expected_parts);
int			normalize_orientation(t_cylinder *cylinder);
int			parse_cylinder_properties(char **tokens, t_cylinder *cylinder);
int			parse_color(char *color_str, t_color *color);
void		parse_cylinder(char *line, t_scene *scene);

//can static?
// void        handle_invalid_line(char *line);
// void        parse_scene_element(char *line, t_scene *scene);
// void        open_file(const char *filename, int *fd); 
void		parse_ambient(char *line, t_scene *scene);
void		parse_camera(char *line, t_scene *scene);
void		parse_light(char *line, t_scene *scene);
void		parse_sphere(char *line, t_scene *scene);
void		parse_plane(char *line, t_scene *scene);
void		parse_cylinder(char *line, t_scene *scene);

// Utility functions for parsing
t_vector	parse_vector(const char *str);
int			parse_color(char *color_str, t_color *color);
double		parse_double(const char *str);
int			parse_int(const char *str);

// Error handling
void		exit_with_error(const char *msg);

#endif // PARSER_H
