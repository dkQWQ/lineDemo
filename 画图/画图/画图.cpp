// 画图.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
using namespace std;
struct Point {
	int x, y;
	Point()
	{
		x = -1;
		y = -1;
	}
	Point(int xx, int yy)
	{
		x = xx;
		y = yy;
	}
};
struct lineTool 
{
	int size;
	COLORREF color;
	Point begin;
	bool isdown;
	lineTool() {

	}
	lineTool(int linesize, COLORREF linecolor) {
		size = linesize;
		color = linecolor;
		isdown = false;
	}
	void callMouse(MOUSEMSG m)
	{
		if (m.uMsg == WM_LBUTTONDOWN){
			isdown= true;
			begin = Point(m.x, m.y);
		}
		if (m.uMsg == WM_LBUTTONUP) {
			isdown = false;
		}
		if (m.uMsg == WM_MOUSEMOVE && isdown) {
			setlinestyle(PS_ENDCAP_ROUND, size);
			setlinecolor(color);
			line(begin.x, begin.y, m.x, m.y);
		}
		begin = Point(m.x, m.y);
		if (m.uMsg == WM_RBUTTONDOWN) {
			setbkcolor(WHITE);
			cleardevice();
		}
	}
};
int main()
{
	initgraph(800, 600);
	setbkcolor(WHITE);
	cleardevice();
	lineTool *pline = new lineTool(5, RED);
	while (1) {
		while (MouseHit()) {
			MOUSEMSG m =  GetMouseMsg();
			pline->callMouse(m);
		}
		if (_kbhit())
		{
			char userkey = _getch();
			if (userkey == '+') {
				pline->size++;
			}
			if (userkey == '-') {
				pline->size--;
			}
			if (userkey == '\r') {
				saveimage(_T("1.bmp"));
				break;
			}
		}
	}
	delete pline;
	pline = NULL;
	_getch();
	closegraph();
	return 0;
}