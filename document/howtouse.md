[TOC]

# Kuro Libraryの使い方

## 準備

C++17で使うことを想定しています．ライブラリへのパスを指定してコンパイルするか，環境変数にライブラリへのパスを通しておいてください．

コードの先頭で次のように書いて使うことを想定しています．

```cpp
#include <bits/stdc++.h>
using namespace std;
```

## インクルード

例えば，`segtree.hpp` の中身を使いたい場合，次のように書きます．

```cpp
#include <kuro/segtree>
using namespace kuro;
```

## 提出

`expander.py` を使ってライブラリの内容を展開できます．例えば，`main.cpp` を展開して提出用ファイル `submit.cpp` を作成したいときは，以下のコマンドを実行してください．

```shell
python3 expander.py main.cpp submit.cpp
```

