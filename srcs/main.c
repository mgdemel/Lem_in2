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
	room = initialize_room(lem);
	lem->all_rooms = room;
	if (file_is_valid(lem, fd) == 0)
	{
		fd = open(argv[1], O_RDONLY); //had to call it again to restart the GNL read
		if (store_data(line, lem, room, fd) == 1 || tree_creation(lem) == 1)
			return(1);
		free(line);
		lem->test_index = 1;
   		create_path_arr(lem);
		test_structs(lem);
		ft_printf("\n\nFREE\n");
		free_tree(lem->tree, lem);
		while (1);
		return (0);
	}
	else
	{
		error_message(lem, room);
		ft_printf("ERROR\n");
		return (1);
	}
}