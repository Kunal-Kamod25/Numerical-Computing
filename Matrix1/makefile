CC = g++
CFLAGS = -std=c++17 -Wall -IInclude
AR = ar rcs

# Source files
SRC_FILES = Src/Matrix_Methods.cpp Src/Matrix_Algorithms.cpp Src/LU.cpp Src/Iterative.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Library names
STATIC_LIB = libmatrix.a
DYNAMIC_LIB = matrix.dll
SOLVER = solver

all: static dynamic executables solver

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
executables: main.exe main_lu.exe main_iterative.exe

solver: Main.cpp $(STATIC_LIB)
	$(CC) Main.cpp -L. -lmatrix $(CFLAGS) -o $@

main.exe: Main.cpp $(STATIC_LIB)
	$(CC) Main.cpp -L. -lmatrix $(CFLAGS) -o $@

main_lu.exe: Main_LU.cpp $(STATIC_LIB)
	$(CC) Main_LU.cpp -L. -lmatrix $(CFLAGS) -o $@

main_iterative.exe: Main_Iterative.cpp $(STATIC_LIB)
	$(CC) Main_Iterative.cpp -L. -lmatrix $(CFLAGS) -o $@

# New target for dynamic executables
dynamic_main.exe: Main.cpp $(DYNAMIC_LIB)
	$(CC) Main.cpp -L. -lmatrix $(CFLAGS) -o $@

.PHONY: clean all static dynamic executables run_all solver

clean:
	rm -f solver *.exe *.a *.dll *.so Src/*.o

run_all: all
	@echo "=== Running Gaussian Elimination ===" && LD_LIBRARY_PATH=. ./solver
	@echo "\n=== Running LU Decomposition ===" && LD_LIBRARY_PATH=. ./main_lu.exe