#include "../includes/lem_in.h"

int main(void)
{
	t_lem	lem;
	t_room	r_data;
	char	*line;

	line = NULL;
	initialize_lem(&lem);
	initialize_room(&r_data);		
	lem->first_room = r_data;
	// the file needs to be opened and read properly
	
	store_data(line, &r_data, &lem);
	return (0);
}



create head node room{first room data}
	-> create new node room{second room data}
		-> create new node room{third room data}...
