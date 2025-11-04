cls

del *.exe

windres InputBoxResource.rc -o InputBoxResource.o

g++ -mwindows -m64 -static -Wall -Wextra InputBoxApp.cpp InputBoxDialog.cpp InputBoxResource.o -o InputBoxApp.exe
