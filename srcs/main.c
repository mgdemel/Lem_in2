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
		// ft_printf("\nStarting get_tunnel_int_arr\n");
		get_tunnel_int_arr(lem);
		// ft_printf("ENDING get_tunnel_int_arr\n");
		// ft_printf("Starting tree_creation\n");
		if (tree_creation(lem))
		{
			error_message(lem, lem->all_rooms);
			return (1);
		}
		// ft_printf("Ending tree_creation\n");
		// lem->test_index = 1;
		// ft_printf("Started Create path arr\n");
		create_path_arr(lem);
		// ft_printf("Completed Create path arr\n");
		// lem->test_index = 0;
		// ft_printf("Started count_valid_paths\n");
		count_valid_paths(lem);
		// ft_printf("completed count_valid_paths\n");
		// ft_printf("ALL PATHS:\n");
		// print_double_arr(lem->all_paths, lem->max_paths);
		// ft_printf("Started sort_paths\n");
		sort_paths(lem);
		// ft_printf("completed sort_paths\n");
	//	test_structs(lem);
		// ft_printf("Started flow_management\n");
		flow_management(lem);
		// ft_printf("completed flow_management\n");
		// ft_printf("Started output\n");
		output(lem);
		while (1);
		// ft_printf("completed output\n");
		// ft_printf("\nto compare with map:%d\n", lem->printed);
		// lem->test_index = 0;
		free_tree(lem->tree, lem);
		//ft_printf("FREED TREE\n");
	//	free_room(lem->all_rooms);
	//	ft_printf("FREED ROOM\n");
		//free_lem(lem);
		//ft_printf("FREED LEM\n");

	}
	else
	{
		error_message(lem, lem->all_rooms);
		return (1);
	}
	return (0);
}
