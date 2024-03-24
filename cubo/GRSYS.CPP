//grsys.cpp
#include <fstream.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include "grsys.h"
const float BIG = 1e30;
int x__max, y__max, foregrcolor, backgrcolor, ncolors,
	ingraphicsmode=0;
float x_min=0, y_min=0,x_max=10, y_max, x_center, y_center,
	r_max, density;

static int outside=0;
ofstream fplot;
static int hpgoutput=0;

static int grbrfun(void)
	{
	to_text(); return 0;
	}

static int txtbrfun(void)
	{
	return 0;
	}

void set_color (int color)
	{
	setcolor (color);
	foregrcolor= color;
	}

void set_backgroundcolor(int color)
	{
	setbkcolor(color);
	backgrcolor=color;
	}

int get_maxcolor(void)
	{
	return getmaxcolor();
	}

inline int plotcoor(float x)
	{
	return int (1000 * (x)+ 0.5);
	}

void set_rgb_palette (int colornr, int R, int G, int B)
	{
	palettetype pal;
	getpalette (&pal);
	setrgbpalette (pal.colors[colornr], R, G, B);
	}

void shaded_colors (void)
	{
	int i, j, red, green, blue;
	if (ncolors!=16) errmess ("no standrs vga in use ");
	ifstream palfile ("palfile.txt");
	if (palfile)
		{
		for (i=0; i<ncolors; i++)
			{
			palfile >>red >>green >>blue;
			if (palfile.fail()) errmess ("incorrect file PALETTE.TXT");
			set_rgb_palette (i, red, green, blue);
			}
		}
	else
		{
		set_rgb_palette(0, 0, 0,63);
		for (i=1;i<ncolors;i++)
			{
			j=4 * i + 3;
			set_rgb_palette (i,j,j,0);
			}

		}
	}


void initgr (char *hpgfile)
	{
	/*int GraphDriver,GraphMode,VGA256,w,h,errorcode;
	VGA256 = installuserdriver("VGA256",NULL);
	GraphDriver = VGA256;
	initgraph ( &GraphDriver, &GraphMode, "" );*/

	int gdriver=EGA, gmode=EGAHI,w,h,errorcode;
	initgraph(&gdriver, &gmode, "c:");

	errorcode = graphresult();
	if (errorcode !=grOk)
		{
		cout << grapherrormsg(errorcode) << endl;
		exit (1);
		}
	ingraphicsmode = 1;
	ctrlbrk(grbrfun);
	ncolors = getmaxcolor() + 1;
	set_rgb_palette (0,0,0,63);
	set_rgb_palette (14,63,63,0);
	set_backgroundcolor(0);
	set_color (14);
	x__max= getmaxx();y__max= getmaxy();
	getaspectratio(&w,&h);
	/*if (w!=h)errmess ("vga usado (square pixes required)");*/
	density= x__max / (x_max-x_min);
	y_max= y_min + y__max/density;
	x_center = 0.5 * (x_min+x_max);
	y_center = 0.5 * (y_min+y_max);
	r_max = (x_center < y_center ? x_center : y_center);
	if (hpgfile)
		{
		fplot.open(hpgfile);
		if (fplot)
			{
			fplot<<"in;spo;sco,10000,0," << plotcoor (y_max-y_min)
			     <<";\n";
			hpgoutput =1;
			}
		}
	}

void to_text (void)
	{
	if (ingraphicsmode)
		{
		closegraph();
		ctrlbrk(txtbrfun);
		ingraphicsmode = 0;
		if (outside)
                        cout << "O desenho podera nao ter sido mostrado correctamente \n"
                                "porque houveram linhas que passaram a area do ecra.\n";
		}
	}


void endgr()
	{
	getch();to_text();
	}

static int IY(float y)
	{
	int Y = y__max -int (density * (y-y_min));
	if (Y<0)
		{
		/*Y=0;*/
		outside=1;
		}
	if (Y>y__max)
		{
		/*Y= y__max;*/
		outside=1;
		}
	return Y;
	}


static int IX(float x)
	{
	int X = x__max -int (density * (x-x_min));
	if (X<0)
		{
		/*X=0;*/
		outside=1;
		}
	if (X>x__max)
		{
		/*X= x__max;*/
		outside=1;
		}
	return X;
	}


int ix (float x) {return IX(x);}
int iy (float y) {return y__max - IY(y);}

void move (float x, float y)
	{
	moveto (IX(x), IY(y));
	if (hpgoutput)
	fplot <<"PU,PA" << plotcoor (x-x_min) << ","
		<< plotcoor (y-y_min) << ";\n";
	}

void text (float x, float y,char *s,char color)
	{
	char auxcolor;
	auxcolor=getcolor();
	setcolor(color);
	outtextxy(IX(x),IY(y),s);
	setcolor(auxcolor);

	}
void draw (float x, float y)
	{
	kbhit();
	lineto (IX(x), IY(y));
	if (hpgoutput)
		fplot <<"PU,PA" << plotcoor (x-x_min) << ","
		<< plotcoor (y-y_min) << ";\n";
	}

void putpix (int x,int y) {putpixel (x,y__max-y,foregrcolor);}

void draw_line (int X1, int Y1, int X2, int Y2)
	{
	kbhit();
	line (X1,y__max-Y1,X2,y__max-Y2);
	}

void horline (int xleft, int xright, int y)
	{
	kbhit();
	line (xleft,y__max-y,xright,y__max-y);
	}

void errmess (char *s)
	{
	if (ingraphicsmode) to_text();
	cout << s << endl;
	exit (1);
	}

void far * far _graphgetmem (unsigned size)
	{
	char *p;
	p=new char[size];
	if (p==NULL)
		{
		cout << "mem";
		exit (1);
		}
	return p;
	}

void far _graphfreemem (void far *ptr, unsigned size)
	{
	delete ptr;
	}
