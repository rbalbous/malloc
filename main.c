#include <stdlib.h>
#include <stdio.h>

int			main()
{
	char *str1;
	char *str2;
	int i = 0;

	str1 = malloc(50);
	str2 = malloc(50);

	while (i < 1000)
	{
		str1[i] = '1';
		i++;
 	}
	i = 0;
	while (i < 1000)
	{
		str2[i] = '2';
		i++;
 	}
	printf("%s %s\n", str1, str2);
	return (0);
}