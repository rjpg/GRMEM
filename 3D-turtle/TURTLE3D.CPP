#include <conio.h>
#include "grmem.cpp"
#include <dos.h>

typedef unsigned char row[320];
row far *screen = (row far *)0xA0000000L; // memoria do ecra real

void circle3d (vec3 &center,double raio,char color,cam &camera,Dmem &drawmem)
{
        vec3 a,b;
        camera.eyecoord(center-camera.target,a);
	if (a.z>0.0001)
	{
		b=a;
		b.x+=raio;
		float af,bf,cf;
		af=camera.dist*(a.x/a.z);
		bf=camera.dist*(b.x/b.z);
		cf=bf-af;
		int raiofinal=drawmem.IX(cf);
		vec center2d=camera.to2d(center,drawmem);
		circlememfit(center2d,raiofinal,drawmem,color);
	}
}

void line3d(vec3 &a3,vec3 &b3,char color,cam &camera,Dmem &drawmem)
{
vec3 a,b;
camera.eyecoord (a3-camera.target, a);
camera.eyecoord (b3-camera.target, b);
if (a.z>0.0001 && b.z>0.0001)
	{
	vec a=camera.to2d(a3,drawmem);
	vec b=camera.to2d(b3,drawmem);
	linememfit(a,b,drawmem,color);
	}
}

vec3 Cfront (cam &c,double numb)
{
	c.target.x +=numb*(sin (c.phi) * cos (c.theta));
	c.target.y +=numb*(sin (c.phi) * sin (c.theta));
	c.target.z +=numb*(cos (c.phi));
	return c.target;

}

void grid (double espa,int n,char xactive,char yactive,char zactive,char color,
                cam &camera,Dmem &drawmem)
{
        int x;
        vec3 a(0,0,0),b;
        if (xactive)
                {
                b=vec3(espa*n,0,0);
                for (x=0;x<n;x++)
                        {
                        line3d(a,b,color,camera,drawmem);
                        a.z+=espa;
                        b.z+=espa;
                        }
                b=vec3(0,0,0);
                for (x=0;x<n;x++)
                        {
                        line3d(a,b,color,camera,drawmem);
                        a.x+=espa;
                        b.x+=espa;
                        }
               
                }
        a=vec3(0,0,0);
        if (yactive)
                {
                b=vec3(0,espa*n,0);
                for (x=0;x<n;x++)
                        {
                        line3d(a,b,color,camera,drawmem);
                        a.z+=espa;
                        b.z+=espa;
                        }
                b=vec3(0,0,0);
                for (x=0;x<n;x++)
                        {
                        line3d(a,b,color,camera,drawmem);
                        a.y+=espa;
                        b.y+=espa;
                        }
               
                }
        a=vec3(0,0,0);
        if (zactive)
                {
                b=vec3(espa*n,0,0);
                for (x=0;x<n;x++)
                        {
                        line3d(a,b,color,camera,drawmem);
                        a.y+=espa;
                        b.y+=espa;
                        }
                b=vec3(0,0,0);
                for (x=0;x<n;x++)
                        {
                        line3d(a,b,color,camera,drawmem);
                        a.x+=espa;
                        b.x+=espa;
                        }
               
                }



}


//#define RADTODEG (180./M_PI)
class turtle
	{
	private:
                double xdelta, ydelta, zdelta;
                double Hang, Vang ;
	protected:
                double x, y, z;
                int col, pen;
	public:
		turtle ();
		turtle (int color);
                ~turtle ();
		void reset ();
                void fw3d (double len,cam &c,Dmem &d);
                void fw3dvirtual (int len,cam &c,Dmem &d);
                void lt (double ang);
                void rt (double ang);
                void ut (double ang);
                void dt (double ang);
		void penup ();
		void pendn ();
		int nwcolor (int nwcol);
		void nwcoord(vec3 &a);
		friend void liga(turtle &a,turtle &b,char color,cam &camera,Dmem &Draw);
                };
	turtle :: turtle ()
		{
		reset ();
                col = 15;
		}
	turtle :: turtle (int color)
		{
		reset ();
		col = color;
		}
	turtle :: ~turtle ()
		{}
	void turtle :: reset ()
		{
                x =0.;y = 0.;z = 0.;
                ydelta = 0.;
                xdelta = 1.;
                zdelta = 0.;
                pen = Hang =0.;
                Vang = 90.;
		}
        void turtle :: fw3d (double len,cam &c,Dmem &d)
		{
                vec3 a(x,y,z);
                x += (double) len *xdelta;
                y += (double) len *ydelta;
                z += (double) len *zdelta;
                vec3 b(x,y,z);

                circle3d(a,2.,3,c,d);
		if (pen)
                     line3d (a,b,col,c,d); //opcional
                }

        void turtle :: fw3dvirtual (int len,cam &c,Dmem &d)
		{
                vec3 a(x,y,z),b;
                (b.x += (double) len *xdelta);
                (b.y += (double) len *ydelta);
                (b.z += (double) len *zdelta);

		if (pen)
                     line3d (a,b,col,c,d); //opcional
                 }
        void turtle :: lt (double ang)
	{
        Hang += ang;
        xdelta =(sin (Vang*pidiv180) * cos (Hang *pidiv180));
        ydelta =(sin (Vang*pidiv180) * sin (Hang *pidiv180));
        zdelta =(cos (Vang*pidiv180));
	}
        inline void turtle :: rt (double ang)
	{
	lt (-ang);
	}

        void turtle :: dt (double ang)
	{
        Vang += ang;
        xdelta =(sin (Vang*pidiv180) * cos (Hang *pidiv180));
        ydelta =(sin (Vang*pidiv180) * sin (Hang *pidiv180));
        zdelta =(cos (Vang*pidiv180));
	}
        inline void turtle :: ut (double ang)
	{
        dt (-ang);
	}

	int turtle :: nwcolor (int nwcolor)
		{
		int oldc = col;
		if (nwcolor)
			col = nwcolor;
		return oldc;
		}
	void turtle :: penup ()
		{
		pen = 0;
		}
	void turtle :: pendn ()
		{
		pen =1;
                }
        void turtle :: nwcoord(vec3 &a)
                {
                x=a.x;
                y=a.y;
                z=a.z;
		}
	void liga(turtle &a,turtle &b,char color,cam &camera,Dmem &Draw)
	{
	vec3 va(a.x,a.y,a.z);
	vec3 vb(b.x,b.y,b.z);
	line3d (va,vb,color,camera,Draw);
	}

