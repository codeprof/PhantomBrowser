#!/bin/bash

#firefox_path=/home/benutzer/Downloads/mozilla-release

#if [ ! -v firefox_path ]
#then
	read -p "Enter path to mozilla-release (e.g. /home/benutzer/Downloads/mozilla-release): " firefox_path
#fi

cd $firefox_path

rm nsprpub/pr/src/misc/prnetdb.o

#BUILD NEW WAY
#=======================================================

echo ===============================================================
echo =========================             =========================
echo                          DESKTOP BUILD
echo =========================             =========================
echo ===============================================================

cp $firefox_path/mozconfig-desktop $firefox_path/mozconfig -f
./mach build
./mach package
#./mach install


exit 0

#BUILD OLD WAY
#=======================================================
echo build old way

mkdir mkff
cd mkff

./../mozilla-release/configure --disable-gstreamer --disable-directshow --disable-wmf --disable-ffmpeg --disable-crashreporter --disable-libjpeg-turbo --disable-webrtc --enable-official-branding --disable-webgl --enable-release --disable-debug --with-app-name=godzilla --with-app-basename=godzilla --disable-tests --enable-optimize

make -j 4

echo Change settings in about:config
echo Set own.autosetDefaults:True

godzilla &

#=======================================================
#Tested compile options with FF 40.0.2 (working!)

