#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"

// Parsing functions
void		parse_file(const char *filename, t_scene *scene);
void		handle_pars_error(char **tokens, const char *error_message);
char		**split_and_validate(char *str, int expected_parts);
int			parse_cylinder_properties(char **tokens, t_cylinder *cylinder);
void		parse_ambient(char *line, t_scene *scene);
void		parse_camera(char *line, t_scene *scene);
void		parse_light(char *line, t_scene *scene);
void		parse_sphere(char *line, t_scene *scene);
void		parse_plane(char *line, t_scene *scene);
void		parse_cylinder(char *line, t_scene *scene);
int			parse_color(char *color_str, t_color *color);
// Error handling
void		exit_with_error(const char *msg);
int			validate_ratio(double value, const char *element_name);
int			validate_color(t_color *color);
int			validate_nrmlzd_vector(t_vector *vec, char *context);
int			validate_fov(int fov);
int			validate_unique_element(t_scene *scene, char type);
int			is_valid_number(const char *str);

#endif // PARSER_H
