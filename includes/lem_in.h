#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libftprintf/ft_printf.h"
# include <stdlib.h>

typedef struct			s_room
{
	char				*name;
	int					y;
	int					x;
	int					roomtype; //1=start, 2=normal, 3=end
	struct s_room		*prev;
	struct s_room		*next;
}						t_room;

typedef struct		s_lem
{
	int 			ants;
	struct s_room	*first_room;
}					t_lem;


void		initialize_lem(t_lem *lem);
void		initialize_room(t_lem *room);
int			get_rooms(char *line, t_room *r_data);

#endif