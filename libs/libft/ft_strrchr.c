/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunajed <mmunajed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:53:01 by mmunajed          #+#    #+#             */
/*   Updated: 2024/10/12 14:25:11 by mmunajed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	ch;
	char			*ptr;
	size_t			index;

	index = ft_strlen(str);
	ch = (unsigned char)c;
	ptr = (char *)str + index;
	if (ch == '\0')
		return (ptr++);
	while (ptr >= str)
	{
		if (*ptr == ch)
			return (ptr);
		ptr--;
	}
	ptr = NULL;
	return (ptr);
}
