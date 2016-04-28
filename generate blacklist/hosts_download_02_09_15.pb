Global NewMap badhosts.i()
Global NewMap whitelist.i()
Global NewMap domaincount.i()
Global Dim used(255)


Global BLOCKED_DOMAINS$
BLOCKED_DOMAINS$="|ru|in|bg|gov|mil|ar|al|am|af|ae|az|bf|bd|bi|bg|br|bt|bw|by|cd|cf|cm|cn|cr|cu|cy|dj|dm"
BLOCKED_DOMAINS$+"|ec|eg|et|fk|ga|gd|ge|gh|gi|gf|gm|gn|gt|gu|gw|gy|hk|hm|hn|hr|ht|hu|il|iq|ir|jm|jo|ke|kg"
BLOCKED_DOMAINS$+"|kh|km|kp|kr|kw|ky|kz|la|lb|lk|lr|ls|lt|lv|ly|ma|md|mg|mh|mk|ml|mm|mn|mo|mp|mq|mr|ms|mt"
BLOCKED_DOMAINS$+"|mu|mv|mw|mx|my|mz|na|nc|ne|nf|ng|ni|np|nr|nu|nz|pa|pe|pf|pg|ph|pk|pl|pm|pn|pr|ps|pw|py"
BLOCKED_DOMAINS$+"|re|ro|rw|sa|sb|sc|sd|sh|si|sj|sk|sl|sn|so|sr|st|sv|sy|sz|tc|td|tf|tg|th|tj|tk|tm|tn|to"
BLOCKED_DOMAINS$+"|tp|tr|tt|tw|tz|ua|ug|um|uy|uz|vc|ve|vg|vi|vn|vu|ws|wf|ye|yt|yu|za|zm|zw"


Global CONSOLE_OPENED = #False
#USE_CONSOLE_DEBUG = #True

Procedure DebugOut(A$)
  If #USE_CONSOLE_DEBUG
    If CONSOLE_OPENED = #False
      OpenConsole()
      CONSOLE_OPENED = #True
    EndIf
    PrintN(A$)
  Else
    Debug A$
  EndIf
EndProcedure



Procedure.s getmaindomain(A$)
  A$=ReplaceString(A$,".co.uk", ".co$$$uk")
  c=CountString(A$,".")
  If c < 2
    A$=ReplaceString(A$, ".co$$$uk",".co.uk")
    ProcedureReturn A$
  Else
    A$=StringField(A$,c,".")+"."+StringField(A$,c+1,".")
    A$=ReplaceString(A$, ".co$$$uk",".co.uk")
    ProcedureReturn A$    
  EndIf
EndProcedure

Procedure add(key.s) 
  right.s = GetExtensionPart(key);Right(key,3)
  
  ;If right = ".ru" Or right = ".in" Or right = ".bg"
    ;Komplett geblock!
    ;ProcedureReturn 0
  ;EndIf
  If FindString(BLOCKED_DOMAINS$, right) > 0
    ;Komplett geblock!
    ProcedureReturn 0
  EndIf  
  
  main_domain.s = getmaindomain(key)
  
  If whitelist(key) ; Wenn exakt so in der Whitelist, dann auf keinen Fall sperren
    ProcedureReturn 0
  EndIf
  
  
  If whitelist(main_domain) = 0 ; wenn in der whiteliste dann nicht komplette domain sperren (z.B: live.com)
    If badhosts(key) = 0    ;Ansonsten einfach evtl. nur doppelt
      domaincount(main_domain)+1
      ;Für seiten mit vielen schlechten Domains wird ein globaler *. eintrag angelegt
      If domaincount(main_domain) > 3
        badglobal.s = "*." + main_domain
        If badhosts(badglobal) = 0
          DebugOut("Adding global bad domain:" + badglobal)
          used(Asc(badglobal) & 255) = 1
          badhosts(badglobal) = 1
          ;Auch ohne *. hinzufügen!
          badglobal.s = main_domain          
          used(Asc(badglobal) & 255) = 1
          badhosts(badglobal) = 1          
        EndIf
      EndIf
    EndIf
  EndIf
  
  used(Asc(key) & 255)=1
  badhosts(key) = 1
EndProcedure

