# Kuro Library

## 概要

- 僕が普段使っているC++プログラミングコンテスト用ライブラリです．
- プログラミングコンテストチャレンジブック，[AtCoder Live Library](https://github.com/atcoder/live_library)，[AtCoder Library](https://github.com/atcoder/ac-library) から取ってきたものがほとんどです．

## 注意

- 制約外の入力を入れたときの挙動はすべて未定義です．

- バグに関する責任は持ちません．使用する際は必ず自分で検証をしてください．

## 使い方

[こちら](document/howtouse.md)

## リスト


### 便利道具

| ドキュメント                     | コード                            | 概要                     |
| :------------------------------- | --------------------------------- | ------------------------ |
| [Tool](document/tool.md)         | [tool.hpp](kuro/tool.hpp)         | 便利関数詰め合わせ       |
| [Marathon](document/marathon.md) | [marathon.hpp](kuro/marathon.hpp) | マラソン用関数詰め合わせ |


### データ構造

| ドキュメント                                 | コード                                  | 概要                                    |
| :------------------------------------------- | --------------------------------------- | --------------------------------------- |
| [Fenwick Tree](document/fenwicktree.md)      | [fenwicktree.hpp](kuro/fenwicktree.hpp) | BIT: Binary Indexed Tree (フェニック木) |
| [Segment Tree](document/segtree.md)          | [segtree.hpp](kuro/segtree.hpp)         | セグメント木                            |
| [Lazy Segment Tree](document/lazysegtree.md) | [lazysegtree.hpp](kuro/lazysegtree.hpp) | 遅延伝播セグメント木                    |
| [Range Sum Query](document/rsq.md)           | [rsq.hpp](kuro/rsq.hpp)                 | RSQ: Range Sum Query (区間和クエリ)     |

### 数学

| ドキュメント                                          | コード                            | 概要                       |
| :---------------------------------------------------- | --------------------------------- | -------------------------- |
| [Mod int](document/modint.md)                         | [modint.hpp](kuro/modint.hpp)     | 自動mod                    |
| [Math](document/math.md)                              | [math.hpp](kuro/math.hpp)         | 数論アルゴリズム詰め合わせ |
| [Sieve of Eratosthenes](document/sieve.md)            | [sieve.hpp](kuro/sieve.hpp)       | エラトステネスの篩         |
| [Segment Sieve of Eratosthenes](document/segsieve.md) | [segsieve.hpp](kuro/segsieve.hpp) | 区間エラトステネスの篩     |
| [Matrix](document/matrix.md)                          | [matrix.hpp](kuro/matrix.hpp)     | 行列                       |
| [Gaussian Elimination](document/gaussian.md)          | [gaussian.hpp](kuro/gaussian.hpp) | ガウスの消去法             |
| [Kitamasa Method](document/kitamasa.md)               | [kitamasa.hpp](kuro/kitamasa.hpp) | Kitamasa法                 |
| [Geometry](document/geometry.md)                      | [geometry.hpp](geometry.hpp)      | 幾何学図形詰め合わせ       |

### グラフ

| ドキュメント                                        | コード                                      | 概要                      |
| :-------------------------------------------------- | ------------------------------------------- | ------------------------- |
| [Union-Find Tree](document/unionfind.md)            | [unionfind.hpp](kuro/unionfind.hpp)         | Union-Find木              |
| [Max Flow](document/maxflow.md)                     | [mfaxflow.hpp](kuro/maxflow.hpp)            | 最大流問題                |
| [Bipartite Matching](document/bimatching.md)        | [bimatching.hpp](kuro/bimatching.hpp)       | 二部マッチング            |
| [Min Cost Flow (2点間)](document/mincostflow2p.md)  | [mincostflow2p.hpp](kuro/mincostflow2p.hpp) | 最小費用流問題 (2点間)    |
| [Min Cost Flow (b-フロー)](document/mincostflow.md) | [mincostflow.hpp](kuro/mincostflow.hpp)     | 最小費用流問題 (b-フロー) |
| [Strongly Conected Components](document/scc.md)     | [scc.hpp](kuro/scc.hpp)                     | 強連結成分分解            |
| [2-SAT](document/twosat.md)                         | [twosat.hpp](kuro/twosat.hpp)               | 2-SAT                     |

### 木

| ドキュメント                                   | コード                            | 概要         |
| :--------------------------------------------- | --------------------------------- | ------------ |
| [Lowest Common Ancestor](document/lca.md)      | [lca.hpp](kuro/lca.hpp)           | 最小共通祖先 |
| [Centroid Decomposition](document/centroid.md) | [centroid.hpp](kuro/centroid.hpp) | 重心分解     |

