
#include "Allegro.hpp"
#include "Tela.hpp"
#include "Player.hpp"
#include "Physics.hpp"
#include "Bullet.hpp"
#include "Input.hpp"
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;

#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/keyboard.h>



int ScreenManager::num_screen_managers = 0;

//============================================================================================================================================================

ScreenManager::ScreenManager ()
{
	title_screen = new TitleScreen ();
	game_screen = new GameScreen ();
	score_screen = new ScoreScreen ();
	game_over = new GameOver ();

	current_screen = title_screen;

	screen_manager_input = new InputManager ();
}


ScreenManager::~ScreenManager ()
{
	if (title_screen)
	{
		delete title_screen;
		title_screen = NULL;
	}

	if (game_screen)
	{
		delete game_screen;
		game_screen = NULL;
	}

	if (screen_manager_input)
	{
		delete screen_manager_input;
		screen_manager_input = NULL;
	}

	if (score_screen)
	{
		delete score_screen;
		score_screen = NULL;
	}

	current_screen = NULL;
}


ScreenManager* ScreenManager::createScreenManager ()
{
	ScreenManager* new_screen_manager = new ScreenManager ();
	return new_screen_manager;
}


void ScreenManager::menu ()
{
	current_screen = title_screen;
}

void ScreenManager::play ()
{
	current_screen = game_screen;
}


void ScreenManager::score ()
{
	current_screen = score_screen;
}


void ScreenManager::update (ALLEGRO_EVENT ev)
{
	current_screen->update (ev);
}

void ScreenManager::draw (ALLEGRO_DISPLAY* display)
{
	current_screen->draw (display);
}


void ScreenManager::resetGameScreen ()
{
	if (game_screen)
	{
		delete game_screen;

		game_screen = new GameScreen ();
	}
}


void ScreenManager::gameOver ()
{
	current_screen = game_over;
}

//============================================================================================================================================================

Screen::Screen () {}
Screen::~Screen () {}
void Screen::update (ALLEGRO_EVENT ev) {}
void Screen::draw (ALLEGRO_DISPLAY* display) {}



//============================================================================================================================================================

TitleScreen::TitleScreen ()
{
	title_screen_bitmap = al_load_bitmap ("Images/capa.png");
	if (!title_screen_bitmap)
		al_show_native_message_box (0, "Error", "Error", "Cannot load title screen bitmap", 0, 0);

	title_screen_input = new InputManager ();
}


TitleScreen::~TitleScreen ()
{
	if (title_screen_bitmap)
	{
		al_destroy_bitmap (title_screen_bitmap);
		title_screen_bitmap = NULL;
	}

	if (title_screen_input)
	{
		delete title_screen_input;
		title_screen_input = NULL;
	}
}

void TitleScreen::update (ALLEGRO_EVENT ev)
{
}


void TitleScreen::draw (ALLEGRO_DISPLAY* display)
{
	al_set_target_bitmap (al_get_backbuffer (display));
	al_draw_bitmap (title_screen_bitmap, 0, 0, 0);
}


//============================================================================================================================================================

GameScreen::GameScreen () : max_nuvis (MAX_NUVIS)
{
	game_screen_bitmap = al_load_bitmap ("Images/Bg.png");

	ground = new Ground* [2];
	for (int i = 0; i < 2; i++)
		ground[i] = new Ground (i);

	if (!game_screen_bitmap)
		al_show_native_message_box (0, "Error", "Error", "Cannot load game screen bitmap", 0, 0);

	nuvis = new Nuvi* [max_nuvis];
	for (int i = 0; i < max_nuvis; i++)
        nuvis[i] = NULL;
    num_nuvis = 0;

	game_screen_input = new InputManager ();
}

GameScreen::~GameScreen ()
{
	if (game_screen_bitmap)
	{
	    al_destroy_bitmap (game_screen_bitmap);
		game_screen_bitmap = NULL;
	}

    for (int i = 0; i < num_nuvis; i++)
    	delete nuvis[i];
	delete[] nuvis;
}


void GameScreen::update (ALLEGRO_EVENT ev)
{
	if (!(rand () % PRIME_NUVI_SPAWN))
		{
			if (num_nuvis < max_nuvis)
			{
				nuvis[num_nuvis] = new Nuvi ();
				num_nuvis++;
			}
		}

		for (int i = 0; i < num_nuvis; i++)
		{
			nuvis[i]->update ();

			if (nuvis[i]->position->getPosition ().x < -200)
			{
				delete nuvis[i];
				for (int j = i; j < num_nuvis - 1; j++)
					nuvis[j] = nuvis[j + 1];
				num_nuvis--;
			}
		}
    for (int i = 0; i < 2; i++)
        ground[i]->update ();
}


void GameScreen::draw (ALLEGRO_DISPLAY* display)
{
	al_set_target_bitmap (al_get_backbuffer (display));

	al_draw_bitmap (game_screen_bitmap, 0, 0, 0);
	for (int i = 0; i < 2; i++)
        ground[i]->draw ();

	for (int i = 0; i < num_nuvis; i++)
		nuvis[i]->draw (display);
}

