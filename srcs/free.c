/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:50:53 by rbalbous          #+#    #+#             */
/*   Updated: 2019/11/22 15:21:56 by rbalbous         ###   ########.fr       */
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
				parser->free = 1;
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
