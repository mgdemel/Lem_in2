#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h> //for reading files from FD

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					roomtype; //1=start, 2=normal, 3=end
	struct s_room		*prev;
	struct s_room		*next;
}						t_room;

typedef struct		s_lem
{
	int 			ants;
	int				nbr_tunnels;
	struct s_room	*first_room;
	char			**tunnels;
}					t_lem;


t_lem 		*initialize_lem(t_lem *lem);
t_room		*initialize_room(t_room *room);
int			store_data(char *line, t_room *room, t_lem *lem);
void		test_structs(t_lem *lem, t_room *room);

#endif