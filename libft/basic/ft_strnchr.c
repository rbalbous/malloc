/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 16:35:02 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/27 19:59:13 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *str, int c, size_t len)
{
	int	i;

	i = 0;
	if (c == 0)
		return ((char*)(str + len));
	while (str[i] && len-- > 0)
	{
		if (str[i] == (char)c)
			return ((char*)(str + i));
		i++;
	}
	return (NULL);
}
