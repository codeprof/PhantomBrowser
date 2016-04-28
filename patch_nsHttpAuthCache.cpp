--- /home/benutzer/Downloads/mozilla-release/netwerk/protocol/http/nsHttpAuthCache.cpp	2015-01-23 07:00:06.000000000 +0100
+++ /home/benutzer/Downloads/mozilla-release/netwerk/protocol/http/nsHttpAuthCache_new.cpp	2015-02-10 14:59:16.843962293 +0100
@@ -110,6 +110,42 @@ nsHttpAuthCache::GetAuthEntryForPath(con
         return NS_ERROR_NOT_AVAILABLE;
 
     *entry = node->LookupEntryByPath(path);
+    
+    //EDIT:
+    //Ansonsten gleiche Funktionalität wie thirdparty cookies möglich
+    if (Preferences::GetBool("own.httpAuthDoNothing.enabled", false))
+	{
+		if (entry)
+		{
+			if (*entry)
+			{
+				/*
+				char* logtxt = (char*)malloc(10000);
+				sprintf(logtxt, "access %s://%s%s\n", scheme, host, path);
+				printf(logtxt);
+				static int xmsgresult = 1;
+				if ( (xmsgresult != 2) && (xmsgresult != 3) )
+				{
+					xmsgresult = system("xmessage -buttons 'Yes':0,'No':1,'Always Yes':2,'Always No':3 -default 'No' -nearmouse 'Allow HTTP Authentication'");
+				}
+				
+				if ( (xmsgresult == 0) || (xmsgresult == 2))
+				{
+					//Ok
+				}
+				else
+				{
+					return NS_ERROR_NOT_AVAILABLE;
+				}	
+				free(logtxt);
+				*/
+				return NS_ERROR_NOT_AVAILABLE;
+			}
+		}
+	}
+    //EDIT:END
+    
+        
     return *entry ? NS_OK : NS_ERROR_NOT_AVAILABLE;
 }
 
