/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 21:55:34 by rbalbous          #+#    #+#             */
/*   Updated: 2019/10/15 01:46:19 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_malloc_pages	g_malloc_pages = {NULL, NULL, NULL, NULL};

void		*malloc_tiny_small(size_t size, t_page **page)
{
	if (!g_malloc_pages)
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
		return (malloc_tiny_small(size, g_malloc_pages.tiny));
	if (type == small)
		return (malloc_tiny_small(size, g_malloc_pages.small));
	if (type == large)
	ft_printf("ok\n");
	return (NULL);
}
