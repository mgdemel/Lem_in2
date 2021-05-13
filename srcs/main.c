#include "lem_in.h"

void	error_message(t_lem *lem, t_room *room)
{
	free(lem);
	free(room);
	ft_printf("ERROR\n");
}

int	main(void)
{
	t_lem	*lem;

	lem = initialize_lem();
	lem->all_rooms = initialize_room(lem);
	if (store_data(lem, lem->all_rooms, 0) == 0)
	{
		get_tunnel_int_arr(lem);
		if (tree_creation(lem))
		{
			error_message(lem, lem->all_rooms);
			return (1);
		}
		create_path_arr(lem);
		count_valid_paths(lem);
		// ft_printf("ALL PATHS:\n");
		// print_double_arr(lem->all_paths, lem->max_paths);
		sort_paths(lem);
		flow_management(lem);
<<<<<<< HEAD
		// ft_printf("completed flow_management\n");
		// ft_printf("Started output\n");
		output(lem);
		//while (1);
		 ft_printf("completed output\n");
		ft_printf("\nto comp with map:%d, to comp with result:%d\n", lem->printed, lem->result[1]);
		// lem->test_index = 0;
=======
		output(lem);
		//while (1);
		ft_printf("\nprinted:%d, steps:%d\n", lem->printed, lem->result[1]);
>>>>>>> 6c5b6f86cad1f44e8ec679fc4f2d301c4d37d85f
		free_tree(lem->tree, lem);
		//free_room(lem->all_rooms);
		//free_lem(lem);
	}
	else
	{
		error_message(lem, lem->all_rooms);
		return (1);
	}
	return (0);
}
