cls

del *.exe

g++ -mwindows -m64 -static -Wall -Wextra InputBoxApp.cpp InputBox.cpp Registry.cpp -o InputBoxApp.exe
