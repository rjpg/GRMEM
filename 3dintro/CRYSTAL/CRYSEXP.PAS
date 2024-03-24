{**************************************************************************}
{*   Voici un petit programme d'exemple d'int‚gration de mes routines     *}
{*   dans un programme en pascal.                                         *}
{*              							  *}
{*   L'ordre d'appel des fonctions est important.                         *}
{*									  *}
{* Programm‚ par S‚bastien Granjoux                                       *}
{* Commenc‚ le 06/01/93                                                   *}
{* Modification le 25/10/94						  *}

PROGRAM CRYSEXP;

{$M 4096,0,8192} { Comme mes routines se chargent seules d'allouer la place
		   m‚moire n‚cessaire au chargement du MOD, il faut leur
		   laisser de la place.                                     }


Uses CRYSTAL;    { Utilise l'unit‚                                          }

VAR
   Fichier:STRING;
   Test:INTEGER;
   Irq,Dma:BYTE;
   Device,Dport:WORD;

BEGIN

  Test:=USEGUS;                   { Choisit les cartes sonores utilisables  }
  Test:=USESP;
  Test:=USESB;
  Test:=USEDAC;
  Test:=USESPK;
  Test:=USEADL;

  Fichier:='c:patega.mod'+chr(0);  { J'utilise la convention du C qui est
				     diff‚rentes de celle du pascal pour
				     la repr‚sentation des chaines de
				     de caractŠres. Elles doivent se
				     terminer par 0 et commencer au
				     premier caractŠre.                    }

  Dport:=0;
  Irq:=0;
  Dma:=0;
  Device:=THE_BEST;

  Test:=DETECTSND(Device,Dport,Irq,Dma); { Cherche la meilleur cartes sonore
				           dans les variables
                                           d'environnements  }

  Test:=FLOADMOD(Addr(Fichier[1]));   { Charge le MOD. Le nom est pass‚ sous
				       la forme d'une chaine C              }

  Test:=SETMOD(1800,Device,Dport,Irq,Dma); { Prepare la MOD … 18kHz avec la
					    carte son trouv‚                }

  STARTMOD;			      { Commence la musique		    }

  { A partir de ce moment la musique commence … jouer, si vous ne voulez pas
   la d‚grader (surtout avec le PC speaker) ‚vit‚ de bloquer les
   interruptions                                                            }

   REPEAT
   BEGIN
	;                             { Ici vous pouvez appeler MAKEMOD     }
   END
   UNTIL PORT[$60]<$80;               { Beaucoup plus rapide qu'une fonction
				       du genre de keypress et donc meilleur
				       pour la qualit‚ de la musique	    }

   STOPMOD;         		      { Arrˆte la musique et remet le PC dans
				       son ‚tat initial			    }

   UNLOADMOD;          		      { Rend la m‚moire utilis‚ pour charger
				       le MOD au DOS		           }

END.
