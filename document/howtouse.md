[TOC]

# Kuro Libraryの使い方

## インクルード

コードの先頭でに以下のように書いて使うことを前提としています．

```cpp
#include <bits/stdc++.h>
using namespace std;
```

例えば，`segtree.hpp` の中身を使いたい場合，以下のように書きます．

```cpp
#include <kuro/segtree>
using namespace kuro;
```

## 提出

`expander.py` を使ってライブラリの内容を展開できます．例えば，`main.cpp` を展開して提出用ファイル `submit.cpp` を作成したいときは，以下のコマンドを実行してください．

```shell
python3 expander.py main.cpp submit.cpp
```

