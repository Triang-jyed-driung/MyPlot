@echo off
echo ��ʾ�������ܣ�
pause
Myplot.exe
func1.bmp
func2.bmp
func3.bmp
func4.bmp
func5.bmp
func6.bmp
echo ��ʾ��չ���ܣ�
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

