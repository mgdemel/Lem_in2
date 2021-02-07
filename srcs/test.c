


#include "../libft/include/libft.h"
#include <stdio.h>

char	*ft_strstr2(const char *haystack, const char *needle)
{
	int i;
	int a;
	char *temp;

	i = 0;
	a = 0;
	temp = ft_strnew(ft_strlen(haystack) - ft_strlen(needle) - 1);
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[i] != '\0')
	{
		if (needle[a] == '\0')
			return (NULL);
		while (haystack[a + i] == needle[a] && haystack[a + i] != '\0')
		{
			if (needle[a + 1] == '\0' && haystack[a + i + 1] != '\0')
				return ((char*)&haystack[i + ft_strlen(needle) + 1]); // start-r1  needle = start
			else if (needle[a + 1] == '\0' && haystack[a + i + 1] == '\0')
				return ((char*)temp); // start-r1 needle = r1
			a++;
		}
		if (haystack[i] != '-')
			temp[i] = haystack[i];
		a = 0;
		i++;
	}
	return (NULL);
}


int	main(void)
{
	char *haystack;
	char *needle;

	printf("\n");
	haystack = "start-r1";
	needle = "r1";
	printf("%s", ft_strstr2(haystack, needle));
	return (0);
}