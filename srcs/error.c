#include "../includes/lem_in.h"

static int	check_tunnel_validity(char *line, t_lem *lem)
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

int	check_rooms_validity(char *line, t_lem *lem)
{
	char *new;

	if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
		lem->found_start_end++;
	else if (!(ft_strstr(line, "-")))
	{
		if (ft_strstr(line, "#"))
			return (0);
		else
		{
			new = ft_strtrim(line);
			if (ft_isalldigit(new))
				return (1);
			lem->nbr_rooms++;
			free(new);
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
		if (check_rooms_validity(line, lem) == 1 || lem->found_start_end > 2)
			return (1);
		if (ft_strstr(line, "-") && !ft_strstr(line, "#"))
			break ;
		else
			ft_strdel(&line);
	}
	if (check_tunnel_validity(line, lem) == 1 || lem->found_start_end != 2
		|| lem->nbr_rooms == 0)
		return (1);
	ft_strdel(&line);
	while (get_next_line(fd, &line) > 0)
	{
		if (check_tunnel_validity(line, lem) == 1 || lem->found_start_end != 2
		|| lem->nbr_rooms == 0)
			return (1);
		ft_strdel(&line);
	}
	return (0);
}
