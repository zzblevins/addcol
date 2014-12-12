#
# Makefile for addcol.c
#

# CC = icc
CC = g++
DEBUG = -ggdb
DATE = `date +%Y%m%d%H%M`

APP = addcol

$(APP): $(APP).c
	$(CC) $(APP).c -o $(APP)

debug: $(APP).c
	$(CC) $(DEBUG) $(APP).c -o $(APP).debug

install:
	cp -f $(APP) ~/bin

backup:
	cp -f $(APP).c /nfs/projnfs/backups/$(APP)/$(APP).c.$(DATE)
	cp -f Makefile /nfs/projnfs/backups/$(APP)/Makefile.$(DATE)

clean:
	rm -f *.o ; rm $(APP)
