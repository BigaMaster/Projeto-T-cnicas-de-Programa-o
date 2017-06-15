#include "Classes.hpp"
#include "Allegro.hpp"
#include "Input.hpp"

#include <stdlib.h>
#include <iostream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/keyboard.h>

ALLEGRO_DISPLAY* display;
ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* event_queue;
int contador = 0;

const double fps = 60;

int main ()
{
	if (!Allegro::initialize ())
		return 0;

	display = al_create_display (DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!display)
		al_show_native_message_box (0, "Error", "Error", "Cannot create display", 0, 0);

	timer = al_create_timer (1.0 / fps);
	if (!timer)
		al_show_native_message_box (0, "Error", "Error", "Cannot create timer", 0, 0);

	event_queue = al_create_event_queue ();

	al_register_event_source (event_queue, al_get_keyboard_event_source ());
    al_register_event_source (event_queue, al_get_timer_event_source (timer));
    al_register_event_source (event_queue, al_get_display_event_source (display));

    Game* game = new Game ();

    InputManager input;

    al_start_timer (timer);

    while (game->getKeepPlaying ())
    {
		ALLEGRO_EVENT ev;
        al_wait_for_event (event_queue, &ev);

        game->update (ev);

        if (game->getKeepPlaying ())
            game->draw (display);

        al_flip_display ();
    }

    delete game;
    al_destroy_timer (timer);
    al_destroy_event_queue (event_queue);
    al_destroy_display (display);

	return 0;
}
