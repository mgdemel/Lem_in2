#include "../includes/lem_in.h"

static int		get_a_room(char *line, t_room *r_data)
{
	int		i;
	char	**coord;

	i = 0;
	if (*line == 'L')
		return (1);
	while (*line != ' ')
	{
		r_data->name[i] = *line;
		i++;
		line++;
	} 
	i++;
	if (!(coord = ft_strsplit(&line[i], ' ')))
		return (1);
	r_data->y = ft_atoi(coord[0]);
	r_data->x = ft_atoi(coord[1]);
	free_array(coord);
	return (0);
}

static int		get_room(char *line, t_room *r_data)
{
	t_room temp;
	t_room new_room;

	temp = r_data;
	if (r_data->name != NULL)
	{
		initialize_room(&new_room);
		r_data->next = new_room;
		r_data = new_room;
		r_data->prev = temp;	
	}
	if (ft_strstr((char*)line, "-"))
		get_tunnel(void);
	else if (ft_strstr((char*)line, "##start") || ft_strstr(line, "##end"))
	{
		room_values(line);
		if (ft_strstr((char*)line, "##start"))
			r_data->roomtype = 1;
		else
			r_data->roomtype = 3;
	}
	else
		r_data->roomtype = 2;
	return (0);
}

int				store_data(char *line, t_room *r_data, t_lem *lem)
{
	t_room new_room;
	t_room temp;
	int i;

	i = 0;
	get_next_line(2, &line);
	lem->ants = ft_atoi(line);
	ft_strdel(&line);
	while (get_next_line(2, &line) > 0)
	{
		if (!(ft_strstr(line, "-")))
			get_room(line, r_data);
		else
			lem-> tunnels[i++] = ft_strdup(line);  // check if it works
		ft_strdel(&line);
	}
	return (0);
}
