--- /home/benutzer/Downloads/mozilla-release/dom/base/nsGlobalWindow.cpp	2015-01-23 07:00:03.000000000 +0100
+++ /home/benutzer/Downloads/mozilla-release/dom/base/nsGlobalWindow_new.cpp	2015-02-10 15:30:40.067991608 +0100
@@ -4661,7 +4661,16 @@ nsGlobalWindow::SetName(const nsAString&
   FORWARD_TO_OUTER_OR_THROW(SetName, (aName, aError), aError, );
 
   if (mDocShell) {
-    aError = mDocShell->SetName(aName);
+    //EDIT:  
+    if (Preferences::GetBool("own.windowNameDoNothing.enabled", false))
+	{
+		//aError = mDocShell->SetName(aName);
+	}
+	else
+	{
+		aError = mDocShell->SetName(aName);
+	}
+    //EDIT:END
   }
 }
 
