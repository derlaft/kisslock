INSTALL_DIR = /usr/bin

all: kisslock.c link

kisslock.o: kisslock.c
	gcc -c kisslock.c -I/usr/X11/include

link: kisslock.o
	gcc kisslock.o -L/usr/X11/lib -lX11 -o kisslock

clean: 
	rm kisslock.o kisslock

install: 
	cp kisslock ${INSTALL_DIR}/kisslock

uninstall:
	rm ${INSTALL_DIR}/kisslock
