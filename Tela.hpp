#pragma once

#include "Classes.hpp"
#include "Input.hpp"

#include <stdio.h>
#include <iostream>
using namespace std;


//============================================================================================================================================================



class ScreenManager
{
	static int num_screen_managers;
	Screen* current_screen;
	TitleScreen* title_screen;
	GameScreen* game_screen;
	ScoreScreen* score_screen;
    GameOver* game_over;
	InputManager* screen_manager_input;

	ScreenManager ();
	friend Game;

public:
	~ScreenManager ();
	static ScreenManager* createScreenManager ();

	void menu ();
	void play ();
	void score ();
    void gameOver ();

	void update (ALLEGRO_EVENT ev);
	void draw (ALLEGRO_DISPLAY* display);
    void resetGameScreen ();
};



//============================================================================================================================================================

class Screen
{
public:
	Screen ();
    virtual ~Screen ();

    virtual void draw (ALLEGRO_DISPLAY *display);
    virtual void update (ALLEGRO_EVENT ev);
};



//============================================================================================================================================================

class TitleScreen : public Screen
{
	ALLEGRO_BITMAP* title_screen_bitmap, *cursor;
	InputManager* title_screen_input;

public:
	TitleScreen ();
	~TitleScreen ();
	void draw (ALLEGRO_DISPLAY* display);
	void update (ALLEGRO_EVENT ev);
};




//============================================================================================================================================================

class GameScreen : public Screen
{
	ALLEGRO_BITMAP* game_screen_bitmap;
    Ground** ground;
	Nuvi** nuvis;
	const int max_nuvis;
	int num_nuvis;
	InputManager* game_screen_input;

public:
	GameScreen();
	~GameScreen();
	void update (ALLEGRO_EVENT ev);
	void draw (ALLEGRO_DISPLAY* display);
};

//============================================================================================================================================================

class Selector
{
	friend Game;
	static ALLEGRO_BITMAP* selector_bitmap;
	Position* position;
    Speed *increment_position, *decrement_position;
	int state;
	InputManager selector_input;
public:
	Selector ();
	~Selector ();
	void update (ALLEGRO_EVENT ev);
	void draw (ALLEGRO_DISPLAY* display);
};


//============================================================================================================================================================

class Nuvi
{
    int type;
    ALLEGRO_BITMAP* nuvi_bitmap;
    Position* position;
    Speed* speed;
  friend GameScreen;

public:
    Nuvi();
    ~Nuvi();

    void draw (ALLEGRO_DISPLAY* display);
    void update ();
};

//============================================================================================================================================================

class Ground
{
	ALLEGRO_BITMAP* ground_bitmap;
	Position* position;
	static Speed* speed;
	static Acceleration<float>* acceleration;
	friend Game;
public:
	Ground(int i);
	~Ground();

	void update ();
	void draw ();

	void resetPosition ();
};



//============================================================================================================================================================

class ScoreScreen : public Screen
{
	ALLEGRO_BITMAP* score_screen_bitmap;
	ALLEGRO_FONT* radical;

public:
    struct ScoreData
	{
		int pontuacao;
		char nome[4];
	};
	ScoreData score_data[11];

	ScoreScreen ();
	~ScoreScreen ();

	void readScoreFile ();
	void addScore (ScoreData new_score_data);
	void writeScoreFile ();
	void sortScoreData ();

	void draw (ALLEGRO_DISPLAY* display);
};


//=========================================================================================================================================

class Score
{
    char nome[4];
    int pontuation;
    friend Player;
    friend Game;
public:
    Score (bool flag);
    ~Score ();
    void atualizaPontuacao(bool);
    bool operator > (Score*);
};


//============================================================================================================================================================


class GameOver : public Screen
{
    ALLEGRO_BITMAP* game_over_bitmap;
public:
    GameOver ();
    ~GameOver ();
    void draw (ALLEGRO_DISPLAY* display);
    void update (ALLEGRO_EVENT ev);
};

