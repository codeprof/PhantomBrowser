

A$="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_#!+?$%~"
B$="8a~$6uJ+Vdjgx01DozBO2fs4SvXF_#ArH59MTY%ipqnQRWew!lyZGULm7tCEhKP?3NIcbk"


S$=InputRequester("Passwort","Passwort eingeben","")
R$="µ"
For t=1 To Len(S$)
  p = FindString(B$,Mid(S$,t,1))
  If p > 0
    R$+Mid(A$,p,1)
  Else
    R$+Mid(S$,t,1)
  EndIf
Next

InputRequester("Passwort","Kodiertes Passwort",R$)



; IDE Options = PureBasic 5.22 LTS Beta 2 (Linux - x64)
; CursorPosition = 7
; EnableUnicode
; EnableXP