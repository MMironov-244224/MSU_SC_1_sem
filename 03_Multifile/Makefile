GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so README
TRASH = *.o *~ o.*
FILES = file[1-9]
CFLAGS = -Wall -fPIC
COMPARE = $(shell cmp)

all:    README prog liboutput_static.a liboutput.so prog-a prog-so

prog-so: prog.o liboutput.so
	cc -o prog-so prog.o -L. liboutput.so -Wl,-rpath,.
#	cc -o prog-so prog.o -L. liboutput.so

prog-a: prog.o liboutput_static.a
	cc -o prog-a prog.o -L. liboutput_static.a

liboutput.so: fun.o const.o
	cc -shared fun.o const.o -o liboutput.so

liboutput_static.a: fun.o const.o
	ar -rcs liboutput_static.a fun.o const.o

prog:   const.o fun.o prog.o

README: prog
	./$< 2> $@

fun.o:  outlib.h

test:	test1
	@echo $(shell cmp file1 file2)
	@echo $(shell cmp file2 file3)
	@echo $(shell cmp file1 file3)

test1: 
	./prog &> file1
	./prog-a &>> file1
	./prog-so &>> file1

	./prog this_is_arg_1 &> file2
	./prog-a this_is_arg_1 &>> file2
	./prog-so this_is_arg_1 &>> file2

	./prog this_is_arg_1 this_is_arg_2 this_is_arg_3 &> file3
	./prog-a this_is_arg_1 this_is_arg_2 this_is_arg_3 &>> file3
	./prog-so this_is_arg_1 this_is_arg_2 this_is_arg_3 &>> file3

clean:
	rm -rf $(GENERATES) $(TRASH) $(FILES)
	