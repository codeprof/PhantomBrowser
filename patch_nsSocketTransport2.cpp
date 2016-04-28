--- /home/benutzer/Downloads/mozilla-release/netwerk/base/src/nsSocketTransport2_new.cpp	2015-02-25 21:38:32.068605846 +0100
+++ /home/benutzer/Downloads/mozilla-release/netwerk/base/src/nsSocketTransport2.cpp	2015-02-25 21:41:26.304601279 +0100
@@ -53,6 +53,10 @@
 #endif
 /* End keepalive config inclusions. */
 
+//EDIT:
+#include "mozilla/Preferences.h"
+//EDIT:END
+
 using namespace mozilla;
 using namespace mozilla::net;
 
@@ -1209,6 +1213,37 @@ nsSocketTransport::InitiateSocket()
         }
 #endif
 
+
+		//EDIT:
+		//TODO: Überprüfen, ob überprüfung auf lokale IP überhaupt nötig ist 
+		if (Preferences::GetBool("own.disallowDirectIPUsage.enabled", false))
+		{
+					
+			if (mHost.Length() >= 1)
+			{
+				//IP-Adressen blockieren! (Alles was mit einer Zahl anfängt und aufhört! Zahl am Anfang reicht nicht)
+				if ( (mHost[0] >= '0') && (mHost[0] <= '9') )
+					if ( (mHost[mHost.Length()-1] >= '0') && (mHost[mHost.Length()-1] <= '9') )
+					{						
+						char* privateIPs[] = { "127.", "192.168.", "172.16.", "172.17.", "172.18.", "172.19.", "172.20.", "172.21.", "172.22.", "172.23.", "172.24.", "172.25.", "172.26.", "172.27.", "172.28.", "172.29.", "172.30.", "172.31."};
+						bool isPrivateIP = false;
+						
+						for(int i = 0; i < 18; i++)
+						{
+							if (mHost.Length() >= strlen(privateIPs[i]))
+							{
+								if (strncmp(privateIPs[i], mHost.get(), strlen(privateIPs[i])) == 0)
+									isPrivateIP = true;
+							}						
+						}
+						if (isPrivateIP == false)		
+							return NS_ERROR_CONNECTION_REFUSED;
+					}
+				
+			}
+		}
+		//EDIT:END
+
         if (NS_SUCCEEDED(mCondition) &&
             crashOnNonLocalConnections &&
             !(IsIPAddrAny(&mNetAddr) || IsIPAddrLocal(&mNetAddr))) {
