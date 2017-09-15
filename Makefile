NAME=gbemu
TEST_NAME=test

SRCEXT=cc
MAINFILE=main
INSTALLDIR=/usr/local/bin

CXX=g++

CXXFLAGS=-Wall -O3
LIBS= -lSDL2 -lGL -lGLEW

TEST_CXXFLAGS=$(CXXFLAGS)
TEST_LIBS=$(LIBS) -lgtest -lgtest_main -lpthread 

BINDIR=bin
SRCDIR=src
TESTDIR=test
BUILDDIR=build
INCLUDE=-I include

SRCS=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJS:=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRCS:.$(SRCEXT)=.o))
OBJS:=$(filter-out $(BUILDDIR)/$(MAINFILE).o, $(OBJS))

TEST_SRCS=$(shell find $(TESTDIR) -type f -name *.$(SRCEXT))
TEST_OBJS=$(patsubst $(TESTDIR)/%,$(BUILDDIR)/%,$(TEST_SRCS:.$(SRCEXT)=.o))

TARGET=$(BINDIR)/$(NAME)
TEST_TARGET=$(BINDIR)/$(TEST_NAME)

RM=rm -Rf
CP=cp
ECHO=echo
MKDIR=mkdir -p

all : $(TARGET)
 
clean :
	@$(RM) $(BUILDDIR)
	@$(ECHO) "Removed objs"

distclean: clean
	@$(RM) $(BINDIR)
	@$(ECHO) "Removed binaries"

testclean:
	@$(RM) $(TEST_OBJS)
	@$(ECHO) "Removed only test objs"
	

test: $(TEST_TARGET)

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	@$(ECHO) "Linking test"
	@$(MKDIR) $(BINDIR)
	@$(CXX) $^ -o $(TEST_TARGET) $(TEST_LIBS)
	

$(BUILDDIR)/%.o: $(TESTDIR)/%.$(SRCEXT)
	@$(MKDIR) $(BUILDDIR)
	@$(ECHO) "Compiling test" $@
	@$(CXX) $(TEST_CXXFLAGS) $(INCLUDE) -c -o $@ $<
	
$(TARGET): $(OBJS) $(BUILDDIR)/$(MAINFILE).o
	@$(ECHO) "Linking"
	@$(MKDIR) $(BINDIR)
	@$(CXX) $^ -o $(TARGET) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@$(MKDIR) $(BUILDDIR)
	@$(ECHO) "Compiling" $@
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

install: $(TARGET)
	@$(CP) $(TARGET) $(INSTALLDIR)
	@$(ECHO) "Installed to" $(INSTALLDIR)

uninstall:
	@$(RM) $(INSTALLDIR)/$(NAME)
	@$(ECHO) "Uninstalled" $(INSTALLDIR)/$(TARGET)
	
