/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:24:33 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/06 18:14:52 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s10;
	unsigned char	*s20;

	i = 0;
	s10 = (unsigned char *)s1;
	s20 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n && (s10[i] != 0 || s20[i] != 0))
	{
		if (s10[i] > s20[i])
			return (s10[i] - s20[i]);
		if (s10[i] < s20[i])
			return (s10[i] - s20[i]);
		i++;
	}
	return (0);
}
