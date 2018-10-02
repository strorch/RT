/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:21:58 by mstorcha          #+#    #+#             */
/*   Updated: 2018/05/23 13:24:38 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define HEIGHT 1200
# define WIDTH 1200
# define SIDE_W 400
# define MEN_H 60
# define BT_H 30
# define BT_W 100
# define BT_COUNT 17
# define MAX_SOURCE_SIZE 0x100000

# include "../libft/libft.h"
# include "../libTFD/tinyfiledialogs.h"
# include <math.h>
# include <pwd.h>

# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"

# ifdef linux
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
# else
#  include "SDL.h"
#  include "SDL_image.h"
# endif

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#  include <CL/cl.h>
# endif

/*
** 1 - cam
** 2 - light
** 3 - sphere
** 4 - cone
** 5 - cylinder
** 6 - plane
*/
# define PLANE 6
# define CYLINDER 5
# define CONE 4
# define SPHERE 3
# define DISK 7
# define CUBE 8
# define ELLIPSOID 9
# define PARABOLOID 10
# define TWOSHEET_HYPERBOLOID 11
# define HYPERBOLOID 12

# define MEM_LENGTH 1440000

typedef struct	s_point
{
	int x;
	int y;
	int z;
}				t_point;

typedef struct	s_figure
{
	int			text;
	int			matirial;
	int			index;
	int			type;
	float		radius;
	float		angle;
	float		rfl;
	float		cap;
	cl_float3	color;
	cl_float3	p;
	cl_float3	d;
	cl_float3	min;
	cl_float3	max;
	float		size;
	float		scale;
}				t_figure;

typedef struct	s_texture
{
	int			*pix;
	int			h;
	int			w;
	int			index;
}				t_texture;

typedef struct	s_fig_text
{
	t_figure	*fig;
	t_texture	*text;
}				t_fig_text;

typedef struct	s_slist
{
	void				*data;
	struct s_slist		*next;
}				t_slist;

typedef struct	s_scene
{
	int			effect;
	int			l_num;
	int			o_num;
	t_figure	cam;
	int			textures_num;
	int			*textures;
	cl_int4		*textures_info;
	t_figure	*objects;
	t_figure	*lights;
}				t_scene;

typedef struct	s_opencl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	unsigned int		ret_num_plat;
	unsigned int		ret_num_devices;
	cl_context			context;
	cl_command_queue	command_queue;
	size_t				source_size;
	char				*source_str;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				memobj_data;
	cl_mem				memobj_figures;
	cl_mem				memobj_light;
	cl_mem				memobj_textures;
	cl_mem				memobj_textures_sz;
}				t_opencl;

typedef struct	s_interface
{
	SDL_Surface		*menu;
	SDL_Surface		*sb;
	SDL_Surface		**menu_button;
	SDL_Surface		*message;
	SDL_Texture		*menu_text;
	SDL_Texture		*sb_text;
	TTF_Font		*heading;
	TTF_Font		*par;
	SDL_Color		grey;
	SDL_Color		black;
	char			show_info;
	t_figure		*curr_figure;
	int				btn_pos_y[19];
}				t_interface;

typedef struct	s_sdl
{
	SDL_Window		*wind;
	SDL_Renderer	*rend;
	SDL_Surface		*sur;
	SDL_Texture		*text;
	SDL_Event		event;
	const Uint8		*keyboard_state;
	t_interface		ui;
}				t_sdl;

typedef struct	s_prev
{
	int			mouse_x;
	int			mouse_y;
}				t_prev;

typedef struct	s_main
{
	t_scene		*scene;
	t_opencl	*cl;
	t_sdl		*sdl;
	t_prev		prev;
}				t_main;

cl_int4			*get_texture_info(t_slist *lst);
void			parse_camera(char **str, t_figure *camera);
t_figure		*array_cast(t_slist *lst, t_scene *sc, int num, t_slist **text);
t_slist			*parse_objects(char **str, char *type, t_opencl *cl);
char			*ft_get_substr(const char *str, char *start, char *end);
cl_float3		json_arr_to_vector(char *str,
					char *pattern, char *start, char *end);
float			json_get_float(char *str, char *pattern);
char			*ft_fgets(char *file);
char			*ft_brackets(char *str, int len);
char			*json_get_array(char *str, char *pattern, char *stack, int top);
t_figure		*get_object(char *str);
t_figure		*get_light(char *str);
cl_float3		json_arr_to_color(char *str,
					char *pattern, char *start, char *end);
char			*json_get_object(char *str, char *pattern);
t_texture		*get_texture(char *str, t_opencl *cl, cl_float3 color);
void			color_manage(cl_float3 *color);

/*
** ADD Figure
*/

t_figure		new_sphere(t_figure cam, float r);
t_figure		new_cylinder(t_figure cam);
t_figure		new_cone(t_figure cam);
t_figure		new_plane(t_figure cam);
t_figure		new_hyperboloid(t_figure cam);
t_figure		new_twosheet_hyperboloid(t_figure cam);
t_figure		new_paraboloid(t_figure cam);
t_figure		new_ellipsoid(t_figure cam);
t_figure		new_disk(t_figure cam);
t_figure		new_cube(t_figure cam);
void			add_figure(t_main *mlx,
					t_figure **figures, t_figure cam, char type);

cl_float3		rotate_ort(cl_float3 point, cl_float3 rot);
int				figure_actions(t_main *mlx, int x, int y);

/*
**	CL parsing
*/

