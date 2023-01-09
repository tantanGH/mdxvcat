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

### History

0.1.0 (2023/01/09) ... 初版