/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:53:03 by jblack-b          #+#    #+#             */
/*   Updated: 2019/04/19 02:04:21 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "libsdl.h"
#include "doom_editor.h"


t_game game;
void ft_put_vertex(t_sdl *sdl)
{
	ft_put_pixel(sdl->surface, &(t_point){sdl->mouse.x, sdl->mouse.y}, 0xFF0000);
}

void ft_mouse_pressed(t_sdl *sdl, SDL_Event *ev)
{
	sdl->mouse.pressed = 1;
	sdl->mouse.last_x = sdl->mouse.x;
	sdl->mouse.last_y = sdl->mouse.y;
	sdl->mouse.x = ev->button.x;
	sdl->mouse.y = ev->button.y;
	ft_put_vertex(sdl);
	ft_plot_line(game.sdl->surface, &(t_point){sdl->mouse.last_x, sdl->mouse.last_y}, &(t_point){sdl->mouse.x, sdl->mouse.y}, 0x00FF00);
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

void ft_update(t_game *game)
{
	while(1)
	{
		//ft_surface_clear(game->sdl->surface);
		ft_input(game->sdl, &ft_input_keys);
		ft_plot_line(game->sdl->surface, &(t_point){0,0}, &(t_point){500,500}, 0xFF0000);
		//  SDL_UpdateTexture(game->sdl->texture, NULL,\
		//  game->image->data, game->image->width * sizeof(Uint32));
		ft_put_pixel(game->sdl->surface, &(t_point){500,500}, 0xFF0000);
		ft_surface_present(game->sdl, game->sdl->surface);
	}
}

int main()
{
	
	game.sdl = malloc(sizeof(t_sdl));
	game.image = ft_surface_create(WIN_W, WIN_H);
	ft_init_window(game.sdl, WIN_W, WIN_H);
	printf("%zu, %zu\n", game.sdl->surface->height, game.sdl->surface->width);

	ft_update(&game);
	ft_exit(NULL);
}