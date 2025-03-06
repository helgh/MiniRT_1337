/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:05:28 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/06 17:57:05 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

char	*ft_strdup(t_scene *scene, const char *s1)
{
	int		i;
	char	*dup;

	i = ft_strlen(s1);
	dup = ft_malloc(scene, sizeof(char) * (i + 1));
	i = -1;
	while (s1[++i] != 0)
		dup[i] = s1[i];
	dup[i] = 0;
	return (dup);
}
