#include "../includes/lem_in.h"

void	error_message(t_lem *lem, t_room *room)
{
	free(lem);
	free(room);
}

int		main(int argc, char **argv)
{
	t_lem	*lem;
	char	*line;
	int fd;

	line = NULL;
	fd = open(argv[1], O_RDONLY);
	argc = 0; //only because w-flag complains it's unused
	lem = initialize_lem();
	lem->all_rooms = initialize_room(lem);
	ft_printf("allroomname %d\n", lem->all_rooms->roomtype);
	if (file_is_valid(lem, fd) == 0)
	{
		fd = open(argv[1], O_RDONLY); //had to call it again to restart the GNL read
		if (store_data(line, lem, lem->all_rooms, fd) == 1 || tree_creation(lem) == 1)
			return(1);
		free(line);
		lem->test_index = 1;
   		create_path_arr(lem);
	//	test_structs(lem);
		free_tree(lem->tree, lem);
		ft_printf("FREED TREE\n");
		free_room(lem->all_rooms);
		ft_printf("FREED ROOM\n");
	//	free_lem(lem);
	//	ft_printf("\n\nFREE LEM\n");
		while (1);
		return (0);
	}
	else
	{
		error_message(lem, lem->all_rooms);
		ft_printf("ERROR\n");
		return (1);
	}
}