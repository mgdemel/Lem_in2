#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"
# include <stdlib.h>

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


void		initialize_lem(t_lem *lem);
void		initialize_room(t_lem *room);
int			store_data(char *line, t_room *r_data, t_lem *lem);

#endif