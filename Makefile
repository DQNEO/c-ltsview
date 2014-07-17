PROGNAME = ltsview
all : $(PROGNAME).c
	gcc -g3 -O0 -Wall $(PROGNAME).c -o $(PROGNAME)
