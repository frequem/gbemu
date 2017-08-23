TARGET=gbemu

SRCEXT=cc
INSTALLDIR=/usr/local/bin

CXX=g++
CXXFLAGS=-Wall -O3
LIBS=

SRCDIR=src
BUILDDIR=build
INCLUDE=-I include

SRCS=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJS=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRCS:.$(SRCEXT)=.o))

RM=rm -Rf
CP=cp
ECHO=echo
MKDIR=mkdir -p

all : $(TARGET)
 
clean :
	@$(RM) $(BUILDDIR)
	@$(ECHO) "Removed objs"

distclean: clean
	@$(RM) $(TARGET)
	@$(ECHO) "Removed target"

$(TARGET): $(OBJS)
	@$(ECHO) "Linking"
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
	
