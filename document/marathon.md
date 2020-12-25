[TOC]

# Marathon

マラソン用関数詰め合わせです．

## get_time

```cpp
double get_time()
```
現在の時間をミリ秒単位で取得します．必ず `main` 関数の最初に一度呼んでください．

## RandGenerator

```cpp
struct RandGenerator {
  uint32_t gen();
  double gen_double();
  uint32_t gen_mod(uint32_t mod);
  uint32_t gen_range(uint32_t l, uint32_t r);
  bool gen_bool(double x);
  void shuffle(vector<T>& a);
};
```

乱数を生成する構造体です．

- `gen` : `0` 以上 `4294967295` 以下の乱数を返します．
- `gen_double` : `0.0` 以上 `1.0` 以下の乱数を返します．
- `gen_mod` : `0` 以上 `mod-1` 以下の乱数を返します．
- `gen_range` : `l` 以上 `r-1` 以下の乱数を返します．
- `gen_bool` : `x` の確率で `true` を，`1-x` の確率で `false` を返します．(制約 $0.0 \leq x \leq 1.0$)
- `suffle` : 型 `T` の配列をシャッフルします．

**コンストラクタ**

```cpp
RandGenerator(uint32_t seed=3141592653ul)
```

シードを指定できます．シードが適切でない場合，乱数が一様にならないことがあります．

## sep1000

```cpp
string sep1000(T a)
```

型 `T` の辺数 `a` を $3$ 桁区切りの文字列に変換します．スコア表示を見やすくするための関数です．

## コードの雛形

```cpp
#include <bits/stdc++.h>
using namespace std;
#include <kuro/marathon>
using namespace kuro;

struct Input {};

struct Out {};

Input get_input() {}

void show(Out& out) {}

int64_t calc_score(Input& input, Out& out) {}

Out solve(Input& input) {}

int main() {
  double stime = get_time();
  
  Input input = get_input();
  Out out = solve(input);
  show(out);
  
  fprintf(stderr, "Time = %.3f\n", (get_time()-stime)/1000);
  cerr << "Score = " << sep1000(calc_score(input, out)) << '\n';
  return 0;
}
```
