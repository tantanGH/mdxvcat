#include "voice.h"
#include "memory.h"
#include <stdio.h>

void voice_set_close(VOICE_SET* vs) {
  if (vs != NULL && vs->voices != NULL) {
    free_himem(vs->voices, 0);
    vs->voices = NULL;
    vs->voice_count = 0;
  }
}

void voice_set_fwrite(VOICE_SET* vs, FILE* fp, int format) {

  if (vs == NULL || vs->voices == NULL || fp == NULL) return;

  int line = 1000;

  switch (format) {
    case FORMAT_MDX:
      fprintf(fp, "; %s\n\n", vs->comment);
      fprintf(fp, "; %s\n", vs->name);
      break;
    case FORMAT_ZMS:
      fprintf(fp, "/ %s\n\n", vs->comment);
      fprintf(fp, "/ %s\n", vs->name);
      break;
    case FORMAT_XC:
      fprintf(fp, "/* %s */\n\n", vs->comment);
      fprintf(fp, "/* %s */\n", vs->name);
      break;
    case FORMAT_BAS:
      fprintf(fp, "%d /* %s */\n\n", line, vs->comment);
      fprintf(fp, "%d /* %s */\n", line+10, vs->name);
      line += 100;
      break;
  }

  for (int i = 0; i < vs->voice_count; i++) {

    VOICE* v = &(vs->voices[i]);

    switch (format) {

      case FORMAT_MDX:
        fprintf(fp, "\n@%d = {\n", v->voice_id);

        fprintf(fp, ";    AR   DR   SR   RR   SL   TL   KS  MUL  DT1  DT2  AME\n");
        fprintf(fp, "    %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d,\n", 
                v->attack_rate_m1, v->decay_rate1_m1, v->decay_rate2_m1, v->release_rate_m1, v->decay_level1_m1,
                v->total_level_m1, v->key_scaling_m1, v->phase_multi_m1, v->detune1_m1, v->detune2_m1, v->ams_enable_m1);

        fprintf(fp, "    %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d,\n", 
                v->attack_rate_c1, v->decay_rate1_c1, v->decay_rate2_c1, v->release_rate_c1, v->decay_level1_c1,
                v->total_level_c1, v->key_scaling_c1, v->phase_multi_c1, v->detune1_c1, v->detune2_c1, v->ams_enable_c1);

        fprintf(fp, "    %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d,\n", 
                v->attack_rate_m2, v->decay_rate1_m2, v->decay_rate2_m2, v->release_rate_m2, v->decay_level1_m2,
                v->total_level_m2, v->key_scaling_m2, v->phase_multi_m2, v->detune1_m2, v->detune2_m2, v->ams_enable_m2);

        fprintf(fp, "    %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d,\n", 
                v->attack_rate_c2, v->decay_rate1_c2, v->decay_rate2_c2, v->release_rate_c2, v->decay_level1_c2,
                v->total_level_c2, v->key_scaling_c2, v->phase_multi_c2, v->detune1_c2, v->detune2_c2, v->ams_enable_c2);

        fprintf(fp, ";   ALG   FL   OP\n");
        fprintf(fp, "    %3d, %3d, %3d }\n", 
                v->connection, v->feedback, v->slot_mask);
        break;

      case FORMAT_ZMS:
        fprintf(fp, "\n/       AR   DR   SR   RR   SL  OL   KS   MUL  DT1  DT2  AME\n");

        fprintf(fp, "(@%-3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d\n", 
                v->voice_id,
                v->attack_rate_m1, v->decay_rate1_m1, v->decay_rate2_m1, v->release_rate_m1, v->decay_level1_m1,
                v->total_level_m1, v->key_scaling_m1, v->phase_multi_m1, v->detune1_m1, v->detune2_m1, v->ams_enable_m1);

        fprintf(fp, "       %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d\n", 
                v->attack_rate_c1, v->decay_rate1_c1, v->decay_rate2_c1, v->release_rate_c1, v->decay_level1_c1,
                v->total_level_c1, v->key_scaling_c1, v->phase_multi_c1, v->detune1_c1, v->detune2_c1, v->ams_enable_c1);

        fprintf(fp, "       %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d\n", 
                v->attack_rate_m2, v->decay_rate1_m2, v->decay_rate2_m2, v->release_rate_m2, v->decay_level1_m2,
                v->total_level_m2, v->key_scaling_m2, v->phase_multi_m2, v->detune1_m2, v->detune2_m2, v->ams_enable_m2);

        fprintf(fp, "       %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d\n", 
                v->attack_rate_c2, v->decay_rate1_c2, v->decay_rate2_c2, v->release_rate_c2, v->decay_level1_c2,
                v->total_level_c2, v->key_scaling_c2, v->phase_multi_c2, v->detune1_c2, v->detune2_c2, v->ams_enable_c2);

        fprintf(fp, "/       AF   FB   OM  PAN   WF   SY   SP  PMD  AMD  PMS  AMS\n");
        fprintf(fp, "       %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d)\n", 
                v->connection, v->feedback, v->slot_mask, v->pan, v->wave_form,
                v->synchro, v->speed, v->pmd, v->amd, v->pms, v->ams);
        break;

      case FORMAT_XC:
        fprintf(fp, "\nchar voice_data_%d[5][11] = {\n", v->voice_id);

        fprintf(fp, "/*  AF   SM   WF   SY   SP   PMD  AMD  PMS  AMS  PAN  RSV */\n");
        fprintf(fp, "  { %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d },\n", 
                v->connection + v->feedback * 8, v->slot_mask, v->wave_form, v->synchro, v->speed,
                v->pmd, v->amd, v->pms, v->ams, v->pan, v->reserved);

        fprintf(fp, "/*  AR   D1R  D2R  RR   D1L  TL   KS   MUL  DT1  DT2  AME */\n");
        fprintf(fp, "  { %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d },\n", 
                v->attack_rate_m1, v->decay_rate1_m1, v->decay_rate2_m1, v->release_rate_m1, v->decay_level1_m1,
                v->total_level_m1, v->key_scaling_m1, v->phase_multi_m1, v->detune1_m1, v->detune2_m1, v->ams_enable_m1);

        fprintf(fp, "  { %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d },\n", 
                v->attack_rate_c1, v->decay_rate1_c1, v->decay_rate2_c1, v->release_rate_c1, v->decay_level1_c1,
                v->total_level_c1, v->key_scaling_c1, v->phase_multi_c1, v->detune1_c1, v->detune2_c1, v->ams_enable_c1);

        fprintf(fp, "  { %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d },\n", 
                v->attack_rate_m2, v->decay_rate1_m2, v->decay_rate2_m2, v->release_rate_m2, v->decay_level1_m2,
                v->total_level_m2, v->key_scaling_m2, v->phase_multi_m2, v->detune1_m2, v->detune2_m2, v->ams_enable_m2);

        fprintf(fp, "  { %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d }\n", 
                v->attack_rate_c2, v->decay_rate1_c2, v->decay_rate2_c2, v->release_rate_c2, v->decay_level1_c2,
                v->total_level_c2, v->key_scaling_c2, v->phase_multi_c2, v->detune1_c2, v->detune2_c2, v->ams_enable_c2);

        fprintf(fp, "};\n");
        fprintf(fp, "/* m_vset(%d,voice_data_%d); */\n", v->voice_id, v->voice_id);
        break;

      case FORMAT_BAS:
        fprintf(fp, "\n%d dim char voice_data_%d(4,10)\n", line, v->voice_id);
        fprintf(fp, "%d voice_data_%d = \n", line+10, v->voice_id);

        fprintf(fp, "%d /*   AF   SM   WF   SY   SP  PMD  AMD  PMS  AMS  PAN  RSV */\n", line+20);
        fprintf(fp, "%d   { %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d,\n", 
                line+30,
                v->connection + v->feedback * 8, v->slot_mask, v->wave_form, v->synchro, v->speed,
                v->pmd, v->amd, v->pms, v->ams, v->pan, v->reserved);

        fprintf(fp, "%d /*   AR  D1R  D2R   RR  D1L   TL   KS  MUL  DT1  DT2  AME */\n", line+40);
        fprintf(fp, "%d     %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d,\n", 
                line+50,
                v->attack_rate_m1, v->decay_rate1_m1, v->decay_rate2_m1, v->release_rate_m1, v->decay_level1_m1,
                v->total_level_m1, v->key_scaling_m1, v->phase_multi_m1, v->detune1_m1, v->detune2_m1, v->ams_enable_m1);

        fprintf(fp, "%d     %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d,\n", 
                line+60,
                v->attack_rate_c1, v->decay_rate1_c1, v->decay_rate2_c1, v->release_rate_c1, v->decay_level1_c1,
                v->total_level_c1, v->key_scaling_c1, v->phase_multi_c1, v->detune1_c1, v->detune2_c1, v->ams_enable_c1);

        fprintf(fp, "%d     %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d,\n", 
                line+70,
                v->attack_rate_m2, v->decay_rate1_m2, v->decay_rate2_m2, v->release_rate_m2, v->decay_level1_m2,
                v->total_level_m2, v->key_scaling_m2, v->phase_multi_m2, v->detune1_m2, v->detune2_m2, v->ams_enable_m2);

        fprintf(fp, "%d     %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d, %3d  }\n", 
                line+80,
                v->attack_rate_c2, v->decay_rate1_c2, v->decay_rate2_c2, v->release_rate_c2, v->decay_level1_c2,
                v->total_level_c2, v->key_scaling_c2, v->phase_multi_c2, v->detune1_c2, v->detune2_c2, v->ams_enable_c2);

        fprintf(fp, "%d m_vset(%d, voice_data_%d)\n", line+90, v->voice_id, v->voice_id);
        line += 100;
        break;
    }

  }

}

