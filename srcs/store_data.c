#include "../includes/lem_in.h"

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

t_room		*get_room(char *line, t_room *r_data)
{
	t_room new_room;
	t_room temp;
	int		i;
	char	**coord;
	i = 0;

	r_data->next = new_room;
	r_data = new_room;
	r_data->prev = temp;
	if (ft_strstr((char*)line, "##start")) //labels room based on type
	{
		r_data->roomtype = 1;
		ft_strdel(&line);
		get_next_line(2, &line);
	}
	else if (ft_strstr((char*)line, "##end"))
	{
		r_data->roomtype = 3;
		ft_strdel(&line);
		get_next_line(2, &line);
	}
	else
		r_data->roomtype = 2;
	while (*line != ' ') //stores the name of the room
	{
		r_data->name[i] = *line;
		i++;
		line++;
	} 
	i++;
	if (!(coord = ft_strsplit(&line[i], ' ')))
		return (1);
	r_data->x = ft_atoi(coord[0]);
	r_data->y = ft_atoi(coord[1]);
	free_array(coord);
	return(r_data = r_data->next);
}

int				store_data(char *line, t_room *r_data, t_lem *lem)
{
	int i;

	i = 0;
	get_next_line(2, &line);
	lem->ants = ft_atoi(line);
	ft_strdel(&line);
	while (get_next_line(2, &line) > 0)
	{
		if (!(ft_strstr(line, "-")))
			r_data = get_room(line, r_data);
		else
			lem-> tunnels[i++] = ft_strdup(line);  // check if it works
		ft_strdel(&line);
	}
	return (0);
}
