;***************************************************************************
;*	Ce fichier contient les d‚finitions des structures et des variables
;*	permettant la communication entre le driver et le player
;*
;* Programm‚ par S‚bastien Granjoux
;* Commenc‚ le 04/01/95
;* Modification le 04/01/95

IDEAL

STRUC DEVICE
	id	DW 0
	detect	DB 30 DUP (0)
	init	DW 0
	start	DW 0
	stop	DW 0
	make	DW 0
	setbpm	DW 0
	getbyte DW 0
	port	DW 0
	irq	DB 0
	dma	DB 0
ENDS

STRUC VOICE
	samplen DW 0
	volume	DB 0
	finetu	DB 0
	adrvoc	DP 0
	replen	DW 0
	play    DW 0		; note jou‚
	oldnote DW 0		; note pr‚c‚dente (portamento)
	effet   DW 0
	note1   DW 0
	note2   DW 0
	amplit	DB 0
	vitesse	DB 0
	sinpos  DB 0
	compte	DB 0
	inst	DB 0
	gusinf	DB 0	;bit 3 new vol,2 nul vol,1 change adr,0 new inst
	extra	DB 0
	mute	DB 0    ;0=voix coup‚,255 voix normal
	looppos DW 0
	effnb	DB 0
	oldvib	DB 0
	oldtrem DB 0
	oldport DB 0
	oldslid	DB 0
ENDS

BUF_LEN		EQU	4096
VOL_TAB_LEN	EQU	65*256

;** Donn‚es du player utiliser par les drivers

GLOBAL	Voice1:VOICE
GLOBAL	SoundBuf:BYTE:BUF_LEN
GLOBAL	SoundPage:WORD
GLOBAL	SoundPtr:WORD
GLOBAL	VoicesLen:WORD
GLOBAL  VolumeTab:BYTE:VOL_TAB_LEN
GLOBAL	NbVoice:BYTE
GLOBAL	MasterVol:BYTE
GLOBAL	MixRate:WORD
GLOBAL	Notes:WORD
GLOBAL	Frame:BYTE
GLOBAL	OldIrq:DWORD

;** Fonctions utilitaires utilisable par les drivers

GLOBAL	USEDEVICE:NEAR
GLOBAL	calvoltab:NEAR
GLOBAL	caloptvoltab:NEAR
GLOBAL	setautoeoi:NEAR
GLOBAL	reseteoi:NEAR
GLOBAL	defbpm:NEAR
GLOBAL	peekdef:NEAR
GLOBAL	setirq:NEAR
GLOBAL	getirq:NEAR
GLOBAL	switch_makemod:NEAR
GLOBAL  IMAKEMOD:NEAR
GLOBAL	Ampli8:BYTE
