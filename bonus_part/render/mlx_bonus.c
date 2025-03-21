/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:47:53 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/21 01:16:45 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

static int	handle_event(int keycode, t_scene *scene)
{
	if (keycode == 53)
	{
		mlx_destroy_image(scene->mlx->mlx, scene->mlx->mlx_img);
		mlx_clear_window(scene->mlx->mlx, scene->mlx->mlx_win);
		mlx_destroy_window(scene->mlx->mlx, scene->mlx->mlx_win);
		__ft_free(scene, 0);
	}
	return (0);
}

static int	close_window(t_scene *scene)
{
	mlx_destroy_image(scene->mlx->mlx, scene->mlx->mlx_img);
	mlx_clear_window(scene->mlx->mlx, scene->mlx->mlx_win);
	mlx_destroy_window(scene->mlx->mlx, scene->mlx->mlx_win);
	__ft_free(scene, 0);
	return (0);
}

void	render(t_scene *scene)
{
	t_mlx	*m;

	m = scene->mlx;
	if (m->init == false)
		m->mlx = mlx_init();
	m->mlx_win = mlx_new_window(m->mlx, WIDTH, HEIGHT, "miniRT_bonus");
	m->mlx_img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	m->pixels = mlx_get_data_addr(m->mlx_img, &m->bpp, &m->s_line, &m->endian);
	draw(scene, m);
	mlx_put_image_to_window(m->mlx, m->mlx_win, m->mlx_img, 0, 0);
	mlx_key_hook(m->mlx_win, &handle_event, scene);
	mlx_hook(m->mlx_win, 17, 0, close_window, scene);
	mlx_loop(m->mlx);
}
