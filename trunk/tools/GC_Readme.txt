About GreatCode
---------------

GreatCode is a source code formatting tool. All AXE code use it with the configuration file "GC.cfg" located in this directory.

Visit it's homepage at http://perso.club-internet.fr/cbeaudet

Make sure to read axe/docs/coding_style.txt

Installation
------------
In DevStudio 7:

        1/ Menu Tools/Customize.
        2/ Select the "Tool" tab.
        3/ Add GC as a new tool.

        Command:                C:\axe\tools\GC.exe    (example)
        Arguments:              -file-"$(ItemPath)"
        Initial directory:      C:\axe\tools\GC        (example)

        You can then associate a shortkey to that tool :

        1/ Menu Tools/Customize/Keyboard
        2/ Category Tools
        3/ Command UserTool<num> where num is the rank of GC in the external
           tool list.
        4/ And then choose a keyboard shortcut.

        If you don't want a message box each time you press the shortcut :

        1/ Menu Tools/Options.
        2/ Select the "Editor" tab.
        3/ "Automatic reload of externally modified files" must be ON.

Known Issues
------------
GreatCode have some drwback. What I have found:

- If you init n array in the style of
  int a[3] = {0,1,2};
  GC will break it in 
  int a[5];
  int 0;
  int 1;
  int 2;
  
  To avoid this you have 2 options:
  int a[0] = 0;
  int a[1] = 1;
  int a[2] = 2;
  
  or
  
  /$off*/
  int a[3] = {0,1,2};
  /$on*/
  
- GC does not work weel with assembler:
  xor eax, 200000h
  GC will translate it to
  xor eax, 200000 h
  
  Just use /$off*/ assembler code here /$on*/
        
Special thanks
--------------
Thanks to Christophe Beaudet fot this great Tool.

$Id: GC_Readme.txt,v 1.1 2004/05/02 16:32:32 doneval Exp $