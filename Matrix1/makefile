CC = g++
CFLAGS = -std=c++17 -Wall -IInclude
AR = ar rcs

# Source files
SRC_FILES = Src/Matrix_Methods.cpp Src/Matrix_Algorithms.cpp Src/LU.cpp Src/Iterative.cpp Src/Eigenvalues.cpp Src/Interpolation.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Library names
STATIC_LIB = libmatrix.a
DYNAMIC_LIB = matrix.dll
SOLVER = solver

all: static dynamic executables solver run_interpolation

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
executables: main.exe main_lu.exe main_iterative.exe main_gaussian.exe main_gershgorin.exe main_interpolation.exe

solver: Main.cpp $(STATIC_LIB)
	$(CC) Main.cpp -L. -lmatrix $(CFLAGS) -o $@

main.exe: Main.cpp $(STATIC_LIB)
	$(CC) Main.cpp -L. -lmatrix $(CFLAGS) -o $@

main_lu.exe: Main_LU.cpp $(STATIC_LIB)
	$(CC) Main_LU.cpp -L. -lmatrix $(CFLAGS) -o $@

main_iterative.exe: Main_Iterative.cpp $(STATIC_LIB)
	$(CC) Main_Iterative.cpp -L. -lmatrix $(CFLAGS) -o $@

main_gaussian.exe: Main_Gaussian.cpp $(STATIC_LIB)
	$(CC) Main_Gaussian.cpp -L. -lmatrix $(CFLAGS) -o $@

main_gershgorin.exe: Main_Gershgorin.cpp $(STATIC_LIB)
	$(CC) Main_Gershgorin.cpp -L. -lmatrix $(CFLAGS) -o $@

main_interpolation.exe: Main_Interpolation.cpp $(STATIC_LIB)
	$(CC) Main_Interpolation.cpp -L. -lmatrix $(CFLAGS) -o $@

# New target for dynamic executables
dynamic_main.exe: Main.cpp $(DYNAMIC_LIB)
	$(CC) Main.cpp -L. -lmatrix $(CFLAGS) -o $@

.PHONY: clean all static dynamic executables run_all solver fresh rebuild run_interpolation

clean:
	rm -f solver *.exe *.a *.dll *.so Src/*.o

# Clean old binaries and rebuild everything from scratch
fresh: clean all

# Alias for fresh rebuild
rebuild: fresh

run_all: all
	@echo "=== Running Gaussian Elimination ===" && LD_LIBRARY_PATH=. ./solver
	@echo "\n=== Running LU Decomposition ===" && LD_LIBRARY_PATH=. ./main_lu.exe

run_interpolation: main_interpolation.exe
	@echo "=== Running Interpolation Demo (auto input n=49) ==="
	@printf "49\n" | LD_LIBRARY_PATH=. ./main_interpolation.exe