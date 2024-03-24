/**************************************************************************/
/*   Voici un petit programme d'exemple d'int‚gration de mes routines     */
/*   dans un programme C.                                                 */
/*              							  */
/*   Attention comme la routine de chargement du MOD se charge d'allouer  */
/*   elle mˆme la m‚moire dont elle a besoin,il ne faut pas que le tas    */
/*   occupe toutes la m‚moire disponible. (compiler en SMALL). Deplus     */
/*   l'orde d'appel des fonction est importants.	                  */
/*									  */
/* Programm‚ par S‚bastien Granjoux                                       */
/* Commenc‚ le 30/12/93                                                   */
/* Modification le 10/05/95						  */

#include <dos.h>
#include "crystal.h"

void main()
{
 char *Fichier="c:afterthe.mod";    /* Nom du fichier … jouer */
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

 /* A partir de ce moment la musique commence … jouer, si vous ne voulez pas
   la d‚grader (surtout avec le PC speaker) ‚vit‚ de bloquer les
   interruptions                                                          */

 do
 {
				 /* Ici vous pouvez appeler MAKEMOD       */
 }while(inportb(0x60)>=0x80);    /* Beaucoup plus rapide qu'une fonction
				   du genre de kbhit() et donc meilleur
				   pour la qualit‚ de la musique	  */

 STOPMOD();                      /* Arrˆte la musique et remet le PC dans
                                   son ‚tat initial                       */

 UNLOADMOD();                    /* Rend la m‚moire utilis‚ pour charger
                                   le MOD au DOS                          */

}
