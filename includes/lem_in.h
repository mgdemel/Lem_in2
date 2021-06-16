#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h> //for reading files from FD

typedef struct s_lem
{
	int				ants;
	int				nbr_tunnels;
	int				nbr_rooms;
	int				current_roomnum;
	int				**tunnel_dir;
	char			**room_directory;
	int				found_start_end;
	int				test_index; // remove after
	int				tunnel_index;
	int				test_stopper; // remove after
	int				path;
	int				max_paths;
	int				malloc_len;
	int				i_pos;
	int				negative_one;
	int				total_paths; // remove after
	struct s_room	*all_rooms;
	int				**all_paths;
	int				**final;
	char			**tunnels;
	char			*s_room_name;
	char			*e_room_name;
	int				s_room_index;
	int				e_room_index;
	int				sib_name;
	struct s_tree	*tree;
	int				*result;
	int				printed;
	int 			end_trigger;
	int				end_trigger2;
	int				links_found;
}					t_lem;

typedef struct s_tree
{
	int				name;
	struct s_tree	*parent;
	struct s_tree	*child;
	struct s_tree	*sib;
}					t_tree;

typedef struct s_room
{
	char				*name;
	int					roomtype;
	int					roomnum;
	struct s_room		*next;	
}						t_room;

/* ERROR */
void	error_message(t_lem *lem, int i);

/* INITIALIZE */
t_lem		*initialize_lem(void);
t_room		*initialize_room(t_lem *lem);
t_tree		*tree_init(t_lem *lem, t_tree *parent);
t_tree		*head_tree_init(t_lem *lem, int name);

/* STORE_DATA */
void		store_data(t_lem *lem, t_room *room, int fd);
int			check_tunnel_validity(char *line, t_lem *lem);
t_room		*get_room(char *line, t_room *room, t_lem *lem);
int			check_rooms_validity(char *line, t_lem *lem, int i, int space);
void		room_duplicates(t_lem *lem, char *r_name, int i);

/*	TUNNEL_MAKING */
void		get_tunnel_int_arr(t_lem *lem);
void		remove_deadends(t_lem *lem, int prev, int before);

/* TREE_MAKING */
int			find_parent_links(int parent, t_lem *lem, int child, int siborchild);
void		tree_creation(t_lem *lem);
int			make_child(t_tree *parent, t_lem *lem);
int			make_sibling(t_tree *child, t_tree *parent, t_lem *lem);
int			ft_strword(int *haystack, int needle);

/* GATHER_PATHS */
void		create_path_arr(t_lem *lem);
void		get_room_num(t_tree *tree, t_lem *lem, int r, int i);
void		arr_row_size(t_tree *start, t_lem *lem);
void		sort_paths(t_lem *lem);
void		count_valid_paths(t_lem *lem);

/* FLOW_MANAGEMENT */
void		flow_management(t_lem *lem);
int			**append_array(t_lem *lem, int **arr, int max);
int			set_steps(int *option, t_lem *lem, int i, int ants_cpy);
int			scan_similar(t_lem *lem, int *index_of_valid_paths, int *to_comp);

/* OUTPUT */
void		output(t_lem *lem);

/* FREE */
void		free_tree(t_tree *start, t_lem *lem);
void		free_room(t_room *room);
void		free_lem(t_lem *lem);
void		free_array(char **array);
void		free_int_array(int **array, int max_paths);

/* TESTS */
void		print_int_arr(int *arr, int len, char *str);
void		print_double_arr(int **arr, int max);
void		print_tunnel_dir(int **arr, int max);
void		test_structs(t_lem *lem);

#endif