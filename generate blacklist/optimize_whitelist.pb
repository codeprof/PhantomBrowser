Global NewMap whitelist.i()

ReadFile(1,"whitelist.txt")

Repeat
  A$=ReadString(1)
  A$=LCase(Trim(A$))
  If A$<>""
    whitelist(A$) = 1
  EndIf
Until Eof(1)
CloseFile(1)

ForEach whitelist()
  key$= MapKey(whitelist())
  Debug key$
Next

; IDE Options = PureBasic 5.22 LTS Beta 2 (Linux - x64)
; CursorPosition = 5
; EnableUnicode
; EnableXP