//============================================================================================================================================================
ALLEGRO_BITMAP* Selector::selector_bitmap;

Selector::Selector ()
{
	position = new Position (520, 445);

	increment_position = new Speed (0, 42);
	decrement_position = new Speed (0, -42);

	Selector::selector_bitmap = al_load_bitmap ("Images/seletor.png");

	if (!selector_bitmap)
		al_show_native_message_box (0, "Error", "Error", "Cannot load selector bitmap", 0, 0);

	state = Iniciar;
}

Selector::~Selector ()
{
	if (position)
	{
		delete position;
		position = NULL;
	}

	if (increment_position)
	{
		delete increment_position;
		increment_position = NULL;
	}

	al_destroy_bitmap (selector_bitmap);
}

void Selector::update (ALLEGRO_EVENT ev)
{
	if (selector_input.keyIsPressed (ev, ALLEGRO_KEY_DOWN))
	{
		if (state == Sair)
			return ;

		position->changePosition (increment_position);
		state++;
	}

	if (selector_input.keyIsPressed (ev, ALLEGRO_KEY_UP))
	{
		if (state == Iniciar)
			return ;

		position->changePosition (decrement_position);
		state--;
	}
}


void Selector::draw (ALLEGRO_DISPLAY* display)
{
	al_set_target_bitmap (al_get_backbuffer(display));
	al_draw_bitmap (selector_bitmap, position->x, position->y, 0);
}

//============================================================================================================================================================


Nuvi::Nuvi ()
{
	float x_nuvi = DISPLAY_WIDTH;
	float y_nuvi = rand () %  200;
	position = new Position (x_nuvi, y_nuvi);

	float vx_nuvi;
	if (!(rand () % 2))
		vx_nuvi = -1;
	else
		vx_nuvi = -1.125;
	float vy_nuvi = 0;
	speed = new Speed (vx_nuvi, vy_nuvi);

	type = rand () % 4 + 1;
	switch (type)
	{
	case 1:
		nuvi_bitmap = al_load_bitmap ("Images/nuvis - 1.png");
		break;
	case 2:
		nuvi_bitmap = al_load_bitmap ("Images/nuvis - 2.png");
		break;
	case 3:
		nuvi_bitmap = al_load_bitmap ("Images/nuvis - 3.png");
		break;
	case 4:
		nuvi_bitmap = al_load_bitmap ("Images/nuvis - 4.png");
		break;
	}

	if (!nuvi_bitmap)
		al_show_native_message_box (0, "Error", "Error", "Cannot load nuvi bitmap", 0, 0);
}


Nuvi::~Nuvi ()
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

	if (nuvi_bitmap)
	{
		al_destroy_bitmap (nuvi_bitmap);
		nuvi_bitmap = NULL;
	}
}


void Nuvi::update ()
{
	position->changePosition (speed);
}


void Nuvi::draw (ALLEGRO_DISPLAY* display)
{
	al_set_target_bitmap (al_get_backbuffer (display));
	al_draw_bitmap (nuvi_bitmap, position->x, position->y, 0);
}


//============================================================================================================================================================
Speed* Ground::speed = new Speed (-3, 0);
Acceleration<float>* Ground::acceleration = new Acceleration<float> (-0.0005, 0);

Ground::Ground (int i)
{
	ground_bitmap = al_load_bitmap ("Images/Level Bitmap.png");

	if (i)
		position = new Position (0, 0);
	else
		position = new Position (DISPLAY_WIDTH, 0);
}


Ground::~Ground ()
{
	if (position)
	{
		delete position;
		position = NULL;
	}
}

void Ground::update ()
{
	if (position)
	{
		position->changePosition (Ground::speed);
		Ground::speed->changeSpeed (Ground::acceleration);

        if (position->x <= -1280)
            resetPosition ();
	}
}

void Ground::draw ()
{
	al_draw_bitmap (ground_bitmap, position->x, position->y, 0);
}

void Ground::resetPosition ()
{
    Position* reset_position = new Position (DISPLAY_WIDTH, 0);
	position->setPosition (reset_position);
	delete reset_position;
}

//============================================================================================================================================================

ScoreScreen::ScoreScreen ()
{
	score_screen_bitmap = al_load_bitmap ("Images/rigueiscori-A.png");

	radical = al_load_font ("Images/Lady Radical.ttf", 60, 0);

    memset (score_data, 0, sizeof (ScoreData) * 11);

    readScoreFile ();
}

ScoreScreen::~ScoreScreen ()
{
	if (score_screen_bitmap)
	{
		al_destroy_bitmap (score_screen_bitmap);
		score_screen_bitmap = NULL;
	}
}


void ScoreScreen::draw (ALLEGRO_DISPLAY* display)
{
	al_set_target_bitmap (al_get_backbuffer (display));
	al_draw_bitmap (score_screen_bitmap, 0, 0, 0);

	int counter = 0;
	int position_to_draw_x = 190;
	int position_to_draw_y = 170;
	while (counter < 10)
	{
	    if (score_data[counter].pontuacao > 0)
            al_draw_textf (radical, al_map_rgb (255, 255, 255), position_to_draw_x, position_to_draw_y, 0, "%s  %d", score_data[counter].nome, score_data[counter].pontuacao);
   		position_to_draw_y += 98;

   		if (counter == 4)
   		{
   			position_to_draw_x = 800;
   			position_to_draw_y = 170;
   		}
   		counter++;
	}

}



