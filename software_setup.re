= 関連するソフトウェアのインストール

== Visual Studio Code のインストール

@<ami>{windows 編}
　
 * @<href>{https://code.visualstudio.com/download, Visual Studio Code（エディタ）}のインストール ［↓Windwos 7, 8, 10 というアイコンをクリックしてインストーラーをDL，インストール］（※ Visual Studio とは異なるので注意）
 * 拡張機能のインストール（参考ページ）
 * Windows 側で Visual Studio Code（以下 vs code）を立ち上げる
 * 拡張機能の欄で［Remote Development］，[Remote - WSL]と検索してそれぞれインストールする＞
 * vs code を終了させる
 * ubuntu を起動させ，［code］と入力してvs code を起動する（最初は少し時間がかかる．これで，WSL にインストールした ubuntu から，windows 側の vs code を起動できるようになった）

@<ami>{ubuntu 編}



以上で，Linux 関係のインストールは終わりです．今後は，windows / ubuntu 共通で話を進めていきます．

== ssh

ssh のインストールと設定（公開鍵暗号という謎ワードに反応してしまう人は@<href>{こちら, https://knowledge.sakura.ad.jp/3543/}．

 * cd ~
 * ssh-keygen と入力してEnterすると色々聞いてくるが，Enterで流す．
 * ls -al ~/.ssh で id_rsa と id_rsa.pub ができてるか確認（id_rsaは決して人に見せない）

== git/github

「gitとはなんだ？」と思ってしまった迂闊な人は@<href>{こちら, https://o2project.github.io/steins-git/#chapter0-introduction}．

git のインストール

 * @<code>{sudo apt update && sudo apt upgrade -y && sudo apt autoremove}
 * @<code>{sudo apt install git}

ssh のインストールと設定（公開鍵暗号という謎ワードに反応してしまう人はこちら）

 * cd ~
 * ssh-keygen と入力してEnterすると色々聞いてくるが，Enterで流す．
 * ls -al ~/.ssh で id_rsa と id_rsa.pub ができてるか確認（id_rsaは決して人に見せない）
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
