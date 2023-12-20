CC      := gcc
INCLUDE := -Iinclude/
FLAGS   := -std=c17 -O3 -g -Wall -Wextra -Wno-pointer-to-int-cast $(INCLUDE)

LD	    := ld
LDFLAGS := 

libdir 	:= include/lib
libsrc 	:= $(wildcard $(libdir)/*.c $(libdir)/*/*.c)
libobj 	:= $(libsrc:%.c=lib/%.o)

srcdir  := src
src	    := $(wildcard $(srcdir)/*.c) $(wildcard $(srcdir)/*/*.c)
obj	    := $(src:%.c=%.o)

testdir  := test
test_src := $(wildcard $(testdir)/*.c) $(wildcard $(testdir)/*/*.c)
test_obj := $(src:%.c=test/%.o)


bin := bin
OUT := events.exe


.PHONY: build lib all test clean run
run: build
	./$(OUT)

build: lib $(obj)
	$(CC) $(FLAGS) $(wildcard $(bin)/*.o) -o $(OUT)

lib: $(libobj)

test: $(test_obj)
	@for binary in $(wildcard $(bin)/test/*); do \
		./$$binary; \
		echo "==============="; \
	done

%.o: %.c
	-@mkdir -p $(bin)/
	$(CC) $(FLAGS) $< -c -o $(bin)/$(@F)

lib/%.o: %.c
	-@mkdir -p $(bin)/lib/
	$(CC) $(FLAGS) $< -c -o $(bin)/lib/$(@F)

test/%.o: %.c
	-@mkdir -p $(bin)/
	$(CC) $(FLAGS) $< -o $(bin)/test/$(@F)

clean:
	-@rm -r $(bin)/
	-@rm $(OUT)
