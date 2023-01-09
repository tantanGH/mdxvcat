# MDXVCAT.X

MDX Voice Data Extractor for X680x0/Human68k

MDXファイルから音色データのみを抽出し、MDX MML / ZMUSIC MML / XC / X-BASIC 形式のいずれかのフォーマットで定義データを書き出します。

X680x0/Human68k 上で動作します。コマンドラインツールなので run68 上でも動作します。

---

### Install

MDXVCxxx.ZIP をダウンロードして展開し、MDXVCAT.X をパスの通ったディレクトリに置きます。

---

### How to use

引数をつけずに実行するか、`-h` オプションをつけて実行するとヘルプメッセージが表示されます。

    MDXVCAT - MDX Voice Data Extractor version 0.1.0 2023 by tantan
    usage: mdxvcat [option] <mdx-file-name>
    options:
      -f<format>   ... 0:MDX(default) 1:ZMS 2:XC 3:BAS
      -o<out-file> ... output file name (default:stdout)
      -h           ... show help message

`-f` オプションで出力形式を選択します。デフォルトは MDX MML 形式です。数字の他にも mdx, zms, xc, bas のキーワードでも指定可能です。
`-o` オプションで出力先ファイルを指定します。指定しない場合は標準出力に出力されます。ファイルの上書きチェックなどはしていませんので注意してください。

---

### Samples

出力例 MDX 形式

    #title "SAMPLE MDX by tantan"
    
    ; SAMPLE1.MDX

    @33 = {
    ;    AR   DR   SR   RR   SL   TL   KS  MUL  DT1  DT2  AME
         31,  31,   0,  10,   0,  27,   0,   0,   0,   0,   0,
         31,  12,  12,  11,   8,  43,   0,   8,   0,   0,   0,
         31,  14,  10,   8,   3,  21,   0,   0,   0,   0,   0,
         31,  11,   9,  12,   1,  18,   0,   1,   0,   0,   0,
    ;   ALG   FL   OP
          2,   2,  15 }

    @40 = {
    ;    AR   DR   SR   RR   SL   TL   KS  MUL  DT1  DT2  AME
         30,  22,  11,   3,   5,  14,   0,   1,   3,   0,   1,
         18,   7,   8,   7,   4,  28,   0,   1,   6,   0,   0,
         30,  22,  11,   4,   5,  50,   0,  14,   7,   0,   0,
         30,   7,   8,   7,   4,  28,   0,   1,   3,   0,   0,
    ;   ALG   FL   OP
          4,   0,  15 }


---

出力例 ZMS 形式 (音色番号は+1されます)

    .comment SAMPLE MDX by tantan

    / SAMPLE1.MDX

    /       AR   DR   SR   RR   SL  OL   KS   MUL  DT1  DT2  AME
    (@34 ,  31,  31,   0,  10,   0,  27,   0,   0,   0,   0,   0,
            31,  12,  12,  11,   8,  43,   0,   8,   0,   0,   0,
            31,  14,  10,   8,   3,  21,   0,   0,   0,   0,   0,
            31,  11,   9,  12,   1,  18,   0,   1,   0,   0,   0,
    /       AF   FB   OM
             2,   2,  15)

    /       AR   DR   SR   RR   SL  OL   KS   MUL  DT1  DT2  AME
    (@41 ,  30,  22,  11,   3,   5,  14,   0,   1,   3,   0,   1,
            18,   7,   8,   7,   4,  28,   0,   1,   6,   0,   0,
            30,  22,  11,   4,   5,  50,   0,  14,   7,   0,   0,
            30,   7,   8,   7,   4,  28,   0,   1,   3,   0,   0,
    /       AF   FB   OM
             4,   0,  15)


---

出力例 XC 形式 (音色番号は+1されます。ハードウェアLFO関連パラメータは無視されます)

    /* SAMPLE MDX by tantan */

    /* SAMPLE1.MDX */

    char voice_data_34[5][11] = {
    /*  AF   SM   WF   SY   SP   PMD  AMD  PMS  AMS  PAN  RSV */
      {  18,  15,   0,   0,   0,   0,   0,   0,   0,   3,   0 },
    /*  AR   D1R  D2R  RR   D1L  TL   KS   MUL  DT1  DT2  AME */
      {  31,  31,   0,  10,   0,  27,   0,   0,   0,   0,   0 },
      {  31,  12,  12,  11,   8,  43,   0,   8,   0,   0,   0 },
      {  31,  14,  10,   8,   3,  21,   0,   0,   0,   0,   0 },
      {  31,  11,   9,  12,   1,  18,   0,   1,   0,   0,   0 }
    };
    /* m_vset(34,voice_data_34); */

    char voice_data_41[5][11] = {
    /*  AF   SM   WF   SY   SP   PMD  AMD  PMS  AMS  PAN  RSV */
      {   4,  15,   0,   0,   0,   0,   0,   0,   0,   3,   0 },
    /*  AR   D1R  D2R  RR   D1L  TL   KS   MUL  DT1  DT2  AME */
      {  30,  22,  11,   3,   5,  14,   0,   1,   3,   0,   1 },
      {  18,   7,   8,   7,   4,  28,   0,   1,   6,   0,   0 },
      {  30,  22,  11,   4,   5,  50,   0,  14,   7,   0,   0 },
      {  30,   7,   8,   7,   4,  28,   0,   1,   3,   0,   0 }
    };
    /* m_vset(41,voice_data_41); */

---

出力例 X-BASIC 形式 (音色番号は+1されます。ハードウェアLFO関連パラメータは無視されます)

    1000 /* SAMPLE MDX by tantan */
    1010 /* SAMPLE1.MDX */
    1100 dim char voice_data_34(4,10)
    1110 voice_data_34 = {
    1120 /*   AF   SM   WF   SY   SP  PMD  AMD  PMS  AMS  PAN  RSV */
    1130      18,  15,   0,   0,   0,   0,   0,   0,   0,   3,   0,
    1140 /*   AR  D1R  D2R   RR  D1L   TL   KS  MUL  DT1  DT2  AME */
    1150      31,  31,   0,  10,   0,  27,   0,   0,   0,   0,   0,
    1160      31,  12,  12,  11,   8,  43,   0,   8,   0,   0,   0,
    1170      31,  14,  10,   8,   3,  21,   0,   0,   0,   0,   0,
    1180      31,  11,   9,  12,   1,  18,   0,   1,   0,   0,   0  }
    1190 m_vset(34, voice_data_34)
    1200 dim char voice_data_41(4,10)
    1210 voice_data_41 = {
    1220 /*   AF   SM   WF   SY   SP  PMD  AMD  PMS  AMS  PAN  RSV */
    1230       4,  15,   0,   0,   0,   0,   0,   0,   0,   3,   0,
    1240 /*   AR  D1R  D2R   RR  D1L   TL   KS  MUL  DT1  DT2  AME */
    1250      30,  22,  11,   3,   5,  14,   0,   1,   3,   0,   1,
    1260      18,   7,   8,   7,   4,  28,   0,   1,   6,   0,   0,
    1270      30,  22,  11,   4,   5,  50,   0,  14,   7,   0,   0,
    1280      30,   7,   8,   7,   4,  28,   0,   1,   3,   0,   0  }
    1290 m_vset(41, voice_data_41)


---

### History

* 0.1.1 (2023/01/09) ... XCの出力でコメントアウトしてある m_vset() の引数が間違っていたのを修正
* 0.1.0 (2023/01/09) ... 初版