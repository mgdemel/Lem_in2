#include "../includes/lem_in.h"

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
	lem->first_room = room;
	room->first = 1;
	if (file_is_valid(lem, fd) == 0)
	{
		fd = open(argv[1], O_RDONLY); //had to call it again to restart the GNL read
		store_data(line, lem, room, fd);
		test_structs(lem);
		return (0);
	}
	else
		return (1);
}