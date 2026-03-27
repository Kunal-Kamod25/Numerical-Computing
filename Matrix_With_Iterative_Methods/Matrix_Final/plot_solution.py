import matplotlib.pyplot as plt

x = []
y = []

try:
    with open("solution.dat", "r") as f:
        for line in f:
            parts = line.split()
            if len(parts) >= 2:
                x.append(float(parts[0]))
                y.append(float(parts[1]))

    plt.figure(figsize=(8, 5))
    plt.plot(x, y, marker='o', linestyle='-', color='b', markersize=8)
    plt.title("System Solution Vector (x vs y)")
    plt.xlabel("Variable Index (x_0, x_1, x_2, ...)")
    plt.ylabel("Solution Value (y)")
    plt.grid(True, linestyle='--', alpha=0.7)
    
    # Save the plot
    plt.savefig("solution_graph.png")
    print("Success: Graph saved as 'solution_graph.png'")
    
    # Display the plot
    plt.show()

except FileNotFoundError:
    print("Error: Could not find 'solution.dat'. Make sure you have run the C++ solver first!")
