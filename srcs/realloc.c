/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:01:59 by rbalbous          #+#    #+#             */
/*   Updated: 2019/12/01 15:17:04 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*check_alloc(t_page *page, t_block *parser, size_t size, size_t type_size)
{
	size_t	diff;
	t_block *tmp;

	tmp = parser - 24;
	while (page != NULL)
	{
		diff = (tmp->address + tmp->size) - (void*)page;
		if (diff > 0 && diff < type_size * 13 && diff > size)
		{
			return (tmp->address + tmp->size);
		}
		page = page->prev;
	}
	return (NULL);
	
}

void		*realloc(void *ptr, size_t size)
{
	int		count;
	t_page	*info;
	t_block *last;
	t_block	*parser;
	size_t	type_size;
	t_page	*page;

	// ft_printf("ca rentre?\n");
	type_size = 32 + 1016 * (TYPE_SIZE(size) > 0);
	if (TYPE_SIZE(size) == 0)
		page = g_malloc_pages.tiny;
	if (TYPE_SIZE(size) == 1)
		page = g_malloc_pages.small;
	info = g_malloc_pages.info;
	if (ptr == NULL || size == 0)
		return (NULL);
	// ft_printf("%d\n", TYPE_SIZE(size));
	while (info && TYPE_SIZE(size) < 2)
	{
		parser = (t_block*)(info + 16);
		count = 0;
		while (count < 14)
		{
			if (parser == NULL)
			{
				last = parser;
				break ;
			}
			if (ptr == parser->address)
			{
				// ft_printf("ca doit passer la\n");
				if (parser->size >= size)
				{
					parser->size = size;
					return (parser->address);
				}
				if ((parser->address = check_alloc(page, parser, size, type_size)) != NULL)
				{
					return (parser->address);
				}
				else
				{
					break ;
				}
			}
			parser += 24;
			last = parser;
			count++;
		}
		if (info->prev)
			info = info->prev;
		else
			break ;
	}
	// ft_printf("large test\n");
	parser = g_malloc_pages.large;
	while (parser != NULL)
	{
		if (ptr == parser + 24)
		{
			if (size > parser->size * 100)
			{
				parser->free = 1;
				return (ft_malloc(size));
			}
			else
			{
				parser->size = size;
				return (parser + 24);
			}
		}
		parser = parser->address;
	}
	// if (last)
	// {
	// 	last->size = size;
	// 	last->free = 0;
	// 	return(last->address = init_page(&page, size));
	// }
	// else
	// {
	// 	init_page_info(&info, type_size);
	// 	parser = (t_block*)(info + 16);
	// 	parser->size = size;
	// 	parser->free = 0;
	// 	return (parser->address = page + 16);
	// }
	return (NULL);
}
