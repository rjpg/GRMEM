#include <dos.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <ctype.h>
#include "grsys.h"
#include "d3.h"

ifstream ff("fundo.im");
float d;
char chc;
vec3 target(0,0,0);


/*
void screencoord (vec3 &p, float *px, float *py)
	{
	float x,y;

	perspective (p-target,&x, &y);
	*px=(d*x)+(getmaxx()/2);
	*py=(d*y)+(getmaxy()/2);
	}

void mv (vec3 &p)
	{
	float x,y;
	screencoord (p,&x,&y);
        moveto (x,getmaxy()-y);
	}

void dw (vec3 &p)
	{
	float x,y;
	screencoord(p,&x,&y);
	lineto (x,getmaxy()-y);
	}*/

void screencoord (vec3 &p, float *px, float *py)
	{
	float x,y;

	perspective (p-target,&x, &y);
	*px=d*x+x_center;
	*py=d*y+y_center;
	}

void mv (vec3 &p)
	{
	float x,y;
	screencoord (p,&x,&y);move (x,y);
	}

void dw (vec3 &p)
	{
	float x,y;
	screencoord(p,&x,&y);
	draw (x,y);
	}

int main ()
{
int vp=0;

float rho,theta,phi,pidiv180=atan(1)/45;

char ch,exo,s2[80];
float auxx,auxy;

/*cout <<"distancia de visao de rho = EO:"; cin >> rho;
cout <<"entre com dois angulos em graus.\n";
cout <<"theta, andamento desdo eixo x";
cin >> theta;*/

rho=20;
theta=45;
phi=45;
d=8;
theta*=pidiv180; // radianos
phi*=pidiv180;

/*cout <<"phi, distancia vertical eixo Z:";
cin >> phi;*/


cout<< " distancia por defeito?(s,n)";
cin >> ch; ch=toupper(ch);
if (ch!='S')
	{
	cout <<"distancia:";
	cin >> d;
	}

cout<< " reprsentacao dos eixos?(s,n)";
cin >> exo; exo=toupper(exo);

coeff (rho,theta,phi);

initgr();
if (chc == 'S')
	{
        d=rho*(y_max-y_min)/3.5;
	}
vec3 s(0,0.01,0),a(1,0,0),b(1,1,0),
	c(0,1,0), d(0,0,0),
	e(1,0,1), f(1,1,1),
	g(0,1,1), h(0,0,1),
	x(10,0,0),y(0,10,0),z(0,0,10),o(0,0,0);

while (chc!='q')
{
while (!kbhit())
{


setactivepage(vp);
clearviewport();

sprintf (s2,"Ncolors :%d",getmaxcolor());
outtextxy(1,1,s2);
sprintf (s2,"Max-X :%d",getmaxx());
outtextxy(1,10,s2);
sprintf (s2,"Max-Y :%d",getmaxy());
outtextxy(1,20,s2);
sprintf (s2,"Target :%f,%f,%f",target.x,target.y,target.z);
outtextxy(1,30,s2);
sprintf (s2,"V.point :%f,%f,%f",(rho*sin(phi)*cos(theta))+target.x,
				(rho*sin(phi)*sin(theta))+target.y,
				(rho*cos(phi))+target.z);
outtextxy(1,40,s2);

/*text(2,10,s2,3);*/

mv(a); dw(b);dw(c);dw(g);
dw(h); dw(e);dw(a);mv(b);
dw(f); dw(g);mv(f);dw(e);
mv(a); dw(d);dw(c);mv(d);dw(h);

if (exo == 'S')
{
mv(o); dw(x);
screencoord(x,&auxx,&auxy);
text(auxx,auxy,"x",3);
mv(o); dw(y);
screencoord(y,&auxx,&auxy);
text(auxx,auxy,"y",4);
mv(o); dw(z);
screencoord(z,&auxx,&auxy);
text(auxx,auxy,"z",5);
}
move(10,10);draw(x_max,y_max);
setvisualpage(vp);
if (vp==0) vp=1; else vp=0;
}

chc = getche();
	if (chc=='+') rho++;
	if (chc=='-') rho--;
	if (chc=='4') theta+=0.1;
	if (chc=='6') theta-=0.1;
	if (chc=='5') phi+=0.1;
	if (chc=='8') phi-=0.1;
	if (chc=='m')
	{
	h=h+s;
	g=g+s;
	f=f+s;
	e=e+s;
	d=d+s;
	c=c+s;
	b=b+s;
	a=a+s;
	}
	if (chc=='n') target=target+s;

coeff (rho,theta,phi);
}
endgr();
if (ch=='S')
	{
	cout << "a distancia do ecra era:8" ;
	}
cout << "\n\nmade by rui Jorge Pereira Goncalves\n"
     << "isto e um teste de programacao num ambiente 3D\n"
     << "futuramente sera feito um jogo tridimencional\n"
     << "por X-prog  claro !!";

return 0;
}
