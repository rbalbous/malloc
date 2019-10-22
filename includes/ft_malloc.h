/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 23:45:19 by rbalbous          #+#    #+#             */
/*   Updated: 2019/10/22 16:10:24 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# include <sys/mman.h>

/*
**size allocated by the mmap
*/

# define TINY 32
# define SMALL 1048

typedef struct s_block			t_block;
typedef struct s_page			t_page;
typedef struct s_malloc_pages	t_malloc_pages;
extern t_malloc_pages			g_malloc_pages;

struct s_page
{
	t_page	*next;
	t_page	*prev;
};

struct		s_block
{
	size_t	size;
	int		free;
	void	*address;
};

struct		s_malloc_pages
{
	t_page				*tiny;
	t_page				*small;
	t_block				*large;
	t_page				*info;
};

enum e_type
{
	tiny,
	small,
	large
};

void		*malloc(size_t size);

#endif
