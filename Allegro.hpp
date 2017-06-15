#pragma once

#include <allegro5/allegro.h>
#include "Classes.hpp"


class Allegro
{
public:
	static bool initialize ();
};



//============================================================================================================================================================


class Game
{
	ScreenManager* screen_manager;
	Player* player;
	Atiradeiro* atiradeiro;
    Bear* bear;
    Vida* vidaJogador;
    InputManager* game_input;
    GameState game_state;
    Selector* selector;
    bool keep_playing;
    friend ScoreScreen;

public:
    static Acceleration<float>* game_acceleration;

	Game ();
	~Game ();
    void menu ();
	void play ();
	void score ();
	void resetGame ();
	void gameOver ();

    void makeEnemyShoot ();
    bool areaClear ();

	void update (ALLEGRO_EVENT ev);
	void draw (ALLEGRO_DISPLAY* display);
    void checkHit ();

	int getGameState ();
	bool getKeepPlaying ();
};


//===============================================================================================================================================================
class Vida
{
    ALLEGRO_BITMAP* icono;
    ALLEGRO_FONT* radical;
    int n_vidas;
public:
    Vida();
    void tiraVida();
    void draw(ALLEGRO_DISPLAY* display);
    ~Vida();
};
