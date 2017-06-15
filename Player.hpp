#pragma once

#include "Classes.hpp"
#include "Input.hpp"




class InterfaceMove
{
	virtual void jump () = 0;
};


//============================================================================================================================================================

class Character
{
public:
    Position* position;
    Speed* speed;
    static Acceleration<float> gravity;

public:
    Character ();
    virtual ~Character ();
    virtual bool onGround ();
    virtual bool onPlatform ();
    virtual void jump ();
    virtual void shoot ();
    virtual void update (ALLEGRO_EVENT ev);
    virtual void draw (ALLEGRO_DISPLAY* display);
};



//============================================================================================================================================================

class RunnerManager
{
    friend Player;

    static ALLEGRO_BITMAP** runner_bitmaps;
    static int state;
    static int timer_counter;
    static float timer_acceleration, timer_change;
public:
    static void initializeVector (Player* player);
    static void changeRunnerBitmap (Player* player, ALLEGRO_EVENT ev);
    static void destroyVector ();
};

//============================================================================================================================================================


class Player : public Character, public InterfaceMove
{
    ALLEGRO_BITMAP* player_bitmap, *player_jumping_bitmap;
    ALLEGRO_FONT* font;
    Score* score;
    InputManager player_input;
    int num_bullets;
    const int max_bullets;
    int lives;
    float height, width;
    bool is_jumping, score_saved;
    friend Bullet;
    friend ScreenManager;
    friend Game;
    friend RunnerManager;

public:
    Player ();
    ~Player();

    float getHeight ();
    float getWidth ();

    bool onGround ();
    bool onPlatform ();
    void shoot ();
    void jump ();

    void update (ALLEGRO_EVENT ev);
    void draw (ALLEGRO_DISPLAY* display);
    
    void reset ();

    void takeLife ();
};




//============================================================================================================================================================

class Atiradeiro : public Character
{
    ALLEGRO_BITMAP *enemy_bitmap;
    Position *position;
    static Speed *speed;
    float height, width;
    friend ScreenManager;
    friend Game;

public:
    bool hit_player;
    Atiradeiro ();
    ~Atiradeiro ();

    void update (ALLEGRO_EVENT ev);
    void draw (ALLEGRO_DISPLAY* display);

    void die ();
};


//============================================================================================================================================================


class Bear
{
    ALLEGRO_BITMAP* bear_bitmap;
    Position* position;
    static Speed* speed;
    float height, width;
    friend ScreenManager;
    friend Game;

public:
    bool hit_player;
    Bear ();
    ~Bear ();

    void update ();
    void draw (ALLEGRO_DISPLAY* display);

    void die ();
};

//============================================================================================================================================================
