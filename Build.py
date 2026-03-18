import os
import sys
import platform
import subprocess
import time

working_directory: str = os.getcwd()
build_directory: str = "Build"

def run_configurations() -> None:
    if not os.path.exists(build_directory):
        os.makedirs(build_directory)

    os.chdir(build_directory)

    try:
        subprocess.check_call(["cmake", working_directory])
    except subprocess.CalledProcessError as call_process_error:
        print(f"Error while running Cmake configurations: {call_process_error}")
    except FileNotFoundError:
        print(f"Error while running Cmake configurations: CMake executable is not found. Please make sure that CMake is installed")
    finally:
        os.chdir("..")

def run_build() -> None:
    if not os.path.exists(build_directory):
        os.makedirs(build_directory)

    os.chdir(build_directory)

    try:
        subprocess.check_call(["cmake", "--build", "."])
    except subprocess.CalledProcessError as call_process_error:
        print(f"Error while running Cmake build: {call_process_error}")
    except FileNotFoundError:
        print(f"Error while running Cmake build: CMake executable is not found. Please make sure that CMake is installed")
    finally:
        os.chdir("..")

if __name__ == "__main__":
    configuration_start_time: float = time.perf_counter()

    print(f"\n --- Running configuration for project '{os.path.basename(os.getcwd())}' with Python {platform.python_version()} build script and CMake --- \n")
    run_configurations()

    configuration_end_time: float = time.perf_counter()
    configuration_elapsed_time: float = configuration_end_time - configuration_start_time

    print(f"\n --- Configuration completed with the time of {configuration_elapsed_time:.3f} seconds --- \0")

    response: str = str(input(f"Do you want to build the project? [y/n]: ")).lower()

    if response == "n" or response == "no":
        sys.exit()
    else:
        build_start_time: float = time.perf_counter()

        print(f"\n --- Building project '{os.path.basename(os.getcwd())}' with Python {platform.python_version()} build script and CMake --- \n")
        run_build()

        build_end_time: float = time.perf_counter()
        build_elapsed_time: float = build_end_time - build_start_time

        print(f"\n --- Building completed with the time of {configuration_elapsed_time:.3f} seconds --- ")
