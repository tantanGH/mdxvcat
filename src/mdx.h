#ifndef __H_MDX__
#define __H_MDX__

#include "voice.h"
#include <stdio.h>

#define MDX_VOICE_LEN (27)

typedef struct {

  unsigned char file_name[32];

  unsigned char* data_buffer;
  int data_len;

  unsigned char* data_title;
  unsigned char* pcm_file_name;

  unsigned short voice_offset;   
  int voice_count;

  unsigned short channel_offset[16];

} MDX;

int mdx_open(MDX* mdx, const unsigned char* file_name);
void mdx_close(MDX* mdx);
void mdx_describe(MDX* mdx);
VOICE_SET* mdx_get_voice_set(MDX* mdx);

#endif