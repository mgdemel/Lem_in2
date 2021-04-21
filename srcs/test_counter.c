#include "../libft/include/get_next_line.h"

int	main(void)
{
	int fd;
	char *line;
	int c;
	int a;

	c = 0;
	a = 9000;
	line = NULL;
	fd = 0;
	while (get_next_line(fd, &line) > 0)
	{
		c = ft_atoi(line);
		if (c < a && c != 0)
			a = c;
		ft_strdel(&line);
	}
	ft_putstr("Lowest number:");
	ft_putnbr(a);
	ft_putchar('\n');
}