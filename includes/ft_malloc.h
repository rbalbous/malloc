/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 23:45:19 by rbalbous          #+#    #+#             */
/*   Updated: 2019/10/15 01:45:54 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# include <sys/mman.h>

/*
**size allocated by the mmap
*/

# define TINY 128
# define SMALL 4096

typedef struct s_block			t_block;
typedef struct s_page			t_page;
typedef struct s_malloc_pages	t_malloc_pages;
extern t_malloc_pages			g_malloc_pages;

struct s_page
{
	t_page	*next;
	t_page	*prev;
	t_block *current;
};

struct		s_block
{
	size_t	size;
	int		free;
	t_block	*next;
	t_block	*prev;
};

struct		s_malloc_pages
{
	t_page				*info;
	t_page				*tiny;
	t_page				*small;
	t_block				*large;
};

enum e_type
{
	tiny,
	small,
	large
};

void		*malloc(size_t size);

#endif
