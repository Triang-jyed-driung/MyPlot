@echo off
echo 演示基本功能：
pause
Myplot.exe
func1.bmp
func2.bmp
func3.bmp
func4.bmp
func5.bmp
func6.bmp
echo 演示拓展功能：
pause
Myplot.exe plot2D < 2d.txt
custom.bmp
pause
Myplot.exe plotPara < para.txt
custom.bmp
pause
Myplot.exe plot3D < 3d.txt
custom.bmp
pause

