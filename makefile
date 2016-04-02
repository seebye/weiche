CXX		:= g++
CXXFLAGS 	:= -O2 -std=c++11 -Wall -pthread -lX11
CXXFLAGS_DEBUG	:= -g -std=c++11 -Wall -pthread -lX11

TARGET := weiche
SOURCE := jsonxx/jsonxx.cc \
	  source/*


PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

$(TARGET): source/main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) -I.

clean:
	find . -name "*.o" | xargs rm -vf
	rm -vf $(TARGET)

install: $(TARGET)
	modprobe -v uinput 2&>0 || (echo "no uinput device" ; exit 1)
	install -d $(BINDIR)
	install -m 4755 $(TARGET) $(BINDIR)/

uninstall:
	$(RM) $(BINDIR)/$(TARGET)

