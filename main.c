#include "ft_malloc.h"

int			main()
{
	malloc(127);
	malloc(8191);
	malloc(8193);
	ft_printf("%d", getpagesize());
	return (0);
}