#include <stdlib.h>
#include <stdio.h>
#include "libft/includes/libft.h"
#include "includes/ft_malloc.h"

int			main()
{
	char *str1;
	char *str2;
	int i = 0;

	str1 = (char*)ft_malloc(21);
	ft_printf("malloc 1 done\n");
	str2 = (char*)ft_malloc(50);

	while (i < 20)
	{
		str1[i] = '1';
		i++;
 	}
	 ft_printf("%s\n", str1);
	 i = 0;
	while (i < 1000)
	{
		str2[i] = '2';
		i++;
 	}
	printf("%s %s\n", str1, str2);
	return (0);
}
