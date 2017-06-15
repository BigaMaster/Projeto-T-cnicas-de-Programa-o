#pragma once


//============================================================================================================================================================


#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 720

#define MAX_NUVIS 7
#define PRIME_NUVI_SPAWN 113

#define MAX_BULLETS 5
#define MAX_ENEMY_BULLETS 2
#define MAX_PLAYER_BULLETS MAX_BULLETS - MAX_ENEMY_BULLETS
#define PRIME_BULLET_SPAWN 127

#define X_PLAYER_POSITION 100

#define NUM_RUN_IMAGES 5



//============================================================================================================================================================

class Allegro;
class Game;
class Vida;

class ScreenManager;
class Screen;
class TitleScreen;
class GameScreen;
class Selector;
class Nuvi;
class Ground;
class ScoreScreen;
class Score;
class GameOver;

class AudioTitle;
class AudioGame;
class AudioGameOver;
class AudioMorte;
class AudioDamage;
class AudioJump;
class AudioShoot;

class Character;
class RunnerManager;
class Player;
class Atiradeiro;
class Bear;
class InterfaceMove;

class InputManager;

class Bullet;
class GerenciadorBullet;

class Position;
class Speed;
template <typename NumType>
class Acceleration;
class ALLEGRO_BITMAP;
class ALLEGRO_TIMER;
class ALLEGRO_FONT;

const bool player_shooting = true;
const bool enemy_shooting = false;
const int num_high_scores = 10;

enum GameState
{
	in_title_screen,
	playing,
	in_score_screen,
	game_over,
};



enum MenuState
{
	Iniciar,
	Placar,
	Sair,
};


const char numbers[10] = {'0' ,'1' ,'2' ,'3' ,'4' ,'5' ,'6' ,'7' ,'8' ,'9'};

extern ALLEGRO_TIMER* timer;
extern int contador;
