#include <stdlib.h>

int	main(void)
{
	int i;
  	int *a;

  	for (i=0; i < 10; i++){
    	a = malloc(sizeof(int) * 100);
  	}
 	free(a);
  	return 0;
}