Procedure ReadSpecialMailBalcklist()
  CH$= "0123456789abcdefghijklmnopqrstuvwxyz"
  If CreateFile(2,"mail_blacklist.txt")
    For t=1 To Len(CH$)  
      ReceiveHTTPFile("http://www.joewein.de/sw/spam-bl-"+Mid(CH$,t,1)+".htm", "tmp_mail.txt")
      res = ReadFile(1,"tmp_mail.txt") 
      If res
        S$="<!--SPAMDOMAINS-->"
        SE$="<!--/SPAMDOMAINS-->"
        Repeat
          a$=ReadString(1)
        Until Eof(1) Or (Left(Trim(A$),Len(S$))=S$)
        
        If Not Eof(1)
          Repeat
            A$=ReadString(1)
            If Trim(A$)<>SE$
              WriteStringN(2,"0.0.0.0 " + A$)
            EndIf
          Until (Left(Trim(A$),Len(SE$))=SE$) Or Eof(1)
        EndIf
        CloseFile(1)
      Else
        DebugOut("cannot read temp file")
      EndIf
    Next
    CloseFile(2)
  Else
    DebugOut("Cannot create mail blacklist")
  EndIf
EndProcedure


InitNetwork()

Dim urls.s(5)
urls(0) = "own_badlist.txt" 
urls(1) = "mail_blacklist.txt"
urls(2) = "http://pgl.yoyo.org/adservers/serverlist.php?showintro=0;hostformat=hosts"
urls(3) = "http://winhelp2002.mvps.org/hosts.txt"
urls(4) = "http://www.malwaredomainlist.com/hostslist/hosts.txt"
urls(5) = "http://hosts-file.net/download/hosts.txt"
;http://www.joewein.de/sw/spam-bl-a.htm

ReadFile(1,"whitelist.txt")
Repeat
  A$=ReadString(1)
  A$=LCase(Trim(A$))
  If A$<>""
    whitelist(A$) = 1
  EndIf
Until Eof(1)
CloseFile(1)


;DOMAINS KOMPLETT SPERREN
used(Asc("*"))=1
;badhosts("*.ru") = 1
;badhosts("*.in") = 1
;badhosts("*.bg") = 1
For i=0 To CountString(BLOCKED_DOMAINS$, "|")
  DOMAIN$=Trim(StringField(BLOCKED_DOMAINS$,i+1,"|"))
  If DOMAIN$ <> ""
    badhosts("*."+DOMAIN$) = 1    
  EndIf
Next

DebugOut("-- BEGIN DOWNLOAD --")
ReadSpecialMailBalcklist()

For i = 0 To 5
  If i > 1
    ReceiveHTTPFile(urls(i), "tmp"+Str(i)+".txt")
    res = ReadFile(1,"tmp"+Str(i)+".txt") 
  ElseIf i = 1
    res = ReadFile(1,"mail_blacklist.txt")       
  Else
    res = ReadFile(1,"own_badlist.txt")   
  EndIf

  If res
    Repeat
      a$=ReadString(1)
      
      ok = #False
      If Left(a$,Len("127.0.0.1"))="127.0.0.1"
        b$=LCase(Trim(Right(a$,Len(a$)-Len("127.0.0.1"))))
        b$=Trim(ReplaceString(b$,Chr(9), " "))
        ok = #True
      EndIf
      If Left(a$,Len("0.0.0.0"))="0.0.0.0"
        b$=LCase(Trim(Right(a$,Len(a$)-Len("0.0.0.0"))))
        b$=Trim(ReplaceString(b$,Chr(9), " "))
        ok = #True
      EndIf   
      If A$= "127.0.0.1 localhost"
        ok = #False
      EndIf
      If ok
        If FindString(b$, "#")
          b$=Trim(Left(b$,FindString(b$, "#")-1))
        EndIf
        If Len(b$)> 0
          ;Debug b$
          add(b$)
          If Left(b$,2)= "*."
            add(Right(b$,Len(b$)-2))
          EndIf  
        EndIf
      EndIf
    Until Eof(1)
    CloseFile(1)
  Else
    DebugOut("File not found!")
  EndIf
Next




