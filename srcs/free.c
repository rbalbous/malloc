/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:50:53 by rbalbous          #+#    #+#             */
/*   Updated: 2019/12/01 15:13:05 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		free(void	*ptr)
{
	int		count;
	t_page	*info;
	t_block	*parser;

	info = g_malloc_pages.info;
	if (ptr == NULL || info == NULL)
		return ;
	// ft_printf("free 1\n");
	while (info)
	{
		// ft_printf("loop 1\n");
		parser = (t_block*)(info + 16);
		count = 0;
		while (count < 14)
		{
			// ft_printf("loop 2\n");
			if (parser == NULL)
				break ;
			if (ptr == parser->address)
			{
				// ft_printf("ca doit passer la\n");
				parser->free = 1;
				return ;
			}
			parser += 24;
			count++;
		}
		if (info->prev)
			info = info->prev;
		else
			break;
	}
	// ft_printf("ca va jusque la?\n");
	parser = g_malloc_pages.large;
	while (parser != NULL)
	{
		// ft_printf("segfault ici?\n");
		if (ptr == parser + 24)
		{
			// ft_printf("ca free les larges \n");
			parser->free = 1;
		}
		parser = parser->address;
	}
}
