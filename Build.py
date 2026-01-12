import os
import platform
import subprocess
import time

cmake_lists_file: str = os.getcwd() + "/CMakeLists.txt"
batch_file: str = os.getcwd() + "/Build.bat"
shell_file: str = os.getcwd() + "/Build.sh"

def main() -> None:
    if not os.path.exists(cmake_lists_file):
        raise FileNotFoundError(f"Failed to find '{cmake_lists_file}' in the current project")
    if not os.path.exists(batch_file):
        raise FileNotFoundError(f"Failed to find '{batch_file}' in the current project")
    if not os.path.exists(shell_file):
        raise FileNotFoundError(f"Failed to find '{shell_file}' in the current project")

    if platform.system() == "Windows":
        subprocess.run([batch_file], shell=True)
    elif platform.system() == "Linux" or platform.system() == "Darwin":
        subprocess.run([shell_file], shell=True)

if __name__ == "__main__":
    start_time: float = time.perf_counter()

    print(f" --- Building project '{os.path.basename(os.getcwd())}' with Python {platform.python_version()} --- \n")
    main()

    end_time: float = time.perf_counter()
    elapsed_time = end_time - start_time

    print(f"\n --- Build completed with the time of {elapsed_time:.4f} seconds --- ")
