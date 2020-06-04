# TankWarConsole
TankWar Console game written in c++, by cource NJU AP 2020
# How to build
``` powershell
# under src
make
```
# How to play
``` powershell
# under project root
./TankWar.exe
```
# dependencies
+ so far, only windows support is offered
``` c++
<conio.h>
<sys/timeb.h>
```
+ but I am planning to do a linux version
  + <conio.h> has its linux version, so far so good
  + <sys/timeb.h> is going to be replaced using <chrono>
