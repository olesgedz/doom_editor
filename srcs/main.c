/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:53:03 by jblack-b          #+#    #+#             */
/*   Updated: 2019/04/18 15:48:02 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "libsdl.h"
#include "doom_editor.h"

void ft_put_vertex(t_sdl *sdl)
{
	ft_image_set_pixel(sdl, &(t_point){sdl->mouse.x, sdl->mouse.y}, 0xFF0000);
}

void ft_mouse_pressed(t_sdl *sdl, SDL_Event *ev)
{
	sdl->mouse.pressed = 1;
	sdl->mouse.last_x = sdl->mouse.x;
	sdl->mouse.last_y = sdl->mouse.y;
	sdl->mouse.x = ev->button.x;
	sdl->mouse.y = ev->button.y;
	ft_put_vertex(sdl);
	ft_plot_line(sdl, &(t_point){sdl->mouse.last_x, sdl->mouse.last_y}, &(t_point){sdl->mouse.x, sdl->mouse.y}, 0x00FF00);
}

int		ft_input_keys(t_sdl *sdl, SDL_Event *ev)
{
	switch (ev->type)
		{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				switch (ev->key.keysym.sym)
				{
					case SDLK_LCTRL:
					case SDLK_RCTRL:
					case SDLK_ESCAPE: ft_exit(NULL); break;
					case SDLK_z: ; break;
					case SDLK_x: ; break;
					case SDLK_c: ; break;
					default: break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:  ft_mouse_pressed(sdl, ev);
				break;
			case SDL_QUIT: ft_exit(NULL);
		}
	return (1);
}

void ft_update(t_sdl *sdl)
{
	while(1)
	{
		ft_surface_clear(sdl);
		ft_input(sdl, &ft_input_keys);
		ft_image_set_pixel(sdl, &(t_point){50,50}, 0xFF0000);
		ft_plot_line(sdl, &(t_point){0,0}, &(t_point){500,500}, 0xFF0000);
		ft_surface_present(sdl);
	}
}

int main()
{
	t_game game;
	t_sdl sdl;
	game.sdl = sdl;
	game.image = malloc(sizeof(Uint32) * WIN_H * WIN_W);
	printf("Hello\n");
	ft_init_window(&sdl, WIN_W, WIN_H);
	ft_update(&sdl);
	ft_exit(NULL);
}