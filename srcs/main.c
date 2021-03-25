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
	{
		if (tree_creation(lem) == 1)
		lem->test_index = 1;
		create_path_arr(lem);
		test_structs(lem);
		//output(lem);
		//free_tree(lem->tree, lem);
		free_room(lem->all_rooms);
		//free_lem(lem);
	}
	else
	{
		error_message(lem, lem->all_rooms);
		ft_printf("ERROR\n");
		return (1);
	}
	return (0);
}