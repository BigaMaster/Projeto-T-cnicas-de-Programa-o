
#include "Allegro.hpp"
#include "Tela.hpp"
#include "Player.hpp"
#include "Physics.hpp"
#include "Bullet.hpp"
#include "Input.hpp"
#include <stdlib.h>
#include <iostream>
using namespace std;

#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/keyboard.h>


//============================================================================================================================================================

Bullet::Bullet (float position_x, float position_y, float initial_vx, bool _flag)
{
	position = new Position (position_x, position_y);

	flag = _flag;

	if (flag)
		speed = new Speed (10, 0);
	else
		speed = new Speed (-7.5 + initial_vx, 0);
}


Bullet::~Bullet ()
{
	if (position)
	{
		delete position;
		position = NULL;
	}

	if (speed)
	{
		delete speed;
		speed = NULL;
	}
}


void Bullet::update (ALLEGRO_EVENT ev)
{
	position->changePosition (speed);
}

void Bullet::draw (ALLEGRO_DISPLAY* display)
{
	if (position->x >= 1 && position->x < DISPLAY_WIDTH && position->y >= 0 && position->y < DISPLAY_HEIGHT)
		al_draw_bitmap (bullet_bitmap, position->x, position->y, 0);
}






//============================================================================================================================================================
Bullet* GerenciadorBullet::bullets[MAX_BULLETS];
ALLEGRO_BITMAP* GerenciadorBullet::bullet_bitmap;
int GerenciadorBullet::num_enemy_bullets;
int GerenciadorBullet::num_player_bullets;

void GerenciadorBullet::inicializaBullets()
{
    num_enemy_bullets = 0;
    num_player_bullets = 0;

	for (int i = 0; i < MAX_BULLETS; i++)
		bullets[i] = NULL;

	bullet_bitmap = al_create_bitmap (5, 2.5);
	al_set_target_bitmap(bullet_bitmap);
	al_clear_to_color(al_map_rgb (200, 200, 200));
}

void GerenciadorBullet::destroiBullets ()
{
	//if (!bullets)
		//return ;

	for (int i = 0; i < MAX_BULLETS; i++)
		if (bullets[i])
		{
			delete bullets[i];
			bullets[i] = NULL;
		}
	//delete[] bullets;

	al_destroy_bitmap (bullet_bitmap);
}

void GerenciadorBullet::adicionaBullet(float position_x, float position_y, float initial_vx, bool flag)
{
	int i;
	for (i = 0; i < MAX_BULLETS; i++)
		if (bullets[i] == NULL)
			break;
	if (i == MAX_BULLETS)
		return ;

	if (!flag)
	{
		if (num_enemy_bullets == MAX_ENEMY_BULLETS)
			return ;
		num_enemy_bullets++;
	}
	else
	{
		if (num_player_bullets == MAX_PLAYER_BULLETS)
			return ;
		num_player_bullets++;
	}
	bullets[i] = new Bullet (position_x, position_y, initial_vx, flag);

	bullets[i]->bullet_bitmap = bullet_bitmap;
}
void GerenciadorBullet::tiraBullet(int indice)
{
	if (indice < MAX_BULLETS && bullets[indice] != NULL)
	{
		if (!bullets[indice]->flag)
			num_enemy_bullets--;
		else
			num_player_bullets--;
		delete bullets[indice];
		bullets[indice] = NULL;
	}
}


void GerenciadorBullet::atualizaBullets (ALLEGRO_EVENT ev)
{

    for (int i = 0; i < MAX_BULLETS; i++)
    {
    	if (bullets[i] == NULL)
    		continue;
        bullets[i]->update (ev);
    	if (bullets[i]->position->x < -50 || bullets[i]->position->x > DISPLAY_WIDTH)
    	{
    		tiraBullet (i);
    	}
    }
}

void GerenciadorBullet::drawBullets (ALLEGRO_DISPLAY* display)
{
	al_set_target_bitmap (al_get_backbuffer (display));
    for (int i = 0; i < MAX_BULLETS; i++)
    {
    	if (bullets[i] == NULL)
    		continue;
        bullets[i]->draw (display);
    }
}

//============================================================================================================================================================





//============================================================================================================================================================





//============================================================================================================================================================
