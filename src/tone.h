#ifndef __H_TONE__
#define __H_TONE__

#include <stdio.h>
#include <stddef.h>
#include <class.h>

typedef struct {

  unsigned int tone_id;
  short version;

  time_t create_time;
  time_t update_time;

  unsigned int selected;

  unsigned char tone_name[32];

  unsigned char tag1[8];
  unsigned char tag2[8];
  unsigned char tag3[8];
  unsigned char tag4[8];

  unsigned char comment[256];

  unsigned char connection;
  unsigned char feedback;
  unsigned char slot_mask;
  unsigned char wave_form;
  unsigned char synchro;
  unsigned char speed;
  unsigned char pmd;
  unsigned char amd;
  unsigned char pms;
  unsigned char ams;
  unsigned char pan;
  unsigned char reserved;

  unsigned char attack_rate_m1;
  unsigned char decay_rate_m1;
  unsigned char sustain_rate_m1;
  unsigned char release_rate_m1;
  unsigned char sustain_level_m1;
  unsigned char total_level_m1;
  unsigned char key_scaling_m1;
  unsigned char phase_multi_m1;
  unsigned char detune1_m1;
  unsigned char detune2_m1;
  unsigned char ame_enable_m1;

  unsigned char attack_rate_c1;
  unsigned char decay_rate_c1;
  unsigned char sustain_rate_c1;
  unsigned char release_rate_c1;
  unsigned char sustain_level_c1;
  unsigned char total_level_c1;
  unsigned char key_scaling_c1;
  unsigned char phase_multi_c1;
  unsigned char detune1_c1;
  unsigned char detune2_c1;
  unsigned char ame_enable_c1;  

  unsigned char attack_rate_m2;
  unsigned char decay_rate_m2;
  unsigned char sustain_rate_m2;
  unsigned char release_rate_m2;
  unsigned char sustain_level_m2;
  unsigned char total_level_m2;
  unsigned char key_scaling_m2;
  unsigned char phase_multi_m2;
  unsigned char detune1_m2;
  unsigned char detune2_m2;
  unsigned char ame_enable_m2;

  unsigned char attack_rate_c2;
  unsigned char decay_rate_c2;
  unsigned char sustain_rate_c2;
  unsigned char release_rate_c2;
  unsigned char sustain_level_c2;
  unsigned char total_level_c2;
  unsigned char key_scaling_c2;
  unsigned char phase_multi_c2;
  unsigned char detune1_c2;
  unsigned char detune2_c2;
  unsigned char ame_enable_c2;

} TONE;

typedef struct {

  unsigned int tone_set_id;
  short version;

  time_t create_time;
  time_t update_time;

  unsigned char name[32];

  unsigned char tag1[8];
  unsigned char tag2[8];
  unsigned char tag3[8];
  unsigned char tag4[8];

  unsigned char comment[256];

  ULONG tone_count;
  TONE tones[];

} TONE_SET;

// prototype declarations
int tone_set_load(TONE_SET* tone_set, FILE* fp);
int tone_set_save(TONE_SET* tone_set, FILE* fp);
int tone_set_select_tones(TONE_SET* tone_set, TONE* tone_list, int tone_list_size, const char* tag);
int tone_set_sort_tones(TONE_SET* tone_set, int sort_key, int sort_order);
int tone_set_add_tone(TONE_SET* tone_set, TONE* tone);
int tone_set_add_tones(TONE_SET* tone_set, TONE* tones, int tone_count);
int tone_set_delete_tone(TONE_SET* tone_set, unsigned int tone_id);

#endif