DebugOut("-- BEGIN MAKE LIST --")
ListSize = MapSize(badhosts())
DebugOut("SIZE: "+Str(ListSize))
Dim KeyList.s(ListSize)
i = 0
ForEach badhosts()
  KeyList(i) = MapKey(badhosts())
  i+1
Next
DebugOut("SIZE FINAL: "+Str(ListSize))


DebugOut("-- BEGIN WIRTE FILE --")

C$ + "#include <stdio.h>"+#CRLF$
Dim found(255)
For char = 0 To 255
  DebugOut( Str(char)+" "+Chr(char))
  ;found(char) = #False
  If used(char)
    D$ = " char* badhosts"+Str(char)+"[] = { "
    D2$ = ""
    For i = 0 To ListSize-1
      
      key$=KeyList(i)
      If Asc(key$) = char ;Or Asc(MapKey(badhosts())) = '*'  ;* muss überall hinzugefügt werden      
        
        domain.s = getmaindomain(key$)
        badglobal.s = "*." + domain
        If char <> '*' And key$ <> domain And badhosts(badglobal.s)
          ;Domain ignorieren, ES EXISTIERT EINE WEITER GEFASSTE *. DOMAIN!
        Else
          ;found(char) = #True
          D$ + Chr(34)+key$+Chr(34)+", " 
          If cnt = 5
            D$ + #CRLF$
            cnt = 0
          EndIf
          
          If Len(D$) > 2000
            D2$ + D$
            D$= ""
          EndIf
          cnt + 1
        EndIf  
      EndIf
    Next
    ;D$ 
    ;If found(char)
    C$ + #CRLF$ + D2$ + D$ + "NULL};"
    ;EndIf
  EndIf
Next

E$=""
E$ + #CRLF$
E$ + #CRLF$
E$ + #CRLF$
E$ + "char **badhosts[256] = {NULL};"
E$ + #CRLF$
E$ + #CRLF$

E$ + "void initbadhosts(void){"
E$ + #CRLF$
E$ + "  static int isinitalized = 0;" + #CRLF$
E$ + "  if (isinitalized == 0) {"+ #CRLF$
E$ + "    isinitalized = 1;"+ #CRLF$
For char = 0 To 254
  If used(char)
    E$ + "    badhosts["+Str(char)+"] = badhosts"+Str(char)+";" + #CRLF$
  EndIf
Next
E$ + "  }" + #CRLF$
E$ + "}" + #CRLF$

E$ + "int isbadhost2(const char* host, int checkprefix) {" + #CRLF$
E$ + "	initbadhosts();" + #CRLF$
E$ + "	if (host != NULL) {" + #CRLF$
E$ + "			if (strlen(host) > 0) {" + #CRLF$
E$ + "				char **hostlist = badhosts[host[0] & 255];" + #CRLF$
E$ + "				if (checkprefix)" + #CRLF$			
E$ + "					hostlist = badhosts['*' & 255];" + #CRLF$

E$ + "				if (hostlist != NULL) {" + #CRLF$
E$ + "					while (*hostlist != NULL){" + #CRLF$
E$ + "						char *hostfromlist = *hostlist;" + #CRLF$
E$ + "						if (hostfromlist[0] == '*') {" + #CRLF$
E$ + "							if (strlen(host) > strlen(hostfromlist))" + #CRLF$
E$ + "							{" + #CRLF$
E$ + "								if (strcasecmp(host+strlen(host)-strlen(hostfromlist+1), hostfromlist+1) == 0)" + #CRLF$
E$ + "									return 1;" + #CRLF$
E$ + "							}" + #CRLF$
E$ + "						}" + #CRLF$		
E$ + "						if (strcasecmp(host, hostfromlist) == 0)" + #CRLF$
E$ + "							return 1;" + #CRLF$
E$ + "						hostlist++;" + #CRLF$
E$ + "					}" + #CRLF$ 
E$ + "				}" + #CRLF$
E$ + "			}" + #CRLF$
E$ + "	}" + #CRLF$
E$ + "	return 0;" + #CRLF$
E$ + "}" + #CRLF$+ #CRLF$+ #CRLF$

