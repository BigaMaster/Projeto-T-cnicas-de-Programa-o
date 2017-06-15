
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

InputManager::InputManager () {}
InputManager::~InputManager () {}

bool InputManager::keyIsPressed (ALLEGRO_EVENT ev, int key)
{
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		if (ev.keyboard.keycode == key)
			return true;

	return false;
}

bool InputManager::keyIsReleased (ALLEGRO_EVENT ev, int key)
{
	if (ev.type == ALLEGRO_EVENT_KEY_UP)
		if (ev.keyboard.keycode == key)
			return true;

	return false;
}


//============================================================================================================================================================

