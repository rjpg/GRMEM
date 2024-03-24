/* Este programa serve para mostrar a potencialidade  do ficheiro GRMEM.CPP
Made By  (c) X-prog 1997*/
#include "grmem.cpp"
#include <dos.h>
#include <conio.h>
#include "crystal.h"


typedef struct
{int a,b,c,color;double dis;}face;

typedef unsigned char row[320];
row far *screen = (row far *)0xA0000000L; // memoria do ecra real

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




/*------------------------------Z-buffer-------------------------------------*/
void organiza(face *&ord,int n) //Z-buffer
{
int x,i;
face aux;
for(x=0;x<n;x++)
 for(i=x;i<n;i++)
  if (ord[x].dis<ord[i].dis)
   {
   aux=ord[x];
   ord[x]=ord[i];
   ord[i]=aux;
   }
}
/*------------------------------Z-buffer-------------------------------------*/
double zgive(vec3 &a,vec3 &b,vec3 &c,cam &camera)
{
vec3 center,aux;
center.x=(a.x+b.x+c.x)/3;
center.y=(a.y+b.y+c.y)/3;
center.z=(a.z+b.z+c.z)/3;
camera.eyecoord(center,aux);
return aux.z;
}
/*--------------------------------------------------------------------------*/
int main()
{




int modo=GetVideoMode();
SetVideoMode (0x13);  // activar o modo gráfico 320*200-256

int i,j;

	/*-----------------Circulos---------------------------*/
{
cam camera;           // definir uma camera

Dmem jan(100,100);    // área de desenho x:0-99 y:0-99 (0,0) canto inf. esq.

jan.clear(0);         // limpar jan com a cor 0

for (i=0;i<=80;i++)
	{
	circlemem(50,50,i,jan,i+20);  // desenhar círculos na área de desenho jan
	}

for (i=0;i<100;i++)       // passar da área de desenho jan para o ecrã real
   for (j=0;j<100;j++)
	Point (i+0,j+50,jan.mem[i][j]);
getchar();
}
	/*-------------Linhas, pontos e Eixos X,Y,Z--------------*/
{
cam camera;           // definir uma camera

Dmem jan(100,100);    // área de desenho x:0-99 y:0-99 (0,0) canto inf. esq.

jan.clear(0);         // limpar jan com a cor 0

jan.clear(1);         // limpar jan (área de desenho) com a cor 1

linemem (0,0,0,99,jan,13);    // desenhar linhas na área de desenho jan
linemem (0,99,99,99,jan,13);  //       (linhas estas com coord. inteiras
linemem (0,0,99,0,jan,13);    //        e com cor 13)
linemem (99,0,99,99,jan,13);


jan.point(0,99,3);                 // desenhar pontos com a cor 3
jan.point(99,0,3);
jan.point(0,0,3);
jan.point(99,99,3);


vec3 a,b(0,0,0);   // vectores 3D

a=vec3(0,0,10);
linememfit(camera.to2d(a,jan),camera.to2d(b,jan),jan,15);

/* desenha uma linha vista da camera com as coordenadas
   a(0,0,10) b(0,0,0), desenha o eixo Z.

   linememfit (vec a,vec b,Dmem ecra,char cor)
   Esta função desenha linha na área de memória *ecra* com a cor *cor*.
   As coordenadas são do tipo *vec* ou seja não são inteiras (sao float),
   sendo assim tem de ser adaptadas ao tamanho do ecrã.

   vec - Vec e um tipo de dados
	 vec a;
	 a -Vector 2D
	 vec.x -float
	 vec.y -float

   vec3- Vec3 e um tipo de dados
	 vec3 a;
	 a -Vector 3D
	 vec3.x -float
	 vec3.y -float
	 vec3.z -float


   vec camera.to2d(vec3,Dmem)
   --Transformação de coord. tridimensionais para
   coord. bidimensionais atraves da posição da camera.
   O ponto 0,0,0 e o centro da área de memória (Dmem) se o ponto para onde aponta
   a camera, se a origem for (0,0,0).
*/

a=vec3(10,0,0);
linememfit(camera.to2d(a,jan),camera.to2d(b,jan),jan,15);

// a(10,0,0) b(0,0,0), desenha o eixo X.

a=vec3(0,10,0);
linememfit(camera.to2d(a,jan),camera.to2d(b,jan),jan,15);

// a(0,10,0) b(0,0,0), desenha o eixo Y.


for (i=0;i<100;i++)        // passar da área de desenho jan para o ecrã real
      for (j=0;j<100;j++)
	Point (i+110,j+50,jan.mem[j][i]);

getchar();
}
	/*--------------Poligno---------------------------*/
{
cam camera;           // definir uma camera

Dmem jan(100,100);    // área de desenho x:0-99 y:0-99 (0,0) canto inf. esq.

jan.clear(0);         // limpar jan com a cor 0

jan.clear(6);  // limpa jan com a cor 6

int xpoly[6]={20,10,30,40,50,40};
int ypoly[6]={10,30,20,60,30,10};

fillpolimem(xpoly,ypoly,6,jan,10); // enchimento de um polígono com coord. inteiras

for (i=0;i<100;i++)        // passar da área de desenho jan para o ecrã real
      for (j=0;j<100;j++)
	Point (i+220,j+50,jan.mem[j][i]);
getchar();
}
	/*----------------Camera a rodar nos eixos-------------------*/
{
cam camera;           // definir uma camera

Dmem jan(100,100);    // área de desenho x:0-99 y:0-99 (0,0) canto inf. esq.

jan.clear(0);         // limpar jan com a cor 0

int fpx=1,fps=1,s[2],v;
struct  time t;
gettime(&t);

vec3 a,b(0,0,0);   // vectores 3D
int x=0;

while (!kbhit()) // Animação de uma camera a rodar em torno do eixo Z
{
	x++;     // Variável aux.

	jan.clear(0); // limpar jan com cor 0
		      // tenta // antes de jan.clear(0);

	camera.camdef(20,x,45); // actualização das coord. esféricas da camera
	     //    * 20 * distancia da origem do referencial (camera.target)
	     //    * x  *  angulo da camera com o eixo X
	     //    * 45 *  angulo da camera com o eixo Z
	     // tenta camera.camdef(20,x,x); ou
	     // camera.camdef(20,45,x);

	a=vec3(0,0,10);
	linememfit(camera.to2d(a,jan),camera.to2d(b,jan),jan,14);
	a=vec3(10,0,0);
	linememfit(camera.to2d(a,jan),camera.to2d(b,jan),jan,2);
	a=vec3(0,10,0);
	linememfit(camera.to2d(a,jan),camera.to2d(b,jan),jan,4);
	/* desenhar os eixos X,Y,Z. */

	for (i=0;i<100;i++)        // passar da área de desenho jan para o ecrã real
	       memcpy(screen[i+50]+110,jan.mem[i],100);

        	gotoxy (1,23);
		printf ("FPS:%d\n",fpx);
		s[0]=t.ti_sec;
		if (s[0] != s[1])
		{
			fpx=fps;
			fps=0;
		}
		s[1]=t.ti_sec;
		gettime(&t);
		fps ++;



}
}
	/*----------------pirâmide---------------------------*/
{
cam camera;           // definir uma camera


int fpx=1,fps=1,s[2],v;
struct  time t;
gettime(&t);

Dmem jan2(100,100);
int x,i;
getchar();

vec3 piramide[4];
piramide[0]=vec3(-5,0,-5);    // vértices pirâmide triangular
piramide[1]=vec3(5,-5,-5);
piramide[2]=vec3(5,5,-5);
piramide[3]=vec3(0,0,10);

face facesp[4];              // faces da pirâmide
facesp[0].a=0;facesp[0].b=1;facesp[0].c=2;
facesp[1].a=0;facesp[1].b=1;facesp[1].c=3;
facesp[2].a=0;facesp[2].b=2;facesp[2].c=3;
facesp[3].a=1;facesp[3].b=2;facesp[3].c=3;

facesp[0].color=17;           // cor das faces
facesp[1].color=19;
facesp[2].color=21;
facesp[3].color=23;

vec face2d[3];       // vector de faces de 2D para a função fillpolymemfit

camera.dist=14;      // mudar a lente (quanto menor e dist maior e o ang. de visão
		     // tenta camera.dist=8; (que e por defeito) ou menos.

int h;               // V. utilizada para mudar ângulos da camera

while (!kbhit())     // animacao da camera a rodar a volta da pirâmide
{
	h++;            // para rodar mais rápido h+=2;
	camera.camdef(30,h,h);  // tenta camera.camdef(50,h,45);
	jan2.clear(0);
	for(x=0;x<=3;x++)//actualiza a distancia do centro de cada face a camera
		facesp[x].dis=zgive(piramide[facesp[x].a],piramide[facesp[x].b],piramide[facesp[x].c],camera);

	organiza(facesp,4); //organiza as faces de trás para a frente

	for (x=0;x<=3;x++) // projecta as 4 faces da pirâmide
	{
	face2d[0]=camera.to2d(piramide[facesp[x].a],jan2);
	face2d[1]=camera.to2d(piramide[facesp[x].b],jan2);
	face2d[2]=camera.to2d(piramide[facesp[x].c],jan2);
	fillpolymemfit(face2d,3,jan2,facesp[x].color);
	}


	for (i=0;i<100;i+=2)        // passar da área de desenho jan para o ecrã real
	       memcpy(screen[i+50]+110,jan2.mem[i],100);

		gotoxy (1,23);
		printf ("FPS:%d\n",fpx);
		s[0]=t.ti_sec;
		if (s[0] != s[1])
		{
			fpx=fps;
			fps=0;
		}
		s[1]=t.ti_sec;

		gettime(&t);
		fps ++;



}
}
	/*----------------------------------------------*/
	/*----------------pirâmide---------------------------*/
{
cam camera;           // definir uma camera

int fpx=1,fps=1,s[2],v;
struct  time t;
gettime(&t);
Dmem jan2(320,200);
int x,i;
getchar();

vec3 piramide[4];
piramide[0]=vec3(-5,0,-5);    // vértices pirâmide triangular
piramide[1]=vec3(5,-5,-5);
piramide[2]=vec3(5,5,-5);
piramide[3]=vec3(0,0,10);

face facesp[4];              // faces da pirâmide
facesp[0].a=0;facesp[0].b=1;facesp[0].c=2;
facesp[1].a=0;facesp[1].b=1;facesp[1].c=3;
facesp[2].a=0;facesp[2].b=2;facesp[2].c=3;
facesp[3].a=1;facesp[3].b=2;facesp[3].c=3;

facesp[0].color=17;           // cor das faces
facesp[1].color=19;
facesp[2].color=21;
facesp[3].color=23;

vec face2d[3];       // vector de faces de 2D para a função fillpolymemfit

camera.dist=4.8;      // mudar a lente (quanto menor e dist maior e o ang. de visão
		     // tenta camera.dist=8; (que e por defeito) ou menos.

int h2=30,h=30,c=1;               // V. utilizada para mudar ângulos da camera

while (!kbhit())     // animacao da camera a rodar a volta da pirâmide
{
	if(h2>=400) c=-1;if (h2<=20) c=1;
	h2+=2*c;            // para rodar mais rápido h+=2;
        h+=2;  

	camera.camdef(20,h,h);  // tenta camera.camdef(50,h,45);

	jan2.clear(0);

	for(x=0;x<=3;x++)//actualiza a distancia do centro de cada face a camera
		facesp[x].dis=zgive(piramide[facesp[x].a],piramide[facesp[x].b],piramide[facesp[x].c],camera);

	organiza(facesp,4); //organiza as faces de trás para a frente

	for (x=0;x<=3;x++) // projecta as 4 faces da pirâmide
	{
	face2d[0]=camera.to2d(piramide[facesp[x].a],jan2);
	face2d[1]=camera.to2d(piramide[facesp[x].b],jan2);
	face2d[2]=camera.to2d(piramide[facesp[x].c],jan2);
	fillpolymemfit(face2d,3,jan2,facesp[x].color);
	}

		do{                //Respeitar o retra;amento vertical
		v=inportb(0x3DA);
		}while (v & 0x8);

		do {
		v=inportb(0x3DA);
		}while (!(v & 0x8));

	for (i=0;i<200;i++)	// passar da área de desenho jan para o ecrã real
	       memcpy(screen[i],jan2.mem[i],320);
	       /*movmem(screen,jan2.mem,64000);*/

		gotoxy (1,23);
		printf ("FPS:%d\n",fpx);
		s[0]=t.ti_sec;
		if (s[0] != s[1])
		{
			fpx=fps;
			fps=0;
		}
		s[1]=t.ti_sec;
		gettime(&t);
		fps ++;


}
}


/*VT_Abort();*/
/*----------------------------caixa DOB->DATA OBJECT-----------------------*/
SetVideoMode (modo);  // voltar ao modo de vídeo anterior
{

object box("box.dob","caixa");//ler objecto do ficheiro box.dob

printf ("NAME: %s\n",box.name);
printf ("VERTICES: %d ",box.totalV);
printf ("FACES: %d\n",box.totalF);
for(i=0;i<box.totalV;i++)
	printf ("vertice %d <%g,%g,%g>\n",box.vertices[i].number,
		box.vertices[i].vert.x,box.vertices[i].vert.y,box.vertices[i].vert.z);
printf ("face Smooth Material   A   B   C    MapA   MapB   MapC     ab bc ca\n");
for(i=0;i<box.totalF;i++)
printf (" %d    %d     %s     %d   %d   %d    <%g,%g>  <%g,%g>  <%g,%g>    %d  %d  %d\n"
	,i,box.faces[i].smoothgroup,box.faces[i].material,
	box.faces[i].face.a,box.faces[i].face.b,box.faces[i].face.c
	,box.faces[i].map.ma.x,box.faces[i].map.ma.y
	,box.faces[i].map.ma.x,box.faces[i].map.ma.y
	,box.faces[i].map.ma.x,box.faces[i].map.ma.y
	,box.faces[i].ab,box.faces[i].bc,box.faces[i].ca);



getchar();
getchar();

SetVideoMode (0x13);  // activar o modo gráfico 320*200-256
cam camera;
Dmem jan(200,200);
vec T2a,T2b,T2c;
vec3 a,b(0,0,0);   // vectores 3D
int x=0;

jan.clear(1);
camera.camdef(60,50,50);
camera.dist=4;

while (!kbhit())     // animacao da camera a rodar a volta do cubo
{
camera.camdef(30,x++,80);
jan.clear(1);

	a=vec3(0,0,20);
	linememfit(camera.to2d(a,jan),camera.to2d(b,jan),jan,14);
	a=vec3(20,0,0);
	linememfit(camera.to2d(a,jan),camera.to2d(b,jan),jan,2);
	a=vec3(0,20,0);
	linememfit(camera.to2d(a,jan),camera.to2d(b,jan),jan,4);

for (i=0;i<box.totalF;i++)
	{
	T2a=camera.to2d(box.vertices[box.faces[i].face.a].vert,jan);
	T2b=camera.to2d(box.vertices[box.faces[i].face.b].vert,jan);
	T2c=camera.to2d(box.vertices[box.faces[i].face.c].vert,jan);
	linememfit(T2a,T2b,jan,0);
	linememfit(T2b,T2c,jan,0);
	linememfit(T2c,T2a,jan,0);
	}
	for (i=0;i<200;i++)	// passar da área de desenho jan para o ecrã real
	       memcpy(screen[i]+60,jan.mem[i],200);
}

getchar();
}
/*----------------------------tubo DOB->DATA OBJECT-----------------------*/
SetVideoMode (modo);  // voltar ao modo de vídeo anterior
{

object box("tubo.dob","tubo");//ler objecto do ficheiro box.dob

printf ("NAME: %s\n",box.name);
printf ("VERTICES: %d ",box.totalV);
printf ("FACES: %d\n",box.totalF);
for(i=0;i<box.totalV;i++)
	printf ("vertice %d <%g,%g,%g>\n",box.vertices[i].number,
		box.vertices[i].vert.x,box.vertices[i].vert.y,box.vertices[i].vert.z);
printf ("face Smooth Material   A   B   C    MapA   MapB   MapC     ab bc ca\n");
for(i=0;i<box.totalF;i++)
printf (" %d    %d     %s     %d   %d   %d    <%g,%g>  <%g,%g>  <%g,%g>    %d  %d  %d\n"
	,i,box.faces[i].smoothgroup,box.faces[i].material,
	box.faces[i].face.a,box.faces[i].face.b,box.faces[i].face.c
	,box.faces[i].map.ma.x,box.faces[i].map.ma.y
	,box.faces[i].map.ma.x,box.faces[i].map.ma.y
	,box.faces[i].map.ma.x,box.faces[i].map.ma.y
	,box.faces[i].ab,box.faces[i].bc,box.faces[i].ca);



getchar();


SetVideoMode (0x13);  // activar o modo gráfico 320*200-256
cam camera;
Dmem jan(320,200);
vec T2a,T2b,T2c;
vec3 a,b(0,0,0);   // vectores 3D
int x=0;

jan.clear(1);
camera.camdef(90,50,50);
camera.dist=4;
camera.target=vec3(0,0,15);

while (!kbhit())     // animacao da camera a rodar a volta do cubo
{
camera.camdef(45,x++,45);
jan.clear(1);

	a=vec3(0,0,50);
	linememfit(camera.to2d(a,jan),camera.to2d(b,jan),jan,14);
	a=vec3(50,0,0);
	linememfit(camera.to2d(a,jan),camera.to2d(b,jan),jan,2);
	a=vec3(0,50,0);
	linememfit(camera.to2d(a,jan),camera.to2d(b,jan),jan,4);

for (i=0;i<box.totalF;i++)
	{
	T2a=camera.to2d(box.vertices[box.faces[i].face.a].vert,jan);
	T2b=camera.to2d(box.vertices[box.faces[i].face.b].vert,jan);
	T2c=camera.to2d(box.vertices[box.faces[i].face.c].vert,jan);
	if (box.faces[i].ab)
	linememfit(T2a,T2b,jan,15);else linememfit(T2a,T2b,jan,5);
	if (box.faces[i].bc)
	linememfit(T2b,T2c,jan,15);else linememfit(T2b,T2c,jan,5);
	if (box.faces[i].ca)
	linememfit(T2c,T2a,jan,15);else linememfit(T2c,T2a,jan,5);
	}
	for (i=0;i<200;i++)	// passar da área de desenho jan para o ecrã real
	       memcpy(screen[i],jan.mem[i],320);
}

getchar();
}



/*-------------------------------------------------------------------------*/

/*----------------------------x-prog DOB->DATA OBJECT-----------------------*/
SetVideoMode (modo);  // voltar ao modo de vídeo anterior
{

object box("x-prog.dob","tubo");//ler objecto do ficheiro box.dob

printf ("NAME: %s\n",box.name);
printf ("VERTICES: %d ",box.totalV);
printf ("FACES: %d\n",box.totalF);
for(i=0;i<box.totalV;i++)
	printf ("vertice %d <%g,%g,%g>\n",box.vertices[i].number,
		box.vertices[i].vert.x,box.vertices[i].vert.y,box.vertices[i].vert.z);
printf ("face Smooth Material   A   B   C    MapA   MapB   MapC     ab bc ca\n");
for(i=0;i<box.totalF;i++)
printf (" %d    %d     %s     %d   %d   %d    <%g,%g>  <%g,%g>  <%g,%g>    %d  %d  %d\n"
	,i,box.faces[i].smoothgroup,box.faces[i].material,
	box.faces[i].face.a,box.faces[i].face.b,box.faces[i].face.c
	,box.faces[i].map.ma.x,box.faces[i].map.ma.y
	,box.faces[i].map.ma.x,box.faces[i].map.ma.y
	,box.faces[i].map.ma.x,box.faces[i].map.ma.y
	,box.faces[i].ab,box.faces[i].bc,box.faces[i].ca);



getchar();


SetVideoMode (0x13);  // activar o modo gráfico 320*200-256
cam camera;
Dmem jan(320,150);
vec T2a,T2b,T2c;
vec face2d[3];       // vector de faces de 2D para a função fillpolymemfit
int x=45;
face *fz;


fz=new face[box.totalF];
for(i=0;i<box.totalF;i++)
	{
	fz[i].a=box.faces[i].face.a;
	fz[i].b=box.faces[i].face.b;
	fz[i].c=box.faces[i].face.c;
	fz[i].color=i+15;
	}


jan.clear(1);
camera.camdef(90,50,50);
camera.dist=4;
camera.target=vec3(0,0,5);

while (!kbhit())     // animacao da camera a rodar a volta do cubo
{

camera.camdef(330,x+=2,85);
jan.clear(1);


for (i=0;i<box.totalF;i++)
	{
	T2a=camera.to2d(box.vertices[box.faces[i].face.a].vert,jan);
	T2b=camera.to2d(box.vertices[box.faces[i].face.b].vert,jan);
	T2c=camera.to2d(box.vertices[box.faces[i].face.c].vert,jan);
        if (box.faces[i].ab)
	linememfit(T2a,T2b,jan,14); //else linememfit(T2a,T2b,jan,0);
	if (box.faces[i].bc)
	linememfit(T2b,T2c,jan,14); //else linememfit(T2b,T2c,jan,0);
	if (box.faces[i].ca)
	linememfit(T2c,T2a,jan,14); //else linememfit(T2c,T2a,jan,0);
	}
	for (i=0;i<150;i++)	// passar da área de desenho jan para o ecrã real
	       memcpy(screen[i+25],jan.mem[i],320);
}

getchar();
char ch;
int vang=80,d=330;
int fpx=1,fps=1,s[2],v;
struct  time t;

                gotoxy (1,23);
                printf ("PRESS 'q' TO EXIT\n");
                printf ("PRESS '8' TO ROTATE UP '5' FOR DOWN");

 char *Fichier="c:000089kb.mod";    /* Nom du fichier … jouer */
 int port=220;
 char irq=5;
 char dma=1;
 int dev=THE_BEST;

 //USEGUS();
 //USESP();
 USESB();
 //USEDAC();
 //USESPK();
 //USEADL();


 DETECTSND(&dev,&port,&irq,&dma); /* Cherche la meilleur cartes sonore
				    dans les variables d'environnements   */

 FLOADMOD(Fichier);               /* Charge le fichier MOD                */

 SETMOD(1800,dev,port,irq,dma);	  /* Pr‚pare le MOD … 18kHz avec la carte
				    son trouv‚                            */

 STARTMOD();			  /* Commence la musique                  */


while (ch!='q')
{
while (!kbhit())     // animacao da camera a rodar a volta do cubo
{
camera.camdef(d,x+=3,vang);
jan.clear(1);

for(i=0;i<box.totalF;i++)//actualiza a distancia do centro de cada face a camera
	fz[i].dis=zgive(box.vertices[fz[i].a].vert,box.vertices[fz[i].b].vert,box.vertices[fz[i].c].vert,camera);
organiza(fz,box.totalF); //organiza as faces de trás para a frente



for (i=0;i<box.totalF;i++)
	{
        fz[i].color++;
	if (fz[i].dis>0)
		{
		face2d[0]=camera.to2d(box.vertices[fz[i].a].vert,jan);
		face2d[1]=camera.to2d(box.vertices[fz[i].b].vert,jan);
		face2d[2]=camera.to2d(box.vertices[fz[i].c].vert,jan);
		fillpolymemfit(face2d,3,jan,fz[i].color);
		}
	}
for (i=0;i<150;i++)	// passar da área de desenho jan para o ecrã real
       memcpy(screen[i+25],jan.mem[i],320);

                gotoxy (1,2);
                printf ("FPS:%d ",fpx);
		s[0]=t.ti_sec;
		if (s[0] != s[1])
		{
			fpx=fps;
			fps=0;
		}
		s[1]=t.ti_sec;
		gettime(&t);
		fps ++;

}
ch=getch();
switch (ch)
		{
		case '8' : vang--;break;
		case '5' : vang++;break;
                //case '+' : d++;break;
                //case '-' : if (d>10) d--;break;
		}

}

 STOPMOD();                      /* Arrˆte la musique et remet le PC dans
				   son ‚tat initial			  */

 UNLOADMOD();                    /* Rend la m‚moire utilis‚ pour charger
				   le MOD au DOS		          */

delete fz;
getchar();
}



/*-------------------------------------------------------------------------*/



SetVideoMode (modo);  // voltar ao modo de vídeo anterior
printf("                              The End\n\n");
printf("                         Made by X-prog with\n\n");
printf("                        GRMEM (c) 1997 Rui Jorge\n");
printf("                                and\n");
printf("                   CRYSTAL (c) 1995 S‚bastien Granjoux\n\n\n");
return 0;

}
