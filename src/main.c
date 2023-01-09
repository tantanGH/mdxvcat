#include "mdx.h"
#include <stdio.h>

int main(int argc, char* argv[]) {

  MDX mdx;

  mdx_open(&mdx, (const unsigned char*)(argv[1]));
  mdx_describe(&mdx);

  VOICE voices[ mdx.voice_count ];
  mdx_get_voices(&mdx, voices, 256);
  for (int i = 0; i < mdx.voice_count; i++) {
    voice_fwrite(&voices[i], stdout, 0);
  }

  mdx_close(&mdx);

  return 0;
}