/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:50:53 by rbalbous          #+#    #+#             */
/*   Updated: 2019/11/14 16:43:26 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		free(void	*ptr)
{
	int		count;
	t_page	*info;
	t_block	*parser;

	info = g_malloc_pages.info;
	if (ptr == NULL)
		return ;
	if (info == NULL)
		return ;
	while (info)
	{
		parser = (t_block*)(info + sizeof(t_page));
		count = 0;
		while (count < 128)
		{
			if (parser == NULL)
			{
				break ;
			}
			if (ptr == parser->address)
			{
				parser->free = 1;
				return ;
			}
			parser += sizeof(t_block);
		}
		if (info->prev)
			info = info->prev;
		else
			break;
	}
	return ;
}
