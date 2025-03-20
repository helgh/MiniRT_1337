/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:13:16 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/20 00:14:43 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*l;
	unsigned char	s;
	size_t			i;

	l = (unsigned char *) b;
	s = (unsigned char) c;
	i = 0;
	while (i < len)
	{
		l[i] = c;
		i++;
	}
	return (b);
}
