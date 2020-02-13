#include <stdlib.h>
#include <stdio.h>
#include "libft/includes/libft.h"
#include "includes/ft_malloc.h"

int			main()
{
	char *str1;
	char *str2;
	char *str3;
	char *str4;
	int i = 0;
	int j = 0;

	while (i < 130)
	{
		j = 0;
		str1 = (char*)ft_malloc(21);
		while (j < 20)
		{
			str1[j] = '1';
			j++;
		}
		// ft_printf("%s\n", str1);
		i++;
	}
	i = 0;
	free(str1);
	str1 = (char*)ft_malloc(21);
	// ft_printf("malloc 1 done\n");
	str2 = (char*)ft_malloc(50);
	while (i < 1000)
	{
		str2[i] = '2';
		i++;
	 }
	free(str2);
	str2 = realloc(str2, 40);
	i = 0;
	while (i < 20)
	{
		str1[i] = '1';
		i++;
	 }
	str3 = (char*)ft_malloc(6000);
	str4 = (char*)ft_malloc(6500);
	i = 0;
	while (i < 6000)
	{
		str3[i] = '3';
		i++;
	}
	// ft_printf("%s\n %s\n %s\n", str1, str2, str3);
	free(str3);
	// ft_printf("\n");
	show_alloc_mem();
	return (0);
}
