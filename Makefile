#
# Makefile for addcol.c,py
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
	cp -f $(APP).py ~/bin

backup:
	cp -f $(APP).c /nfs/projnfs/backups/$(APP)/$(APP).c.$(DATE)
	cp -f $(APP).py /nfs/projnfs/backups/$(APP)/$(APP).py.$(DATE)
	cp -f Makefile /nfs/projnfs/backups/$(APP)/Makefile.$(DATE)

clean:
	rm -f *.o ; rm $(APP)
