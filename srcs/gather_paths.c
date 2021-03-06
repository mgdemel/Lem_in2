#include "../includes/lem_in.h"

void copy_previous_path(t_lem *lem, int r, int i)
{
    while (r >= 0)
    { 
        lem->all_paths[i][r] = lem->all_paths[i - 1][r];
        r--;
    }
}


int scan_paths(t_tree *start, t_lem *lem, int i, int r)
{
    t_tree *tree;
    t_room *room;

    tree = start;
    room  = lem->all_rooms;
    ft_printf("path: %d\n", lem->path);
    ft_printf("i : %d\nr : %d\n", i, r);
    while (ft_strcmp(tree->name, lem->end_room_name) != 0)
    {
        while(room->next != NULL && (ft_strcmp(room->name, tree->name) != 0))
            room = room->next;
        ft_printf("tree->name here: %s\n", tree->name);
        ft_printf("room->name here: %s, %d\n", room->name, room->roomnum);
        lem->all_paths[i][r] = room->roomnum;
        if (tree->sibling != NULL)
        {
            ft_printf("Found Sibling when name is %s\n", tree->name);
            ft_printf("Path when sibling was found is %d\n", i);
            lem->path++;
            copy_previous_path(lem, r, lem->path);
            scan_paths(tree->sibling, lem, lem->path, r);
        }
        r++;
        tree = tree->child;
        room  = lem->all_rooms;
        ft_printf("r = %d\n", r);
    }
    return (0);
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
    //new function call happens here
    if (!(lem->all_paths = (int**)malloc(sizeof(int*) * 10))) //need to find all possible paths
		return (1);
    while (i < 10) //need to find all possible paths
	{
		if (!(lem->all_paths[i] = (int*)malloc(sizeof(int) * lem->nbr_rooms))) //the most it could be is all of the rooms connected to one anohter
			return (1);
        i++;
    }
    scan_paths(start, lem, 0, 0);
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





