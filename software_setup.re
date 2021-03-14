= 開発用ソフトのインストール

//lead{
本章では，エディタやソースコード管理ソフトなど，開発に使うソフトウェアのインストールについて説明します．ただし，開発マシンの種類（ Windows + Ubuntu / Ubuntu / Raspberry Pi OS ) で異なる場合があります．異なる場合は「〇〇編」のように分けて記載しています．
//}

== Visual Studio Code

@<ami>{（インストール）Windows 編}

 * @<href>{https://code.visualstudio.com/download, Visual Studio Code（エディタ）}のインストール ［↓Windwos 7, 8, 10 というアイコンをクリックしてインストーラーをDL，インストール］（※ Visual Studio とは異なるので注意）


@<ami>{（インストール）ubuntu 編}

 * ubuntu

@<ami>{（インストール）Raspberry Pi OS 編}

 * Visual Studio Code：[メインメニュー] > [Recommended Software] から探してインストール．

@<ami>{（設定）共通}

 * 拡張機能のインストール（参考ページ）
 * Windows 側で Visual Studio Code（以下 vs code）を立ち上げる
 * 拡張機能の欄で［Remote Development］，[Remote - WSL]と検索してそれぞれインストールする＞
 * vs code を終了させる
 * ubuntu を起動させ，［code］と入力してvs code を起動する（最初は少し時間がかかる．これで，WSL にインストールした ubuntu から，windows 側の vs code を起動できるようになった）

以上で，Linux 関係のインストールは終わりです．今後は，windows / ubuntu 共通で話を進めていきます．

== ssh

コンピュータにネットワーク超しにログインするためのツール．公開鍵暗号という謎ワードに反応してしまう人は@<href>{こちら, https://knowledge.sakura.ad.jp/3543/}．

@<ami>{（インストール）Ubuntu 編}

 * openssh の存在の確認
 * 必要ならインストール

@<ami>{（インストール）Raspberry Pi OS 編}

 * ssh の設定：最初からインストールされていますが，外からの接続が許可されていないので，[メインメニュー] > [Raspberry Pi の設定] の [システムタブ] で自動ログインを無効に，[インターフェースタブ] で ssh を有効にしておく．

@<ami>{（設定）共通}

 * cd ~
 * ssh-keygen と入力してEnterすると色々聞いてくるが，Enterで流す．
 * ls -al ~/.ssh で id_rsa と id_rsa.pub というファイルができてるか確認（id_rsaは決して人に見せない）

== git/github

「gitとはなんだ？」と思ってしまった迂闊な人は@<href>{https://o2project.github.io/steins-git/#chapter0-introduction, こちら}．

@<ami>{（インストール）共通}

 * @<code>{sudo apt update && sudo apt upgrade -y && sudo apt autoremove}
 * @<code>{sudo apt install git}

@<ami>{（設定）共通}

git と github の違いを説明．

 * github にアカウントを作成
 * github HPに移動
 * 右上の sing up を選んで必要事項を記入．アカウント種別は無料（free）でOK（なんも難しいことはないと思うが参考ページ）
 * github に公開鍵を登録
 * github にログインして右上のメニューから［Settings］を選択
 * 左柱のメニューから［SSH & GPG keys］を選択
 * ［SSH key］欄の［New SSH key］を選び
 * Title欄はなんでもよい（my wsl とか）
 * key には以下の手順で id_rsa.pub の中身をコピペ
 * cat ~/.ssh/id_rsa.pub
 * ↑で画面に文字列が表示されるので，以下のssh-rsa から k-kame@control-kame （これは人によって違う）をマウスで選択して ctrl-c
 * key 欄にペーストして［Add SSH key］

//image[fig_gitset][fig_gitset]{
githubの環境設定
//}

//image[fig_sshset][fig_sshset]{
sshhubの環境設定
//}

== screen

 * LXTerminal（黒い画面）で，screen @<fn>{app_screen} というアプリをインストールしておくと，一枚の画面で複数作業を実行できて便利なのでお薦め．
 ** インストール：@<code>{sudo apt install screen}

//footnote[app_screen][使い方は適当にググってください．この辺のアプリになると，Ubuntu でも CentOS でもはたまた mac でも同じです．例えば@<href>{https://bacchi.me/linux/how-2-use-screen/, このページ}]
