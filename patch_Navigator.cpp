--- /home/benutzer/Downloads/mozilla-release_org/dom/base/Navigator.cpp	2015-01-23 07:00:03.000000000 +0100
+++ /home/benutzer/Downloads/mozilla-release/dom/base/Navigator.cpp	2015-02-10 22:04:24.892359350 +0100
@@ -109,6 +109,11 @@
 
 #include "mozilla/dom/FeatureList.h"
 
+//EDIT:
+#include "mozilla/Preferences.h"
+//EDIT:END
+
+
 namespace mozilla {
 namespace dom {
 
@@ -1246,6 +1251,12 @@ Navigator::MozGetUserMedia(const MediaSt
                            NavigatorUserMediaErrorCallback& aOnError,
                            ErrorResult& aRv)
 {
+
+  //EDIT:
+  aRv.Throw(NS_ERROR_NOT_AVAILABLE);
+  return;
+  //EDIT:END
+  
   CallbackObjectHolder<NavigatorUserMediaSuccessCallback,
                        nsIDOMGetUserMediaSuccessCallback> holder1(&aOnSuccess);
   nsCOMPtr<nsIDOMGetUserMediaSuccessCallback> onsuccess =
@@ -1272,6 +1283,11 @@ Navigator::MozGetUserMediaDevices(const
                                   uint64_t aInnerWindowID,
                                   ErrorResult& aRv)
 {
+  //EDIT:
+  aRv.Throw(NS_ERROR_NOT_AVAILABLE);
+  return;
+  //EDIT:END
+  
   CallbackObjectHolder<MozGetUserMediaDevicesSuccessCallback,
                        nsIGetUserMediaDevicesSuccessCallback> holder1(&aOnSuccess);
   nsCOMPtr<nsIGetUserMediaDevicesSuccessCallback> onsuccess =
@@ -2419,8 +2435,26 @@ Navigator::GetAppVersion(nsAString& aApp
 
   rv = service->GetPlatform(str);
   NS_ENSURE_SUCCESS(rv, rv);
+  
+  
+  //EDIT:
+  //rv = service->GetPlatform(str);
+  //NS_ENSURE_SUCCESS(rv, rv);
+  //AppendASCIItoUTF16(str, aAppVersion);
+  if (Preferences::GetBool("own.changeUserAgent.enable", false))
+  {
+	  AppendASCIItoUTF16("Windows", aAppVersion);
+  }
+  else
+  {
+	rv = service->GetPlatform(str);
+	NS_ENSURE_SUCCESS(rv, rv);
+	AppendASCIItoUTF16(str, aAppVersion);	  
+  }
+  //EDIT:END
+		  
 
-  AppendASCIItoUTF16(str, aAppVersion);
+  
   aAppVersion.Append(char16_t(')'));
 
   return rv;
