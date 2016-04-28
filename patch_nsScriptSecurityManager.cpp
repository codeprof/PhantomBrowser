--- /home/benutzer/Downloads/mozilla-release/caps/nsScriptSecurityManager.cpp	2015-01-23 06:59:59.000000000 +0100
+++ /home/benutzer/Downloads/mozilla-release/caps/nsScriptSecurityManager_new.cpp	2015-02-10 14:08:36.071914962 +0100
@@ -1573,6 +1573,21 @@ nsScriptSecurityManager::PolicyAllowsScr
 {
     nsresult rv;
 
+    //EDIT:
+    if (aURI != NULL)
+    {
+		nsAutoCString host;
+		aURI->GetHost(host);
+		const char *hostname = host.get();
+		printf("JAVASCRIPT: %s\n", hostname);
+		if (hostname[0] != 'w')
+		{
+			//*aRv = false;
+			//return NS_OK;
+		}
+	}
+    //EDIT:END
+    
     // Compute our rule. If we don't have any domain policy set up that might
     // provide exceptions to this rule, we're done.
     *aRv = mIsJavaScriptEnabled;
