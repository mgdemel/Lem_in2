#include "lem_in.h"

void	error_message(t_lem *lem, t_room *room)
{
	free(lem);
	free(room);
	ft_printf("ERROR\n");
}

int		main(void)
{
	t_lem	*lem;
	int		fd;

	fd = 0;
	lem = initialize_lem();
	lem->all_rooms = initialize_room(lem);
	if (store_data(lem, lem->all_rooms, fd) == 0)
	{
		if (tree_creation(lem))
		{
			error_message(lem, lem->all_rooms);
			return (1);
		}
		lem->test_index = 1;
		create_path_arr(lem);
		lem->test_index = 0;
		count_valid_paths(lem);
		sort_paths(lem);
		//test_structs(lem);
		flow_management(lem);
		output(lem);
		lem->test_index = 0;
		free_tree(lem->tree, lem);
		//ft_printf("FREED TREE\n");
	//	free_room(lem->all_rooms);
	//	ft_printf("FREED ROOM\n");
		//free_lem(lem);
		//ft_printf("FREED LEM\n");
		//while (1);
	}
	else
	{
		error_message(lem, lem->all_rooms);
		return (1);
	}
	return (0);
}
