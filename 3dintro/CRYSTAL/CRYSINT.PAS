{**************************************************************************}
{*   Cette unit‚ comprend les fonctions internes de crystal. Normalement  *}
{*   vous n'avez pas utiliser directement ces fonctions.                  *}
{*   Toutefois pour eviter un appel inutile … MAKEMOD par exemple vous    *}
{*   pouvez utiliser directement le fonctions du premier blocs.           *}
{*                                                                        *}
{* Programm‚ par S‚bastien Granjoux                                       *}
{* Commenc‚ le 01/06/93                                                   *}
{* Modification le 18/03/95                                               *}

UNIT CRYSINT;

INTERFACE

FUNCTION SETMOD(frequence,device,port:WORD;irq,dma:BYTE):INTEGER;
PROCEDURE MAKEMOD;
PROCEDURE STARTMOD;
PROCEDURE STOPMOD;
FUNCTION DETECTSND(VAR device,port:WORD;VAR irq,dma:BYTE):INTEGER;
PROCEDURE CHANGEVOL(newvol:BYTE);
PROCEDURE SETMODPOS(newpos:WORD);
FUNCTION GETMODPOS:WORD;
PROCEDURE SETMODCALL(number:BYTE;handler:POINTER);
FUNCTION USEGUS:INTEGER;
FUNCTION USESPK:INTEGER;
FUNCTION USEDAC:INTEGER;
FUNCTION USEADL:INTEGER;
FUNCTION USESB:INTEGER;
FUNCTION USESP:INTEGER;

{ Les fonctions suivantes sont en fait des donn‚es utilis‚es par les deux    }
{ unit‚es. Il y a a priori aucune raison pour que vous les utilisiez.        }

PROCEDURE TEMPO;
PROCEDURE BPM;
PROCEDURE NBVOICE;
PROCEDURE INSTRUMENT1;
PROCEDURE PATTERNSEG;
PROCEDURE SEQUENCE;
PROCEDURE COMMENTS;
PROCEDURE LASTPOS;

{ Ceci est une vrai fonction interne … Crystal Player                        }

PROCEDURE RESETMOD;

IMPLEMENTATION

{$L CRYS260.OBJ}
{$L CRYSDEV.OBJ}
{$L GUS.OBJ}
{$L SNDBLAST.OBJ}
{$L SNDPRO.OBJ}
{$L DAC.OBJ}
{$L SPEAKER.OBJ}
{$L ADLIB.OBJ}
FUNCTION SETMOD(frequence,device,port:WORD;irq,dma:BYTE):INTEGER;EXTERNAL;
PROCEDURE MAKEMOD;EXTERNAL;
PROCEDURE STARTMOD;EXTERNAL;
PROCEDURE STOPMOD;EXTERNAL;
FUNCTION DETECTSND(VAR device,port:WORD;VAR irq,dma:BYTE):INTEGER;EXTERNAL;
PROCEDURE CHANGEVOL(newvol:BYTE);EXTERNAL;
PROCEDURE SETMODPOS(newpos:WORD);EXTERNAL;
FUNCTION GETMODPOS:WORD;EXTERNAL;
PROCEDURE SETMODCALL(number:BYTE;handler:POINTER);EXTERNAL;
FUNCTION USESPK:INTEGER;EXTERNAL;
FUNCTION USEGUS:INTEGER;EXTERNAL;
FUNCTION USEDAC:INTEGER;EXTERNAL;
FUNCTION USESB:INTEGER;EXTERNAL;
FUNCTION USEADL:INTEGER;EXTERNAL;
FUNCTION USESP:INTEGER;EXTERNAL;

PROCEDURE TEMPO;EXTERNAL;
PROCEDURE BPM;EXTERNAL;
PROCEDURE NBVOICE;EXTERNAL;
PROCEDURE INSTRUMENT1;EXTERNAL;
PROCEDURE PATTERNSEG;EXTERNAL;
PROCEDURE SEQUENCE;EXTERNAL;
PROCEDURE COMMENTS;EXTERNAL;
PROCEDURE LASTPOS;EXTERNAL;
PROCEDURE RESETMOD;EXTERNAL;

END.

