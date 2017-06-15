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

//Classe Allegro
//Inicialização da biblioteca
bool Allegro::initialize ()
{
	if (!al_init ())
    {
        al_show_native_message_box (0, "Error", "Error", "Cannot initialize Allegro 5", 0, 0);
        return false;
    }
    if (!al_install_keyboard ())
    {
        al_show_native_message_box (0, "Error", "Error", "Cannot initialize keyboard", 0, 0);
        return false;
    }

    if (!al_install_mouse ())
    {
        al_show_native_message_box (0, "Error", "Error", "Cannot initialize mouse", 0, 0);
        return false;
    }

    if (!al_init_image_addon ())
    {
        al_show_native_message_box (0, "Error", "Error", "Cannot initialize audio", 0, 0);
        return false;
    }

    if (!al_init_acodec_addon ())
    {
        al_show_native_message_box (0, "Error", "Error", "Cannot initialize audio codecs", 0, 0);
        return false;
    }

    al_init_font_addon ();
    al_init_ttf_addon ();

    return true;
}



//============================================================================================================================================================
Acceleration<float>* Game::game_acceleration = new Acceleration<float> (-0.001, 0);

Game::Game ()
{
	GerenciadorBullet::inicializaBullets();
	screen_manager = ScreenManager::createScreenManager ();

	player = new Player ();
	atiradeiro = new Atiradeiro ();
	bear = NULL;

	game_state = in_title_screen;

	game_input = new InputManager ();

	selector = new Selector ();

	vidaJogador = new Vida();

//	score_board = new ScoreBoard ();

	keep_playing = true;
}


Game::~Game ()
{
	GerenciadorBullet::destroiBullets();

	if (screen_manager)
	{
		delete screen_manager;
		screen_manager = NULL;
	}

	if (player)
	{
		delete player;
		player = NULL;
	}

	if (atiradeiro)
	{
		delete atiradeiro;
		atiradeiro = NULL;
	}

	if (bear)
	{
		delete bear;
		bear = NULL;
	}

	if (game_input)
	{
		delete game_input;
		game_input = NULL;
	}

	if (selector)
	{
		delete selector;
		selector = NULL;
	}

/*
	if (score_board)
	{
		delete score_board;
		score_board = NULL;
	}
*/
}


void Game::menu ()
{
	screen_manager->menu ();
	game_state = in_title_screen;
}


void Game::play ()
{
	screen_manager->play ();
	game_state = playing;
}


void Game::score ()
{
	screen_manager->score ();
	game_state = in_score_screen;


///	for (int i = 0; i < num_high_scores; i++)
///	{
///		for (int j = 0; j < 3; j++)
///	        cout << score_board->top_ten[i]->nome[j];
///	    cout << " " << score_board->top_ten[i]->pontuation << endl;
///	}

///    cout << player->score->nome << " " << player->score->pontuation << endl;
}


void Game::update (ALLEGRO_EVENT ev)
{
	if (keep_playing)
	{
		if (game_state == in_title_screen)
		{
			if (!selector)
				selector = new Selector ();
			else
				selector->update (ev);
		}
		else
		{
			if (selector)
			{
				delete selector;
				selector = NULL;
			}
		}

		if (game_input->keyIsPressed (ev, ALLEGRO_KEY_ENTER))
		{
            if ((game_state == playing || game_state == game_over))
            {
                menu ();
                resetGame ();
            }

			if (game_state == in_score_screen)
				menu ();

			if (game_state == in_title_screen && selector)
			{
				if (selector->state == Iniciar)
                {
                	play ();
				    player->reset ();
                }
				else if (selector->state == Placar)
					score ();
				else
					keep_playing = false;

			}

            if (!selector)
                selector = new Selector ();
		}


		screen_manager->update (ev);

		if (game_state == playing)
		{
			if (player)
				player->update (ev);
			else
				player = new Player ();

			if (!(rand () % PRIME_BULLET_SPAWN))
			{
				if (atiradeiro)
					makeEnemyShoot ();
			}

            GerenciadorBullet::atualizaBullets (ev);

			if (atiradeiro)
			{
				atiradeiro->update (ev);
				if (player && !atiradeiro->hit_player &&
					atiradeiro->position->x <= player->position->x + player->width && player->position->x < atiradeiro->position->x + atiradeiro->width &&
					atiradeiro->position->y <= player->position->y + player->height)
				{
					player->takeLife ();
					vidaJogador->tiraVida ();
					atiradeiro->hit_player = true;
				}
			}

			else
				if (!(rand () % PRIME_NUVI_SPAWN) && areaClear ())
					atiradeiro = new Atiradeiro ();

			Atiradeiro::speed->changeSpeed (Game::game_acceleration);

			if (bear)
			{
				bear->update ();
				if (player && !bear->hit_player &&
					bear->position->x <= player->position->x + player->width && player->position->x < bear->position->x + bear->width &&
					bear->position->y <= player->position->y + player->height)
				{
					player->takeLife ();
					vidaJogador->tiraVida ();
					bear->hit_player = true;
				}

				if (bear->position->x + bear->width < -35 && contador > 600 && !(rand () % PRIME_NUVI_SPAWN) && !(rand () % 2))
				{
					delete bear;
					bear = NULL;
				}
			}
			else
				if (!(rand () % PRIME_NUVI_SPAWN) && areaClear ())
					bear = new Bear ();


			Bear::speed->changeSpeed (Game::game_acceleration);

			checkHit ();

			if (player && player->lives == -1)
				gameOver ();
		}
	}
}


void Game::makeEnemyShoot ()
{
	GerenciadorBullet::adicionaBullet(atiradeiro->position->x, atiradeiro->position->y + 25, Atiradeiro::speed->vx, enemy_shooting);
}

