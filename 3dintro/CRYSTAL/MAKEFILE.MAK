#***************************************************************************
#*      Fichier MAKE permettant de faire les librairies de Crystal Player
#*
#* Programm‚ par S‚bastien Granjoux
#* Commenc‚ le 18/03/95
#* Modification le 18/03/95
#*

#** Compilateurs et options **

PC = c:\program\tp\tpc.exe
PCOPTS =
AS = c:\program\tasm\tasm.exe
ASOPTS = -mx -m4
LB = c:\program\bin\tlib.exe
LBOPTS = 

#** Fichiers **

MAINSRC = CRYS260.OBJ CRYSDEV.OBJ
LOADSRC = CRYSMEM.OBJ CRYSOVL.OBJ CRYSLOAD.OBJ CRYSFILE.OBJ
MODSRC  = MLOADMOD.OBJ OLOADMOD.OBJ FLOADMOD.OBJ LOADMOD.OBJ
BASEDRV = ADLIB.OBJ DAC.OBJ SPEAKER.OBJ SNDBLAST.OBJ GUS.OBJ SNDPRO.OBJ
MAININC = CRYSLOAD.INC CRYSDEV.INC CRYSID.INC CRYSERR.INC

#** Commandes principales **

all:    compile
	@$(PC) $(PCOPTS) CRYSINT.PAS
	@$(PC) $(PCOPTS) CRYSTAL.PAS

#** Regle par d‚faut **

{$(SRCDIR)}.asm.asm:
	@copy $(SRCDIR)\$.

{$(SRCDIR)}.inc.inc:
	@copy $(SRCDIR)\$.

.asm.obj:
	@$(AS) $(ASOPTS) $.
	@$(LB) $(LBOPTS) CRYSTAL.LIB +$&.OBJ

#** Commandes secondaires **

compile: $(MAININC) $(MAINSRC) $(LOADSRC) $(MODSRC) $(BASEDRV)
	