void SetVideoMode(int mode)   // activar o modo de vídeo
{
    _AH = 0x00;
    _AL = mode;
    geninterrupt(0x10);
}
int GetVideoMode(void)        // obter o modo de vídeo
{
    _AH = 0x0F;
    geninterrupt(0x10);

    return _AL;
}

void Point(int x, int y, int color) // por um ponto no ecrã real
{                                   // origem no canto sup. esq.
    screen[y][x] = color;
}

void t1(cam &camera,Dmem &drawmem) // esta fun‡Æo ‚ um exemplo
{
vec3 Torig(100,100,0);
turtle a(14),b(13);
a.pendn();
b.pendn();
int x,i;
b.ut(30);
b.lt(180);
a.ut(30);
b.nwcoord(Torig);
a.nwcoord(Torig+vec3(15,-75,0));
for (x=0;x<60;x++)
	{
	liga(a,b,4,camera,drawmem);
	b.lt(20);
	b.fw3d(15,camera,drawmem);
	a.lt(20);
	a.fw3d(15,camera,drawmem);

//	a.ut(x);
//	a.fw3d(1,camera,drawmem);
//	b.ut(x);
//	b.fw3d(1,camera,drawmem);

        }

}

void main (void)
{
int modo=GetVideoMode();
SetVideoMode (0x13);  // activar o modo gráfico 320*200-256

cam camera1;
Dmem draw1(320,190);
int dist=20,VCang=45,HCang=45;
camera1.camdef(dist,HCang,VCang);
vec3 targetC1(200,200,200);
int i,x,gridn=10,xgrid=1,ygrid=1,zgrid=1;
char tecla=0;
while (tecla != 's')
{
while (!kbhit())
	{

        draw1.clear(1);

        circle3d(camera1.target,2.,3,camera1,draw1);

	grid (10.,gridn,xgrid,ygrid,zgrid,0,camera1,draw1);

	t1(camera1,draw1);

	for (x=0;x<190;x++)     // passar da área de desenho jan para o ecrã real
	       memcpy(screen[x+10],draw1.mem[x],320);

        }
	tecla = getch();
	switch (tecla)
		{
		case '1' : targetC1=Cfront (camera1,5.); break;
		case '0' : targetC1=Cfront (camera1,-5.); break;

		case '8' : VCang--;break;
                case '5' : VCang++;break;
		case '4' : HCang++;break;
		case '6' : HCang--;break;

		case '+' : dist-=5;break;
		case '-' : dist+=5;break;
                case '/' : gridn++;break;
                case '*' : gridn--;break;

                case 'z' : if (xgrid==0)xgrid=1;else xgrid=0;break;
                case 'x' : if (ygrid==0)ygrid=1;else ygrid=0;break;
                case 'c' : if (zgrid==0)zgrid=1;else zgrid=0;break;

                case 'u' : targetC1.x+=10.;break;
                case 'j' : targetC1.x-=10.;break;
                case 'i' : targetC1.y+=10.;break;
                case 'k' : targetC1.y-=10.;break;
                case 'o' : targetC1.z+=10.;break;
                case 'l' : targetC1.z-=10.;break;
		}
        camera1.camdef(dist,HCang,VCang);
	camera1.target=targetC1;
	gotoxy(1,1);
        printf("T:%f,%f,%f\n",targetC1.x,targetC1.y,targetC1.z);


}


getchar();
SetVideoMode (modo);
}
