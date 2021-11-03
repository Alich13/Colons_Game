#########################################
# Directory where to put the object files
OBJDIR = .

#########################################
# Directory where to locate source files
SRCDIR = .

#########################################
# Compiler
CC=g++

######################
# All the object files      
OBJFILES = $(OBJDIR)/my_window.o  $(OBJDIR)/data_structures.o $(OBJDIR)/dessin.o  $(OBJDIR)/board.o $(OBJDIR)/main.o 

###############
# All the flagss
DEBUGFLAGS = -O5 -g -DDEBUG -m64 -L /lib64 `pkg-config gtkmm-3.0 --cflags`	
STFLAGS    = -DLCB -DLENGTHTYPE=Uint -pthread `pkg-config gtkmm-3.0 --libs`

out: $(OBJFILES)
	$(CC)  $^ $(STFLAGS) -o $(OBJDIR)/$@

# How to make the object files:
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC)  $(DEBUGFLAGS) -c $? -o $@

# Cleaning target (only works with fileutils):
clean:
	/bin/rm -f $(OBJFILES) out
