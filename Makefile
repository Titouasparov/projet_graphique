CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -I$(INCDIR) -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LDLIBS = -lglfw -lGLEW -lGL
SRCDIR = src
OBJDIR = obj
INCDIR = include
SHADIR = shaders
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS = $(wildcard $(INCDIR)/*.h) $(wildcard $(SHADIR)/*.vert) $(wildcard $(SHADIR)/*.frag)
TARGET = main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPS)
	@if [ ! -d "$(OBJDIR)" ]; then mkdir $(OBJDIR); fi
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
