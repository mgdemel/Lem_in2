#include "../includes/lem_in.h"

static int	check_tunnel_validity(char *line, t_lem *lem)
{
	if (ft_strstr(line, "-"))
	{
		if (ft_strstr(line, "#"))
			return (0);
		
	}
}

static int	check_rooms_validity(char *line, t_lem *lem)
{
	if (!(ft_strstr(line, "-")))
	{
		if (ft_strstr(line, "#"))
			return (0);
		else
		{
			if (ft_isalldigit(ft_strtrim(line)))
				return (1);
			lem->nbr_rooms++;
		}
	}
	return (0);
}

int			file_is_valid(t_lem *lem, int fd)
{
	char	*line;
	int		found_start_end;

	found_start_end = 0;
	get_next_line(fd, &line);
	if (!ft_isalldigit(line))
		return (1);
	ft_strdel(&line);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
			found_start_end++;
		if (check_rooms_validity(line, lem) == 1 || found_start_end > 2)
			return (1);
		ft_strdel(&line);
	}
	while (get_next_line(fd, &line) > 0)
	{
		if (check_tunnel_validity(line, lem) == 1 || found_start_end != 2)
			return (1);
		ft_strdel(&line);
	}
	lem->nbr_tunnels++;
	ft_strdel(&line);
	return (0);
}
