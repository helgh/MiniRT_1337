/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:26:40 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/22 18:12:11 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

static int	count_str(char const *str, char c)
{
	int	i;
	int	leng;

	i = 0;
	leng = 0;
	while (str[i] != 0)
	{
		while (str[i] == c && str[i] != 0)
			i++;
		if (str[i] != c && str[i] != 0)
			leng++;
		while (str[i] != c && str[i] != 0)
			i++;
	}
	return (leng);
}

static int	start(char const *str, char c)
{
	int	l;

	l = 0;
	while (str[l] != 0 && str[l] == c)
		l++;
	return (l);
}

static int	endstr(char const *str, char c)
{
	int	l;

	l = 0;
	while (str[l] != 0 && str[l] != c)
		l++;
	return (l);
}

static char	*coppy(t_scene *scene, char const *str, int l, char **all, int h)
{
	int		i;
	char	*s1;

	i = 0;
	s1 = (char *) ft_malloc(scene, sizeof(char) * l + 1, true);
	if (s1 == NULL)
	{
		while (h > 0)
		{
			h--;
			free (all[h]);
		}
		free (all);
		all = NULL;
		return (NULL);
	}
	while (i < l)
	{
		s1[i] = str[i];
		i++;
	}
	s1[i] = 0;
	return (s1);
}

char	**ft_split(t_scene *scene, char const *s, char c)
{
	int		i;
	char	**all;
	int		end;
	int		size;
	int		len;

	size = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	len = count_str(s, c);
	all = (char **)ft_malloc(scene, sizeof(char *) * (len + 1), true);
	if (all == NULL)
		return (NULL);
	while (i < len)
	{
		size += start(s + size, c);
		end = endstr(s + size, c);
		all[i] = coppy(scene, s + size, end, all, i);
		size += end;
		i++;
	}
	all[i] = NULL;
	return (all);
}
