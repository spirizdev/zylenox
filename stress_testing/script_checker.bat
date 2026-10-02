@echo off
echo One more WA, one step closer to AC.

echo compiling gen...
g++ -std=c++14 gen.cpp -O2 -static -s -o gen -Wl,--stack,66060288
echo done

echo compiling my...
g++ -std=c++14 my.cpp -O2 -static -s -o my -Wl,--stack,66060288
echo done

echo compiling checker...
g++ -std=c++14 checker.cpp -O2 -static -s -o checker -Wl,--stack,66060288
echo done

:loop
set /a cnt+=1
echo Running on test %cnt%...
gen.exe > input.txt
my.exe < input.txt > my.txt
checker.exe

if errorlevel 1 (
    echo WA detected. Keep going!
) else (
    goto loop
)

pause
