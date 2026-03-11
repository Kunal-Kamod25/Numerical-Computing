CC = g++
CFLAGS = -std=c++17 -Wall -IInclude
AR = ar rcs

# Source files
SRC_FILES = Src/Matrix_Methods.cpp Src/Matrix_Algorithms.cpp Src/LU.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Library names
STATIC_LIB = libmatrix.a
DYNAMIC_LIB = matrix.dll

all: static dynamic executables

# Compile object files with Position Independent Code for dynamic library
Src/%.o: Src/%.cpp
	$(CC) -c $< $(CFLAGS) -fPIC -o $@

# Build static library
static: $(STATIC_LIB)
$(STATIC_LIB): $(OBJ_FILES)
	$(AR) $@ $(OBJ_FILES)

# Build dynamic library
dynamic: $(DYNAMIC_LIB)
$(DYNAMIC_LIB): $(OBJ_FILES)
	$(CC) -shared -o $@ $(OBJ_FILES)

# Build executables (Static linking by default)
executables: main.exe main_lu.exe

main.exe: Main.cpp $(STATIC_LIB)
	$(CC) Main.cpp -L. -lmatrix $(CFLAGS) -o $@

main_lu.exe: Main_LU.cpp $(STATIC_LIB)
	$(CC) Main_LU.cpp -L. -lmatrix $(CFLAGS) -o $@

# New target for dynamic executables
dynamic_main.exe: Main.cpp $(DYNAMIC_LIB)
	$(CC) Main.cpp -L. -lmatrix $(CFLAGS) -o $@

.PHONY: clean all static dynamic executables

clean:
	powershell -Command "Remove-Item -ErrorAction SilentlyContinue *.exe, *.a, *.dll, Src/*.o"