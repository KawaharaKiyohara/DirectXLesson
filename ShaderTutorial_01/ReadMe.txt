GPUへのデータ転送。

シェーダー定数にカラーデータを転送してみる。
実習、サンプルでは一つの乗算カラーしか使っていないが、３頂点分の乗算カラーを送ってみよう。
      頂点シェーダーで行っている、カラーの変更をピクセルシェーダーに書き換えてみる。