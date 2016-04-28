--- /home/benutzer/Downloads/ff/mozilla-release/toolkit/components/url-classifier/nsUrlClassifierDBService_org.cpp	2015-09-02 18:26:14.545606839 +0200
+++ /home/benutzer/Downloads/ff/mozilla-release/toolkit/components/url-classifier/nsUrlClassifierDBService.cpp	2015-09-03 21:03:02.226530800 +0200
@@ -51,6 +51,12 @@
 #include "ProtocolParser.h"
 #include "nsContentUtils.h"
 
+
+//EDIT: 
+#include <stdio.h>
+#include "safesearch_ignore.h"
+//EDIT:END  
+
 using namespace mozilla;
 using namespace mozilla::safebrowsing;
 
@@ -1324,6 +1330,173 @@ nsUrlClassifierDBService::LookupURI(nsIP
 
   uri = NS_GetInnermostURI(uri);
   NS_ENSURE_TRUE(uri, NS_ERROR_FAILURE);
+  
+  //EDIT:  
+  if (Preferences::GetBool("own.useIgnoreListSafeBrowsing.enabled", true)) //own.useIgnoreListSafeSearch.enabled
+  {
+	  nsAutoCString aHost; //nsACString
+	  nsAutoCString aExt; //nsACString
+	  nsAutoCString aPath; //nsACString
+
+	  rv = uri->GetPath(aPath);
+	  if (NS_SUCCEEDED(rv) && !aPath.IsEmpty()) {
+		  //ok
+	  }
+	  else
+	  {
+		*didLookup = false;  
+		return NS_OK;
+	  }	
+	  char* sPath = (char*)aPath.BeginReading();
+	  int pathLen = strlen(sPath);
+
+	  char* sExt3 = sPath+pathLen-3;	  
+	  char* sExt4 = sPath+pathLen-4;
+	  char* sExt5 = sPath+pathLen-5;
+	  if (pathLen < 3) sExt4 = "";	  
+	  if (pathLen < 4) sExt4 = "";
+	  if (pathLen < 5) sExt5 = "";
+				
+	  rv = uri->GetAsciiHost(aHost);
+	  if (NS_SUCCEEDED(rv) && !aHost.IsEmpty()) {
+		  //ok
+	  }
+	  else
+	  {
+		*didLookup = false;  
+		return NS_OK;
+	  }
+	  char* sHost = (char*)aHost.BeginReading();
+	   
+	  bool check_url = true;
+	  
+	  if (Preferences::GetBool("own.safeBrowsingIgnoreImages.enabled", true))
+	  {	  
+		  if (strcasecmp(sExt4, ".jpg") == 0) check_url = false;
+		  if (strcasecmp(sExt5, ".jpeg") == 0) check_url = false;		
+		  if (strcasecmp(sExt4, ".gif") == 0) check_url = false;		
+		  if (strcasecmp(sExt4, ".png") == 0) check_url = false;	
+		  if (strcasecmp(sExt4, ".ico") == 0) check_url = false;	
+		  if (strcasecmp(sExt4, ".bmp") == 0) check_url = false;								
+		  //if (strcasecmp(sExt4, ".svg") == 0) //maybe to unsecure
+			//check_url = false;						
+	  }
+	  
+	  if (Preferences::GetBool("own.safeBrowsingIgnoreMedia.enabled", false)) //NOTE: For Video NOT enabled by default!
+	  {	 	  
+		  if (strcasecmp(sExt4, ".ogg") == 0) check_url = false;	
+		  if (strcasecmp(sExt4, ".ogv") == 0) check_url = false;		
+		  if (strcasecmp(sExt4, ".mpg") == 0) check_url = false;		
+		  if (strcasecmp(sExt4, ".mp4") == 0) check_url = false;	
+		  if (strcasecmp(sExt4, ".mp3") == 0) check_url = false;	
+		  if (strcasecmp(sExt4, ".mkv") == 0) check_url = false;	
+		  if (strcasecmp(sExt4, ".flv") == 0) check_url = false;	
+		  if (strcasecmp(sExt4, ".wmv") == 0) check_url = false;	
+		  if (strcasecmp(sExt4, ".wma") == 0) check_url = false;				
+		  if (strcasecmp(sExt4, ".avi") == 0) check_url = false;
+		  if (strcasecmp(sExt4, ".mov") == 0) check_url = false;		
+		  if (strcasecmp(sExt4, ".asf") == 0) check_url = false;
+		  if (strcasecmp(sExt4, ".3gp") == 0) check_url = false;	  	
+		  if (strcasecmp(sExt5, ".webm") == 0) check_url = false;			  
+		  if (strcasecmp(sExt5, ".mpeg") == 0) check_url = false;		  	  		  																		
+	  }			
+				
+	  if (!check_url)
+	  {
+		printf("SAFEBROWSING: %s%s (NO LOOKUP)\n", sHost, sPath);
+		*didLookup = false;  
+		return NS_OK;			  
+	  }		  
+	  
+	  bool force_check = false;
+	  
+	  /*
+	  if (strcasecmp(sExt4, ".ogg") == 0) force_check = true;	
+	  if (strcasecmp(sExt4, ".ogv") == 0) force_check = true;		
+	  if (strcasecmp(sExt4, ".mpg") == 0) force_check = true;		
+	  if (strcasecmp(sExt4, ".mp4") == 0) force_check = true;	
+	  if (strcasecmp(sExt4, ".mp3") == 0) force_check = true;	
+	  if (strcasecmp(sExt4, ".mkv") == 0) force_check = true;	
+	  if (strcasecmp(sExt4, ".flv") == 0) force_check = true;	
+	  if (strcasecmp(sExt4, ".wmv") == 0) force_check = true;	
+	  if (strcasecmp(sExt4, ".wma") == 0) force_check = true;				
+	  if (strcasecmp(sExt4, ".avi") == 0) force_check = true;
+	  if (strcasecmp(sExt4, ".mov") == 0) force_check = true;		
+	  if (strcasecmp(sExt4, ".asf") == 0) force_check = true;
+	  if (strcasecmp(sExt4, ".3gp") == 0) force_check = true;	  	
+	  if (strcasecmp(sExt5, ".webm") == 0) force_check = true;		  
+	  if (strcasecmp(sExt5, ".mpeg") == 0) force_check = true;	
+	  */
+	  
+	  if (strcasecmp(sExt3, ".sh") == 0) force_check = true;	 		
+	  if (strcasecmp(sExt3, ".7z") == 0) force_check = true;	 
+	  if (strcasecmp(sExt3, ".gz") == 0) force_check = true;		  
+	  if (strcasecmp(sExt3, ".vb") == 0) force_check = true;			
+		
+	  if (strcasecmp(sExt4, ".jar") == 0) force_check = true;	 
+	  if (strcasecmp(sExt4, ".xml") == 0) force_check = true;	
+	  if (strcasecmp(sExt4, ".xsl") == 0) force_check = true;					
+	  if (strcasecmp(sExt4, ".reg") == 0) force_check = true;	
+	  if (strcasecmp(sExt4, ".rtf") == 0) force_check = true;
+	  if (strcasecmp(sExt4, ".hlp") == 0) force_check = true;	
+	  if (strcasecmp(sExt4, ".chm") == 0) force_check = true;										
+	  //if (strcasecmp(sExt4, ".swf") == 0) //to much privay issues
+	  //	force_check = true;			
+	  if (strcasecmp(sExt4, ".pdf") == 0) force_check = true;				  
+	  if (strcasecmp(sExt4, ".apk") == 0) force_check = true;	  
+	  if (strcasecmp(sExt4, ".zip") == 0) force_check = true;
+	  if (strcasecmp(sExt4, ".rar") == 0) force_check = true;		
+	  if (strcasecmp(sExt4, ".cab") == 0) force_check = true;	 			 
+	  if (strcasecmp(sExt4, ".exe") == 0) force_check = true;	 
+	  if (strcasecmp(sExt4, ".msi") == 0) force_check = true;	 	
+	  if (strcasecmp(sExt4, ".com") == 0) force_check = true;	 //Should cuase no problems with .com domains			
+	  if (strcasecmp(sExt4, ".scr") == 0) force_check = true;	 		
+	  if (strcasecmp(sExt4, ".bat") == 0) force_check = true;	 
+	  if (strcasecmp(sExt4, ".cmd") == 0) force_check = true;		
+	  if (strcasecmp(sExt4, ".pif") == 0) force_check = true;	 
+	  if (strcasecmp(sExt4, ".hta") == 0) force_check = true;				
+	  if (strcasecmp(sExt4, ".tar") == 0) force_check = true;					
+	  if (strcasecmp(sExt4, ".jse") == 0) force_check = true;			
+	  if (strcasecmp(sExt4, ".vbs") == 0) force_check = true;	 	
+	  if (strcasecmp(sExt4, ".doc") == 0) force_check = true;	 		
+	  if (strcasecmp(sExt4, ".xls") == 0) force_check = true;	 	
+	  if (strcasecmp(sExt4, ".ppt") == 0) force_check = true;
+	  	 		
+	  if (strcasecmp(sExt5, ".class") == 0) force_check = true;	  	 		
+	  if (strcasecmp(sExt5, ".docm") == 0) force_check = true;	
+	  if (strcasecmp(sExt5, ".dotm") == 0) force_check = true;			
+	  if (strcasecmp(sExt5, ".xlsm") == 0) force_check = true;			
+	  if (strcasecmp(sExt5, ".xltm") == 0) force_check = true;	
+	  if (strcasecmp(sExt5, ".xlam") == 0) force_check = true;	
+	  if (strcasecmp(sExt5, ".pptm") == 0) force_check = true;	
+	  if (strcasecmp(sExt5, ".potm") == 0) force_check = true;	
+	  if (strcasecmp(sExt5, ".ppam") == 0) force_check = true;	
+	  if (strcasecmp(sExt5, ".ppsm") == 0) force_check = true;	
+	  if (strcasecmp(sExt5, ".sldm") == 0) force_check = true;		
+	  if (strcasecmp(sExt5, ".xlsx") == 0) force_check = true;																
+	  if (strcasecmp(sExt5, ".docx") == 0) force_check = true;
+	  if (strcasecmp(sExt5, ".pptx") == 0) force_check = true;		
+								
+	  if (!force_check)
+	  {					  
+		  init_safesearch_ignore_list();
+		  if (is_in_safesearch_ignore_list(sHost))
+		  {
+			printf("SAFEBROWSING: %s%s (NO LOOKUP)\n", sHost, sPath);
+			*didLookup = false;  
+			return NS_OK;	
+		  }
+		  else
+		  {
+			printf("SAFEBROWSING: %s%s\n", sHost, sPath);	  
+		  }
+	  }
+	  else
+	  {
+		printf("SAFEBROWSING: %s%s\n (FORCE)", sHost, sPath);			  
+	  }
+  }
+  //EDIT:END
 
   nsAutoCString key;
   // Canonicalize the url
