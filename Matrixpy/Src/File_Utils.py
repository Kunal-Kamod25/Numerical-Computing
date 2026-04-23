import os

def discover_input_files(subdirectory):
    """
    Scans the Matrixpy/Inputs/[subdirectory] folder for available files.
    Returns a sorted list of absolute paths.
    """
    base_path = os.path.join("Matrixpy", "Inputs", subdirectory)
    if not os.path.exists(base_path):
        return []
    
    files = [f for f in os.listdir(base_path) if os.path.isfile(os.path.join(base_path, f))]
    files.sort()
    return [os.path.join(base_path, f) for f in files]

def choose_input_file(subdirectory):
    """
    Prompts the user to select an input file from a list of discovered files.
    Allows for a custom path input if '0' is selected.
    """
    files = discover_input_files(subdirectory)
    
    print(f"\n--- Select Input File for {subdirectory} ---")
    if not files:
        print("No predefined input files found.")
    else:
        for i, f in enumerate(files):
            print(f"  {i + 1}. {os.path.basename(f)}")
            
    print("  0. Custom path")
    
    try:
        # User selection via numeric index
        choice = int(input(f"Select file (0-{len(files)}): "))
        if 1 <= choice <= len(files):
            return files[choice - 1]
    except ValueError:
        pass
        
    return input("Enter custom file path: ").strip()

def ensure_output_dir(subdirectory):
    """
    Ensures that the Matrixpy/Outputs/[subdirectory] path exists.
    Creates directories recursively if necessary.
    """
    path = os.path.join("Matrixpy", "Outputs", subdirectory)
    if not os.path.exists(path):
        os.makedirs(path)
    return path
