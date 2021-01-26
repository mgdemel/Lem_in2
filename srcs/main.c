#include "../includes/lem_in.h"

int		main(int argc, char **argv)
{
	t_lem	*lem = NULL; //had to go back to this way of doing it because the other way output errors galore
	t_room 	*room = NULL;
	char	*line;
	int fd;

	line = NULL;
	fd = open(argv[1], O_RDONLY);
	argc = 0; //only because w-flag complains it's unused
	lem = initialize_lem();
	room = initialize_room();
	if (file_is_valid(lem, fd) == 0)
	{
		ft_putstr("program start\n");
		lem->first_room = room;
		ft_putstr("initialized structs\n");
		test_structs(lem, room);
		store_data(line, room, lem, fd);
		ft_putstr("stored data\n");
		test_structs(lem, room);
		return (0);
	}
	else
		return (1);
}