#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h> //for reading files from FD

typedef struct		s_lem
{
	int 			ants;
	int				nbr_tunnels;
	int				nbr_rooms;
	struct s_room	*first_room;
	struct s_room	*temp;
	char			**tunnels;
}					t_lem;

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

#endif