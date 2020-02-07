# How to Use APIs

APIの使い方はここを見てください。



## img.h

画像の出力とバッファの管理を行うAPI。

### struct color

構造体struct colorはRGBAの値を保存します。定義は次のとおりです。

```c
struct color { unsigned char r, g, b; double a; };
```

double aは不透明度(alpha)を表し、その値は0〜1で決定されます。



### void img_clear

イメージバッファを消去して白(#ffffff)で塗り潰します。



### void img_write

バッファの中身をppmファイルとして保存します。ファイル名はimg0000.ppmで保存され、関数が呼び出される度カウンタが増加します。



### struct color mix_color

作成者：つまみ

- **struct color** c
  - 混ぜる色のcolorオブジェクト。
- **struct color** base
  - 混ぜられる色のcolorオブジェクト。

ベースとなる色baseに色cを重ねたときの色を返します。




### struct color get_pixel

作成者：つまみ

- **int** x, y
  - 取得する色の存在するバッファの座標

バッファの指定した座標の色を返します。



### void put_pixel

作成者：つまみ

- **struct color** c
  - 塗りつぶす色
- **int** x, y
  - 塗りつぶす座標

指定した座標を指定した色で塗り潰します。



### void merge_layer

作成者：つまみ

- **struct color** layer [HEIGHT] [WIDTH]
  - バッファと同じ形式で色が保存された配列

バッファにlayerをマージします。



### bool color_equal

作成者：つまみ

- **struct color** c1, c2
  - 比較したい色

指定した色のRGBAが全て一致しているかどうかを確認します。



## layer.h

レイヤ関連の処理を行うAPI



### レイヤの定義

レイヤは次のように定義してください。また、使用前は必ず初期化を行ってください。

```c
struct color layer[HEIGHT][WIDTH];
clear_layer(layer);
```



### bool is_valid_alpha

作成者：つまみ

- **struct color** c
  - 調べたい色

色cのアルファ値c.aが0から1の範囲に入っているかどうか調べ、入っていればtrue、そうでなければfalseを返します。



### void copy_layer

作成者：つまみ

- **int** new_layer [HEIGHT] [WIDTH] [3]
  - コピー先のレイヤ
- **struct color** layer [HEIGHT] [WIDTH]
  - コピー元のレイヤ

レイヤをそのままコピーします。



### void paint_layerpixel (削除済み)

作成者：つまみ

- **int** pixel [3]
  - 色を塗るピクセル
- **int** color [3]
  - 塗る色

指定したピクセルに指定した3要素配列の色を代入します。ピクセルからピクセルへの色のコピーとして使うことができます。



### void clear_layer

作成者：つまみ

- **struct color** layer [HEIGHT] [WIDTH]
  - 描画する対象のレイヤ

レイヤの全ピクセルを {-1,-1,-1} (透明色)で初期化します。



### void unite_layer

作成者：つまみ

- **struct color** lower_layer [HEIGHT] [WIDTH]
  - 下敷きになるレイヤ
- **struct color** upper_layer [HEIGHT] [WIDTH]
  - 上にのせるレイヤ
- **struct color** new_layer [HEIGHT] [WIDTH]
  - 被せた結果を出力するレイヤ

2つのレイヤを1つにします。lower_layerの上にupper_layerを被せた結果をnew_layerに代入します。



### void subtract_layer

作成者：つまみ

- **struct color** lower_layer [HEIGHT] [WIDTH]
  - 減算されるレイヤ
- **struct color** upper_layer [HEIGHT] [WIDTH]
  - 減算するレイヤ
- **struct color** new_layer [HEIGHT] [WIDTH]
  - 減算されたレイヤの出力先レイヤ

lower_layerとupper_layerのかぶった部分をlower_layerから引き、new_layerに出力します。



### void linear_transform

作成者：つまみ

- **struct color** layer [HEIGHT] [WIDTH]
  - 変換されるレイヤ
- **double** matrix [2] [2]
  - 変換に使う2*2行列
- **int** origin_x, origin_y
  - 変換するにあたって原点として扱う点の座標
- **struct color** new_layer [HEIGHT] [WIDTH]
  - 変換先レイヤ

レイヤを指定された行列で変換します。



### void fill_painted_pixel

作成者：つまみ

- **struct color** layer [HEIGHT] [WIDTH]
  - 塗りつぶすレイヤ
- **struct color** c
  - 塗りつぶす色

指定したレイヤの色が塗られている部分全てを指定した色で塗り潰します。




## object.h

アニメーションのパーツをバッファに描画するAPI。



### void draw_background (未完成)

- **struct color** layer [HEIGHT] [WIDTH]
  - 描画する対象のレイヤ

背景を渡されたレイヤに保存します。



### void draw_cookieband

作成者：つまみ

- **struct color** layer [HEIGHT] [WIDTH]
  - 描画する対象のレイヤ

クッキーのカウンタを表示するための帯をレイヤに出力します。



### void bake_cookie (未完成)

- **struct color** layer [HEIGHT] [WIDTH]
  - 描画する対象のレイヤ

中央のクッキーを渡されたレイヤに上書きします。



### void background_cookie (未完成)

背景を流れるクッキーをバッファに上書きします。



### void img_fillcircle

- **struct color** c
  - 塗りつぶす色
- **int** x,y
  - 中央の座標
- **int** r
  - 円の半径
- **struct color** layer [HEIGHT] [WIDTH]
  - 描画する対象のレイヤ

円を描画し指定されたレイヤに上書きします。



### void fill_polygon

作成者：つまみ

- **int** x[], y[]
  - 塗りつぶす多角形の頂点集合。配列の座標の順に外枠が結ばれる。
- **int** dots
  - 頂点数
- **struct color** c
  - 塗りつぶす色
- **struct color** layer [HEIGHT] [WIDTH]
  - 描画する対象のレイヤ

指定した頂点集合を結んだ多角形を塗り潰し、指定されたレイヤに描画します。垂直な線を引くと塗り潰しがバグるので、垂直に線を引きたいときは1px横にずらすなどして下さい。

また塗り潰しアルゴリズムの特性上、これを通したレイヤはもともと描画されていたものが全て消えてしまうため、新しく作成したレイヤに実行するようにしてください。



