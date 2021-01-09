g++ func1.cpp -c -Os
g++ func2.cpp -c -Os
g++ func3.cpp -c -Os
g++ func4.cpp -c -Os
g++ func5.cpp -c -Os
g++ func6.cpp -c -Os
g++ extend.cpp -c -Os
g++ myplot.cpp -c -Os
g++ main.cpp -c -Os
g++ extend.o main.o myplot.o func1.o func2.o func3.o func4.o func5.o func6.o -o MyPlot.exe -Wl,-s -Wl,--stack=16777216 -Os
MyPlot.exe
pause
extend.bat
pause

