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
	int				nbr_paths;
	int				found_start_end;
	struct s_room	*all_rooms; // an unordered list of all rooms found in init scan
	struct s_path	**all_paths; //all the valid paths we found
	char			**paths_found;
	char			**tunnels;
	char			*start_room_name;
	char			*end_room_name;
}					t_lem;

typedef struct		s_path
{
	struct s_room	*start_room; // start
	struct s_room	**inbetween_rooms; // r1, r2, r3
	struct s_room	*end_room; // end
	int				length;
}					t_path;

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					roomtype; //1=start, 2=normal, 3=end
	int					first;
	struct s_room		*prev;
	struct s_room		*next;	
}						t_room;

t_lem 		*initialize_lem();
t_room		*initialize_room();
int			store_data(char *line, t_lem *lem, t_room *room, int fd);
void		test_structs(t_lem *lem);
int 		file_is_valid(t_lem *lem, int fd);
int			search_for_all_paths(t_lem *lem);

#endif