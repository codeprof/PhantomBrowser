--- /home/benutzer/Downloads/ff/mozilla-release/netwerk/protocol/http/nsHttpHandler_org.cpp	2015-09-02 18:26:14.537606840 +0200
+++ /home/benutzer/Downloads/ff/mozilla-release/netwerk/protocol/http/nsHttpHandler.cpp	2015-09-04 01:04:15.502165891 +0200
@@ -67,6 +67,12 @@
 #include "nsCocoaFeatures.h"
 #endif
 
+//EDIT:
+#include <stdlib.h>
+#include <time.h>
+//EDIT:END
+
+
 //-----------------------------------------------------------------------------
 #include "mozilla/net/HttpChannelChild.h"
 
@@ -635,10 +641,17 @@ nsHttpHandler::BuildUserAgent()
     // Application comment
     mUserAgent += '(';
 #ifndef UA_SPARE_PLATFORM
-    if (!mPlatform.IsEmpty()) {
-      mUserAgent += mPlatform;
-      mUserAgent.AppendLiteral("; ");
-    }
+
+//EDIT:
+	if (!Preferences::GetBool("own.changeUserAgent.enable", false))
+	{
+		if (!mPlatform.IsEmpty()) {
+		  mUserAgent += mPlatform;
+		  mUserAgent.AppendLiteral("; ");
+		}
+	}
+//EDIT:END
+
 #endif
     if (!mCompatDevice.IsEmpty()) {
         mUserAgent += mCompatDevice;
@@ -661,7 +674,13 @@ nsHttpHandler::BuildUserAgent()
     mUserAgent += '/';
     mUserAgent += mProductSub;
 
+
+
     bool isFirefox = mAppName.EqualsLiteral("Firefox");
+    
+	//EDIT:
+		isFirefox = true; //Sicherstellen, dass Name Firefox im Useragent angezeigt wird (und nicht gorzilla oder aehnlich)
+    //EDIT:END	    
     if (isFirefox || mCompatFirefoxEnabled) {
         // "Firefox/x.y" (compatibility) app token
         mUserAgent += ' ';
@@ -674,6 +693,7 @@ nsHttpHandler::BuildUserAgent()
         mUserAgent += '/';
         mUserAgent += mAppVersion;
     }
+
 }
 
 #ifdef XP_WIN
@@ -703,6 +723,533 @@ nsHttpHandler::InitUserAgentComponents()
     );
 #endif
 
