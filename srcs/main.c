#include "../includes/lem_in.h"

void	error_message(t_lem *lem, t_room *room)
{
	free(lem);
	free(room);
}

int		main(int argc, char **argv)
{
	t_lem	*lem;
	t_room 	*room;
	char	*line;
	int fd;

	line = NULL;
	fd = open(argv[1], O_RDONLY);
	argc = 0; //only because w-flag complains it's unused
	lem = initialize_lem();
	room = initialize_room();
	lem->all_rooms = room;
	room->first = 1;
	if (file_is_valid(lem, fd) == 0)
	{
		fd = open(argv[1], O_RDONLY); //had to call it again to restart the GNL read
		store_data(line, lem, room, fd);
		pathfinding(lem);
		test_structs(lem);
		return (0);
	}
	else
	{
		error_message(lem, room);
		ft_printf("ERROR\n");
		return (1);
	}
}