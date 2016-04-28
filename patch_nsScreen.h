--- /home/benutzer/Downloads/mozilla-release/dom/base/nsScreen.h	2015-01-23 07:00:03.000000000 +0100
+++ /home/benutzer/Downloads/mozilla-release/dom/base/nsScreen_new.h	2015-02-10 15:35:45.159996357 +0100
@@ -14,6 +14,35 @@
 #include "nsCOMPtr.h"
 #include "nsRect.h"
 
+//EDIT:
+#include "mozilla/Preferences.h"
+using namespace mozilla;
+#if defined(XP_WIN)
+#include <windows.h>
+#else
+#include <sys/types.h>
+#include <unistd.h>
+#endif
+/*
+768x1024
+800x600
+1024x768
+1152x720
+1280x720
+1280x800
+1280x1024
+1366x626
+1366x768
+1400x1050
+1440x900
+1600x900
+1600x1200
+1680x1050
+1920x1080
+1366x768 (doppelt da am häufigsten)
+*/
+//EDIT:END
+
 class nsDeviceContext;
 
 // Script "screen" object
@@ -61,6 +90,35 @@ public:
     }
 
     aRv = GetRect(rect);
+    //EDIT:  
+	if (!Preferences::GetBool("own.desktopMod.enabled", false))
+		return rect.width;
+		    
+#if defined(XP_WIN)
+	int pid = GetCurrentProcessId();  
+#else
+	int pid = (int)getpid();
+#endif
+    
+    switch ( pid & 15 ) {
+      case 0: return 768; break;
+      case 1: return 800; break;
+      case 2: return 1024; break;
+      case 3: return 1152; break;
+      case 4: return 1280; break;
+      case 5: return 1280; break;
+      case 6: return 1280; break;
+      case 7: return 1366; break;
+      case 8: return 1366; break;
+      case 9: return 1400; break;
+      case 10: return 1440; break;
+      case 11: return 1600; break;
+      case 12: return 1600; break;
+      case 13: return 1680; break;
+      case 14: return 1920; break;
+      default: return 1366; break;
+    }
+    //EDIT:END
     return rect.width;
   }
 
@@ -77,7 +135,35 @@ public:
     }
 
     aRv = GetRect(rect);
-    return rect.height;
+    //EDIT:
+	if (!Preferences::GetBool("own.desktopMod.enabled", false))
+		return rect.height;
+		    
+#if defined(XP_WIN)
+	int pid = GetCurrentProcessId();  
+#else
+	int pid = (int)getpid();
+#endif
+    
+    switch ( pid & 15 ) {
+      case 0: return 1024; break;
+      case 1: return 600; break;
+      case 2: return 768; break;
+      case 3: return 720; break;
+      case 4: return 720; break;
+      case 5: return 800; break;
+      case 6: return 1024; break;
+      case 7: return 626; break;
+      case 8: return 768; break;
+      case 9: return 1050; break;
+      case 10: return 900; break;
+      case 11: return 900; break;
+      case 12: return 1200; break;
+      case 13: return 1050; break;
+      case 14: return 1080; break;
+      default: return 768; break;
+    }
+    //EDIT:END
   }
 
   int32_t GetPixelDepth(ErrorResult& aRv);
@@ -104,14 +190,71 @@ public:
   {
     nsRect rect;
     aRv = GetAvailRect(rect);
-    return rect.width;
+    //EDIT:
+    
+	if (!Preferences::GetBool("own.desktopMod.enabled", false))
+		return rect.width;
+		    
+#if defined(XP_WIN)
+	int pid = GetCurrentProcessId();  
+#else
+	int pid = (int)getpid();
+#endif
+    
+    switch ( pid & 15 ) {    
+      case 0: return 768; break;
+      case 1: return 800; break;
+      case 2: return 1024; break;
+      case 3: return 1152; break;
+      case 4: return 1280; break;
+      case 5: return 1280; break;
+      case 6: return 1280; break;
+      case 7: return 1366; break;
+      case 8: return 1366; break;
+      case 9: return 1400; break;
+      case 10: return 1440; break;
+      case 11: return 1600; break;
+      case 12: return 1600; break;
+      case 13: return 1680; break;
+      case 14: return 1920; break;
+      default: return 1366; break;
+    }
+    //EDIT:END
   }
 
   int32_t GetAvailHeight(ErrorResult& aRv)
   {
     nsRect rect;
     aRv = GetAvailRect(rect);
-    return rect.height;
+    //EDIT:
+	if (!Preferences::GetBool("own.desktopMod.enabled", false))
+		return rect.height;
+		    
+#if defined(XP_WIN)
+	int pid = GetCurrentProcessId();  
+#else
+	int pid = (int)getpid();
+#endif
+    
+    switch ( pid & 15 ) {        
+      case 0: return 1024-40; break;
+      case 1: return 600-40; break;
+      case 2: return 768-40; break;
+      case 3: return 720-40; break;
+      case 4: return 720-40; break;
+      case 5: return 800-40; break;
+      case 6: return 1024-40; break;
+      case 7: return 626-40; break;
+      case 8: return 768-40; break;
+      case 9: return 1050-40; break;
+      case 10: return 900-40; break;
+      case 11: return 900-40; break;
+      case 12: return 1200-40; break;
+      case 13: return 1050-40; break;
+      case 14: return 1080-40; break;
+      default: return 768-40; break;
+    }
+    //EDIT:END
   }
 
   void GetMozOrientation(nsString& aOrientation);
