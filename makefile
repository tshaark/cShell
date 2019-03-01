TARGETS = rsh

all: $(TARGETS)

%o: %.c
	gcc -g -c -o  $@ $<
rsh: ls.o cd.o echo.o pwd.o pinfo.o  main.o chkperm.o printtime.o launch.o exit.o remind.o clock.o handler.o read.o split.o semi.o  envvar.o  
	gcc -o rsh ls.o cd.o echo.o pwd.o pinfo.o main.o chkperm.o printtime.o launch.o exit.o remind.o clock.o handler.o read.o split.o semi.o  envvar.o  

.PHONY: clean
clean:
	rm -f $(TARGETS) *.o