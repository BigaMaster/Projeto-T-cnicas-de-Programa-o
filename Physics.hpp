#pragma once

#include "Classes.hpp"



//============================================================================================================================================================

class Position
{
    friend Game;
    friend Selector;
    friend Player;
    friend Atiradeiro;
    friend Bullet;
public:
    float x, y;
    Position (float initial_x, float initial_y);
    ~Position();
    void changePosition (Speed* increment);
    void setPosition (Position* new_position);
    Position& getPosition ();
};


//============================================================================================================================================================

class Speed
{
    friend Player;
public:
    float vx, vy;
    Speed(float initial_vx, float initial_vy);
    ~Speed();
    void changeSpeed (Acceleration<float>* increment);
    Speed& getSpeed ();
    void setSpeed (Speed* new_speed);
};


//============================================================================================================================================================
template <typename NumType>
class Acceleration
{
    float ax, ay;
    friend Player;
    friend Speed;
public:
    Acceleration(NumType initial_ax, NumType initial_ay);
    ~Acceleration();
    void changeAccelerationX (NumType increment_x);
    void changeAccelerationY (NumType increment_y);
    Acceleration& getAcceleration ();
};





//============================================================================================================================================================






//============================================================================================================================================================






//============================================================================================================================================================






//============================================================================================================================================================





//============================================================================================================================================================
