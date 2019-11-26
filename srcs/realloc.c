/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:01:59 by rbalbous          #+#    #+#             */
/*   Updated: 2019/11/25 22:06:42 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*check_alloc(t_page *info, t_block *parser, size_t size)
{
	int		type_size;
	t_page	*page;
	int		diff;
	t_block *tmp;

	type_size = 32 + 1016 * (TYPE_SIZE(size) > 0);
	tmp = parser - 24;
	if (TYPE_SIZE(size) == 0)
		page = g_malloc_pages.tiny;
	if (TYPE_SIZE(size) == 1)
		page = g_malloc_pages.small;
	if (TYPE_SIZE(size) == 2)
		page = g_malloc_pages.large;
	while (page != NULL)
	{
		diff = (tmp->address + tmp->size) - (void*)page;
		if (diff > 0 && diff < type_size * 13 && diff > size)
		{
			
			return (tmp->address + tmp->size);
		}
		temp_page = temp_page->prev;
	}
	
}

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
				if (parser->size >= size)
				{
					parser->size = size;
					return (parser->address);
				}
				return (check_alloc(info, parser, size));
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
