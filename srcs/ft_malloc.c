/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 21:55:34 by rbalbous          #+#    #+#             */
/*   Updated: 2019/11/14 00:09:58 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_malloc_pages	g_malloc_pages = {NULL, NULL, NULL, NULL};

void		*init_page(t_page **page, size_t size)
{
	t_page	*new;
	int		type_size;

	type_size = 32 + 1016 * (TYPE_SIZE(size) > 0);
	ft_printf("type_size %d\n", type_size);
	new = mmap(NULL, type_size * 128, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	ft_printf("page inited 1\n");
	new->next = NULL;
	ft_printf("page inited 2\n");
	new->prev = *page;
	ft_printf("page inited 3\n");
	if (*page)
		(*page)->next = new;
	ft_printf("page inited 4\n");
	*page = new;
	ft_printf("page inited 5\n");
	return (*page + sizeof(t_page));
}

void		*find_space(t_page **info, t_page **page, size_t size, int *count)
{
	int			tot_size;
	t_block		*parser;

	tot_size = getpagesize();
	parser = (t_block*)(*info + sizeof(t_page));
	while (parser->address != NULL)
	{
		if (parser->free == 1 && parser->size <= size)
		{
			parser->size = size;
			parser->free = 0;
			return (parser->address);
		}
		if (*count > 127)
		{ 
			ft_printf("ptdr\n");
			return (NULL);
		}
		*parser = *(parser + sizeof(t_block));
		(*count)++;
	}
	ft_printf("parser address null\n");
	parser->size = size;
	parser->free = 0;
	return (parser->address = init_page(page, size));
}

void		init_page_info(t_page **info, size_t type_size)
{
	t_page		*new;

	(void)type_size;
	ft_printf("init\n");
	new = mmap(NULL, 16 + 32 * 128, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	new->next = NULL;
	new->prev = *info;
	if (*info)
		(*info)->next = new;
	*info = new;
}

void		*add_block(t_page **info, t_page **page, size_t type_size, size_t size)
{
	void		*ret;
	int			count;

	ft_printf("add_block\n");
	while (*info != NULL)
	{
		count = 1;
		if ((ret = find_space(info, page, size, &count)) != NULL)
			return (ret);
		else
		{
			if ((*info)->prev == NULL)
			{
				while ((*info)->next != NULL)
					*info = (*info)->next;
				init_page_info(info, type_size);
				return (find_space(info, page, size, &count));
			}
			else
			{
				*info = (*info)->prev;
				continue ;
			}
		}
	}
	return (NULL);
}

void		*malloc_tiny_small(size_t size, size_t type_size, t_page **page)
{
	ft_printf("mts %d\n", type_size);
	if (!(g_malloc_pages.info))
		init_page_info(&g_malloc_pages.info, type_size);
	return (add_block(&g_malloc_pages.info, page, type_size, size));
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
	int type_size;
	
	type_size = TYPE_SIZE(size);
	if (type_size == tiny)
	{
		ft_printf("ca passe dans tiny\n");
		return (malloc_tiny_small(size, TINY, &(g_malloc_pages.tiny)));
	}
	else if (type_size == small) 
	{
     	
		ft_printf("ca passe dans small\n");
		return (malloc_tiny_small(size, SMALL, &(g_malloc_pages.small)));
	}
	else if (type_size == large)
	{
		return (NULL); //to do
	}
	ft_printf("ok\n");
	return (NULL);
}
