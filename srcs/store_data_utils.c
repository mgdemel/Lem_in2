#include "lem_in.h"

int			find_start_end(char *line, t_lem *lem)
{
	if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
	{
		lem->found_start_end++;
		return (1);
	}
	return (0);
}

int			check_rooms_validity(char *line, t_lem *lem)
{
	int i;
	int space;

	space = 0;
	i = 0;
	if (find_start_end(line, lem))
		return (0);
	else if (!(ft_strstr(line, "-")))
	{
		if (ft_strstr(line, "#"))
			return (0);
		else
		{
			while (line[i] != '\0')
			{
				if (line[i] == ' ')
					space++;
				i++;
			}
			lem->nbr_rooms++;
		}
	}
	if (space == 2)
		return (0);
	return (1);
}

int			check_tunnel_validity(char *line, t_lem *lem)
{
	if (ft_strstr(line, "-") || ft_strstr(line, "#"))
	{
		if (ft_strstr(line, "#"))
			return (0);
		lem->nbr_tunnels++;
	}
	else
		return (1);
	return (0);
}
