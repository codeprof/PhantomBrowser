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
echo ==============================================================
echo =========================            =========================
echo                          MOBILE BUILD
echo =========================            =========================
echo ==============================================================

cp $firefox_path/mozconfig-mobile $firefox_path/mozconfig -f
./mach build
./mach package
#./mach install


#echo Change settings in about:config
#echo Set own.autosetDefaults:True

exit 0
