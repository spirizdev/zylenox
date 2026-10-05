@echo off
set "PATH=C:\Program Files\CodeBlocks\MinGW\bin;%PATH%"

echo One more WA, one step closer to AC.

echo compiling gen...
g++ -std=c++14 gen.cpp -O2 -static -s -o gen -Wl,--stack,66060288
echo done

echo compiling my...
g++ -std=c++14 my.cpp -O2 -static -s -o my -Wl,--stack,66060288
echo done

echo compiling correct...
g++ -std=c++14 correct.cpp -O2 -static -s -o correct -Wl,--stack,66060288
echo done

:loop
set /a cnt+=1
echo Running on test %cnt%...
gen.exe > input.txt
my.exe < input.txt > my.txt
correct.exe < input.txt > correct.txt

fc my.txt correct.txt > nul
if errorlevel 1 (
    echo WA detected. Keep going!
) else (
    goto loop
)

pause
