#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h> //for reading files from FD
# include <stdio.h> //REMOVE THIS DUMBASS (Melissa)!!! 

typedef struct		s_lem
{
	int 			ants;
	int				nbr_tunnels;
	int				nbr_rooms;
	int				nbr_paths;
	int				found_start_end;
	int				path_index;
	int				trigger;
	int				*forbidden_array;
	struct s_room	*all_rooms; // an unordered list of all rooms found in init scan
	char			**all_paths;
	char			**tunnels;
	char			*start_room_name;
	char			*end_room_name;
	struct t_tree	*tree; //head branch
}					t_lem;

typedef struct 		s_tree
{
	char			*name;  //or int name?
	struct s_tree	*parent;
	struct s_tree	*child;
	struct s_tree	*sibling;
	int				used;
}					t_tree;


typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					roomtype; //1=start, 2=normal, 3=end
	struct s_room		*prev;
	struct s_room		*next;	
}						t_room;

t_lem 		*initialize_lem();
t_room		*initialize_room();
int			store_data(char *line, t_lem *lem, t_room *room, int fd);
void		test_structs(t_lem *lem);
int 		file_is_valid(t_lem *lem, int fd);
int			search_for_all_paths(t_lem *lem);
int 		pathfinding(t_lem *lem);
char		*needle_crop(const char *haystack, const char *needle);
int			find_parent_links(char **tunnels, char *parent, t_lem *lem);

#endif