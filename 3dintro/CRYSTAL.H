/***************************************************************************
/*	Fichier D'ent�te permettant l'utilisation de la librairie          *
/*	CRYSTAL.LIB.                                                       *
/*                                                                         *
/* Programm� par S�bastien Granjoux                                        *
/* Commenc� le 18/03/95                                                    *
/* Modification le 10/05/95                                                */
#if __STDC__
#define _Cdecl
#else
#define _Cdecl	cdecl
#endif

#ifndef __PAS__
#define _CType _Cdecl
#else
#define _CType pascal
#endif

#ifndef _STDDEF
#define _STDDEF
#ifndef _PTRDIFF_T
#define _PTRDIFF_T
#if	defined(__LARGE__) || defined(__HUGE__) || defined(__COMPACT__)
typedef long	ptrdiff_t;
#else
typedef int	ptrdiff_t;
#endif
#endif
#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif
#endif

#ifndef NULL
#if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
#define NULL	0
#else
#define NULL	0L
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif
int far pascal SETMOD(unsigned int frequence,int device,int port,char irq,char dma);
int far pascal FLOADMOD(char far *filename);
int far pascal MLOADMOD(char far *adress);
int far pascal OLOADMOD(long int position);
int far pascal DETECTSND(int far *device,int far *port,char far *irq,char far *dma);
void far pascal CHANGEVOL(unsigned char newvol);
void far pascal SETMODPOS(unsigned int newpos);
int far pascal GETMODPOS();
void far pascal SETMODCALL(unsigned char number,void (*handler)(void));
void far pascal UNLOADMOD();
void far pascal STARTMOD();
void far pascal MAKEMOD();
void far pascal STOPMOD();
int far pascal USEGUS();
int far pascal USESPK();
int far pascal USEDAC();
int far pascal USEADL();
int far pascal USESB();
int far pascal USESP();
#ifdef __cplusplus
}
#endif

#define	THE_BEST	0
#define	PC_SPEAKER	1
#define	DAC_ON_LPT	2
#define	SOUNDBLASTER	3
#define GUS		4
#define	SOUNDPRO	5
#define	ADLIB		6
#define NO_DEVICE	7


