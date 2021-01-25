#include "../includes/lem_in.h"

int main(void)
{
	t_lem	lem;
	t_room	r_data;
	char	*line;

	line = NULL;
	initialize_lem(&lem);
	initialize_room(&r_data);		
	lem->first_room = r_data;
	// the file needs to be opened and read properly
	get_next_line(2, &line);
		lem->ants = ft_atoi(line);
	ft_strdel(&line);
	get_rooms(line, &r_data);
	return (0);
}
