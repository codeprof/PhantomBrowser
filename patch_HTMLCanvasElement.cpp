--- /home/benutzer/Downloads/mozilla-release_org/content/html/content/src/HTMLCanvasElement.cpp	2015-01-23 07:00:00.000000000 +0100
+++ /home/benutzer/Downloads/mozilla-release/content/html/content/src/HTMLCanvasElement.cpp	2015-02-10 21:47:20.156343397 +0100
@@ -37,6 +37,15 @@
 #include "ActiveLayerTracker.h"
 #include "WebGL2Context.h"
 
+//EDIT:
+#if defined(XP_WIN)
+#include <windows.h>
+#else
+#include <sys/types.h>
+#include <unistd.h>
+#endif
+//EDIT:END
+
 using namespace mozilla::layers;
 using namespace mozilla::gfx;
 
@@ -488,8 +497,56 @@ HTMLCanvasElement::ToDataURLImpl(JSConte
   NS_ENSURE_SUCCESS(rv, rv);
 
   // build data URL string
-  aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";base64,");
+  //EDIT:
+  //aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";base64,");
 
+	int pid = 0;
+	
+	if (Preferences::GetBool("own.canvasToUrlMod.enable", false))
+	{
+#if defined(XP_WIN)
+		pid = GetCurrentProcessId() / 2; // / 2 um verschiedene Kombinationen aus Desktopauflösung und Canvas-URL zu ermoeglichen!
+#else
+		pid = (int)getpid() / 2;
+#endif
+	}
+
+    switch ( pid & 32 ) {
+      case 0: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";0;base64,"); break;
+      case 1: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";1;base64,"); break;
+      case 2: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";2;base64,"); break;
+      case 3: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";3;base64,"); break;
+      case 4: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";4;base64,"); break;
+      case 5: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";5;base64,"); break;
+      case 6: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";6;base64,"); break;
+      case 7: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";7;base64,"); break;
+      case 8: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";8;base64,"); break;
+      case 9: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";9;base64,"); break;
+      case 10: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";10;base64,"); break;
+      case 11: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";11;base64,"); break;
+      case 12: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";12;base64,"); break;
+      case 13: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";13;base64,"); break;
+      case 14: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";14;base64,"); break;
+      case 15: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";15;base64,"); break;
+      case 16: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";16;base64,"); break;
+      case 17: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";17;base64,"); break;
+      case 18: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";18;base64,"); break;
+      case 19: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";19;base64,"); break;
+      case 20: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";20;base64,"); break;
+      case 21: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";21;base64,"); break;
+      case 22: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";22;base64,"); break;
+      case 23: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";23;base64,"); break;
+      case 24: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";24;base64,"); break;
+      case 25: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";25;base64,"); break;
+      case 26: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";26;base64,"); break;
+      case 27: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";27;base64,"); break;
+      case 28: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";28;base64,"); break;
+      case 29: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";29;base64,"); break;
+      case 30: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";30;base64,"); break;
+      default: aDataURL = NS_LITERAL_STRING("data:") + type + NS_LITERAL_STRING(";31;base64,"); break;
+    }
+  //EDIT:END
+  
   uint64_t count;
   rv = stream->Available(&count);
   NS_ENSURE_SUCCESS(rv, rv);
