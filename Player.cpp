
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

Character::Character () {}

Character::~Character (){
}

//Métodos virtuais implementados nas classes filhas
void Character::jump () {}
void Character::shoot () {}
void Character::update (ALLEGRO_EVENT ev) {}
void Character::draw (ALLEGRO_DISPLAY* display) {}

bool Character::onGround () { return true; }

bool Character::onPlatform () { return true; }




//============================================================================================================================================================

ALLEGRO_BITMAP** RunnerManager::runner_bitmaps;
int RunnerManager::state = 0;
int RunnerManager::timer_counter = 0;
float RunnerManager::timer_change = 10;
float RunnerManager::timer_acceleration = 0.005;


void RunnerManager::initializeVector (Player* player)
{
	runner_bitmaps = new ALLEGRO_BITMAP* [NUM_RUN_IMAGES];

	runner_bitmaps[0] = al_load_bitmap ("Images/correndinho1.png");
	runner_bitmaps[1] = al_load_bitmap ("Images/correndinho2.png");
	runner_bitmaps[2] = al_load_bitmap ("Images/correndinho3.png");
	runner_bitmaps[3] = al_load_bitmap ("Images/correndinho4.png");
	runner_bitmaps[4] = al_load_bitmap ("Images/correndinho5.png");

	for (int i = 0; i < NUM_RUN_IMAGES; i++)
    {
        if (!runner_bitmaps[i])
            cout << "Cannot load bitmap " << i << endl;
    }

    player->player_bitmap = runner_bitmaps[0];
}

void RunnerManager::changeRunnerBitmap (Player* player, ALLEGRO_EVENT ev)
{
	if (ev.type == ALLEGRO_EVENT_TIMER)
		timer_counter++;
	if (abs (timer_counter - timer_change) < 1)
	{
		if (timer_change > 5)
			timer_change -= timer_acceleration;

		timer_counter = 0;
		if (state < NUM_RUN_IMAGES - 1)
			state++;
		else
			state = 1;

		player->player_bitmap = runner_bitmaps[state];
	}

}


void RunnerManager::destroyVector ()
{
	for (int i = 0; i < NUM_RUN_IMAGES; i++)
	{
		al_destroy_bitmap (runner_bitmaps[i]);
		runner_bitmaps[i] = NULL;
	}

	delete[] runner_bitmaps;
}

//============================================================================================================================================================


Player::Player () : max_bullets (MAX_BULLETS)
{
	RunnerManager::initializeVector (this);
	if (!player_bitmap)
		al_show_native_message_box (0, "Error", "Error", "Cannot load player bitmap", 0, 0);

	player_jumping_bitmap = al_load_bitmap ("Images/pulandinho.png");
	if (!player_jumping_bitmap)
		al_show_native_message_box (0, "Error", "Error", "Cannot load player jumping bitmap", 0, 0);

	height = 130;
	width = 50;
	is_jumping = true;

	position = new Position (X_PLAYER_POSITION, DISPLAY_HEIGHT - height - 100);

	speed = new Speed (0, 0);

	score = new Score (true);
	score_saved = false;

	font = al_load_font ("Images/Lady Radical.ttf", 40, 0);

	lives = 2;
}


Player::~Player ()
{
	RunnerManager::destroyVector ();

	if (player_jumping_bitmap)
	{
		al_destroy_bitmap (player_jumping_bitmap);
		player_bitmap = NULL;
	}

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

	if (score)
	{
		delete score;
		score = NULL;
	}
}


float Player::getHeight ()
{
	return height;
}

float Player::getWidth ()
{
	return width;
}


bool Player::onGround ()
{
	if (DISPLAY_HEIGHT - 100 <= (position->y + height))
	{
		Speed stop (0, 0);
		speed->setSpeed (&stop);
		is_jumping = false;
		return true;
	}
	return false;
}


bool Player::onPlatform ()
{
	if (DISPLAY_HEIGHT - 100 <= position->y  + height)
	{
		Speed stop (0, 0);
		speed->setSpeed (&stop);
		is_jumping = false;
		return true;
	}
	return false;
}


void Player::jump ()
{
	if (!is_jumping)
	{
		Speed jump_speed (0, -10);
		speed->setSpeed (&jump_speed);
		is_jumping = true;
	}
}

void Player::shoot ()
{
    GerenciadorBullet::adicionaBullet (position->x + width, position->y + 62.5, speed->vx, player_shooting);
}