E$ + "int isbadhost(const char* host) {" + #CRLF$
E$ + "	if (isbadhost2(host, 1))" + #CRLF$
E$ + "		return 1;" + #CRLF$		
E$ + "	if (isbadhost2(host, 0))" + #CRLF$
E$ + "		return 1;" + #CRLF$
E$ + "	return 0;" + #CRLF$
E$ + "}" + #CRLF$
C$+E$
CreateFile(1,"badhosts.h")
WriteStringN(1,"//BAD HOSTS - CREATED " + FormatDate("%yyyy-%mm-%dd", Date()))
WriteStringN(1,C$)
CloseFile(1)

;====================================
;Create whitelist for safe searching


size_whitelist = 0
WHITELIST_SAFESEARCH$ = ""
ReadFile(1,"whitelist.txt")
Repeat
  A$=ReadString(1)
  A$=LCase(Trim(A$))
  If A$<>""
    WHITELIST_SAFESEARCH$ + "  ss_whitelist[" + Str(size_whitelist) +"] = (char*)"+Chr(34) + A$ + Chr(34) + ";" + Chr(13)
    WHITELIST_SAFESEARCH$ + "  ss_whitelist2[" + Str(size_whitelist) +"] = (char*)"+Chr(34) + "." + A$ + Chr(34) + ";" + Chr(13)    
    size_whitelist+1
  EndIf
Until Eof(1)
CloseFile(1)
ReadFile(1,"disabled_safebrowsing.txt") ;not in whitelist.txt but no safe browsing... //may contains also tracking/ad pages (NOTE: They should be disabled with DNS blocking!!! Otherwise this is a security hole!!!)
Repeat
  A$=ReadString(1)
  A$=LCase(Trim(A$))
  If A$<>""
    WHITELIST_SAFESEARCH$ + "  ss_whitelist[" + Str(size_whitelist) +"] = (char*)"+Chr(34) + A$ + Chr(34) + ";" + Chr(13)
    WHITELIST_SAFESEARCH$ + "  ss_whitelist2[" + Str(size_whitelist) +"] = (char*)"+Chr(34) + "." + A$ + Chr(34) + ";" + Chr(13)    
    size_whitelist+1
  EndIf
Until Eof(1)
CloseFile(1)

CreateFile(1,"safesearch_ignore.h")
WriteStringN(1,"//SAFE SEARCH WHITELIST - CREATED " + FormatDate("%yyyy-%mm-%dd", Date()))

WriteStringN(1, "#include <stdio.h>")
WriteStringN(1, "#include <string.h>")
WriteStringN(1, "")
WriteStringN(1, "static char* ss_whitelist["+Str(size_whitelist)+"];" )
WriteStringN(1, "static char* ss_whitelist2["+Str(size_whitelist)+"];")

WriteStringN(1, "void init_safesearch_ignore_list(){")
WriteStringN(1, "  static int isinitalized = 0;");
WriteStringN(1, "  if (isinitalized == 0) {")
WriteStringN(1, WHITELIST_SAFESEARCH$)
WriteStringN(1, "  }")
WriteStringN(1, "  isinitalized = 1;")
WriteStringN(1, "}")
WriteStringN(1, "")
WriteStringN(1, "int is_in_safesearch_ignore_list(char * host) {")
WriteStringN(1, "  int i;")
WriteStringN(1, "  for (i = 0; i < " +Str(size_whitelist) + "; i++) {")
WriteStringN(1, "    if (strcasecmp(ss_whitelist[i], host) == 0) return 1;")
WriteStringN(1, "    int host_len  = strlen(host);")
WriteStringN(1, "    int item_len  = strlen(ss_whitelist2[i]);")
WriteStringN(1, "    if (host_len > item_len) {")
WriteStringN(1, "      if (strcasecmp(ss_whitelist2[i], host + (host_len - item_len)) == 0) return 1;")    
WriteStringN(1, "    }")
WriteStringN(1, "  }")
WriteStringN(1, "  return 0;")
WriteStringN(1, "}")
CloseFile(1)
; IDE Options = PureBasic 5.31 (Linux - x64)
; CursorPosition = 287
; FirstLine = 285
; Folding = -
; EnableUnicode
; EnableXP
; Executable = hosts_download_02_09_15
; Debugger = Console