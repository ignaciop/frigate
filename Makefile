PROJNAME = frigate

CC := gcc

SRCDIR := src

BUILDDIR := build

OBJDIR := $(BUILDDIR)/obj

TARGET := $(BUILDDIR)

SRCEXT := c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

CFLAGS := 
LIB := -L lib
INC := -I inc

debug: clean
debug: CFLAGS := -g -Wall -Wextra -pedantic
debug: TARGET := $(BUILDDIR)/debug/$(PROJNAME)
debug: $(TARGET)

release: clean
release: CFLAGS := -Wall -Wextra -pedantic -O2 -march=native
release: TARGET := $(BUILDDIR)/release/$(PROJNAME)
release: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)/obj
	mkdir -p $(BUILDDIR)/debug
	mkdir -p $(BUILDDIR)/release
	@echo " Building..."
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(OBJDIR) $(TARGET)"; $(RM) -r $(OBJDIR) $(TARGET)

# Tests
#tester:
#	$(CC) $(CFLAGS) tests/test_queue.c $(INC) $(LIB) -o $@ $<

.PHONY: clean