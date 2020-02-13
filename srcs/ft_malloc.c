/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 21:55:34 by rbalbous          #+#    #+#             */
/*   Updated: 2019/12/03 14:36:44 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_malloc_pages	g_malloc_pages = {NULL, NULL, NULL, NULL};

void		*init_page(t_page **page, size_t size)
{
	t_page	*new;
	int		type_size;

	// ft_printf("INIT PAGE\n\n");
	type_size = 32 + 1016 * (TYPE_SIZE(size) > 0);
	new = mmap(NULL, type_size * 128, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	new->next = NULL;
	new->prev = *page;
	if (*page)
		(*page)->next = new;
	*page = new;
	return (*page + 16);
}

void		*add_or_init(t_page **page, t_block *block, size_t size, int *count)
{
	t_block *tmp;
	int		diff;
	int		type_size;
	t_page	*temp_page;

	temp_page = *page;
	// ft_printf("ca rentre la ?\n");
	type_size = 32 + 1016 * (TYPE_SIZE(size) > 0);
	// ft_printf("count : %d\n", *count);
	if (*count == 1)
	{
		// ft_printf("ca devrait etre la\n");
		return (init_page(page, size));
	}
	tmp = block - 24;
	// ft_printf("address block = %d\n", block);
	// ft_printf("block_size %d\n", block->size);
	// ft_printf("block_free %d\n", block->free);
	// ft_printf("block_address %d\n", block->address);
	// ft_printf("address tmp = %d\n", tmp);
	// ft_printf("address %d\n", tmp->address);
	while (temp_page != NULL)
	{
		// ft_printf("boucle\n");
		// ft_printf("address %d\n", tmp->address);
		// ft_printf("address size %d\n", tmp->address + tmp->size);
		diff = (tmp->address + tmp->size) - (void*)temp_page;
		// ft_printf("%d\n", diff);
		if (diff > 0 && diff < type_size * 13)
		{
			// ft_printf("ADD\n\n");
			return (tmp->address + tmp->size);
		}
		temp_page = temp_page->prev;
	}
	return (init_page(page, size));
}

void		*find_space(t_page **info, t_page **page, size_t size, int *count)
{
	t_block		*parser;

	// ft_printf("info address : %d\n", *info);
	parser = (t_block*)(*info + 16);
	// ft_printf("parser %d\n", parser);
	while (parser->address != NULL)
	{
		// ft_printf("parser boucle 1 %d\n", parser);
		// ft_printf("parser address 1 %d\n", parser->address);
		if (parser->free == 1 && parser->size <= size)
		{
			parser->size = size;
			parser->free = 0;
			return (parser->address);
		}
		// ft_printf("count : %d\n", *count);
		if (*count > 13)
		{ 
			// ft_printf("count\n");
			return (NULL);
		}
		parser = parser + 24;
		// ft_printf("parser boucle 2 %d\n", parser);
		(*count)++;
	}
	// ft_printf("parser 2 %d\n", parser);
	parser->size = size;
	parser->free = 0;
	return (parser->address = add_or_init(page, parser, size, count));
}

void		init_page_info(t_page **info, size_t type_size)
{
	t_page		*new;

	(void)type_size;
	// ft_printf("init\n");
	new = mmap(NULL, 16 + 32 * 128, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	new->next = NULL;
	new->prev = *info;
	if (*info)
		(*info)->next = new;
	*info = new;
	// ft_printf("info address : %d\n", *info);
}

void		*add_block(t_page **info, t_page **page, size_t type_size, size_t size)
{
	void		*ret;
	int			count;

	// ft_printf("add_block\n");
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
				count = 1;
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
	// ft_printf("mts %d\n", type_size);
	if (!(g_malloc_pages.info))
		init_page_info(&g_malloc_pages.info, type_size);
	return (add_block(&g_malloc_pages.info, page, type_size, size));
}

void		*malloc_large(size_t size, t_block **block)
{
	t_block *current;
	t_block *temp;

	ft_printf("mlarge\n");
	temp = *block;
	while (temp != NULL)
	{
		if (temp->free == 1 && temp->size <= size)
		{
			temp->free = 0;
			temp->size = size;
			return (temp->address);
		}
		temp = temp->address;
	}
	current = mmap(NULL, (size + 24) * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	current->size = size;
	current->free = 0;
	if (!(*block))
	{
		current->address = NULL;
	}
	else
	{
		current->address = *block;
	}
	*block = current;
	return (*block + 24);
}

void		*ft_malloc(size_t size)
{
	int type_size;
	
	type_size = TYPE_SIZE(size);
	if (type_size == tiny)
	{
		// ft_printf("ca passe dans tiny\n");
		return (malloc_tiny_small(size, TINY, &(g_malloc_pages.tiny)));
	}
	else if (type_size == small) 
	{
     	
		// ft_printf("ca passe dans small\n");
		return (malloc_tiny_small(size, SMALL, &(g_malloc_pages.small)));
	}
	else if (type_size == large)
	{
		return (malloc_large(size, &(g_malloc_pages.large)));
	}
	ft_printf("ok\n");
	return (NULL);
}
