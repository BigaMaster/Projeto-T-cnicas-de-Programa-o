#pragma once

#include "Classes.hpp"




//============================================================================================================================================================

class GerenciadorBullet
{
    static Bullet* bullets[MAX_BULLETS];
    static ALLEGRO_BITMAP* bullet_bitmap;
    static int num_enemy_bullets, num_player_bullets;
public:
    friend Game;
    static void inicializaBullets();
    static void destroiBullets ();
    static void atualizaBullets (ALLEGRO_EVENT ev);
    static void drawBullets (ALLEGRO_DISPLAY* display);
    static void adicionaBullet(float position_x, float position_y, float initial_vx, bool flag);
    static void tiraBullet(int indice);
};

class Bullet
{
    friend Game;
    friend Player;
    friend Atiradeiro;
    friend GerenciadorBullet;
    friend ScreenManager;
    ALLEGRO_BITMAP* bullet_bitmap;
    Position* position;
    Speed* speed;
    bool flag;
public:
    Bullet(float position_x, float position_y, float initial_vx, bool _flag);
    ~Bullet();
    void draw (ALLEGRO_DISPLAY* display);
    void update (ALLEGRO_EVENT ev);
};

