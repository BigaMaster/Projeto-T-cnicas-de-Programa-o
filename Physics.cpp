
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


Acceleration<float> Character::gravity (0, 0.25);



//============================================================================================================================================================

Position::Position (float initial_x, float initial_y)
{
	x = initial_x;
	y = initial_y;
}

Position::~Position () {}

void Position::changePosition (Speed* increment)
{
	x += increment->getSpeed ().vx;
	y += increment->getSpeed ().vy;
}

Position& Position::getPosition ()
{
	return *this;
}

void Position::setPosition (Position* new_position)
{
	x = new_position->getPosition ().x;
	y = new_position->getPosition ().y;
}


//============================================================================================================================================================
Speed::Speed (float initial_vx, float initial_vy)
{
	vx = initial_vx;
	vy = initial_vy;
}

Speed::~Speed () {}

void Speed::changeSpeed (Acceleration<float>* increment)
{
	vx += increment->getAcceleration ().ax;
	vy += increment->getAcceleration ().ay;
}

Speed& Speed::getSpeed ()
{
	return *this;
}

void Speed::setSpeed (Speed* new_speed)
{
	vx = new_speed->vx;
	vy = new_speed->vy;
}



//============================================================================================================================================================
template <class NumType>
Acceleration<NumType>::Acceleration (NumType initial_ax, NumType initial_ay)
{
	ax = initial_ax;
	ay = initial_ay;
}

template <class NumType>
Acceleration<NumType>::~Acceleration () {}

template <class NumType>
void Acceleration<NumType>::changeAccelerationX (NumType increment_x)
{
	ax += increment_x;
}

template <class NumType>
void Acceleration<NumType>::changeAccelerationY (NumType increment_y)
{
	ay += increment_y;
}

template <class NumType>
Acceleration<NumType>& Acceleration<NumType>::getAcceleration ()
{
	return *this;
}



