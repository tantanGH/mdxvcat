#ifndef __H_MDX__
#define __H_MDX__

#include "voice.h"
#include <stdio.h>

typedef struct {

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
int mdx_get_voices(MDX* mdx, VOICE* voices, int buffer_size);

#endif