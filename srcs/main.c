#include "../includes/lem_in.h"

int main(void)
{
	t_lem	lem;
	t_room	r_data;
	char	*line;

	line = NULL;
	// if (file_is_valid() == 0) //THIS IS NEW! (WHERE WE CALL VALIDATION FUNCTION)
	// {
	// 	if (!(lem->tunnels = (int**)malloc(sizeof(int*) * lem->nbr_tunnels)))
	// 		return (1);
	// 	initialize_lem(&lem); //is this ever needed, really?
	// 	initialize_room(&r_data); //is this ever needed, really?
	// 	lem->first_room = r_data;
	// 	store_data(line, &r_data, &lem);
	// 	return (0);
	// }
	// else
	// 	return (1);
	initialize_lem(&lem);
	initialize_room(&r_data);
	lem->first_room = *r_data;
	store_data(line, &r_data, &lem);
	test_structs(lem, r_data);
	return (0);
}