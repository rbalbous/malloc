/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 23:45:19 by rbalbous          #+#    #+#             */
/*   Updated: 2019/10/12 01:41:50 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# include <sys/mman.h>

/*
**size allocated by the mmap
*/
# define MEM_SIZE 10000000

typedef struct s_block	t_block;
typedef struct s_page	t_page;

struct s_page
{
	t_block *block;
	t_block *free;
	t_page	*next;
	t_page	*prev;
};


struct		s_block
{
	size_t	size;
	int		free;
	t_block	*next;
	t_block *prev;
};

void		*ft_malloc(size_t size);

#endif
