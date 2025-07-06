MODULE=chan_dongle_ng.so
SRC=chan_dongle_ng.c chan_dongle_ng_cli.c

ASTCFLAGS=`asterisk -C | grep ^ASTCFLAGS= | cut -d= -f2`
ASTLIBDIR=`asterisk -C | grep ^ASTLIBDIR= | cut -d= -f2`

all:
	gcc -fPIC -Wall -shared -o $(MODULE) $(SRC) $(ASTCFLAGS) -I/usr/include/asterisk
	mv $(MODULE) $(ASTLIBDIR)/modules/
