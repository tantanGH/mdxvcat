#include "mdx.h"
#include "voice.h"
#include "memory.h"
#include <stdio.h>

int mdx_open(MDX* mdx, const unsigned char* file_name) {

  int rc = 0;

  // read MDX file content to memory buffer
  FILE* fp = NULL;
  if ((fp = fopen(file_name, "rb")) != NULL) {

    // get file size
    fseek(fp, 0, SEEK_END);
    mdx->data_len = (int)ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // allocate memory buffer and read
    mdx->data_buffer = malloc_himem(mdx->data_len, 0);
    fread(mdx->data_buffer, 1, mdx->data_len, fp);
    
    // close
    fclose(fp);
    fp = NULL;    

  } else {
    rc = -1;
    goto catch;
  }

  // parse data title
  mdx->data_title = NULL;
  int ofs = 0;
  while ( ofs + 2 < mdx->data_len ) {
    if (mdx->data_buffer[ ofs ] == 0x0d && mdx->data_buffer[ ofs + 1 ] == 0x0a && mdx->data_buffer[ ofs + 2 ] == 0x1a ) {
          mdx->data_title = mdx->data_buffer;
          mdx->data_title[ ofs ] = '\0';
          break;
    }
    ofs++;
  }
  ofs += 3;
  if (ofs >= mdx->data_len) {
    rc = -2;
    goto catch;
  }

  // parse pcm file name
  mdx->pcm_file_name = NULL;
  int ofs_pcm = ofs;
  while ( ofs < mdx->data_len ) {
    if (mdx->data_buffer[ ofs++ ] == 0x00) {
      mdx->pcm_file_name = mdx->data_buffer + ofs_pcm;
      break;
    }
  }
  if (ofs >= mdx->data_len) {
    rc = -2;
    goto catch;
  }

  // channel and tone data offset base
  int ofs_base = ofs;

  // voice data offset
  mdx->voice_offset = ofs_base + ( mdx->data_buffer[ ofs ] * 256 ) + mdx->data_buffer[ ofs + 1 ];
  if (mdx->voice_offset > mdx->data_len) {
    rc = -2;
    goto catch;
  }
  ofs += 2;

  // count voices
  mdx->voice_count = ( mdx->data_len - mdx->voice_offset ) / 27;

  // channel data offset
  for (int i = 0; i < 9; i++) {   // OPM 8 + PCM 1
    mdx->channel_offset[i] = ofs_base + ( mdx->data_buffer[ ofs ] * 256 ) + mdx->data_buffer[ ofs + 1 ];
    if (mdx->channel_offset[i] > mdx->data_len) {
      rc = -2;
      goto catch;
    }
    ofs += 2;
  }
  if (mdx->channel_offset[0] >= ofs_base + 0x22) {   // ex-pcm mode?
    for (int i = 9; i < 16; i++) {
      mdx->channel_offset[i] = ofs_base + ( mdx->data_buffer[ ofs ] * 256 ) + mdx->data_buffer[ ofs + 1 ];
      if (mdx->channel_offset[i] > mdx->data_len) {
        rc = -2;
        goto catch;
      }
      ofs += 2;
    }
  } else {
    for (int i = 9; i < 16; i++) {
      mdx->channel_offset[i] = 0;
    }
  }

  goto exit;

catch:
  mdx->data_len = 0;
  if (mdx->data_buffer != NULL) {
    free_himem(mdx->data_buffer,0);
    mdx->data_buffer = NULL;
  }

exit:
  return rc;
}

void mdx_close(MDX* mdx) {
  if (mdx->data_buffer != NULL) {
    free_himem(mdx->data_buffer, 0);
    mdx->data_buffer = NULL;
  }
}

int mdx_get_voices(MDX* mdx, VOICE* voice_buffer, int voice_buffer_size) {

}

void mdx_describe(MDX* mdx) {
  printf("data title: [%s]\n", mdx->data_title);
  printf("pcm name: [%s]\n", mdx->pcm_file_name);
  printf("voice offset: %d\n", mdx->voice_offset);
  printf("voice count: %d\n", mdx->voice_count);
  for (int i = 0; i < 8; i++) {
    printf("channel offset %C: %d\n", 'A'+i, mdx->channel_offset[i]);
  }
  for (int i = 0; i < 8; i++) {
    printf("channel offset %C: %d\n", 'P'+i, mdx->channel_offset[i+8]);
  }
}