void			cl_start(t_opencl *cl);
void			cl_kernel_buffer_1(t_opencl *cl, t_main *mlx, int memlenth);
void			cl_kernel_buffer_2(t_opencl *cl, t_main *mlx);
void			cl_args_1_1(t_opencl *cl, t_main *mlx);
void			cl_args_1_2(t_opencl *cl, t_main *mlx);
void			cl_args_2(t_opencl *cl, t_main *mlx, int i, int j);
void			cl_init(t_main *mlx);
void			rendering(t_main *mlx);
int				find_figure(t_main *mlx, int i, int j);
void			apply_effects(t_main *mlx, int effect);
void			get_disruption(t_texture *text,
					t_opencl *cl, cl_float3 color, int type);
void			cl_kernel_buffer_3(t_opencl *cl);
void			cl_args_3(t_opencl *cl, cl_float3 color, int type);

void			exit_message(const char *str);
t_slist			*readf(char *argv);

float			v_length(cl_float3 p);
cl_float3		num_dil(cl_float3 p, float n);
float			v_length(cl_float3 p);
int				return_color(cl_float3 c);
t_scene			*scene_create(char *argv);
t_scene			*parse_json(char *file, t_opencl *cl);

/*
** HANDLERS
*/

void			init_sdl(t_sdl *sdl);
void			mousemove_events(t_main *mlx);
void			mousewheel_events(t_main *mlx, SDL_Event *event);
void			mouse_events1(t_main *mlx);
void			mouse_events2(t_main *mlx);
void			key_events(t_main *mlx, SDL_Event *event);
void			write_in_file(t_scene sc);
int				key(int key_code, t_main *mlx);
int				mouse(int key_code, int x, int y, t_main *mlx);
void			screen_shoot(t_main mlx);
void			call_dialog(t_main *mlx);

void			ft_list_push_back(t_slist **begin_list, void *data);

t_slist			*list_objects(char **argv);
void			*free_lst(t_slist *list);

t_slist			*get_lights(t_slist *strs);
int				get_camera(t_slist *strs, t_figure *cam);
t_figure		*get_figure(t_slist *strs);
int				count_elems(char **str);
t_slist			*no_empty(t_slist *lst);
int				return_point(char **splitted, char *value, cl_float3 *p);
int				return_value(char **splitted, char *value, float *val);
cl_float3		p_to_c(cl_float3 p);
int				return_color_t(char **splitted, char *value, cl_float3 *p);

cl_float3		*norming(cl_float3 *p);
int				ft_list_count(t_slist *begin_list);
int				na(char *name);

void			user_interface(t_sdl *sdl, t_scene *scene);
void			draw_button(t_sdl *sdl, int i, int x, int width);
cl_float3		get_unit_vector(cl_float3 vec);
cl_float3		rotate_dir(cl_float3 point, cl_float3 rot);

void			del_scene(t_main *mlx);
void			set_curr_fig(t_figure **curr, t_figure *fig, int i);
char			*ft_strjoinfree(char *s1, char *s2);
char			*ft_strjoinlit(char *s1, const char *s2);

void			handle_curr_obj(t_main *mlx, int x, int y);
void			print_message(t_sdl *sdl, const char *str, char type, int *y);

void			draw_info_btns(t_sdl *sdl);

void			filling_textures(t_scene *scene, t_slist *text_list);

/*
** init_interface.c
*/

SDL_Surface		*create_button(char *src);
void			init_ui(t_sdl *sdl);
void			init_buttons(SDL_Surface **menu_button);
char			*ft_strjoinfree(char *s1, char *s2);
char			*ft_strjoinlit(char *s1, const char *s2);

/*
** sidebar.c
*/

void			draw_sidebar(t_sdl *sdl, t_scene *scene);
char			*cam_pos_message(t_figure cam, char type);
char			*light_message(t_figure *light, int i);
void			show_fig_info(t_sdl *sdl, t_figure *curr);
void			print_fig_float(t_sdl *sdl, float nb, int *y, int i);

/*
** printer.c
*/

void			print_fig_col(t_sdl *sdl, t_figure *figure, int *y, char *patt);
void			print_fig_dir(t_sdl *sdl, t_figure *figure, int *y, char *patt);
void			print_fig_pos(t_sdl *sdl, t_figure *figure, int *y, char *patt);
void			print_fig_type(t_sdl *sdl, t_figure *figure, int *y);
void			print_info_message(t_sdl *sdl,
	const char *str, char type, int *y);
void			print_fig_min(t_sdl *sdl, t_figure *figure, int *y, char *patt);
void			print_fig_max(t_sdl *sdl, t_figure *figure, int *y, char *patt);

/*
** button_manipulator.c
*/

void			handle_curr_obj(t_main *mlx, int x, int y);
void			handle_curr_obj2(t_main *mlx, int x, int y);
void			handle_curr_obj3(t_main *mlx, int x, int y);
void			handle_curr_obj4(t_main *mlx, int x, int y);
void			handle_curr_obj8(t_main *mlx, int x, int y);
void			handle_curr_obj7(t_main *mlx, int x, int y);
void			handle_curr_obj6(t_main *mlx, int x, int y);
void			handle_curr_obj5(t_main *mlx, int x, int y);

/*
** button_drawer.c
*/
void			draw_info_btns(t_sdl *sdl);
void			draw_info_btns2(t_sdl *sdl);
void			draw_info_btns3(t_sdl *sdl);

/*
** crutches.c
*/

char			*ft_ftoa(float num);
void			change_float_val(float *val,
					char operator, float nb, float max);

#endif
