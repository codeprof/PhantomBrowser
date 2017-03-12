#!/bin/bash

#firefox_path=/home/benutzer/Downloads/mozilla-release
read -p "Enter path to mozilla-release (e.g. /home/benutzer/Downloads/mozilla-release): " firefox_path

cd $firefox_path

cp $firefox_path/nsprpub/pr/src/misc/prnetdb.c $firefox_path/nsprpub/pr/src/misc/prnetdb_org.c
cp $firefox_path/caps/nsScriptSecurityManager.cpp $firefox_path/caps/nsScriptSecurityManager_org.cpp
cp $firefox_path/browser/base/content/browser.xul $hosts_download_02_09_15firefox_path/browser/base/content/browser_org.xul
cp $firefox_path/browser/base/content/browser.js $firefox_path/browser/base/content/browser_org.js
cp $firefox_path/netwerk/protocol/http/nsHttpAuthCache.cpp $firefox_path/netwerk/protocol/http/nsHttpAuthCache_org.cpp
cp $firefox_path/netwerk/protocol/http/nsHttpHandler.cpp $firefox_path/netwerk/protocol/http/nsHttpHandler_org.cpp
cp $firefox_path/netwerk/base/src/nsSocketTransport2.cpp $firefox_path/netwerk/base/src/nsSocketTransport2_org.cpp
cp $firefox_path/dom/html/HTMLCanvasElement.cpp $firefox_path/dom/html/HTMLCanvasElement_org.cpp
cp $firefox_path/dom/html/HTMLInputElement.cpp $firefox_path/dom/html/HTMLInputElement_org.cpp
#cp $firefox_path/dom/workers/Navigator.h $firefox_path/dom/workers/Navigator_org.h
cp $firefox_path/dom/base/nsGlobalWindow.cpp $firefox_path/dom/base/nsGlobalWindow_org.cpp
cp $firefox_path/dom/base/nsScreen.h $firefox_path/dom/base/nsScreen_org.h
cp $firefox_path/dom/base/Navigator.cpp $firefox_path/dom/base/Navigator_org.cpp
cp $firefox_path/toolkit/components/url-classifier/nsUrlClassifierDBService.cpp $firefox_path/toolkit/components/url-classifier/nsUrlClassifierDBService_org.cpp
#cp $firefox_path/mobile/android/base/AndroidManifest.xml.in $firefox_path/mobile/android/base/AndroidManifest_org.xml.in
cp $firefox_path/mobile/android/base/FennecManifest_permissions.xml.in $firefox_path/mobile/android/base/FennecManifest_permissions_org.xml.in


echo Now modify files in $firefox_path
sed -n q </dev/tty

diff -rupN $firefox_path/nsprpub/pr/src/misc/prnetdb_org.c $firefox_path/nsprpub/pr/src/misc/prnetdb.c > patch_prnetdb.c
diff -rupN $firefox_path/caps/nsScriptSecurityManager_org.cpp $firefox_path/caps/nsScriptSecurityManager.cpp > patch_nsScriptSecurityManager_new.cpp
diff -rupN $firefox_path/browser/base/content/browser_org.xul $firefox_path/browser/base/content/browser.xul > patch_browser.xul
diff -rupN $firefox_path/browser/base/content/browser_org.js $firefox_path/browser/base/content/browser.js > patch_browser.js
diff -rupN $firefox_path/netwerk/protocol/http/nsHttpAuthCache_org.cpp $firefox_path/netwerk/protocol/http/nsHttpAuthCache.cpp > patch_nsHttpAuthCache.cpp
diff -rupN $firefox_path/netwerk/protocol/http/nsHttpHandler_org.cpp $firefox_path/netwerk/protocol/http/nsHttpHandler.cpp > patch_nsHttpHandler.cpp
diff -rupN $firefox_path/netwerk/base/src/nsSocketTransport2_org.cpp $firefox_path/netwerk/base/src/nsSocketTransport2.cpp > patch_nsSocketTransport2.cpp
diff -rupN $firefox_path/dom/html/HTMLCanvasElement_org.cpp $firefox_path/dom/html/HTMLCanvasElement.cpp > patch_HTMLCanvasElement.cpp
diff -rupN $firefox_path/dom/html/HTMLInputElement_org.cpp $firefox_path/dom/html/HTMLInputElement.cpp > patch_HTMLInputElement.cpp
#diff -rupN $firefox_path/dom/workers/Navigator_org.h $firefox_path/dom/workers/Navigator.h > patch_Navigator.h
diff -rupN $firefox_path/dom/base/nsGlobalWindow_org.cpp $firefox_path/dom/base/nsGlobalWindow.cpp > patch_nsGlobalWindow.cpp
diff -rupN $firefox_path/dom/base/nsScreen_org.h $firefox_path/dom/base/nsScreen.h > patch_nsScreen.h
diff -rupN $firefox_path/dom/base/Navigator_org.cpp $firefox_path/dom/base/Navigator.cpp > patch_Navigator.cpp
diff -rupN $firefox_path/toolkit/components/url-classifier/nsUrlClassifierDBService_org.cpp $firefox_path/toolkit/components/url-classifier/nsUrlClassifierDBService.cpp > patch_nsUrlClassifierDBService.cpp
#diff -rupN $firefox_path/mobile/android/base/AndroidManifest_org.xml.in $firefox_path/mobile/android/base/AndroidManifest.xml.in > patch_AndroidManifest.xml.in
diff -rupN $firefox_path/mobile/android/base/FennecManifest_permissions_org.xml.in $firefox_path/mobile/android/base/FennecManifest_permissions.xml.in > patch_FennecManifest_permissions.xml.in