void ScoreScreen::readScoreFile ()
{
	FILE* fin = fopen("Score.txt", "rb");
    if (fin)
    {
	    fread(score_data, sizeof(ScoreData), 10, fin);
	    fclose(fin);
    }
}


void ScoreScreen::addScore (ScoreData new_score_data)
{
	score_data[10] = new_score_data;
}

void ScoreScreen::writeScoreFile ()
{
	FILE* fout = fopen("Score.txt", "wb");
    fwrite(score_data, sizeof(ScoreData), 10, fout);
    fclose(fout);
}


void ScoreScreen::sortScoreData ()
{
	int troca;
	ScoreData aux;
	for (int n = 0; n < 11 - 1; n++)
	{
	    troca = 0;

	    for (int i = 0; i < 11-1-n; i++)
        {
            if (score_data[i].pontuacao <  score_data[i+1].pontuacao)
            {
                aux = score_data[i+1];
                score_data[i+1] = score_data[i];
                score_data[i] = aux;
                troca = 1;
            }
        }

        if(troca == 0)
            break;
	}
}


//============================================================================================================================================================
/*
ScoreBoard::ScoreBoard()
{
	FILE* input_score_file = fopen ("Score.txt", "r");

	for (int i = 0; i < num_high_scores; i++)
		top_ten[i] = new Score (false);

    char c;

    for (int line = 0; line < num_high_scores; line++)
    {
        int counter = 0;
        //Getting top ten players name
        while (counter < 3)
        {
            c = fgetc (input_score_file);
            top_ten[line]->nome[counter] = c;
///            cout << top_ten[line]->nome[counter];
            counter++;
        }

        fscanf (input_score_file, "%d\n", &top_ten[line]->pontuation);
///        cout << top_ten[line]->pontuation << endl << endl;
    }

    fclose (input_score_file);
}

void ScoreBoard::adicionaTop(Score* new_score)
{
    for(int i = 0; i < num_high_scores; i++)
    {
        if (top_ten[i]->pontuation > new_score->pontuation)
            continue;

        for(int j = i; j < num_high_scores - 1; j++)
            top_ten[j + 1] = top_ten[j];

        for (int j = 0; j < 3; j++)
        	top_ten[i]->nome[j] = new_score->nome[j];
        top_ten[i]->pontuation = new_score->pontuation;

        break;
    }

}

void ScoreBoard::saveScore ()
{
	if (top_ten)
	{
        FILE* output_file = fopen ("Score.txt", "w");

		for(int i = 0; i < num_high_scores; i++)
    	{
	        for (int j = 0; j < 3; j++)
	        	fprintf(output_file, "%c", top_ten[i]->nome[j]);
	        fprintf(output_file, " %d\n", top_ten[i]->pontuation);
	    }

		for (int i = 0; i < num_high_scores; i++)
		{
			if (top_ten[i])
			{
				delete top_ten[i];
				top_ten[i] = NULL;
			}
		}

		fclose (output_file);
	}

	else
		cout << "Erro ao salvar as maiores pontuacoes" << endl;

}

ScoreBoard::~ScoreBoard()
{
	if (top_ten)
	{
        FILE* output_file = fopen ("Score.txt", "w");

		for(int i = 0; i < num_high_scores; i++)
    	{
	        for (int j = 0; j < 3; j++)
	        	fprintf(output_file, "%c", top_ten[i]->nome[j]);
	        fprintf(output_file, " %d\n", top_ten[i]->pontuation);
	    }

		for (int i = 0; i < num_high_scores; i++)
		{
			if (top_ten[i])
			{
				delete top_ten[i];
				top_ten[i] = NULL;
			}
		}

		fclose (output_file);
	}

	else
		cout << "Erro ao salvar as maiores pontuacoes" << endl;
}
*/

//============================================================================================================================================================

Score::Score(bool flag)
{
	if (flag)
	{
	    pontuation = 0;
	    cout << "Insira seu nome:" << endl;
	    fgets (nome, 4, stdin);
	}
}

Score::~Score () {}


bool Score::operator > (Score* t)
{
    if (pontuation > t->pontuation)
        return (true);
    return (false);
}

void Score::atualizaPontuacao (bool flag)
{
    contador++;
    if (!(contador % 10))
        pontuation++;
    if (flag)
    	pontuation += 100;
}

//============================================================================================================================================================

GameOver::GameOver ()
{
	game_over_bitmap = al_load_bitmap ("Images/Game Over.png");
}


GameOver::~GameOver ()
{
	if (game_over_bitmap)
		al_destroy_bitmap (game_over_bitmap);
}


void GameOver::draw (ALLEGRO_DISPLAY* display)
{
	al_set_target_bitmap (al_get_backbuffer (display));
	al_draw_bitmap (game_over_bitmap, 0, 0, 0);
}

void GameOver::update (ALLEGRO_EVENT ev) {}
