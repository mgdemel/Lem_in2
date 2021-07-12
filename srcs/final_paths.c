#include "lem_in.h"
void    create_final_arr(t_lem *lem)
{
    int i;
    int j;
    int tab;

    i = 0;
    j = 0;
    while (i < lem->max_paths)
    {
        if (lem->sorted[i][lem->sorted[i][0] * -1] == -1)
             lem->final_tab++;
        i++;
    }
    lem->final = (int **)malloc(sizeof(int *) * lem->final_tab);
    if (lem->final == NULL)
		error_message(lem, 1);
    i = 0;
    while (i < lem->max_paths)
    {
        tab = 0;
        if (lem->sorted[i][lem->sorted[i][0] * -1] == -1)
        {
            lem->final[j] = (int *)malloc(sizeof(int) * ((lem->sorted[i][0] * -1) + 1));
            if (lem->final[j] == NULL)
		        error_message(lem, 1);
            while (lem->sorted[i][tab] != -1)
            {
                lem->final[j][tab] = lem->sorted[i][tab];
                tab++;
            }
            lem->final[j][tab] = -1;
            j++;
        }
        i++;
    }
    ft_putstr("\n\nALL FINAL PATHS: \n"); //remove after
	print_double_arr(lem->final, lem->final_tab); //remove after
}

void	remove_dup_paths(t_lem *lem)
{
	int i;
	int j;
	int room;
	int tab;
	
	i = 0;
	j = 1;
	while (i < lem->max_paths)
	{
		if (lem->sorted[i][lem->sorted[i][0] * -1] == -2)
		{
			while (i < lem->max_paths && lem->sorted[i][lem->sorted[i][0] * -1] == -2)
				i++;
		}
		if (i > (lem->max_paths -2))
			break ;
		tab = lem->sorted[i][0];
		j = i + 1;
		if (j < lem->max_paths && lem->sorted[j][0] == tab)
		{
			while (j < lem->max_paths && lem->sorted[j][0] == tab)
			{
				room = 0;
				while (lem->sorted[i][room] == lem->sorted[j][room] && lem->sorted[i][room] != -1)
					room++;
				if (lem->sorted[i][room] == -1)
					lem->sorted[j][room] = -2;
				j++;
			}
		}
		i++;
	}
}