#
# Makefile for tips.c
#

# CC = icc
CC = g++
DEBUG = -ggdb
DATE = `date +%Y%m%d%H%M`

addcol: addcol.c
	$(CC) addcol.c -o addcol

debug: addcol.c
	$(CC) $(DEBUG) addcol.c -o addcol.debug

install:
	cp -f addcol ~/bin

backup:
	cp -f addcol.c /nfs/projnfs/backups/addcol/addcol.c.$(DATE)
	cp -f Makefile /nfs/projnfs/backups/addcol/Makefile.$(DATE)

clean:
	rm *.o
