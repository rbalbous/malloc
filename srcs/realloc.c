/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:01:59 by rbalbous          #+#    #+#             */
/*   Updated: 2019/11/22 18:40:43 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*realloc(void *ptr, size_t size)
{
	int		count;
	t_page	*info;
	t_block	*parser;

	info = g_malloc_pages.info;
	if (ptr == NULL || info == NULL || size == 0)
		return (NULL);
	while (info)
	{
		parser = (t_block*)(info + 16);
		count = 0;
		while (count < 14)
		{
			if (parser == NULL)
				break ;
			if (ptr == parser->address)
			{
				ft_printf("ca doit passer la\n");
				check_alloc(info, );
				return ;
			}
			parser += 24;
		}
		if (info->prev)
			info = info->prev;
		else
			break;
	}
	return ;
}
