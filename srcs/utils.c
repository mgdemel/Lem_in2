#include "../includes/lem_in.h"

/*
**	This functions will find the needle in the haystack, then return
**	the other part of the haystack minus the middle character
**	dividing them.
*/

char	*needle_crop(const char *haystack, const char *needle)
{
	int i;
	int a;
	char *temp;

	i = 0;
	a = 0;
	temp = ft_strnew(ft_strlen(haystack) - ft_strlen(needle) - 1);
	while (haystack[i] != '\0')
	{
		if (needle[a] == '\0')
			return (NULL);
		while (haystack[a + i] == needle[a] && haystack[a + i] != '\0')
		{
			if (needle[a + 1] == '\0' && haystack[a + i + 1] != '\0')
				return ((char*)&haystack[i + ft_strlen(needle) + 1]);
			else if (needle[a + 1] == '\0' && haystack[a + i + 1] == '\0')
				return ((char*)temp);
			a++;
		}
		if (haystack[i] != '-')
			temp[i] = haystack[i];
		a = 0;
		i++;
	}
	return (NULL);
}
