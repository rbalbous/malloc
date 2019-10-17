/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 21:55:34 by rbalbous          #+#    #+#             */
/*   Updated: 2019/10/17 20:50:46 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_malloc_pages	g_malloc_pages = {NULL, NULL, NULL, NULL};

void		init_pages_info(t_page **page, size_t size)
{
	t_page		*new;

	new = mmap(NULL, sizeof(t_block) * 32, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	new->prev = NULL;
	if (*page = NULL)
		new->next = NULL;
	else
		new->next = *page;
	*page = new;
	*page->block->size = size;
	*page->block->free = 0;
	*page->block->nb = 1;
	*page->block->prev = NULL;
	*page->block->nb = NULL;
}

void		*malloc_tiny_small(size_t size, size_t type_size, t_page **page, t_page **info)
{
	t_page		*new;
	t_block		*block;

	new = *page;
	if (!(*info))
		return (init_page_info(info, size));
	while (*info->block->next != NULL)
	{
		if  (*info->free && *info->size > size)
			block_reclaim()
		if (*info->block->nb == 31)
			return (init_page_info(info, size));
		
		
	}
	
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
	
	block = mmap(NULL, (size + sizeof(t_block)) * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

void		*malloc(size_t size)
{
	void	*mem;
	const t_uint8	type = (size > TINY) + (size > SMALL);

	if (!size)
		return (NULL);
	if (type == tiny)
		return (malloc_tiny_small(size, TINY, &g_malloc_pages->tiny, &g_malloc_pages->info));
	if (type == small)
		return (malloc_tiny_small(size, SMALL, g_malloc_pages.small));
	if (type == large)
	ft_printf("ok\n");
	return (NULL);
}
