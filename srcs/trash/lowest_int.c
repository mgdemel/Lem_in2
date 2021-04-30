#include "lem_in.h"

int	main(void)
{
	char *line;
	int lowest;

	lowest = 1000;
	while (get_next_line(0, &line) > 0)
	{
		if (ft_atoi(line) < lowest)
		{
			lowest = ft_atoi(line);
		}
		ft_strdel(&line);
	}	
	ft_printf("lowest:%d\n", lowest);
	return (0);
}