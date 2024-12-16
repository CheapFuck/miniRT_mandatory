#ifndef MINIRT_H
# define MINIRT_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "scene.h"
# include "objects.h"
# include "parser.h"
# include "utils.h"
# include "render.h"

# define WIDTH      320
# define HEIGHT     240
# define SAMPLES    1
# define EPSILON	1e-6 // Threshold for floating-point precision errors

void		render_scene(mlx_t *mlx, t_scene *scene);
void		exit_with_error(const char *msg);
int			main(int argc, char **argv);

t_ray		create_ray(int x, int y, t_camera *camera);
t_vector	world_to_local(t_vector point, t_vector orientation,
				t_vector center);
void		ft_hook(void* param);

#endif // MINIRT_H
