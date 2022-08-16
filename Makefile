#Main Makefile
CC := gcc
CFLAGS := -Wall

#Directories
IDIR := ./lib
SDIR := ./src

ODIR := ./obj

#Paths
INCLUDE_PATHS = $(IDIR:%=-I%)

#Libraries
LIBRARIES = -lpthread

#Compilation line
COMPILE = $(CC) $(CFLAGS) $(INCLUDE_PATHS)

OUTPUT = main.out

#FILEs
#---------------Source----------------#
SRCS = $(wildcard $(SDIR)/*.c)
#---------------Object----------------#
OBJS = $(SRCS:$(SDIR)/%.c=$(ODIR)/%.o)
#-------------Dependency--------------#
DEPS = $(SRCS:$(SDIR)/%.c=$(ODIR)/%.d)


all: md-obj $(OBJS)
	$(COMPILE) $(OBJS) main.c -o $(OUTPUT) $(LIBRARIES)


# Include all .d files
-include $(DEPS)

$(ODIR)/%.o: $(SDIR)/%.c
	$(COMPILE) -c $< -o $@ $(LIBRARIES)

run:
	./$(OUTPUT)

.PHONY : clean
md-obj:
	mkdir -p obj
clean:
	rm -rf *.d obj/* *.txt