+//EDIT:
+	if (Preferences::GetBool("own.changeUserAgent.enable", false))
+	{
+#if defined(ANDROID)
+			mPlatform.AssignLiteral("Android");			
+#else
+			mPlatform.AssignLiteral("Windows");
+#endif
+	}
+//EDIT:END
+
+//EDIT:	
+	//Updates generell deaktivieren
+	Preferences::SetBool("app.update.auto", false);
+	Preferences::SetBool("app.update.enabled", false);
+	
+	Preferences::SetBool("own.autosetDefaultsX", true);			
+		
+	static int rndset = 0;
+	if (rndset == 0)
+	{ 
+		srand (time(NULL));
+		Preferences::SetInt("own.rnd", (rand() % 1000) + (rand() % 1000) * 1000 + (rand() % 1000) * 1000000);	
+		rndset = 1;
+	}
+	
+	//Bringt evtl. minimal mehr Sicherheit...
+	static void* useless_data = NULL;
+	#if defined(ANDROID)
+		//memory is rare on mobile devices
+	#else	
+		if (useless_data == NULL)
+		{
+			for (int i = 0; i < 25; i++)
+				useless_data = malloc(1 * 1024 * 1024); //25 MB allokieren
+		}
+	#endif
+	//show visited pages with: about:networking
+
+	if (Preferences::GetBool("own.autosetDefaults", false))
+	{
+		#if defined(ANDROID)
+		//Not so good for android but can be set by user if wished
+		#else					
+		Preferences::SetBool("own.changeUserAgent.enable", true);
+		#endif
+				
+		Preferences::SetBool("own.canvasToUrlMod.enable", true);
+		#if defined(ANDROID)
+		//Not so good for android but can be set by user if wished
+		#else		
+		Preferences::SetBool("own.desktopMod.enabled", true);	
+		#endif
+		Preferences::SetBool("own.windowNameDoNothing.enabled", true);	
+		Preferences::SetBool("own.httpAuthDoNothing.enabled", true); //Kann ansonsten zur realisierung von thirdparty cookies verwendet werden			
+		Preferences::SetBool("own.disallowDirectIPUsage.enabled", true);			
+		Preferences::SetBool("own.useIgnoreListSafeBrowsing.enabled", true);
+					
+		Preferences::SetBool("own.secpwd.enable", true);		
+		Preferences::SetString("own.secpwd.searchStr", u"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_#!+?$%~");		
+		Preferences::SetString("own.secpwd.replaceStr", u"8a~$6uJ+Vdjgx01DozBO2fs4SvXF_#ArH59MTY%ipqnQRWew!lyZGULm7tCEhKP?3NIcbk");		
+
+		if (Preferences::GetBool("own.chnageHomepage", true))
+		{
+			Preferences::SetString("browser.startup.homepage", u"https://ixquick.de");		
+			if (Preferences::GetBool("own.randomStartPage", true))
+			{
+				if (Preferences::GetBool("own.randomStartPageSecure", false))
+				{
+					int rnd = rand() % 4;
+					if (rnd == 0)
+						Preferences::SetString("browser.startup.homepage", u"https://ixquick.de");		
+					if (rnd == 1)
+						Preferences::SetString("browser.startup.homepage", u"https://startpage.com");						
+					if (rnd == 2)
+						Preferences::SetString("browser.startup.homepage", u"https://duckduckgo.com");					
+					if (rnd == 3)
+						Preferences::SetString("browser.startup.homepage", u"https://www.metager.de");										
+					//https://www.metager.de/  has SSL Problems
+				}
+				else
+				{
+					int rnd = rand() % 9;
+					if (rnd == 0)
+						Preferences::SetString("browser.startup.homepage", u"https://www.google.de");		
+					if (rnd == 1)
+						Preferences::SetString("browser.startup.homepage", u"https://www.google.com");
+					if (rnd == 2)
+						Preferences::SetString("browser.startup.homepage", u"https://ixquick.de");		
+					if (rnd == 3)
+						Preferences::SetString("browser.startup.homepage", u"https://startpage.com");					
+					if (rnd == 4)
+						Preferences::SetString("browser.startup.homepage", u"https://www.bing.com");	
+					if (rnd == 5)
+						Preferences::SetString("browser.startup.homepage", u"https://duckduckgo.com");	
+					if (rnd == 6)
+						Preferences::SetString("browser.startup.homepage", u"https://www.qwant.com");	
+					if (rnd == 7)
+						Preferences::SetString("browser.startup.homepage", u"https://www.yandex.com");					
+					if (rnd == 8)
+						Preferences::SetString("browser.startup.homepage", u"https://www.metager.de");										
+					//https://www.metager.de/  has SSL Problems				
+				}
+			}
+		}
+		
+		Preferences::SetString("browser.selfsupport.url", u"https://127.0.0.1:7999");	
+		Preferences::SetBool("device.sensors.enabled", false);		
+		Preferences::SetString("browser.newtab.url", u"about:blank");			
+		Preferences::SetBool("dom.gamepad.enabled", false);		
+		
+		Preferences::SetBool("media.getusermedia.screensharing.enabled", false);		
+		Preferences::SetString("media.getusermedia.screensharing.allowed_domains", u"");
+		//media.eme.enabled
+		//Preferences::SetBool("media.opus.enabled", false);	//Used by anyone?	
+		//Preferences::SetBool("media.wave.enabled", false);	//Used by anyone?			
+		
+		Preferences::SetBool("media.webvtt.enabled", false);
+		Preferences::SetString("readinglist.server", u"https://127.0.0.1:7999");		
+		Preferences::SetBool("social.remote-install.enabled", false);		
+		
+		//Disable Pocket
+		Preferences::SetString("browser.pocket.api", u"https://127.0.0.1:7999");
+		Preferences::SetBool("browser.pocket.enabled", false);	
+		Preferences::SetBool("browser.toolbarbuttons.introduced.pocket-button", false);			
+		Preferences::SetString("browser.pocket.oAuthConsumerKey", u"");		
+		Preferences::SetString("browser.pocket.site", u"https://127.0.0.1:7999");			
+				
+		Preferences::SetBool("dom.ipc.plugins.flash.subprocess.crashreporter.enabled", false);		
+		
+		//WebRTC deaktivieren (Lokale Addressen können ermittelt werden!)
+		//http://www.whatismybrowser.com/what-is-my-local-ip-address
+		if (Preferences::GetBool("own.disallowPeerAndh264", true))
+		{
+			Preferences::SetBool("media.peerconnection.enabled", false);			
+		}
+		
+		//Regelmaesig ueberpruefen, ob flag noch unterstuetzt wird!
+		Preferences::SetBool("beacon.enabled", false);		
+		//Wahrscheinlich, sogar ohne JS moeglich!
+		Preferences::SetBool("browser.send_pings", false);
+		
+		Preferences::SetInt("urlclassifier.keyupdatetime.https://sb-ssl.google.com/safebrowsing/newkey", 0);
+		
+		Preferences::SetBool("services.sync.engine.bookmarks", false);
+		
+		Preferences::SetInt("browser.sessionhistory.max_entries", 2);
+		
+		Preferences::SetBool("services.sync.prefs.sync.browser.safebrowsing.enabled", false);
+		Preferences::SetBool("services.sync.prefs.sync.browser.safebrowsing.malware.enabled",false);
+		Preferences::SetBool("services.sync.prefs.sync.dom.event.contextmenu.enabled",false);		
+		
+		Preferences::SetString("plugin.disable_full_page_plugin_for_types",u"application/pdf");
+		
+		/*
+		 plugin.state.flash = 0 --> never activate
+		 plugin.state.flash = 1 --> ask to activate
+		 plugin.state.flash = 2 --> always activate
+		*/ 
+		Preferences::SetInt("plugin.state.flash", 0); //Flash deaktiveren
+		Preferences::SetInt("plugin.state.libgnome-shell-browser-plugin",0); //Nur für Linux relevant
+		Preferences::SetInt("plugin.state.librhythmbox-itms-detection-plugin", 0); //Nur für Linux relevant
+		Preferences::SetInt("plugin.state.libvlcplugin", 0); //Nur für Linux relevant  (VLC zu riskant)
+		Preferences::SetBool("plugins.click_to_play", true);		
+		
+		//Schlechte Lösung, um Plugins zu verstecken (Enumeration funktioniert nicht mehr, aber Direktabfrage)
+		//Youtube scheint zu funktionieren
+		Preferences::SetString("plugins.enumerable_names", u"Shockwave"); //Normalerweise *
+		
+		//Altes suchfeld (Funktioniert besser)
+		bool modifyBar = true;
+		
+		#if defined(ANDROID)
+			//No change for mobile platform
+			modifyBar = false;	
+		#endif	
+		if (Preferences::GetBool("own.forceModifyBar", false))
+		{
+			modifyBar = true;				
+		}
+		if (Preferences::GetBool("own.forceKeepBar", false))
+		{
+			modifyBar = false;				
+		}		
+		if (modifyBar)
+		{
+			Preferences::SetBool("browser.search.showOneOffButtons", false);
+			Preferences::SetBool("browser.urlbar.autocomplete.enabled", false);	
+			Preferences::SetInt("accessibility.typeaheadfind.flashBar", 0);			
+			//Achtung: Adresszeile daruch nicht mehr zur Suche Verwendbar
+			Preferences::SetBool("keyword.enabled", false);		
+			Preferences::SetBool("browser.fixup.alternate.enabled", false);								
+		}
+		
+		//Java immer deaktivieren
+		Preferences::SetInt("plugin.state.java", 0);
+				
+		Preferences::SetBool("network.allow-experiments", false);
+			
+		//DO-Not-Track sollte nach http://ip-check.info/?lang=en aktiviert werden
+		Preferences::SetBool("privacy.donottrackheader.enabled", true);
+		Preferences::SetInt("privacy.donottrackheader.value", 1);
+		
+		Preferences::SetBool("pref.privacy.disable_button.cookie_exceptions", false);
+		Preferences::SetBool("pref.privacy.disable_button.view_cookies", false);
+		
+		Preferences::SetInt("browser.display.use_document_fonts", 0); //Nach http://ip-check.info/?lang=en empfohlen!
+	
+		Preferences::SetBool("browser.rights.3.shown", true); // disables the request to send performance data from displaying
+				
+		Preferences::SetInt("browser.sessionstore.privacy_level", 2);    //Never store extra session data.
+		Preferences::SetBool("browser.sessionstore.resume_from_crash", false);  //Do not restore the previous session.
+
+		Preferences::SetBool("dom.indexedDB.enabled", false); //Clientseitiges speichern
+		
+		Preferences::SetBool("dom.ipc.plugins.flash.subprocess.crashreporter.enabled", false);
+		Preferences::SetBool("dom.ipc.plugins.reportCrashURL", false);
+
+		//https://community.hide.me/threads/sicherheitseinstellungen-des-webbrowsers-chrome-firefox.155/
+
+		Preferences::SetString("breakpad.reportURL", u"https://127.0.0.1:7999");			
+		
+		Preferences::SetBool("network.predictor.enabled", false);				
+		Preferences::SetBool("network.predictor.enable-hover-on-ssl", false);	
+
+		//Noch zu neu?
+		Preferences::SetBool("javascript.options.asmjs", false);		
+		
+		//Needed for help menu entry
+		//Preferences::SetString("datareporting.healthreport.about.reportUrl", u"https://127.0.0.1:7999");
+		Preferences::SetString("datareporting.healthreport.documentServerURI", u"https://127.0.0.1:7999");	
+		Preferences::SetBool("datareporting.healthreport.service.enabled", false);					
+		Preferences::SetBool("datareporting.healthreport.uploadEnabled", false);	
+		Preferences::SetString("datareporting.healthreport.about.reportUrl", u"https://127.0.0.1:7999");	
+		Preferences::SetBool("datareporting.policy.dataSubmissionEnabled", false);			
+		Preferences::SetBool("datareporting.healthreport.logging.consoleEnabled", false);			
+					
+
+		
+		if (Preferences::GetBool("own.SafeBrowsingBackupDone", false) == false)
+		{
+			Preferences::SetBool("own.backup.browser.safebrowsing.enabled", Preferences::GetBool("browser.safebrowsing.enabled"));	
+			Preferences::SetBool("own.backup.browser.safebrowsing.downloads.enabled", Preferences::GetBool("browser.safebrowsing.downloads.enabled"));
+			Preferences::SetBool("own.backup.browser.safebrowsing.downloads.remote.enabled", Preferences::GetBool("browser.safebrowsing.downloads.remote.enabled"));						
+			Preferences::SetBool("own.backup.browser.safebrowsing.remoteLookups", Preferences::GetBool("browser.safebrowsing.remoteLookups"));	
+			Preferences::SetString("own.backup.browser.safebrowsing.gethashURL", Preferences::GetString("browser.safebrowsing.gethashURL"));	
+			Preferences::SetString("own.backup.browser.safebrowsing.keyURL", Preferences::GetString("browser.safebrowsing.keyURL"));						
+			Preferences::SetBool("own.backup.browser.safebrowsing.malware.enabled", Preferences::GetBool("browser.safebrowsing.malware.enabled"));		
+			Preferences::SetString("own.backup.browser.safebrowsing.malware.reportURL", Preferences::GetString("browser.safebrowsing.malware.reportURL"));					
+			Preferences::SetString("own.backup.browser.safebrowsing.reportErrorURL", Preferences::GetString("browser.safebrowsing.reportErrorURL"));	
+			Preferences::SetString("own.backup.browser.safebrowsing.reportGenericURL", Preferences::GetString("browser.safebrowsing.reportGenericURL"));	
+			Preferences::SetString("own.backup.browser.safebrowsing.reportMalwareErrorURL", Preferences::GetString("browser.safebrowsing.reportMalwareErrorURL"));	
+			Preferences::SetString("own.backup.browser.safebrowsing.reportMalwareURL", Preferences::GetString("browser.safebrowsing.reportMalwareURL"));	
+			Preferences::SetString("own.backup.browser.safebrowsing.reportPhishURL", Preferences::GetString("browser.safebrowsing.reportPhishURL"));	
+			Preferences::SetString("own.backup.browser.safebrowsing.reportURL", Preferences::GetString("browser.safebrowsing.reportURL"));	
+			Preferences::SetString("own.backup.browser.safebrowsing.updateURL", Preferences::GetString("browser.safebrowsing.updateURL"));	
+			Preferences::SetString("own.backup.browser.safebrowsing.warning.infoURL", Preferences::GetString("browser.safebrowsing.warning.infoURL"));	
+			Preferences::SetString("own.backup.browser.safebrowsing.appRepURL", Preferences::GetString("browser.safebrowsing.appRepURL"));		
+			Preferences::SetBool("own.SafeBrowsingBackupDone", true);
+		}
+		
+		if (Preferences::GetBool("own.RestoreSafeBrowsing", false))
+		{	
+			Preferences::SetBool("browser.safebrowsing.enabled", Preferences::GetBool("own.backup.browser.safebrowsing.enabled"));	
+			Preferences::SetBool("browser.safebrowsing.downloads.enabled", Preferences::GetBool("own.backup.browser.safebrowsing.downloads.enabled"));
+			Preferences::SetBool("browser.safebrowsing.downloads.remote.enabled", Preferences::GetBool("own.backup.browser.safebrowsing.downloads.remote.enabled"));						
+			Preferences::SetBool("browser.safebrowsing.remoteLookups", Preferences::GetBool("own.backup.browser.safebrowsing.remoteLookups"));	
+			Preferences::SetString("browser.safebrowsing.gethashURL", Preferences::GetString("own.backup.browser.safebrowsing.gethashURL"));	
+			Preferences::SetString("browser.safebrowsing.keyURL", Preferences::GetString("own.backup.browser.safebrowsing.keyURL"));						
+			Preferences::SetBool("browser.safebrowsing.malware.enabled", Preferences::GetBool("own.backup.browser.safebrowsing.malware.enabled"));		
+			Preferences::SetString("browser.safebrowsing.malware.reportURL", Preferences::GetString("own.backup.browser.safebrowsing.malware.reportURL"));					
+			Preferences::SetString("browser.safebrowsing.reportErrorURL", Preferences::GetString("own.backup.browser.safebrowsing.reportErrorURL"));	
+			Preferences::SetString("browser.safebrowsing.reportGenericURL", Preferences::GetString("own.backup.browser.safebrowsing.reportGenericURL"));	
+			Preferences::SetString("browser.safebrowsing.reportMalwareErrorURL", Preferences::GetString("own.backup.browser.safebrowsing.reportMalwareErrorURL"));	
+			Preferences::SetString("browser.safebrowsing.reportMalwareURL", Preferences::GetString("own.backup.browser.safebrowsing.reportMalwareURL"));	
+			Preferences::SetString("browser.safebrowsing.reportPhishURL", Preferences::GetString("own.backup.browser.safebrowsing.reportPhishURL"));	
+			Preferences::SetString("browser.safebrowsing.reportURL", Preferences::GetString("own.backup.browser.safebrowsing.reportURL"));	
+			Preferences::SetString("browser.safebrowsing.updateURL", Preferences::GetString("own.backup.browser.safebrowsing.updateURL"));	
+			Preferences::SetString("browser.safebrowsing.warning.infoURL", Preferences::GetString("own.backup.browser.safebrowsing.warning.infoURL"));	
+			Preferences::SetString("browser.safebrowsing.appRepURL", Preferences::GetString("own.backup.browser.safebrowsing.appRepURL"));				
+			Preferences::SetBool("own.RestoreSafeBrowsing", false);	
+		}
+
+		bool disableSafeBrowsing = true;
+		#if defined(ANDROID)
+			disableSafeBrowsing = false;
+		#endif
+		if (Preferences::GetBool("own.forceDisableSafeBrowsing", false))
+		{		
+			disableSafeBrowsing = true;
+		}
+		if (Preferences::GetBool("own.forceDisableSafeBrowsing", false))
+		{		
+			disableSafeBrowsing = true;
+		}		
+		if (Preferences::GetBool("own.forceKeepSafeBrowsing", false))
+		{		
+			disableSafeBrowsing = false;
+		}						
+		if (disableSafeBrowsing)
+		{
+			Preferences::SetBool("browser.safebrowsing.enabled", false);	
+			Preferences::SetBool("browser.safebrowsing.downloads.enabled", false);
+			Preferences::SetBool("browser.safebrowsing.downloads.remote.enabled", false);						
+			Preferences::SetBool("browser.safebrowsing.remoteLookups", false);	
+			Preferences::SetString("browser.safebrowsing.gethashURL", u"https://127.0.0.1:7999");	
+			Preferences::SetString("browser.safebrowsing.keyURL", u"https://127.0.0.1:7999");						
+			Preferences::SetBool("browser.safebrowsing.malware.enabled", false);		
+			Preferences::SetString("browser.safebrowsing.malware.reportURL", u"https://127.0.0.1:7999");					
+			Preferences::SetString("browser.safebrowsing.reportErrorURL", u"https://127.0.0.1:7999");	
+			Preferences::SetString("browser.safebrowsing.reportGenericURL", u"https://127.0.0.1:7999");	
+			Preferences::SetString("browser.safebrowsing.reportMalwareErrorURL", u"https://127.0.0.1:7999");	
+			Preferences::SetString("browser.safebrowsing.reportMalwareURL", u"https://127.0.0.1:7999");	
+			Preferences::SetString("browser.safebrowsing.reportPhishURL", u"https://127.0.0.1:7999");	
+			Preferences::SetString("browser.safebrowsing.reportURL", u"https://127.0.0.1:7999");	
+			Preferences::SetString("browser.safebrowsing.updateURL", u"https://127.0.0.1:7999");	
+			Preferences::SetString("browser.safebrowsing.warning.infoURL", u"https://127.0.0.1:7999");	
+			Preferences::SetString("browser.safebrowsing.appRepURL", u"https://127.0.0.1:7999");			
+		}	
+		
+		Preferences::SetBool("browser.search.update", false);
+		Preferences::SetString("app.update.certs.1.commonName", u"https://127.0.0.1:7999");		
+		Preferences::SetString("app.update.certs.2.commonName", u"https://127.0.0.1:7999");		
+		
+		Preferences::SetBool("dom.disable_image_src_set", true);	
+		Preferences::SetBool("layout.css.visited_links_enabled", false);	
+		Preferences::SetBool("dom.event.clipboardevents.enabled", false);	
+		Preferences::SetBool("dom.event.contextmenu.enabled", false);				
+
+		Preferences::SetBool("dom.storage.enabled", false);
+		Preferences::SetBool("dom.network.enabled", false);
+
+		Preferences::SetBool("dom.server-events.enabled",false);
+		Preferences::SetBool("dom.sms.requestStatusReport",false);
+		Preferences::SetInt("dom.storage.default_quota",0);
+		Preferences::SetBool("dom.webnotifications.enabled",false);
+
+
+		Preferences::SetInt("network.cookie.cookieBehavior", 1);
+		Preferences::SetInt("network.cookie.lifetime.days", 1);
+		Preferences::SetInt("network.cookie.lifetimePolicy", 2);
+
+		Preferences::SetBool("network.cookie.prefsMigrated", true);
+
+		Preferences::SetBool("network.cookie.thirdparty.sessionOnly",true);
+
+		Preferences::SetBool("network.dns.disableIPv6",true);
+
+		Preferences::SetBool("network.dns.disablePrefetch",true);
+
+//network.http.sendRefererHeader;0
+//network.http.sendSecureXSiteReferrer;false
+
+		Preferences::SetBool("network.prefetch-next",false);
+		
+		Preferences::SetBool("network.http.sendSecureXSiteReferrer", false); //Don't send the Referer header when navigating from a https site to another https site.
+
+		Preferences::SetBool("toolkit.telemetry.enabled", false);
+		Preferences::SetString("toolkit.telemetry.server", u"https://127.0.0.1:7999");
+		Preferences::SetString("experiments.manifest.uri", u"https://127.0.0.1:7999");
+	
+		Preferences::SetBool("geo.enabled", false);		
+		Preferences::SetString("geo.wifi.uri", u"https://127.0.0.1:7999");	
+		Preferences::SetString("browser.search.geoip.url", u"https://127.0.0.1:7999");		
+			
+		Preferences::SetBool("browser.shell.checkDefaultBrowser", false);								
+					
+						
+		//Nicht nötig
+		//Preferences::SetString("general.useragent.override", u"");
+
+		Preferences::SetBool("security.ssl.treat_unsafe_negotiation_as_broken", true);	
+		Preferences::SetBool("security.ssl.require_safe_negotiation", true);
+		
+		//SSL mit RC4 nicht verwenden
+		//SSL-Test: https://www.howsmyssl.com/
+		Preferences::SetBool("security.ssl3.ecdh_ecdsa_rc4_128_sha", false);	
+		Preferences::SetBool("security.ssl3.ecdh_rsa_rc4_128_sha", false);	
+		Preferences::SetBool("security.ssl3.ecdhe_ecdsa_rc4_128_sha", false);	
+		Preferences::SetBool("security.ssl3.ecdhe_rsa_rc4_128_sha", false);	
+		Preferences::SetBool("security.ssl3.rsa_rc4_128_md5", false);	
+		Preferences::SetBool("security.ssl3.rsa_rc4_128_sha", false);	
+
+		Preferences::SetBool("security.ssl3.rsa_fips_des_ede3_sha", false); //Sollte bereits deaktivert sein
+		Preferences::SetInt("security.tls.version.min", 2); //3 wäre besser!
+				
+
+		Preferences::SetInt("browser.cache.disk.capacity", 0);
+		Preferences::SetBool("browser.cache.disk.enable", false);
+		Preferences::SetInt("browser.cache.disk.max_entry_size", 0);					
+		Preferences::SetBool("browser.cache.disk.smart_size.enabled", false);
+		Preferences::SetBool("browser.cache.disk.smart_size.first_run", false);		
+		Preferences::SetBool("browser.cache.disk.smart_size.use_old_max", false);
+		Preferences::SetInt("browser.cache.disk.smart_size_cached_value", 0);				
+
+		Preferences::SetBool("browser.cache.disk_cache_ssl", false); //Wichtig!
+		Preferences::SetInt("browser.cache.offline.capacity", 0);
+		Preferences::SetBool("browser.cache.offline.enable", false);				
+	
+		Preferences::SetInt("network.http.sendRefererHeader",0); //Never send the Referer header or set document.referrer.
+		//Preferences::SetInt("security.tls.version.min",3); //derzeit zu aggresiv (siehe metager.de)
+				
+		Preferences::SetBool("privacy.sanitize.migrateFx3Prefs",true);  //Then your Firefox will not automatically set "privacy.clearOnShutdown.cookies" and "privacy.cpd.cookies" to false.
+		Preferences::SetBool("privacy.clearOnShutdown.history", true);
+		Preferences::SetBool("privacy.clearOnShutdown.formdata", true);
+		Preferences::SetBool("privacy.clearOnShutdown.passwords", true);
+		Preferences::SetBool("privacy.clearOnShutdown.downloads", true);
+		Preferences::SetBool("privacy.clearOnShutdown.cookies", true);
+		Preferences::SetBool("privacy.clearOnShutdown.cache", true);
+		Preferences::SetBool("privacy.clearOnShutdown.sessions", true);
+		Preferences::SetBool("privacy.clearOnShutdown.offlineApps", true);
+		Preferences::SetBool("privacy.clearOnShutdown.siteSettings", true);
+		Preferences::SetBool("privacy.cpd.history", true);
+		Preferences::SetBool("privacy.cpd.formdata", true);
+		Preferences::SetBool("privacy.cpd.passwords", true);
+		Preferences::SetBool("privacy.cpd.downloads", true);
+		Preferences::SetBool("privacy.cpd.cookies", true);
+		Preferences::SetBool("privacy.cpd.cache", true);
+		Preferences::SetBool("privacy.cpd.sessions", true);
+		Preferences::SetBool("privacy.cpd.offlineApps", true);
+		Preferences::SetBool("privacy.cpd.siteSettings", true);			
+	
+		Preferences::SetBool("webgl.disabled", true);		
+		Preferences::SetBool("browser.privatebrowsing.autostart", true);		
+		Preferences::SetBool("signon.rememberSignons", false);
+		
+		//Eigentlich nicht nötig / Speed
+		Preferences::SetInt("layout.spellcheckDefault", 0);				
+		Preferences::SetBool("general.smoothScroll", false);
+
+				
+		Preferences::SetBool("browser.cache.memory.enable", false);
+
+		Preferences::SetBool("browser.search.suggest.enabled", false);	
+
+		if (Preferences::GetBool("own.disallowPeerAndh264", true))
+		{
+			Preferences::SetBool("media.gmp-gmpopenh264.provider.enabled", false);	
+			Preferences::SetBool("media.gmp-gmpopenh264.enabled", false);		
+			Preferences::SetBool("media.peerconnection.video.h264_enabled", false);
+		}	
+		
+		//2014-10-16	
+		Preferences::SetString("browser.newtabpage.directory.ping", u"https://127.0.0.1:7999");
+		Preferences::SetString("browser.newtabpage.directory.source", u"https://127.0.0.1:7999");
+		Preferences::SetString("browser.contentHandlers.types.0.uri", u"https://127.0.0.1:7999");
+
+		if (Preferences::GetBool("own.enableTrrackingProtection", false))
+		{
+			Preferences::SetBool("privacy.trackingprotection.enabled", true);
+		}
+		else
+		{
+			Preferences::SetBool("privacy.trackingprotection.enabled", false);			
+			Preferences::SetString("browser.trackingprotection.gethashURL", u"https://127.0.0.1:7999");
+			Preferences::SetString("browser.trackingprotection.updateURL", u"https://127.0.0.1:7999");
+		}
+		
+		Preferences::SetString("browser.uitour.pinnedTabUrl", u"https://127.0.0.1:7999");
+
+		Preferences::SetString("browser.dictionaries.download.url", u"https://127.0.0.1:7999");
+
+		Preferences::SetString("gecko.handlerService.schemes.webcal.0.uriTemplate", u"https://127.0.0.1:7999");
+
+		//Preferences::SetString("extensions.webservice.discoverURL", u"https://127.0.0.1:7999");
+		Preferences::SetString("gecko.handlerService.schemes.irc.0.uriTemplate", u"https://127.0.0.1:7999");
+		Preferences::SetString("gecko.handlerService.schemes.ircs.0.uriTemplate", u"https://127.0.0.1:7999");
+		Preferences::SetString("gecko.handlerService.schemes.mailto.0.uriTemplate", u"https://127.0.0.1:7999");
+		Preferences::SetString("gecko.handlerService.schemes.mailto.1.uriTemplate", u"https://127.0.0.1:7999");
+		Preferences::SetString("gecko.handlerService.schemes.webcal.0.uriTemplate", u"https://127.0.0.1:7999");
+
+		Preferences::SetString("identity.fxaccounts.auth.uri", u"https://127.0.0.1:7999");
+		Preferences::SetString("identity.fxaccounts.remote.force_auth.uri", u"https://127.0.0.1:7999");
+		Preferences::SetString("identity.fxaccounts.remote.signin.uri", u"https://127.0.0.1:7999");
+		Preferences::SetString("identity.fxaccounts.remote.signup.uri", u"https://127.0.0.1:7999");
+		Preferences::SetString("identity.fxaccounts.settings.uri", u"https://127.0.0.1:7999");
+
+		Preferences::SetString("loop.feedback.baseUrl", u"https://127.0.0.1:7999");
+		Preferences::SetString("loop.learnMoreUrl", u"https://127.0.0.1:7999");
+		Preferences::SetString("loop.legal.ToS_url", u"https://127.0.0.1:7999");
+		Preferences::SetString("loop.legal.privacy_url", u"https://127.0.0.1:7999");
+		Preferences::SetString("loop.oauth.google.scope", u"https://127.0.0.1:7999");
+		Preferences::SetString("loop.server", u"https://127.0.0.1:7999");
+		Preferences::SetString("media.gmp-manager.url", u"https://127.0.0.1:7999");
+
+		Preferences::SetString("social.whitelist", u"");
+
+		Preferences::SetString("app.feedback.baseURL", u"https://127.0.0.1:7999");
+		Preferences::SetString("app.support.baseURL", u"https://127.0.0.1:7999");
+
+		Preferences::SetString("app.update.url", u"https://127.0.0.1:7999");
+		Preferences::SetString("app.update.url.details", u"https://127.0.0.1:7999");
+		Preferences::SetString("app.update.url.manual", u"https://127.0.0.1:7999");
+
+		//Preferences::SetString("extensions.update.background.url", u"https://127.0.0.1:7999");
+		//Preferences::SetString("extensions.update.url", u"https://127.0.0.1:7999");
+
+		Preferences::SetString("services.sync.fxa.privacyURL", u"https://127.0.0.1:7999");
+		Preferences::SetString("services.sync.fxa.termsURL", u"https://127.0.0.1:7999");
+		Preferences::SetString("services.sync.jpake.serverURL", u"https://127.0.0.1:7999");
+		Preferences::SetString("services.sync.privacyURL", u"https://127.0.0.1:7999");
+		Preferences::SetString("services.sync.serverURL", u"https://127.0.0.1:7999");
+		Preferences::SetString("services.sync.statusURL", u"https://127.0.0.1:7999");
+		Preferences::SetString("services.sync.syncKeyHelpURL", u"https://127.0.0.1:7999");
+		Preferences::SetString("services.sync.termsURL", u"https://127.0.0.1:7999");
+		Preferences::SetString("services.sync.tokenServerURI", u"https://127.0.0.1:7999");
+		
+		Preferences::SetString("services.push.serverURL", u"https://127.0.0.1:7999");
+		Preferences::SetBool("services.push.enabled", false);		
+		
+		Preferences::SetString("social.directories", u"https://127.0.0.1:7999");
+		Preferences::SetString("social.shareDirectory", u"https://127.0.0.1:7999");
+
+		Preferences::SetBool("network.http.spdy.enabled", false);
+		Preferences::SetBool("network.http.spdy.enabled.http2", false);
+		Preferences::SetBool("network.http.spdy.enabled.http2draft", false);
+		Preferences::SetBool("network.http.spdy.enabled.v3", false);
+		Preferences::SetBool("network.http.spdy.enabled.v3-1", false);
+		//2014-10-16 end
+		//http://www.quirksmode.org/js/detect.html
+		
+		Preferences::SetBool("security.ssl.errorReporting.enabled", false);
+		Preferences::SetString("security.ssl.errorReporting.url", u"https://127.0.0.1:7999");
+														
+	}
+//EDIT:END
+
    // Add the `Mobile` or `Tablet` token when running on device or in the
    // b2g desktop simulator.
 #if defined(ANDROID) || defined(FXOS_SIMULATOR)
@@ -818,6 +1365,13 @@ nsHttpHandler::InitUserAgentComponents()
 #endif
 #endif
 
+//EDIT:
+	if (Preferences::GetBool("own.changeUserAgent.enable", false))
+	{
+			mOscpu.AssignLiteral("Windows NT 6.1; WOW64");
+	}
+//EDIT:END
+
     mUserAgentIsDirty = true;
 }
 
