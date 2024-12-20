#include "../../includes/minirt.h"



// Validation functions for different types of inputs
int validate_ratio(double value, const char *element_name)
{
    if (value < 0.0 || value > 1.0) {
        printf("Error: %s ratio must be between 0.0 and 1.0\n", element_name);
        return 0;
    }
    return 1;
}

int validate_color(t_color *color)
{
    if (color->r < 0 || color->r > 255 || 
        color->g < 0 || color->g > 255 || 
        color->b < 0 || color->b > 255) {
        printf("Error: Color values must be between 0 and 255\n");
        return 0;
    }
    return 1;
}

int validate_normalized_vector(t_vector *vector, const char *element_name)
{
    if (vector->x < -1.0 || vector->x > 1.0 || 
        vector->y < -1.0 || vector->y > 1.0 || 
        vector->z < -1.0 || vector->z > 1.0) {
        printf("Error: %s normalized vector components must be between -1 and 1\n", 
               element_name);
        return 0;
    }
    return 1;
}

int validate_fov(int fov) {
    if (fov < 0 || fov >= 180) {
        return 0;
    }
    return 1;
}

// Function to track unique elements
int validate_unique_element(t_scene *scene, char type)
{
    printf("Validating element type: %c\n", type);  // Debug print
    printf("Current flags - Ambient: %d, Camera: %d, Light: %d\n",  // Debug print
           scene->has_ambient, scene->has_camera, scene->has_light);
    
    switch (type)
    {
        case 'A':
            if (scene->has_ambient)
            {
                printf("Error: Ambient lighting (A) can only be declared once\n");
                return 0;
            }
            scene->has_ambient = 1;
            break;
        case 'C':
            if (scene->has_camera)
            {
                printf("Error: Camera (C) can only be declared once\n");
                return 0;
            }
            scene->has_camera = 1;
            break;
        case 'L':
            if (scene->has_light)
            {
                printf("Error: Light (L) can only be declared once\n");
                return 0;
            }
            scene->has_light = 1;
            break;
    }
    return 1;
}
int is_valid_number(const char *str)
{
    int i = 0;
    int has_digit = 0;
    int decimal_points = 0;

    // Handle negative numbers
    if (str[i] == '-' || str[i] == '+')
        i++;

    // String can't just be a sign
    if (!str[i])
        return 0;

    while (str[i])
    {
        if (ft_isdigit(str[i]))
            has_digit = 1;
        else if (str[i] == '.')
        {
            decimal_points++;
            if (decimal_points > 1)
                return 0;
        }
        else
            return 0;
        i++;
    }
    return has_digit;
}

void init_scene(t_scene *scene)
{
    scene->has_ambient = 0;
    scene->has_camera = 0;
    scene->has_light = 0;
    scene->num_spheres = 0;
    scene->num_planes = 0;
    scene->num_cylinders = 0;
    scene->num_lights = 0;
}