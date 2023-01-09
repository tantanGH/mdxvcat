#include "mdx.h"
#include "mdxvcat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

  int rc = 1;

  if (argc < 2) {
    printf("usage: mdxvcat [option] <mdx-file-name>\n");
    printf("options:\n");
    printf("  -f<format>   ... 0:MDX(default) 1:ZMS 2:XC 3:BAS\n");
    printf("  -o<out-file> ... output file name (default:stdout)\n");
    goto exit;
  }

  char* mdx_file = NULL;
  char* out_file = NULL;
  int format = FORMAT_MDX;
  int ofs = 1;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'f') {
        format = atoi(argv[i]+2);
      } else if (argv[i][1] == 'o') {
        out_file = argv[i]+2;
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
    op = fopen(out_file, "w");
    if (op == NULL) {
      printf("error: cannot open output file.\n");
      goto exit;
    }
  }
  
  MDX mdx;
  mdx_open(&mdx, mdx_file); 
  //mdx_describe(&mdx);

  VOICE_SET* vs = mdx_get_voice_set(&mdx);
  voice_set_fwrite(vs, op, format);
  voice_set_close(vs);

  mdx_close(&mdx);

  if (out_file != NULL) {
    fclose(op);
  }

exit:
  return rc;
}