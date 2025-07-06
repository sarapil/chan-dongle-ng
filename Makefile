MODULE=chan_dongle_ng.so
SRC=src/chan_dongle_ng.c
OBJ=$(SRC:.c=.o)

CFLAGS+=-Iinclude $(ASTCFLAGS)
LDFLAGS+=$(ASTLDFLAGS)

all: $(MODULE)

$(MODULE): $(OBJ)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(MODULE)
