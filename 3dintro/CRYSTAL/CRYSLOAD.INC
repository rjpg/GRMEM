;***************************************************************************
;*	Ce fichier contient les d‚finitions des structures et des variables
;*	permettant la communication entre les routines de chargement des
;*	modules et le player
;*
;* Programm‚ par S‚bastien Granjoux
;* Commenc‚ le 04/01/95
;* Modification le 04/01/95

IDEAL

STRUC INSTRUMENT
	length  DW 0
	volume  DB 0
	fintune DB 0
	adrseg	DW 0	; correspond … l'adresse de r‚p‚tition au d‚but
	replen  DW 0
ENDS

STRUC FILESYS
	open	DW 0
	close	DW 0
	seek	DW 0
	read	DW 0
ENDS

SAMPLE_BORDER	EQU	2676
MIN_REPEAT	EQU	32
MAX_INST	EQU	128
MAX_VOICE	EQU	32
MAX_PART	EQU	256
COMMENT_LEN	EQU	992
NAME_LEN	EQU	28

GLOBAL	ResetMod:FAR
GLOBAL	Tempo:BYTE
GLOBAL	Bpm:BYTE
GLOBAL  NbVoice:BYTE
GLOBAL	Instrument1:INSTRUMENT:MAX_INST
GLOBAL	PatternSeg:WORD
GLOBAL	Sequence:WORD:MAX_PART
GLOBAL	LastPos:WORD
GLOBAL	Comments:FAR

;*************************************************************************

GLOBAL	allocmem:near
GLOBAL	freemem:near
GLOBAL	open:near
GLOBAL	close:near
GLOBAL	seek:near
GLOBAL	read:near
GLOBAL	getenvadr:far

