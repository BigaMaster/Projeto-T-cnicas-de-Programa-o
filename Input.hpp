#pragma once

#include "Classes.hpp"


//============================================================================================================================================================

class InputManager
{
    ALLEGRO_KEYBOARD_STATE keyState;
public:
    InputManager();
    ~InputManager();

    bool keyIsPressed (ALLEGRO_EVENT ev, int key);

    bool keyIsReleased (ALLEGRO_EVENT ev, int key);
};

