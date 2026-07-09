# VC6 makefile

C_FLAGS = /c /O2 /nologo /W3 /WX /MD
LD_FLAGS = /FILEALIGN:512 /NOLOGO /RELEASE

utf-8-bom-remover.exe: main.obj makefile
    link main.obj $(LD_FLAGS) /OUT:utf-8-bom-remover.exe

lib-utf-8-bom-remover.dll: main-lib.obj makefile
    link main-lib.obj $(LD_FLAGS) /DLL /OUT:utf-8-bom-remover.dll

main.obj: main.c makefile
	cl $(C_FLAGS) main.c

main-lib.obj: main.c makefile
	cl $(C_FLAGS) main-lib.c
