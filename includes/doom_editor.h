#ifndef DOOM_EDITOR_H
#define DOOM_EDITOR_H

#define WIN_W 1280
#define WIN_H 720

#include "SDL2/SDL.h"
#include "libsdl.h"

typedef struct s_vertex t_vertex;
typedef struct s_sector t_sector;
typedef struct s_object t_object;
typedef struct s_coord t_coord;

typedef	struct 	s_p3d
{
	float x;
	float y;
	float z;
} t_p3d;

struct s_vertex
{
	t_p3d position;
	float U, V;
};

typedef struct s_coord
{
	t_vertex original;
	t_vertex rotated;
	char processed;
} t_coord;

typedef struct s_polygon
{
	t_vertex **vertices;
	int nvertices;
	//Texture
	t_sector *sector;
	//Plane
} t_polygon;

struct s_object
{
	t_polygon *polygons;
	t_object *childs;
	//matrix matrix
};

struct s_sector
{
	t_polygon *polygons;
};

typedef  struct s_world
{
	t_sector *sectors;
} t_world;

typedef struct s_game
{
	t_sdl *sdl;
	t_surface *image;
	t_list *verties;
	int finished;
} t_game;
#endif