void Game::checkHit ()
{
	Bullet** bullets = GerenciadorBullet::bullets;
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i] == NULL)
			continue;


		//Deleta as balas do player se acertam o urso
		if (bullets[i]->flag && bear)
            if (bear->position->x + 30 <= bullets[i]->position->x && bullets[i]->position->x <= bear->position->x + bear->width
				&& bear->position->y <= bullets[i]->position->y && bullets[i]->position->y <= bear->position->y + bear->height)
			{
				GerenciadorBullet::tiraBullet (i);
				continue;
			}

		//Deleta as balas do player se acertam o inimigo
		if (bullets[i]->flag && atiradeiro && atiradeiro->position->x + 30 <= bullets[i]->position->x && bullets[i]->position->x <= atiradeiro->position->x + atiradeiro->width
				&& atiradeiro->position->y <= bullets[i]->position->y && bullets[i]->position->y <= atiradeiro->position->y + atiradeiro->height)
			{
				GerenciadorBullet::tiraBullet (i);
				delete atiradeiro;
				atiradeiro = NULL;
				player->score->atualizaPontuacao (true);
			}

		//Deleta as balas do inimigo se acertam o player
		else if (!bullets[i]->flag && player->position->x <= bullets[i]->position->x && bullets[i]->position->x <= player->position->x + player->width
				&& player->position->y <= bullets[i]->position->y && bullets[i]->position->y <= player->position->y + player->height)
			{
				GerenciadorBullet::tiraBullet (i);
				player->takeLife ();
				vidaJogador->tiraVida();
			}
	}

}


bool Game::areaClear ()
{
	if (bear)
    {
		if (0 <= bear->position->x && bear->position->x < DISPLAY_WIDTH)
			return false;
    }

	else
	{
		if (atiradeiro)
		{
			if (0 <= atiradeiro->position->x && atiradeiro->position->x < DISPLAY_WIDTH)
				return false;
		}
	}

	return true;
}


void Game::draw (ALLEGRO_DISPLAY* display)
{
	screen_manager->draw (display);

	if (selector)
		selector->draw (display);

	if (game_state == playing)
	{
    	GerenciadorBullet::drawBullets (display);

		if (player)
			player->draw (display);

		if (atiradeiro != NULL)
			atiradeiro->draw (display);

        if (bear)
            bear->draw (display);

		if (vidaJogador)
			vidaJogador->draw (display);
	}
}





void Game::resetGame ()
{
	if (!player->score_saved)
	{
		ScoreScreen::ScoreData new_score_data;
		strcpy (new_score_data.nome, player->score->nome);
		new_score_data.pontuacao = player->score->pontuation;
		player->score_saved = true;
		screen_manager->score_screen->addScore (new_score_data);
		screen_manager->score_screen->sortScoreData ();
		screen_manager->score_screen->writeScoreFile ();
	}

	screen_manager->resetGameScreen ();

	if (atiradeiro)
	{
		delete atiradeiro;
		atiradeiro = NULL;
	}

	if (bear)
	{
		delete bear;
		bear = NULL;
	}

	GerenciadorBullet::destroiBullets ();
	GerenciadorBullet::inicializaBullets ();

	if (vidaJogador)
	{
		delete vidaJogador;
		vidaJogador = new Vida;
	}

	if (Atiradeiro::speed)
	{
		delete Atiradeiro::speed;
		Atiradeiro::speed = new Speed (-1, 0);
	}

	if (Bear::speed)
	{
		delete Bear::speed;
		Bear::speed = new Speed (-1, 0);
	}

	if (Ground::speed)
	{
		delete Ground::speed;
		Ground::speed = new Speed (-1, 0);
	}
}


void Game::gameOver ()
{
	screen_manager->gameOver ();
    if (!player->score_saved)
    {
    	ScoreScreen::ScoreData new_score_data;
		strcpy (new_score_data.nome, player->score->nome);
		new_score_data.pontuacao = player->score->pontuation;
		player->score_saved = true;
		screen_manager->score_screen->addScore (new_score_data);
		screen_manager->score_screen->sortScoreData ();
		screen_manager->score_screen->writeScoreFile ();
    }
    player->score->pontuation = 0;
	game_state = game_over;
}


int Game::getGameState ()
{
	return game_state;
}

bool Game::getKeepPlaying ()
{
	return keep_playing;
}



//===========================================================================================================================================

Vida::Vida()
{
    icono = NULL;
    n_vidas = 3;
    icono = al_load_bitmap ("Images/vida.png");
    radical = al_load_font ("Images/Lady Radical.ttf", 50, 0);
    if (!radical)
    	cout << "Cannot load radical font" << endl;
    if (!icono)
        al_show_native_message_box (0, "Error", "Error", "Cannot load life bitmap", 0, 0);
}


void Vida::draw (ALLEGRO_DISPLAY* display)
{
	char text[2];

	al_set_target_bitmap (al_get_backbuffer (display));
    al_draw_bitmap (icono, 1100, 630, 0);


    if (n_vidas == 3)
    {
        text[0] = '0';
        text[1] = '3';
    }
    else if (n_vidas == 2)
    {
        text[0] = '0';
        text[1] = '2';
    }
    else if (n_vidas == 1)
    {
        text[0] = '0';
        text[1] = '1';
    }
    else
    {
        text[0] = '0';
        text[1] = '0';
    }

    al_set_target_bitmap (al_get_backbuffer (display));
    al_draw_text (radical, al_map_rgb (255, 255, 255), 1180, 660, 0, text);
}

void Vida::tiraVida()
{
    n_vidas--;
}

Vida::~Vida()
{
    al_destroy_bitmap (icono);
}

