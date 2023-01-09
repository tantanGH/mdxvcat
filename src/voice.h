#ifndef __H_VOICE__
#define __H_VOICE__

#include <stdio.h>
#include <stddef.h>
#include <class.h>

typedef struct {

  unsigned int voice_id;

  time_t create_time;
  time_t update_time;
  
  unsigned char version[8];       // opmvedit.x version

  unsigned char name[24];
  unsigned char tag1[8];
  unsigned char tag2[8];
  unsigned char tag3[8];
  unsigned char tag4[8];
  unsigned char comment[64];

  unsigned char favorite;
  unsigned char selected;         // for UI use only (not serialized)
  unsigned char deleted;          // for UI use only (not serialized)

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

} VOICE;

typedef struct {

  unsigned int voice_set_id;
  unsigned char version[8];       // opmvedit.x version

  time_t create_time;
  time_t update_time;

  unsigned char name[24];
  unsigned char tag1[8];
  unsigned char tag2[8];
  unsigned char tag3[8];
  unsigned char tag4[8];
  unsigned char comment[64];

  int voice_count;
  VOICE voices[];

} VOICE_SET;

// prototype declarations
/*
int voice_set_load(OPM_VOICE_SET* ovs, FILE* fp);
int voice_set_save(OPM_VOICE_SET* ovs, FILE* fp);
int voice_set_select_voices(OPM_VOICE_SET* ovs, OPM_VOICE* ov_list, int ov_count, const char* tag);
int voice_set_sort_voices(VOICE_SET* ovs, int sort_key, int sort_order);
int voice_set_add_voice(VOICE_SET* ovs, OPM_VOICE* ov);
int voice_set_add_voices(VOICE_SET* ovs, OPM_VOICE* VOICEs, int VOICE_count);
int voice_set_delete_VOICE(VOICE_SET* ovs, unsigned int VOICE_id);
int voice_set_up_VOICE(VOICE_SET* VOICE_set, unsigned int VOICE_id);
int voice_set_down_VOICE(VOICE_SET* VOICE_set, unsigned int VOICE_id);
int voice_set_describe(VOICE_SET* VOICE);
*/
void voice_fwrite(VOICE* v, FILE* fp, int format);

#endif