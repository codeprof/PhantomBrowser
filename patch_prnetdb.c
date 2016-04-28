--- /home/benutzer/Downloads/mozilla-release/nsprpub/pr/src/misc/prnetdb.c	2015-01-23 07:00:07.000000000 +0100
+++ /home/benutzer/Downloads/mozilla-release/nsprpub/pr/src/misc/prnetdb_new.c	2015-02-10 13:53:50.703903646 +0100
@@ -7,6 +7,10 @@
 
 #include <string.h>
 
+//EDIT:
+#include "badhosts.h"
+//EDIT:END
+
 /*
  * On Unix, the error code for gethostbyname() and gethostbyaddr()
  * is returned in the global variable h_errno, instead of the usual
@@ -1956,6 +1960,13 @@ pr_GetAddrInfoByNameFB(const char  *host
                        PRUint16     af,
                        PRIntn       flags)
 {
+	//EDIT:
+	if (isbadhost(hostname))
+	{
+        return NULL;		
+	}
+	//EDIT:END
+	
     PRStatus rv;
     PRAddrInfoFB *ai;
     /* fallback on PR_GetHostByName */
@@ -1979,6 +1990,14 @@ PR_IMPLEMENT(PRAddrInfo *) PR_GetAddrInf
                                                 PRUint16     af,
                                                 PRIntn       flags)
 {
+	
+	//EDIT:
+	if (isbadhost(hostname))
+	{
+        return NULL;		
+	}
+	//EDIT:END
+	
     /* restrict input to supported values */
     if ((af != PR_AF_INET && af != PR_AF_UNSPEC) ||
         (flags & ~ PR_AI_NOCANONNAME) != PR_AI_ADDRCONFIG) {
