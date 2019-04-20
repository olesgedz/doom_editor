/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:53:03 by jblack-b          #+#    #+#             */
/*   Updated: 2019/04/20 14:19:49 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "libsdl.h"
#include "doom_editor.h"

	t_game game;

int ft_point_compare(t_list *list, void *target)
{
	if ((((t_point *)list->content)->x == ((t_point *)target)->x) &&
		(((t_point *)list->content)->y == ((t_point *)target)->y))
		{
			printf("S:%d %d %d %d\n", ((t_point *)list->content)->x,((t_point *)target)->x,
			((t_point *)list->content)->y , ((t_point *)target)->y);
			return (1);
		}
	return (0);
}
int ft_point_compare_range(t_list *list, void *target, int range)
{
	if ((((t_point *)list->content)->x - 5 <= ((t_point *)target)->x)  && (((t_point *)list->content)->x + 5 >= ((t_point *)target)->x)
	 &&	(((t_point *)list->content)->y - 5 <= ((t_point *)target)->y) && ((t_point *)list->content)->y + 5 >= ((t_point *)target)->y)
		{
			printf("S:%d %d %d %d\n", ((t_point *)list->content)->x,((t_point *)target)->x,
			((t_point *)list->content)->y , ((t_point *)target)->y);
			return (1);
		}
	return (0);
}
void ft_lst_free(void *content, size_t size)
{
	ft_memdel((void **)&content);
}
t_list		*ft_list_search(t_list *lst, void *target, int (*f)(t_list *, void *, int))
{
	while (lst != NULL)
	{
		if (f(lst, target, 5))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void ft_put_vertex(t_game *game)
{
	ft_put_pixel(game->image, &(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, 0xFF0000);
	if (ft_list_search(game->verties, &(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, ft_point_compare_range))
	{
		printf("Connected\n");
		game->finished = 1;
		ft_lstdel(&game->verties, ft_lst_free);
		game->sdl->mouse.last_x = -1;
		game->sdl->mouse.last_y = -1;
	}
	ft_lstadd(&game->verties, ft_lstnew(&(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, sizeof(t_point)));
	printf("%d %d\n", ((t_point *)game->verties->content)->x, ((t_point *)game->verties->content)->y);
}

void ft_mouse_pressed(t_game *game, SDL_Event *ev)
{
	game->sdl->mouse.pressed = 1;
	game->sdl->mouse.last_x = game->sdl->mouse.x;
	game->sdl->mouse.last_y = game->sdl->mouse.y;
	game->sdl->mouse.x = ev->button.x;
	game->sdl->mouse.y = ev->button.y;
	game->finished  = 0;

	ft_put_pixel(game->image, &(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, 0xFF0000);
	if (ft_list_search(game->verties, &(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, ft_point_compare_range))
	{
		printf("Connected\n");
		game->finished  = 1;
			ft_plot_line(game->image, &(t_point){game->sdl->mouse.last_x, game->sdl->mouse.last_y},\
		&(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, 0x00FF00);
			game->sdl->mouse.x = -1;
			game->sdl->mouse.y = -1;
		
	}
	ft_lstadd(&game->verties, ft_lstnew(&(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, sizeof(t_point)));
	if (game->sdl->mouse.last_x > -1 && game->finished  == 0) 
		ft_plot_line(game->image, &(t_point){game->sdl->mouse.last_x, game->sdl->mouse.last_y},\
		&(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, 0x00FF00);

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
			case SDL_MOUSEBUTTONDOWN:  ft_mouse_pressed(&game, ev);
				break;
			case SDL_QUIT: ft_exit(NULL);
		}
	return (1);
}

void ft_update(t_game *game)
{
	t_rectangle r = (t_rectangle){(t_point){0,0},(t_size){WIN_W, WIN_H}};
	while(1)
	{
		ft_surface_clear(game->sdl->surface);
		ft_input(game->sdl, &ft_input_keys);
		ft_surface_combine(game->sdl->surface, game->image, &r);
		ft_surface_present(game->sdl, game->sdl->surface);
	}
}

int main()
{
	game.sdl = malloc(sizeof(t_sdl));
	game.image = ft_surface_create(WIN_W, WIN_H);
	game.sdl->mouse.x = -1;
	game.sdl->mouse.y = -1;
	game.finished = 0;
	ft_init_window(game.sdl, WIN_W, WIN_H);
	printf("%zu, %zu\n", game.sdl->surface->height, game.sdl->surface->width);

	ft_update(&game);
	ft_exit(NULL);
}