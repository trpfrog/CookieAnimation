# How to Use APIs

APIの使い方はここを見てください。



## img.h

画像の出力とバッファの管理を行うAPI。



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
- **double** opacity
  - cの不透明度。0〜1の範囲で指定します。

ベースとなる色baseに色cを不透明度opacityで乗せたときの色を返します。

返される色のベクトル v は次の式で与えられます。

v = opacity * c + (1-opacity) * base


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
- **double** opacity
  - cの不透明度。0〜1の範囲で指定します。

指定した座標を指定した色で塗り潰します。



### void merge_layer

作成者：つまみ

- **int** layer [HEIGHT] [WIDTH] [3]
  - バッファと同じ形式で色が保存された配列
- **double** opacity
  - マージするときのlayerの不透明度

バッファにlayerをマージします。このとき不透明度を指定してマージすることができます。



## object.h

アニメーションのパーツをバッファに描画するAPI。



### void draw_background (未完成)

背景をバッファに上書きします。



### void bake_cookie (未完成)

中央のクッキーをバッファに上書きします。



### void background_cookie (未完成)

背景を流れるクッキーをバッファに上書きします。



### void img_fillcircle

- struct color c
  - 塗りつぶす色
- int x,y
  - 中央の座標
- int r
  - 円の半径

円を描画しバッファに上書きします。



### void fill_polygon

作成者：つまみ

- **int** x[], y[]
  - 塗りつぶす多角形の頂点集合。配列の座標の順に外枠が結ばれる。
- **int** dots
  - 頂点数
- **struct color** c
  - 塗りつぶす色
- **double** opacity
  - 不透明度

指定した頂点集合を結んだ多角形を塗り潰します。垂直な線を引くと塗り潰しがバグるので、垂直に線を引きたいときは1px横にずらすなどして下さい。
