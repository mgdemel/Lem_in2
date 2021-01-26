#include "../includes/lem_in.h"

int		main(int argc, char **argv)
{
	t_lem	*lem = NULL; //had to go back to this way of doing it because the other way output errors galore
	t_room 	*room = NULL;
	char	*line;
	
	open(argv[1], O_RDONLY);
	argc = 0; //only because w-flag complains it's unused
	line = NULL;
	// if (file_is_valid() == 0) //THIS IS NEW! (WHERE WE CALL VALIDATION FUNCTION)
	// {
		// lem = initialize_lem();
		// room = initialize_room();
		// lem->first_room = room;
		// store_data(line, room, lem);
	// 	return (0);
	// }
	// else
	// 	return (1);
	ft_putstr("program start\n");
	lem = initialize_lem();
	room = initialize_room();
	lem->first_room = room;
	ft_putstr("initialized structs\n");
	store_data(line, room, lem);
	ft_putstr("stored data\n");
	test_structs(lem, room);
	return (0);
}