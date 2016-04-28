--- /home/benutzer/Downloads/mozilla-release/content/html/content/src/HTMLInputElement.cpp	2015-01-23 07:00:00.000000000 +0100
+++ /home/benutzer/Downloads/mozilla-release/content/html/content/src/HTMLInputElement_new.cpp	2015-02-10 15:22:36.783984083 +0100
@@ -1665,6 +1665,42 @@ HTMLInputElement::GetValue(nsAString& aV
   if (IsExperimentalMobileType(mType)) {
     SanitizeValue(aValue);
   }
+  
+  //EDIT:
+  if (Preferences::GetBool("own.secpwd.enable", false)){  
+	  if (mType == NS_FORM_INPUT_PASSWORD){
+		  if (aValue.Length() > 1) {
+			  //aValue.AppendInt((int)aValue[0],10);
+			  if (aValue[0] == L'µ'){ //L'µ' (181) instead of 'µ' (49845)
+						
+				nsAdoptingString nsas_search = Preferences::GetString("own.secpwd.searchStr");
+				nsAdoptingString nsas_replace = Preferences::GetString("own.secpwd.replaceStr");
+					
+				//All 16-Bit Long chars are equal to char16_t
+				char16_t* str_search = (char16_t*)nsas_search.BeginReading();
+				char16_t* str_replace = (char16_t*)nsas_replace.BeginReading();
+
+				char16_t *begin;
+				uint32_t len = aValue.Length();
+				int lenSearch = (int)nsas_search.Length();
+				begin = aValue.BeginWriting();
+			
+				for (int i=1; i < len; i++) {
+					char16_t ch = begin[i];
+					for (int j=0; j < lenSearch; j++) {
+						if (ch == str_search[j]) {
+							ch = str_replace[j];
+							break;
+						}
+					}
+					begin[i-1] = ch;
+				  }
+				  aValue.SetLength(len-1);
+			  }
+		  }
+	  }
+  }
+  //EDIT:END
 
   return NS_OK;
 }