void Player::update (ALLEGRO_EVENT ev)
{
	//Fall
	if (is_jumping)
	{
		if (position->y + speed->vy < DISPLAY_HEIGHT - height - 1)
			position->changePosition (speed);
		else
		{
			Position bottom (position->x, DISPLAY_HEIGHT - height);
			position->setPosition (&bottom);
		}
		speed->changeSpeed (&Character::gravity);
	}

	else
	{
		Speed stop (0, 0);
		speed->setSpeed (&stop);
	}

	if (onGround () || onPlatform ())
	{
		is_jumping = false;
	}

	if (player_input.keyIsPressed (ev, ALLEGRO_KEY_SPACE))
		jump ();

	if (player_input.keyIsPressed (ev, ALLEGRO_KEY_U))
		shoot ();

	RunnerManager::changeRunnerBitmap (this, ev);

	score->atualizaPontuacao (false);
}


void Player::draw (ALLEGRO_DISPLAY* display)
{
	al_set_target_bitmap (al_get_backbuffer (display));
	if (is_jumping)
		al_draw_bitmap (player_jumping_bitmap, position->x - 12, position->y, 0);
	else
		al_draw_bitmap (player_bitmap, position->x, position->y, 0);

	char text[5];
	int counter = 4;
	int score_to_compare = score->pontuation;
	for (int i = 0; counter >= 0; i++)
	{
		if (i == score_to_compare % 10)
		{
			text[counter] = numbers[i];
			score_to_compare /= 10;
			i = -1;
			counter--;
		}
	}

	al_set_target_bitmap (al_get_backbuffer (display));
	al_draw_text (font, al_map_rgb (255, 255, 255), 1050, 40, 0, text);
}


void Player::reset ()
{
    Position* reset_position = new Position (X_PLAYER_POSITION, DISPLAY_HEIGHT - height - 100);
	position->setPosition (reset_position);
	delete reset_position;
	reset_position = NULL;
	score->pontuation = 0;
	score_saved = false;
	lives = 2;
}


void Player::takeLife ()
{
	lives--;
}



//============================================================================================================================================================
Speed* Atiradeiro::speed = new Speed (-3, 0);

Atiradeiro::Atiradeiro ()
{
	width = 50;
	height = 120;
	hit_player = false;
	enemy_bitmap = al_load_bitmap ("Images/atiradeiro.png");

	if (!enemy_bitmap)
		al_show_native_message_box (0, "Error", "Error", "Cannot create atiradeiro bitmap", 0, 0);

	position = new Position (DISPLAY_WIDTH, DISPLAY_HEIGHT - height - 50);
}

Atiradeiro::~Atiradeiro ()
{
	al_destroy_bitmap (enemy_bitmap);

	if (position)
	{
		delete position;
		position = NULL;
	}
}

void Atiradeiro::update (ALLEGRO_EVENT ev)
{
	if (position->x < -120)
    {
    	if (!(rand () % PRIME_BULLET_SPAWN))
    	{
	        Position reset_position ((float) DISPLAY_WIDTH, DISPLAY_HEIGHT - height - 50);
	        position->setPosition (&reset_position);
    	}
    }

    else
    	position->changePosition (Atiradeiro::speed);
}


void Atiradeiro::die ()
{
	Position reset_position ((float) DISPLAY_WIDTH, DISPLAY_HEIGHT - height - 50);
	position->setPosition (&reset_position);
}

void Atiradeiro::draw (ALLEGRO_DISPLAY *display)
{
	al_set_target_bitmap (al_get_backbuffer (display));
	al_draw_bitmap (enemy_bitmap, position->x, position->y, 0);
}



//============================================================================================================================================================
Speed* Bear::speed = new Speed (-3, 0);

Bear::Bear ()
{
	height = 70;
	width = 200;

	hit_player = false;

	bear_bitmap = al_load_bitmap ("Images/meio uso 2.png");
	if (!bear_bitmap)
		al_show_native_message_box (0, "Error", "Error", "Cannot load bear bitmap", 0, 0);

	position = new Position (DISPLAY_WIDTH, DISPLAY_HEIGHT - height - 100);
}


Bear::~Bear ()
{
	al_destroy_bitmap (bear_bitmap);

	delete position;
}


void Bear::update ()
{
	if (position)
	{
		if (position->x + width < 0)
		{
			Position* reset_position = new Position (DISPLAY_WIDTH, DISPLAY_HEIGHT - height - 100);
			position->setPosition (reset_position);
		}
		else
			position->changePosition (Bear::speed);
	}
}


void Bear::draw (ALLEGRO_DISPLAY* display)
{
    al_set_target_bitmap (al_get_backbuffer (display));
    al_draw_bitmap (bear_bitmap, position->x, position->y, 0);
}


void Bear::die ()
{
	Position* reset_position = new Position (DISPLAY_WIDTH, DISPLAY_HEIGHT);
	position->setPosition (reset_position);
	delete reset_position;
}
