#include "../includes/lem_in.h"

void copy_previous_path(t_lem *lem, int r, int path, int i)
{
 //   ft_printf("i:%d\nr:%d\n", i, r);
   // ft_printf("lem->allpaths[i - 1][0]:%d\n", lem->all_paths[i - 1][0]);
   ft_printf("i is: %d\n", i);
   ft_printf("path is: %d\n", lem->path);
    if (i != 0)
    {
        ft_printf("all paths %d\n", lem->all_paths[i - 1][0]);
        if (lem->all_paths[i - 1][0] <= 0)
        {
            while (r >= 0)
            {
                lem->all_paths[path][r] = lem->all_paths[i - 1][r + 1];
                r--;
            }
        }
        else
        {
            while (r >= 0)
            {
                lem->all_paths[path][r] = lem->all_paths[path - 1][r];
                r--;
            }
        }
    }
    else
    {
        while (r >= 0)
        {
            lem->all_paths[path][r] = lem->all_paths[i][r];
            r--;
        }
    }
}

int    *copy_col(int r, int *arr)
{
    int *new;
    int j;
    int k;
    int i;

    k = 0;
    j = 0;
    i = 0;
  //  ft_printf("r is %d\n", r);
    if (!(new = (int*)malloc(sizeof(int) * r + 1)))
			return (NULL);
  //  ft_printf("test r:%d\n", ((r + 1) * -1));
    new[i] = ((r + 1) * -1);
    i++;
    while (i < (r + 1))
    {
        new[i] = arr[i - 1];
        i++;
    }
   // ft_printf("NEW PATH HAS BEEN MADE\n");
   // ft_printf("New[0] is %d\n", new[0]);
    // while (new[0] < 0)
    // {
    //     ft_putnbr(new[k]);
    //     ft_putchar('|');
    //     new[0]++;
    //     k++;
    // }
    // ft_putchar('\n');
    // ft_putchar('\n');
    return (new);
}

void scan_paths(t_tree *start, t_lem *lem, int i, int r)
{
    t_tree *tree;
    t_room *room;
    int k;

    k = 0;
    tree = start;
    room = lem->all_rooms;
 //   ft_printf("r is at the start of scan_paths: %d\n", r);
  //  ft_printf("path: %d\n", lem->path);
    //ft_printf("i : %d\nr : %d\n", i, r);
    while (ft_strcmp(tree->name, lem->end_room_name) != 0)
    {
        while(room->next != NULL && (ft_strcmp(room->name, tree->name) != 0))
            room = room->next;
   //     ft_printf("tree->name here: %s\n", tree->name);
     //   ft_printf("room->name here: %s,room->num %d\n", room->name, room->roomnum);
        lem->all_paths[i][r] = room->roomnum;
        if (tree->sibling != NULL)
        {
        //    ft_printf("Found Sibling name is %s\n", tree->sibling->name);
          //  ft_printf("Path when sibling was found is %d\n", i);
            lem->path++;
            copy_previous_path(lem, r, lem->path, i);
            scan_paths(tree->sibling, lem, lem->path, r);
        }
        r++;
        tree = tree->child;
        room = lem->all_rooms;
        // ft_printf("r = %d\n", r);
    }
    // while(room->next != NULL && (ft_strcmp(room->name, tree->name) != 0))
    //     room = room->next;
    // lem->all_paths[i][r] = room->roomnum;
    k = 0;
    ft_printf("ALL PATHS BEFORE COPY_COL\n");
    while (k < 10)
    {
        ft_putnbr(lem->all_paths[i][k]);
        ft_putchar('|');
        k++;
    }
    ft_putchar('\n');
    lem->all_paths[i] = copy_col(r, lem->all_paths[i]);
}

void arr_row_size(t_tree *start, t_lem *lem)
{
    t_tree *tree;

    tree = start;
    while (ft_strcmp(tree->name, lem->end_room_name) != 0)
    {
        if (tree->sibling != NULL)
        {
            lem->max_paths++;
            arr_row_size(tree->sibling, lem);
        }
        tree = tree->child;
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
    arr_row_size(start, lem);
    ft_printf("paths after search: %d\n", lem->max_paths);
    if (!(lem->all_paths = (int**)malloc(sizeof(int*) * lem->max_paths)))
		return (1);
    while (i < lem->max_paths)
	{
		if (!(lem->all_paths[i] = (int*)malloc(sizeof(int) * lem->nbr_rooms))) //the most it could be is all of the rooms connected to one anohter
			return (1);
        i++;
    }
    scan_paths(start, lem, 0, 0);
    ft_putstr("all_paths:\n");
    while (j < lem->max_paths)
    {
        ft_printf("First index:");
        while (k < (lem->all_paths[j][0] * -1))
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





