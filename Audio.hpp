#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class AudioTitle
{
public:
    bool alerta;
	ALLEGRO_SAMPLE *sample;
	ALLEGRO_SAMPLE_INSTANCE* parador;
	AudioTitle();
	void Play();
	void stop();
	~AudioTitle();
};

class AudioGame
{
public:
    bool alerta;
	ALLEGRO_SAMPLE *sample;
	ALLEGRO_SAMPLE_INSTANCE* parador;
	AudioGame();
	void Play();
	void stop();
	~AudioGame();
};

class AudioGameOver
{
public:
    bool alerta;
	ALLEGRO_SAMPLE *sample;
	ALLEGRO_SAMPLE_INSTANCE* parador;
	AudioGameOver();
	void Play();
	void stop();
	~AudioGameOver();
};

class AudioMorte
{
public:
	bool alerta;
	ALLEGRO_SAMPLE *sample;
	AudioMorte();
	void Play();
	~AudioMorte();
};

class AudioDamage
{
public:
	bool alerta;
	ALLEGRO_SAMPLE *sample;
	AudioDamage();
	void Play();
	~AudioDamage();
};

class AudioJump
{
public:
	bool alerta;
	ALLEGRO_SAMPLE *sample;
	AudioJump();
	void Play();
	~AudioJump();
};

class AudioShoot
{
public:
	bool alerta;
	ALLEGRO_SAMPLE *sample;
	AudioShoot();
	void Play();
	~AudioShoot();
};