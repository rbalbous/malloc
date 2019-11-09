/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 21:55:34 by rbalbous          #+#    #+#             */
/*   Updated: 2019/11/09 15:03:40 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_malloc_pages	g_malloc_pages = {NULL, NULL, NULL, NULL};
int		g_type_size;

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

void		insert_block(t_block *parser, t_block *block, t_page **page)
{
	int		add_diff;
	int		page_size;

	add_diff = 0;
	page_size = getpagesize();
	while (*page != NULL)
	{
		add_diff = parser->address - (void*)*page;
		if (add_diff < page_size)
		{
			if (page_size - add_diff + parser->size + 1 < block->size)
			{
				block->address = parser->address + parser->size + 1;
			}
			else
			{
				block->address = init_page(page, g_type_size);
			}
			return ;
		}
		if ((*page)->prev != NULL)
		{
			*page = (*page)->prev;
		}
		else
		{
			block->address = init_page(page, g_type_size);
			return ;
		}
	}
}

int			find_space(t_page **info, t_page **page, size_t size, t_block *parser)
{
	int			tot_size;
	int			size_index;
	int			count;

	tot_size = getpagesize();
	size_index = 0;
	count = 0;
	if (!parser)
		parser = (t_block*)(*info + sizeof(t_page));
	while (parser != NULL)
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
	*parser = *block;
	insert_block(parser - sizeof(t_block), block, page);
	return (0);
}

void		init_page_info(t_page **info, t_page **page, size_t size, size_t type_size)
{
	t_page		*new;

	ft_printf("init\n");
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
}

	if (!(*page))
		return (block->address = init_page(page, type_size));
	else
	{
		if (((*page)->prev) != NULL)
			return (add_block(info, page, block, g_type_size));
		else
			return (block->address = init_page(page, type_size));
	}
}

void		*add_block(t_page **info, t_page **page, size_t type_size)
{
	int		ret;
	t_block		*block;

	ft_printf("add_block\n");
	while (*info != NULL)
	{
		if ((ret = find_space(info, page, block, NULL)) == 1 || ret == 0)
			return (block->address);
		else
		{
			if ((*info)->prev == NULL)
			{
				while ((*info)->next != NULL)
					*info = (*info)->next;
				return (init_page_info(info, page, block->size, type_size));
			}
			else
			{
				*info = (*info)->prev;
				continue ;
			}
		}
	}
	return (init_page_info(info, page, block->size, type_size));
}

void		*malloc_tiny_small(size_t size, size_t type_size, t_page **page)
{
	ft_printf("mts\n");
	if (!(g_malloc_pages.info))
		init_page_info(&g_malloc_pages.info, page, size, type_size);
	return (add_block(&g_malloc_pages.info, page, type_size));
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

	ft_printf("mlarge\n");
	block = mmap(NULL, (size + sizeof(t_block)) * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	return (NULL);
}

void		*ft_malloc(size_t size)
{
	int		g_type_size = (size > TINY) + (size > SMALL);

	ft_printf("type size : %d\n", g_type_size);
	if (g_type_size == tiny)
	{
		ft_printf("ca passe dans tiny\n");
		return (malloc_tiny_small(size, TINY, &g_malloc_pages.tiny));
	}
	else if (g_type_size == small)
	{
		ft_printf("ca passe dans small\n");
		return (malloc_tiny_small(size, SMALL, &g_malloc_pages.small));
	}
	else if (g_type_size == large)
	ft_printf("ok\n");
	return (NULL);
}
