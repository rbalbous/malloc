/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:22:57 by rbalbous          #+#    #+#             */
/*   Updated: 2020/02/13 15:52:48 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


void	init_modu(char modu[16])
{
	modu[0] = '0';
	modu[1] = '1';
	modu[2] = '2';
	modu[3] = '3';
	modu[4] = '4';
	modu[5] = '5';
	modu[6] = '6';
	modu[7] = '7';
	modu[8] = '8';
	modu[9] = '9';
	modu[10] = 'a';
	modu[11] = 'b';
	modu[12] = 'c';
	modu[13] = 'd';
	modu[14] = 'e';
	modu[15] = 'f';
}

int		print_address(uint32_t n)
{
	char			str[7];
	static char		modu[16];
	int				len;

	if (!modu[0])
		init_modu(modu);
	len = 7;
	str[0] = '0';
	str[1] = 'x';
	while (len-- > 2)
	{
		str[len] = modu[n & 15] - ((n & 15) > 9) * 32;
		n /= 16;
	}
	write(1, str, 7);
	return (0);
}

t_block	*get_smaller_address(t_block *address, t_page *info, size_t size, void *last)
{
	t_block		*parser;
	int			count;

	// ft_printf("la ca va\n");
	count = 0;
	parser = (t_block*)(info + 16);
	// ft_printf("la ca va\n");
	while (parser != NULL && count < 14)
	{
		// ft_printf("boucle get_smaller_address\n");
		// ft_printf("address get smaller : %d %d\n", last, parser->address);
		// ft_printf("parser address and address address: %d %d\n", parser->address, address->address);
		ft_printf("ca rentre la\n");
		if (parser->size <= size && parser->address != NULL && parser->address > last)
		{
			if (address->address == 0 || parser->address < address->address)
			{
				ft_printf("condition 1\n");
				address = parser;
			}
		}
		parser += 24;
		count++;
	}
	// print_address((uint32_t)address->address);
	return (address);
}

void		show_alloc_mem()
{
	t_block *address;
	void	*last;
	t_page *info;
	t_page *tmp_info;

	address = NULL;
	info = g_malloc_pages.info;
	write(1, "TINY : ", 7);
	print_address((uint32_t)(g_malloc_pages.tiny));
	write(1, "\n", 1);
	// ft_printf("show alloc mem\n");
	// print_address((uint32_t)address->address);
	last = NULL;
	// print_address((uint32_t)address->address);
	while (1)
	{
		tmp_info = info;
		ft_printf("boucle\n");
		while (tmp_info != NULL)
		{
			address = get_smaller_address(address, tmp_info, TINY, last);
			ft_printf("boucle 1\n");
			tmp_info = tmp_info->prev;
		}
		ft_printf("ca passe la boucle\n");
		ft_printf("%d %d\n", address->address, last);
		if (last == address->address)
		{
			break;
		}
		print_address((uint32_t)address->address);
		write(1, " - ", 3);
		print_address((uint32_t)(address->address + address->size));
		write(1, "\n", 1);
		last = address->address;
	}
	write(1, "SMALL : ", 7);
	print_address((uint32_t)(g_malloc_pages.small));
	write(1, "\n", 1);
	while (1)
	{
		ft_printf("%d %d\n", address->address, last);
		tmp_info = info;
		while (tmp_info != NULL)
		{
			address = get_smaller_address(address, tmp_info, SMALL, last);
			tmp_info = tmp_info->prev;
		}
		if (last == address->address)
		{
			break;
		}
		print_address((uint32_t)address->address);
		write(1, " - ", 3);
		print_address((uint32_t)(address->address + address->size));
		write(1, "\n", 1);
		last = address->address;
	}
	// print_address(0xBBEEF);
	write(1, "\n", 1);
}
