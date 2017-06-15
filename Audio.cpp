#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Audio.hpp"

using namespace std;


void AudioTitle::Play()
{
    alerta = true;
   sample = al_load_sample( "title.wav" );

   parador = al_create_sample_instance(sample);

   if (!sample){
      printf( "Audio clip sample not loaded!\n" );
   }

   al_attach_sample_instance_to_mixer(parador, al_get_default_mixer());
   al_set_sample_instance_playmode(parador, ALLEGRO_PLAYMODE_LOOP);
   al_play_sample_instance(parador);
}

void AudioTitle::stop()
{
    alerta=false;
    al_stop_sample_instance(parador);
    cout << "parou" << endl;
}

AudioTitle::AudioTitle()
{
    parador = NULL;
    sample = NULL;
    alerta = false;

   if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
   }

   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
   }

   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
   }
}

AudioTitle::~AudioTitle(){}

void AudioGame::Play()
{
    alerta = true;
   sample = al_load_sample( "game.wav" );

   parador = al_create_sample_instance(sample);

   if (!sample){
      printf( "Audio clip sample not loaded!\n" );
   }

   al_attach_sample_instance_to_mixer(parador, al_get_default_mixer());
   al_set_sample_instance_playmode(parador, ALLEGRO_PLAYMODE_LOOP);
   al_play_sample_instance(parador);
}

void AudioGame::stop()
{
    alerta=false;
    al_stop_sample_instance(parador);
    cout << "parou" << endl;
}

AudioGame::AudioGame()
{
    parador = NULL;
    sample = NULL;
    alerta = false;
   if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
   }

   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
   }

   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
   }
}

AudioGame::~AudioGame(){}

void AudioGameOver::Play()
{
    alerta = true;
   sample = al_load_sample( "gameover.wav" );

   parador = al_create_sample_instance(sample);

   if (!sample){
      printf( "Audio clip sample not loaded!\n" );
   }

   al_attach_sample_instance_to_mixer(parador, al_get_default_mixer());
   al_set_sample_instance_playmode(parador, ALLEGRO_PLAYMODE_LOOP);
   al_play_sample_instance(parador);
}

void AudioGameOver::stop()
{
    alerta=false;
    al_stop_sample_instance(parador);
    cout << "parou" << endl;
}

AudioGameOver::AudioGameOver()
{
    parador = NULL;
    sample = NULL;
    alerta = false;

   if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
   }

   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
   }

   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
   }
}

AudioGameOver::~AudioGameOver(){}

void AudioMorte::Play()
{
  alerta = true;
  sample = al_load_sample( "morte.wav" );

  if (!sample){
      printf( "Audio clip sample not loaded!\n" );
   }
  al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

AudioMorte::AudioMorte()
{
  alerta = false;
  sample = NULL;
  if(!al_install_audio()){
    fprintf(stderr, "failed to initialize audio!\n");
  }

  if(!al_init_acodec_addon()){
    fprintf(stderr, "failed to initialize audio codecs!\n");
  }

  if (!al_reserve_samples(1)){
    fprintf(stderr, "failed to reserve samples!\n");
  }
}

AudioMorte::~AudioMorte(){}

void AudioDamage::Play()
{
  alerta = true;
  sample = al_load_sample( "damage.wav" );

  if (!sample){
      printf( "Audio clip sample not loaded!\n" );
   }
  al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

AudioDamage::AudioDamage()
{
  alerta = false;
  sample = NULL;
  if(!al_install_audio()){
    fprintf(stderr, "failed to initialize audio!\n");
  }

  if(!al_init_acodec_addon()){
    fprintf(stderr, "failed to initialize audio codecs!\n");
  }

  if (!al_reserve_samples(1)){
    fprintf(stderr, "failed to reserve samples!\n");
  }
}

AudioDamage::~AudioDamage(){}

void AudioJump::Play()
{
  alerta = true;
  sample = al_load_sample( "jump.wav" );

  if (!sample){
      printf( "Audio clip sample not loaded!\n" );
   }
  al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

AudioJump::AudioJump()
{
  alerta = false;
  sample = NULL;
  if(!al_install_audio()){
    fprintf(stderr, "failed to initialize audio!\n");
  }

  if(!al_init_acodec_addon()){
    fprintf(stderr, "failed to initialize audio codecs!\n");
  }

  if (!al_reserve_samples(1)){
    fprintf(stderr, "failed to reserve samples!\n");
  }
}

AudioJump::~AudioJump(){}

void AudioShoot::Play()
{
  alerta = true;
  sample = al_load_sample( "shoot.wav" );

  if (!sample){
      printf( "Audio clip sample not loaded!\n" );
   }
  al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

AudioShoot::AudioShoot()
{
  alerta = false;
  sample = NULL;
  if(!al_install_audio()){
    fprintf(stderr, "failed to initialize audio!\n");
  }

  if(!al_init_acodec_addon()){
    fprintf(stderr, "failed to initialize audio codecs!\n");
  }

  if (!al_reserve_samples(1)){
    fprintf(stderr, "failed to reserve samples!\n");
  }
}

AudioShoot::~AudioShoot(){}