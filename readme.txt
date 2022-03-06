計算機実践作品　:　OpenGLで地形描画
Author : Ilias-Ange

○内容物

main.c
メインプログラムです。./main で描画できます。
gcc main.c -o main -lglut -lGLU -lGL -lm でコンパイルして下さい。
描画モードは網目がおすすめです。

mode0:wasdで平行移動,rfで回転,zcで鉛直方向移動(l245-l259)
mode1:auto

get_data.c
フォルダ"Single Data"内のファイル 50-20.txt ~ 50-77.txt を読み取り、読み取った全データを whole_data.txt に書き出します。
バラデータ内のファイルが drawing terrain フォルダ直下にないと動きません。

whole_data.txt
get_data.c によって書き出した描画範囲内の全標高データ162万点です。

get_time.c
oku.gpx から位置・時間の情報を読み取ります。
時間のデータのみを gpx_time.txt に書き出します。

gpx_time.txt
GPXデータの内、時間のデータのみを取り出したものです。

hokan.c
トンネルを通った際などはGPS測位が働かないので、跳んでいるデータを人力で線形補間する際に用いました。

gpx.txt
オリジナルのGPXデータです(xml形式)。STRAVAで記録したものをGPXにエクスポートしました。
oku.txt はここから取り出して整形しています。
＊総距離206kmのデータです。今回使用したものはその内15kmほどです。

発表用スライド.pdf
発表スライドです。背景は結構気に入っています。

Picture(Extra)
おまけです。


最終更新日：2021/07/16