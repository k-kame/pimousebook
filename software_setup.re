= 開発用ソフトのセッティング

本章では，開発に使うソフトウェアのセッティングをします．
導入するソフトは以下の通りです．

 * ssh：コンピュータにネットワーク超しにログインして，ファイル編集／実行を行うためのツール．
 * git / github：コード管理
 * Visual Studio Code：エディタ

ただし，開発マシンの種類（ Windows + Ubuntu / Ubuntu / Raspberry Pi OS ) で異なる場合があります．
異なる場合は「〇〇編」のように分けて記載しています．

== ssh

コンピュータにネットワーク超しにログインするためのツールです（@<href>{https://ja.wikipedia.org/wiki/Secure_Shell, 参考：wikipedia}）．

@<ami>{インストール【Ubuntu 編】}

 * まず，次のコマンドでssh クライアントがインストールされているかを調べます．OpenSSH_... と表示されればOK です（終了）．
 ** ssh -V
 * インストールされていなかった場合，ssh をセッティングします．
 ** インストール：sudo apt install -y ssh
 * 設定ファイルの編集：
 ** sudo vi /etc/ssh/sshd_config
 ** 行頭にPermitRootLogin とある行を探し，頭に# が付いていれば取って，PermitRootLogin no としておく．
 * 設定の反映：
 ** sudo /etc/init.d/ssh restart
 
@<ami>{インストール【ラズパイOS 編】}

 * ssh の設定：
 ** 最初からインストールされていますが，外からの接続が許可されていないので，[メインメニュー] > [Raspberry Pi の設定] の [システムタブ] で自動ログインを無効に，[インターフェースタブ] で ssh を有効にしておく．

@<ami>{設定／動作確認【共通】}

 * 設定：
 ** cd ~
 ** ssh-keygen と入力してEnterすると色々聞いてくるが，Enterで流す．
 ** ls -al ~/.ssh で id_rsa と id_rsa.pub というファイルができてるか確認（id_rsaは決して人に見せない）
 * マウスへの接続：
 ** ssh user@ip（user：接続先のユーザー名（準備するマウスではubuntu）／ ip：マウスのip アドレス）

== git/github

git とは，テキストファイル（文章やプログラム）の変更履歴を管理するためのソフトウェア，github はファイルを登録して，コピーしたりされたり共同編集したりするための web サイトです（嘘 50%．正しくは@<href>{https://ja.wikipedia.org/wiki/Git, こちら}．怪しくは@<href>{https://o2project.github.io/steins-git/#chapter0-introduction, こちら}．

@<ami>{インストール【共通】}

以下の手順で git をインストールします．

 * @<code>{sudo apt update && sudo apt upgrade -y && sudo apt autoremove}
 * @<code>{sudo apt install git}

@<ami>{設定【共通】}

github を介してファイルのやり取りをするためのセッティングをします．

 * github にアカウントを作成：
 ** github HP に移動
 ** 右上の sing up を選んで必要事項を記入．アカウント種別は無料（free）で OK．
 * github に公開鍵を登録：
 ** github にログインして右上のメニューから［Settings］を選択（@<img>{fig_gitset}）
 ** 左柱のメニューから［SSH & GPG keys］を選択
 ** ［SSH key］欄の［New SSH key］を選ぶ
 ** Title欄はなんでもよい（my wsl とか）
 ** key には以下の手順で id_rsa.pub の中身をコピー：
 *** cat ~/.ssh/id_rsa.pub
 *** ↑で画面に文字列が表示されるので，以下のssh-rsa から k-kame@control-kame （これは人によって違う）をマウスで選択して ctrl-c（@<img>{fig_sshset}）
 *** key 欄にペーストして［Add SSH key］

//image[fig_gitset][github のセッティング画面]{
githubの環境設定
//}

//image[fig_sshset][公開鍵の設定]{
sshhubの環境設定
//}

== Visual Studio Code

@<ami>{インストール【Windows 編】}

 * @<href>{https://code.visualstudio.com/download, 公式サイト}の［Windwos 7, 8, 10］をクリックしてインストーラーをダウンロードして実行］（注：Visual Studio Code とVisual Studio は違うものなので注意）．

@<ami>{インストール【ubuntu 編】}

 * 右柱の［Ubuntu ソフトウェア］から探してインストール．

@<ami>{インストール【ラズパイOS 編】}

 * ［メインメニュー▶ Recommended Software］から探してインストール．

@<ami>{設定【共通】}

VScode は，拡張機能を追加することで，色々なことができるようになります．本冊子では，開発機のVScode から，ロボットやWSL 領域（Windows + WSL の場合）のファイルを直接編集する拡張機能を追加します．

 * Windows 側で Visual Studio Code（以下 vs code）を立ち上げる．
 * 拡張機能の欄で［Remote Development］，[Remote - WSL]と検索してそれぞれインストールする＞

== （おまけ）screen

 screen というアプリをインストールしておくと，一枚のターミナル画面で複数作業を実行できて便利なのでお薦め．
 
 * インストール：
 ** @<code>{sudo apt install screen}
 * 使い方：
 ** 適当にググってください（例えば@<href>{https://bacchi.me/linux/how-2-use-screen/, このページ}）．この辺のアプリになると Ubuntu でも CentOS でも OS X でも同じです．

以上で，Linux 関係のインストールは終わりです．今後は，Windows / Ubuntu 共通で話を進めていきます．
