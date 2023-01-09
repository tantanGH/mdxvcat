#include "mdx.h"
#include "mdxvcat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <doslib.h>

static void show_help() {
  printf("MDXVCAT - MDX Voice Data Extractor version " VERSION " 2023 by tantan\n");
  printf("usage: mdxvcat [option] <mdx-file-name>\n");
  printf("options:\n");
  printf("  -f<format>   ... 0:MDX(default) 1:ZMS 2:XC 3:BAS\n");
  printf("  -o<out-file> ... output file name (default:stdout)\n");
  printf("  -h           ... show help message\n");
}

int main(int argc, char* argv[]) {

  int rc = 1;

  if (argc < 2) {
    show_help();
    goto exit;
  }

  char* mdx_file = NULL;
  char* out_file = NULL;
  int format = FORMAT_MDX;
  int ofs = 1;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'f') {
        if (argv[i][2] >= '0' && argv[i][2] <= '3') {
          format = atoi(argv[i]+2);
        } else if (strcmp(argv[i]+2,"mdx") == 0) {
          format = FORMAT_MDX;
        } else if (strcmp(argv[i]+2,"zms") == 0) {
          format = FORMAT_ZMS;
        } else if (strcmp(argv[i]+2,"xc") == 0) {
          format = FORMAT_XC;
        } else if (strcmp(argv[i]+2,"bas") == 0) {
          format = FORMAT_BAS;
        } else {
          printf("error: unknown format.\n");
          goto exit;
        }
      } else if (argv[i][1] == 'o') {
        out_file = argv[i]+2;
      } else if (argv[i][1] == 'h') {
        show_help();
        goto exit;
      } else {
        printf("error: unknown option.\n");
        goto exit;
      }
    } else {
      mdx_file = argv[i];
    }
  }

  if (mdx_file == NULL) {
    printf("error: no mdx file.\n");
    goto exit;
  }

  FILE* op = stdout;
  if (out_file != NULL) {
    struct FILBUF filbuf;
    if (FILES(&filbuf, out_file, 0x23) == 0) {
      char c;
      printf("warn: output file (%s) exists. overwrite? (y/n)", out_file);
      scanf("%c",&c);
      if (c != 'y' && c != 'Y') {
        printf("canceled.\n");
        goto exit;
      }
    }    
    op = fopen(out_file, "w");
    if (op == NULL) {
      printf("error: cannot open output file.\n");
      goto exit;
    }
  }
  
  MDX mdx;
  if (mdx_open(&mdx, mdx_file) != 0) {
    printf("error: mdx file read error.\n");
    goto catch;
  }

  //mdx_describe(&mdx);

  VOICE_SET* vs = mdx_get_voice_set(&mdx);
  if (vs == NULL) {
    printf("error: cannot extract any voices.\n");
    goto catch;
  }

  voice_set_fwrite(vs, op, format);
  voice_set_close(vs);

  mdx_close(&mdx);

  rc = 0;

catch:
  if (out_file != NULL) {
    fclose(op);
  }

exit:
  return rc;
}