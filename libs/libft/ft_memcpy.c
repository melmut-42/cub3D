/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunajed <mmunajed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:51:18 by mmunajed          #+#    #+#             */
/*   Updated: 2024/10/07 11:51:19 by mmunajed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*pdest;
	const char		*psrc;

	psrc = (const char *)src;
	pdest = (unsigned char *) dest;
	if (!psrc && !pdest)
		return (0);
	pdest = (unsigned char *)dest;
	psrc = (const char *)src;
	while (n != 0)
	{
		*pdest = *psrc;
		psrc++;
		pdest++;
		n--;
	}
	return (dest);
}
