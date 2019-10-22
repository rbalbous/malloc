/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 21:55:34 by rbalbous          #+#    #+#             */
/*   Updated: 2019/10/22 17:04:35 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_malloc_pages	g_malloc_pages = {NULL, NULL, NULL, NULL};

void		*init_page(t_page **page, size_t type_size)
{
	t_page *new;

	new = mmap(NULL, type_size * 128, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	new->next = NULL;
	if (*page == NULL)
		new->prev = NULL;
	else
	{
		new->prev = *page;
		(*page)->next = new;
	}
	return (*page + sizeof(t_page));
}

void		*add_block(t_page **info, t_page **page, t_block *block)
{
	t_page	**temp;
	int		ret;

	while ( != NULL)
	{
		temp = (*page)->prev;
		if (ret = find_space(info, temp, block, NULL) == 1)
			return (block->address);
		
	}
}

int			find_space(t_page **info, t_page **page, t_block *block, t_block *parser)
{
	int			tot_size;
	int			size_index;
	int			count;

	tot_size = getpagesize();
	size_index = 0;
	count = 0;
	if (!parser)
		parser = (t_block*)(*info + sizeof(t_page));
	while (parser->size > tot_size - size_index)
	{
		if (parser->free == 1 && parser->size <= block->size)
		{
			block->address = parser->address;
			return (1);
		}
		size_index += parser->size;
		if (count > 127)
		{
			return (2);
		}
		*parser = *(parser + sizeof(t_block));
	}
}

void		*init_page_info(t_page **info, t_page **page, size_t size, size_t type_size)
{
	t_page		*new;
	t_block		*block;

	new = mmap(NULL, type_size * 128, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	new->next = NULL;
	if (*info == NULL)
		new->prev = NULL;
	else
	{
		new->prev = *info;
		(*info)->next = new;
	}
	*info = new;
	*info += sizeof(t_page);
	block = (t_block*)*info;
	block->size = size;
	block->free = 0;
	if (!(*page))
		return(block->address = init_page(page, type_size));
	else
		if (((*page)->prev) != NULL)
			add_block(info, page, block);
}

void		*malloc_tiny_small(size_t size, size_t type_size, t_page **page)
{

	if (!(g_malloc_pages.info))
		return (init_page_info(&g_malloc_pages.info, page, size, type_size));
	else
		return (NULL);
	// block = g_malloc_pages.info + sizeof(t_page);
	// while (*info->block->next != NULL)
	// {
	// 	if  (*info->free && *info->size > size)
	// 		block_reclaim()
	// 	if (*info->block->nb == 31)
	// 		return (init_page_info(info, size));
		
		
	// }
	
	// if (new == NULL)
	// {
	// 	new = mmap(NULL, type_size * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	// 	new->prev = NULL;
		
	// 	block = new + sizeof(t_page);
	// 	block->size = 
	// }
	
	
}

void		*malloc_large(size_t size, t_page **page)
{
	t_block *block;
	(void)page;

	block = mmap(NULL, (size + sizeof(t_block)) * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	return (NULL);
}

void		*malloc(size_t size)
{
	const t_uint8	type = (size > TINY) + (size > SMALL);

	if (!size)
		return (NULL);
	if (type == tiny)
		return (malloc_tiny_small(size, TINY, &g_malloc_pages.tiny));
	// if (type == small)
		// return (malloc_tiny_small(size, SMALL, g_malloc_pages.small));
	// if (type == large)
	ft_printf("ok\n");
	return (NULL);
}
