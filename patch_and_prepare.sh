#!/bin/bash

options="--fuzz=3 -l"

#firefox_path="/home/benutzer/Downloads/mozilla-release"
read -p "Enter path to mozilla-release (e.g. /home/benutzer/Downloads/mozilla-release): " firefox_path

echo "Make sure badhosts.h is up to date!"
echo "Adapt paths in mozconfig-mobile!"

cd "generate blacklist"
./hosts_download_02_09_15
cp safesearch_ignore.h ../safesearch_ignore.h
cp badhosts.h ../badhosts.h
cd ..
cd $firefox_path

#now we compile both (Desktop is default)
cp mozconfig-desktop $firefox_path/mozconfig
cp mozconfig-desktop $firefox_path/mozconfig-desktop
cp mozconfig-mobile $firefox_path/mozconfig-mobile

cp badhosts.h $firefox_path/nsprpub/pr/src/misc/badhosts.h
cp safesearch_ignore.h $firefox_path/toolkit/components/url-classifier/safesearch_ignore.h

cp patch\ images\ and\ names/* $firefox_path -rf

echo "Create copies (useful if source is modified later)"
cp $firefox_path/nsprpub/pr/src/misc/prnetdb.c $firefox_path/nsprpub/pr/src/misc/prnetdb_org.c
cp $firefox_path/caps/nsScriptSecurityManager.cpp $firefox_path/caps/nsScriptSecurityManager_org.cpp
#Problem since ff 42 (or a bit earlier)
#cp $firefox_path/browser/base/content/browser.xul $firefox_path/browser/base/content/browser_org.xul
#cp $firefox_path/browser/base/content/browser.js $firefox_path/browser/base/content/browser_org.js
cp $firefox_path/netwerk/protocol/http/nsHttpAuthCache.cpp $firefox_path/netwerk/protocol/http/nsHttpAuthCache_org.cpp
cp $firefox_path/netwerk/protocol/http/nsHttpHandler.cpp $firefox_path/netwerk/protocol/http/nsHttpHandler_org.cpp
cp $firefox_path/netwerk/base/nsSocketTransport2.cpp $firefox_path/netwerk/base/nsSocketTransport2_org.cpp
cp $firefox_path/dom/html/HTMLCanvasElement.cpp $firefox_path/dom/html/HTMLCanvasElement_org.cpp
cp $firefox_path/dom/html/HTMLInputElement.cpp $firefox_path/dom/html/HTMLInputElement_org.cpp
#cp $firefox_path/dom/workers/Navigator.h $firefox_path/dom/workers/Navigator_org.h
cp $firefox_path/dom/base/nsGlobalWindow.cpp $firefox_path/dom/base/nsGlobalWindow_org.cpp
cp $firefox_path/dom/base/nsScreen.h $firefox_path/dom/base/nsScreen_org.h
cp $firefox_path/dom/base/Navigator.cpp $firefox_path/dom/base/Navigator_org.cpp
#disabled for now because of strange problems. Problem since ff 42 (or a bit earlier)
#cp $firefox_path/toolkit/components/url-classifier/nsUrlClassifierDBService.cpp $firefox_path/toolkit/components/url-classifier/nsUrlClassifierDBService_org.cpp
cp $firefox_path/mobile/android/base/AndroidManifest.xml.in $firefox_path/mobile/android/base/AndroidManifest_org.xml.in

echo Patching files
patch $firefox_path/nsprpub/pr/src/misc/prnetdb.c < patch_prnetdb.c $options
patch $firefox_path/caps/nsScriptSecurityManager.cpp < patch_nsScriptSecurityManager.cpp $options
#Problem since ff 42 (or a bit earlier)
#patch $firefox_path/browser/base/content/browser.xul < patch_browser.xul $options
#patch $firefox_path/browser/base/content/browser.js < patch_browser.js $options
patch $firefox_path/netwerk/protocol/http/nsHttpAuthCache.cpp < patch_nsHttpAuthCache.cpp $options
patch $firefox_path/netwerk/protocol/http/nsHttpHandler.cpp < patch_nsHttpHandler.cpp $options
patch $firefox_path/netwerk/base/nsSocketTransport2.cpp < patch_nsSocketTransport2.cpp $options
patch $firefox_path/dom/html/HTMLCanvasElement.cpp < patch_HTMLCanvasElement.cpp $options
patch $firefox_path/dom/html/HTMLInputElement.cpp < patch_HTMLInputElement.cpp $options
#patch $firefox_path/dom/workers/Navigator.h < patch_Navigator.h $options
patch $firefox_path/dom/base/nsGlobalWindow.cpp < patch_nsGlobalWindow.cpp $options
patch $firefox_path/dom/base/nsScreen.h < patch_nsScreen.h $options
patch $firefox_path/dom/base/Navigator.cpp < patch_Navigator.cpp $options
#disabled for now because of strange problems. Problem since ff 42 (or a bit earlier)
#patch $firefox_path/toolkit/components/url-classifier/nsUrlClassifierDBService.cpp < patch_nsUrlClassifierDBService.cpp $options 
patch $firefox_path/mobile/android/base/AndroidManifest.xml.in < patch_AndroidManifest.xml.in $options

echo Adapt default configs
echo "pref(\"own.autosetDefaults\", true);" >> $firefox_path/browser/app/profile/firefox.js
echo "pref(\"own.autosetDefaults\", true);" >> $firefox_path/mobile/android/app/mobile.js

cd $firefox_path

read -p "Do you wish to install dependecies(Y) or no (N)" yn
case $yn in
        [Yy]* ) ./mach bootstrap;;
        [Nn]* ) echo do not install dependecies;;
        * ) exit;;
esac
read -p "Do you wish to install dependecies(Y) or no (N)" yn
case $yn in
        [Yy]* ) ./mach bootstrap;;
        [Nn]* ) echo do not install dependecies;;
        * ) exit;;
esac
