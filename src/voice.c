#include "voice.h"
#include <stdio.h>

void voice_fwrite(VOICE* v, FILE* fp, int format) {

  if (v == NULL || fp == NULL) return;

  // m_vset() format
  fprintf(fp, "char voice_data[5][11] = {\n");

  fprintf(fp, "  { %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d },\n", 
          v->connection + v->feedback * 8, v->slot_mask, v->wave_form, v->synchro, v->speed,
          v->pmd, v->amd, v->pms, v->ams, v->pan, v->reserved);

  fprintf(fp, "  { %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d }, \n",
          v->attack_rate_m1, v->decay_rate_m1, v->sustain_rate_m1, v->release_rate_m1, v->sustain_level_m1,
          v->total_level_m1, v->key_scaling_m1, v->phase_multi_m1, v->detune1_m1, v->detune2_m1, v->ame_enable_m1);

  fprintf(fp, "  { %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d }, \n",
          v->attack_rate_c1, v->decay_rate_c1, v->sustain_rate_c1, v->release_rate_c1, v->sustain_level_c1,
          v->total_level_c1, v->key_scaling_c1, v->phase_multi_c1, v->detune1_c1, v->detune2_c1, v->ame_enable_c1);

  fprintf(fp, "  { %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d }, \n",
          v->attack_rate_m2, v->decay_rate_m2, v->sustain_rate_m2, v->release_rate_m2, v->sustain_level_m2,
          v->total_level_m2, v->key_scaling_m2, v->phase_multi_m2, v->detune1_m2, v->detune2_m2, v->ame_enable_m2);

  fprintf(fp, "  { %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d } \n",
          v->attack_rate_c2, v->decay_rate_c2, v->sustain_rate_c2, v->release_rate_c2, v->sustain_level_c2,
          v->total_level_c2, v->key_scaling_c2, v->phase_multi_c2, v->detune1_c2, v->detune2_c2, v->ame_enable_c2);

  fprintf(fp, "};\n");

}