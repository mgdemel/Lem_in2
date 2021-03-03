#include "../includes/lem_in.h"

void scan_paths(t_tree *start, t_lem *lem, int i)
{
    t_tree *tree;
    t_room *room;
    int path;
    int r;

    tree = start;
    room  = lem->all_rooms;
    path = 0;
    r = 0;
    i = 0;

    while (ft_strcmp(tree->name, lem->end_room_name) != 0)
    {
        while(room->next != NULL && ft_strcmp(room->name, tree->name) == 0)
            room = room->next;
        lem->all_paths[path][r] = room->roomnum;
        r++;
        lem->path++;
        if (tree->sibling != NULL)
        {
            scan_paths(tree->sibling, lem, lem->path);
        }
        tree = tree->child;
        path++;
    }
}

int create_path_arr(t_lem *lem)
{
    int i;
    int j;
    int k;
    t_tree *start;
    
    i = 0;
    j = 0;
    k = 0;
    start = lem->tree;
    if (!(lem->all_paths = (int**)malloc(sizeof(int*) * 10))) //need to find all possible paths
		return (1);
    while (i < 10) //need to find all possible paths
	{
		if (!(lem->all_paths[i] = (int*)malloc(sizeof(int) * lem->nbr_rooms))) //the most it could be is all of the rooms connected to one anohter
			return (1);
		i++;
	}
    scan_paths(start, lem, 1);
    ft_putstr("all_paths:\n");
    while (j < 10)
    {
        while (k < lem->nbr_rooms)
        {
            ft_putnbr(lem->all_paths[j][k]);
            ft_putchar('|');
            k++;
        }
        ft_putchar('\n');
        j++;
        k = 0;
    }
    return(0);
}





