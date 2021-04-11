#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h> //for reading files from FD

typedef struct		s_lem
{
	int 			ants;
	int				nbr_tunnels;
	int				nbr_rooms;
	int				current_roomnum;
	int				found_start_end;
	int				path_index;
	int				test_index; // remove after
	int				path;
	int				max_paths;
	int				malloc_len;
	int				*w_child;
	int				*w_parent;
	int				index_options;
	int				i_placeholder;
	int				negative_one;
	struct s_room	*all_rooms; // an unordered list of all rooms found in init scan
	int				**all_paths; //a 2d int array of all the paths found by our alg
	int				**final_paths;
	char			**tunnels;
	char			*start_room_name;
	char			*e_room_name;
	char			*sib_name;
	int 			compare;
	struct s_tree	*tree; //head branch
	int				*result;
}					t_lem;

typedef struct 		s_tree
{
	char			*name;
	struct s_tree	*parent;
	struct s_tree	*child;
	struct s_tree	*sib;
}					t_tree;

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					roomtype; //1=start, 2=normal, 3=end
	int					roomnum; //assigns a numeric 'name' to the room for pathfinding array
	struct s_room		*next;	
}						t_room;

/*
**	PROTOTYPES
*/

/*
**	INITIALIZE
*/

t_lem		*initialize_lem();
t_room		*initialize_room(t_lem *lem);

/*
**	STORE_DATA.C
*/

int			store_data(t_lem *lem, t_room *room, int fd);
void		test_structs(t_lem *lem);
int 		file_is_valid(t_lem *lem, int fd);
int			search_for_all_paths(t_lem *lem);
char		*needle_crop(char *haystack, char *needle);
int			find_parent_links(char *parent, t_lem *lem, int *forbidden_array);
int			tree_creation(t_lem *lem);
t_tree		*tree_init(t_tree *parent);
int 		add_elem_int_array(int *forbidden_array, t_lem *lem, char *block_name, int parent);
void		make_child(t_tree *parent, t_lem *lem, int *forbidden_array);
char		*make_sibling(t_tree *child, t_tree *parent, t_lem *lem, int *forbidden_array);
t_tree		*head_tree_init(char *name);
int 		create_path_arr(t_lem *lem);
void		free_tree(t_tree *start, t_lem *lem);
void		free_room(t_room *room);
void 		free_lem(t_lem *lem);
void		free_array(char **array);
void		print_int_arr(int *arr, int len, char *str); //remove later!
int			check_tunnel_validity(char *line, t_lem *lem);
t_room		*get_room(char *line, t_room *room, t_lem *lem);
int			check_rooms_validity(char *line, t_lem *lem);
int			*ft_newintarr(int *forbidden_array, int i);
void		get_room_num(t_tree *tree, t_lem *lem, int r, int i);
int			flow_management(t_lem *lem);
int			**append_array(int **arr, int max);
void		sort_paths(t_lem *lem);
void		count_valid_paths(t_lem *lem);
int			ft_strword(char *haystack, char *needle);
void		arr_row_size(t_tree *start, t_lem *lem);
void 		print_double_arr(int **arr, int max); //remove later!
void		output(t_lem *lem);

#endif