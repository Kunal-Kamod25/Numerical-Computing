# =====================================================
# Makefile for Matrix Library with Iterative Solvers
# =====================================================

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3 -IInclude
LDFLAGS = 

# Source files
SRC_DIR = Src
INCLUDE_DIR = Include
OBJ_DIR = obj

# Object files
OBJS = $(OBJ_DIR)/Matrix_Methods.o \
       $(OBJ_DIR)/Matrix_Algorithms.o \
       $(OBJ_DIR)/LU.o \
       $(OBJ_DIR)/IterativeSolver.o

# Executable names
EXEC_MAIN = main_solver
EXEC_TEST = test_methods
EXEC_DEMO = simple_demo
EXEC_OLD = main_old

# Default target
all: directories $(EXEC_MAIN) $(EXEC_TEST) $(EXEC_DEMO)

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p Large_Matrix

# Main program with menu
$(EXEC_MAIN): $(OBJS) Main_Updated.cpp
	$(CXX) $(CXXFLAGS) -o $@ Main_Updated.cpp $(OBJS) $(LDFLAGS)
	@echo "Built $(EXEC_MAIN) successfully!"

# Test program
$(EXEC_TEST): $(OBJS) Test_All_Methods.cpp
	$(CXX) $(CXXFLAGS) -o $@ Test_All_Methods.cpp $(OBJS) $(LDFLAGS)
	@echo "Built $(EXEC_TEST) successfully!"

# Simple demo program
$(EXEC_DEMO): $(OBJS) Simple_Demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ Simple_Demo.cpp $(OBJS) $(LDFLAGS)
	@echo "Built $(EXEC_DEMO) successfully!"

# Original main (for backward compatibility)
$(EXEC_OLD): $(OBJS) Main.cpp
	$(CXX) $(CXXFLAGS) -o $@ Main.cpp $(OBJS) $(LDFLAGS)
	@echo "Built $(EXEC_OLD) successfully!"

# Object file compilation
$(OBJ_DIR)/Matrix_Methods.o: $(SRC_DIR)/Matrix_Methods.cpp $(INCLUDE_DIR)/Matrix.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/Matrix_Algorithms.o: $(SRC_DIR)/Matrix_Algorithms.cpp $(INCLUDE_DIR)/Matrix.hpp $(INCLUDE_DIR)/gauss_elimination.hpp $(INCLUDE_DIR)/SLE.hpp $(INCLUDE_DIR)/LU.hpp $(INCLUDE_DIR)/IterativeSolver.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/LU.o: $(SRC_DIR)/LU.cpp $(INCLUDE_DIR)/LU.hpp $(INCLUDE_DIR)/Matrix.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/IterativeSolver.o: $(SRC_DIR)/IterativeSolver.cpp $(INCLUDE_DIR)/IterativeSolver.hpp $(INCLUDE_DIR)/Matrix.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run test program
test: $(EXEC_TEST)
	./$(EXEC_TEST)

# Run simple demo
demo: $(EXEC_DEMO)
	./$(EXEC_DEMO)

# Run main program
run: $(EXEC_MAIN)
	./$(EXEC_MAIN)

# Clean build files
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(EXEC_MAIN) $(EXEC_TEST) $(EXEC_OLD)
	rm -f solution.dat
	@echo "Cleaned build files"

# Clean everything including output files
cleanall: clean
	rm -f *.dat *.txt *.out
	@echo "Cleaned all files"

# Help message
help:
	@echo "Available targets:"
	@echo "  all        - Build all programs (default)"
	@echo "  test       - Build and run test program"
	@echo "  run        - Build and run main solver program"
	@echo "  clean      - Remove build files"
	@echo "  cleanall   - Remove all generated files"
	@echo "  help       - Show this help message"

.PHONY: all directories test run clean cleanall help
