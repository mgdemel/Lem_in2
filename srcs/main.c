#include "../includes/lem_in.h"

void error_message(t_lem *lem, t_room *room)
{
	free(lem);
	free(room);
}

int main(void)
{
	t_lem *lem;
	int fd;

	fd = 0;
	lem = initialize_lem();
	lem->all_rooms = initialize_room(lem);
	if (store_data(lem, lem->all_rooms, fd) == 0)
	{ // no leaks at this point!
		if (tree_creation(lem) == 1)
			return (1);
		ft_printf("STORED DATA\n");
		lem->test_index = 1;
		create_path_arr(lem);
		ft_printf("Created path arr\n");

		test_structs(lem);
		free_tree(lem->tree, lem);
		ft_printf("FREED TREE\n");
		free_room(lem->all_rooms);
		ft_printf("FREED ROOM\n");
		//free_lem(lem);
		ft_printf("\n\nFREE LEM\n");
	}
	else
	{
		error_message(lem, lem->all_rooms);
		ft_printf("ERROR\n");
		return (1);
	}
	return (0);
}