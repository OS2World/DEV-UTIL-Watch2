watch.hlp: watch.ipf
           ipfc watch.ipf

watch.obj: watch.c watch.h
           cl -c -W3 -Alfw -G2sw /Zpei watch.c

watch.res: watch.rc watch.ico watch.h watch.dlg
           rc -r watch.rc

watch.exe: watch.obj watch.res watch.l watch.def
           link @watch.l
           rc watch.res
