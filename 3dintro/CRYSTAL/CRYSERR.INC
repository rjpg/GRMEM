;***************************************************************************
;*	Ce fichier contient les code d'erreurs renvoy‚ par les fonctions
;*	du player

IDEAL

NO_ERROR	EQU	0
FALSE_DISTANCE	EQU	1	; Code d'erreur DOS pouvant ˆtre renvoy‚
FILE_NOT_FOUND	EQU	2	; par les diff‚rentes fonctions
PATH_NOT_FOUND	EQU	3
NO_FREE_HANDLE	EQU	4
ACCES_DENIED	EQU	5
FILE_NOT_OPEN	EQU	6
MEM_BLK_DESTROY	EQU	7
NOT_ENOUGH_MEM	EQU	8
ILLEGAL_MEM_BLK EQU	9

TOO_MANY_PAT	EQU	257     ; Codes particuliers … Crystal Player
TOO_BIG_SAMP	EQU	258
DAC_NOT_FOUND	EQU	259
SB_NOT_FOUND 	EQU     260
GUS_NOT_FOUND	EQU	261
NOT_ENOUGH_GUS	EQU	262
DRV_NOT_FOUND	EQU	263
NO_VOICE	EQU	264
DEV_NOT_FOUND	EQU	265
ADL_NOT_FOUND	EQU	266
TOO_MANY_DEV	EQU	267
BAD_ARG		EQU	268

IFDEF DEBUG
IF DEBUG

GLOBAL	writelong:far

;**************************************************************************
;*	Afficher de 1 … 4 nombre … l'ecran

MACRO	sign	A,B,C,D

pushad

IFNB <D>
	mov	dh,A
	mov	dl,B
	shl	edx,16
	mov	dh,C
	mov	dl,D
ELSEIFNB <C>
  IF SYMTYPE A EQ 2
	mov	dx,A
	shl	edx,16
	mov	dh,B
	mov	dl,C
  ELSEIF SYMTYPE B EQ 2
	mov	dh,A
	shl	edx,8
	mov	dx,B
	shl	edx,8
	mov	dl,C
  ELSEIF SYMTYPE C EQ 2
	mov	dh,A
	mov	dl,B
	shl	edx,16
	mov	dx,C
  ELSE
	mov	dl,A
	shl	edx,16
	mov	dh,B
	mov	dl,C
	shl	edx,8
	shr	edx,8
  ENDIF
ELSEIFNB <B>
  IF SYMTYPE A EQ 2
    IF SYMTYPE B EQ 2
	mov	dx,A
	shl	edx,16
	mov	dx,B
    ELSE
	mov	dx,A
	shl	edx,8
	mov	dl,B
	shl	edx,8
	shr	edx,8
    ENDIF
  ELSE
    IF SYMTYPE B EQ 2
	mov	dl,A
	shl	edx,8
	mov	dx,B
	shl	edx,8
	shr	edx,8
    ELSE
	mov	dh,A
	mov	dl,B
	shl	edx,16
	shr	edx,16
    ENDIF
  ENDIF
ELSEIFNB <A>
  IF SYMTYPE A EQ 2
	mov	dx,A
	shl	edx,16
	shr	edx,16
  ELSEIF SYMTYPE A EQ 1
	mov	dl,A
	shl	edx,24
	shr	edx,24
  ELSEIF
	mov	edx,A
  ENDIF
ENDIF
  call	writelong
  popad
ENDM
ELSE
  MACRO sign	A,B,C,D
	nop
  ENDM
ENDIF
ELSE
  MACRO sign	A,B,C,D
	nop
  ENDM
ENDIF