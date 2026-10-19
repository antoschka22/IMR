# Exercise 1 - Project Packaging

This exercise counts for the **LU 191.034 Introduction to Mobile Robotics**


Welcome to the first task of the **IMR course**!  
This exercise is designed to give you a foundation in some of the **less glamorous but essential concepts** you’ll need for later exercises.
Your goal is to split a Makefile-based package into two CMake projects, then **build and run** them.
As with all exercises, make sure to **document your approach** and **take screenshots** of your results.
This helps us evaluate your solution’s functionality before looking at the source code, and makes it easier for us to recognize completed tasks.
We will review all your submissions, but only to check whether they match your submission checklist.
During the submission review, you must be able to present your approach and answer questions.

## Setup

Some setup is needed before you start.

### OS

We suggest using a Linux system (Ubuntu 26.04) or similar to work on this exercise. Windows with WSL or macOS might also work but are not supported by us.
Using a virtual machine might work for now, but later we will need more performance.

## Git

We suggest cloning this repository into `$HOME/projects` by running:

```bash
mkdir $HOME/projects
# upload your ssh key first
git clone git@gitlab.tuwien.ac.at:lva-imr/2026/imr-pp.git  $HOME/projects/imr-pp 
```

The folder `$HOME/projects/imr-pp` will be also called workspace (ws)


## Timesheet

We would like you to keep track of the hours you work on the IMR projects.  
Therefore, please record the time you spend working on them.  
A working-hours report is required to receive 100% for a submission. 
Also, make sure to fulfil the other documentation requirements listed in this document.

## Tools `vim` & `bash`

We recommend **not using an IDE** for the following tasks. Instead, try working with tools like **`tmux`** or **`vim`**.  
Do **not trust the tutors**, `vim` is the best editor for the console!
For the next exercise, we will use **VS Code**, but for now, I want you to see **what’s happening behind the curtain**.

## 1.1 CMake
Robotic systems often rely on a large number of software packages.
Because of this, you cannot always depend on a package manager to handle all components, especially once you start building on top of software you have developed yourself.
To make managing our software easier, we use a **standard directory structure** and a **build system based on [CMake](https://cmake.org/)**.
In this task, you will **migrate a Makefile-based package into two separate CMake projects**.

Your initial repo contains a **single Makefile-based** example under `bare/` and a minimal `Dockerfile`:
```
imr-pp/
├── Dockerfile
├── bare/
│   ├── Makefile
│   ├── core.cpp, core.hpp  # a lib
│   ├── example.cpp
│   ├── main_cv_app.cpp
│   └── test_dummy.cpp
└── ...
```

### 1.1.0 Task 0 - Documentation

Your documentation should be a **PDF** and **no longer than 10 pages**.  
It should consist **primarily of screenshots** (use `Alt + Print`, `Shift + Print` or [Flameshot](https://flameshot.org/)). It should be __clearly visible__ which parts you finished.

- Document steps with screenshots.
- Include only the **necessary code lines** and explain **why** you added them.
- Writing your own documentation with your own screenshots is **mandatory** (knockout criterion).

The **first page** of your documentation must include:
- Your **full name** 
- Your **student ID**
- A **table** showing how many tasks you finished
- The number of hours you spent on the tasks

Also document your **top 10 Bash editor commands, shortcuts, or tips** that you found most useful during your work.  
Here are a few examples to give you an idea of what to include:

- Save under a different name in `vim`
- Executing `build` or `make` commands while a file is open
- Is there an alternative to `tmux`, what is tmux?
- Switching quickly between multiple files  
- Enabling mouse support (if possible)  
- Running `git` commands directly from the editor  
- Highlighting code efficiently  
- Managing your music playlist in the background  
- Any other useful tricks you discovered

### 1.1.1 Task 1 - Hello

The first task is a warm-up. Create a folder `01_hello` in your workspace containing a `main.cpp` and a `CMakeLists.txt`.

```
imr-pp/
├── Dockerfile
├── bare/
│   └── ...
└── 01_hello/
    ├── CMakeLists.txt
    └── main.cpp
```

The CMakeLists.txt must contain only one line, starting with `add_executable( ...`.
It should create a program called **hello** which outputs a nice greeting sentence.
Build your project in the folder `01_hello` with the following commands.

```bash
cd imr-pp/01_hello
cmake .
make
```
Be prepared to explain why this is not a good way to build a project.

Since we are using a minimal CMakeLists.txt, CMake will print warnings.

### 1.1.2 Task 2 - Flat CMake

Create a flat CMake project with a very short CMakeLists.txt.
Start by creating a folder `02_flat` and copy `core.{cpp|hpp}` and `example.cpp` into it.

```
imr-pp/
├── ...
└── 02_flat/
    ├── core.hpp
    ├── core.cpp
    ├── example.cpp
    └── CMakeLists.txt
```

Now, as in `bare/Makefile`, create a library **imr_core**, which is then used by a program called **example**.
Try to keep your `CMakeLists.txt` as simple as possible and build in a `build` folder the following commands.

```bash
cd imr-pp/02_flat
mkdir build
cd build
cmake ..
make
```
CMake must produce **NO WARNINGS**, while keeping all CMake statements as minimal as possible.

### 1.1.3 Task 3 - Structured CMake

Create a structured CMake project with a very short CMakeLists.txt.
Start by creating a folder `03_structured` and copy `core.{cpp|hpp}` and `example.cpp` into it, but this time use the following folder structure:

```
imr-pp/
├── ...
└── 03_structured/
    ├── include/
    │   └── imr_core/
    │       └── <.hpp-files>
    ├── src/
    │   ├── apps/
    │   │   ├── <.cpp-files>
    │   │   └── CMakeLists.txt
    │   ├── imr_core/
    │   │   ├── <.cpp-files>
    │   │   └── CMakeLists.txt
    │   └── CMakeLists.txt
    └── CMakeLists.txt
```

Keep it as simple as possible, but add a flag to the `CMakeLists.txt` so that building the __apps__ is optional.
Define the `OUTPUT_DIRECTORY` variables for the libraries and applications to place the libraries and programs into a __lib__ and __bin__ folder, respectively, in your **03_structured** project root.
What can you do with the command `ccmake`? 
Build **imr_core** as a shared library. What happens if you delete the generated `*.so` file and then run your example?
Repeat this with a static library.


### 1.1.4 Task 4 - Include and Library paths

In this task, you have to set up multiple approaches for how CMake can find your libraries.
First, the data structure: create a folder named `04_paths`, copy `03_structured` from the previous task into it, and rename it to `imr_core`. 
Next to `imr_core`, create a second folder called `imr_cv`. 
Set the project name for `imr_core` to `imr_core` and use `${PROJECT_NAME}` for the generated library.
In `imr_cv`, create a project structure similar to the one used in Task 3 for `main_cv.cpp`. The generated executable should be named `imr_cv`.

```
imr-pp/  # imr or root-imr
├── ...
├── 03_structured/
│   └── ...
├── 04_paths/
│   ├── imr_core/
│   │   ├── include/
│   │   ├── src/
│   │   └── CMakeLists.txt
│   └── imr_cv/
│       ├── src/
│       │   ├── apps/
│       │   │   ├── <.cpp-files>
│       │   │   └── CMakeLists.txt
│       │   └── CMakeLists.txt
│       └── CMakeLists.txt
└── ...
```

Use hardcoded, relative include paths and library paths to the `imr_core` library in your `CMakeLists.txt` to build `imr_cv`.
Wrap the hardcoded statements in an `if` block in your `CMakeLists.txt` using a define called `PATHS_HARD_CODED`.
Explain or demonstrate how you can run `imr_cv` if the library path changes after you build the executable.

Add a define `PATHS_WITH_FIND` and output an error if both `PATHS_HARD_CODED` and `PATHS_WITH_FIND` are set, or a warning if neither is set.
Within the `PATHS_WITH_FIND` guard, use the CMake commands `find_library` to locate library paths and `find_path` to locate include paths.

Add a third define `PATHS_IMPORTED` and ensure that exactly one option is set. Use the `add_library` and `set_target_properties` commands to link the correct headers and libraries.

Add an installation target to the `imr_core` library and install the project using `cmake -DCMAKE_INSTALL_PREFIX=~/opt/local ..`.
Instead of installing only the header file, install the entire `imr_core` header folder.
Add `~/opt/local/lib` to the system library directories defined in `/etc/ld.so.conf.d/` and reload the **library search paths of the dynamic linker/loader** from the **trusted directories**.
Now, add a fourth option `PATHS_SYSTEM` and use the system paths. Use the preprocessor directive `#ifdef PATHS_SYSTEM ...` to adapt to the changed include path of `core.hpp`. 
Compile `imr_cv` with `cmake -DPATHS_HARD_CODED=OFF -DPATHS_WITH_FIND=OFF -DPATHS_IMPORTED=OFF -DPATHS_SYSTEM=ON -DCMAKE_PREFIX_PATH=~/opt/local  ..`.
If this works, you can try to install everything into the system without a prefix. Document how you uninstall things.



### 1.1.5 Task 5 - External Library

Create a folder/project `05_show_image` and add `main_show_image.cpp`. Keep the project structure simple, like the following:

```
imr-pp/  # imr or root-imr
├── ...
├── 03_structured/
│   └── ...
├── 04_paths/
├── 05_show_image/
│   ├── src/
│   │   └── <.cpp-files>
│   └── CMakeLists.txt
└── ...
```

This should be your `main_show_image.cpp`. 

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    std::string path = (argc > 1) ? argv[1] : "image.jpg";
    cv::Mat img = cv::imread(path);
    if (img.empty()) { std::cerr << "Could not open " << path << "\n"; return 1; }
    cv::imshow("Image", img);
    cv::waitKey(0);
    return 0;
}
```

In order to build it, you need OpenCV (`sudo apt install libopencv-dev`).
Add the statements needed to find the OpenCV libraries and headers.

### 1.1.6 Task 6 - CMake Config

Copy `05_show_image` and name it `06_cmake_config`. Add the following statements to the CMakeLists.txt:

```
imr-pp/  # imr or root-imr
├── ...
├── 05_show_image/
├── 06_cmake_config/
│   ├── src/
│   │   └── <.cpp-files>
│   └── CMakeLists.txt
└── ...
```

```cpp
message(STATUS "OpenCV config file: ${OpenCV_CONFIG}")
message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
```

Check out the "OpenCV config file". What is the benefit of using such a file compared to __Task 4 - Include and Library paths__?

### 1.1.7 Task 7 - Generated Files

We have now seen in the OpenCV project which data is commonly handled by CMake. 
Now let’s create a proper `__07_file_generation__` project, including an automatically generated `version.hpp` file based on an `.in` file.
This is the time to use an LLM, but you should understand what is going on :-).

The challenges you have to solve in this task are:

- Use only one `CMakeLists.txt` in the project root for simplicity.
- `imr_core` should generate a `version.hpp` file (see CMake).
- The `version.hpp` should implement at least a function `inline std::string get_version_string()` in the project namespace.
- `imr_core` should generate the shared library `libIMRCore.so`.
- `imr_core` should install the header files. (`cmake -DCMAKE_INSTALL_PREFIX=~/opt/local ..`.) Make sure that `~/opt/local` is a **trusted directory** of the dynamic linker.
- `imr_cv` should use the `imr_core` library installed before (`cmake -DCMAKE_PREFIX_PATH=~/opt/local ..`.)
- Extend `main_cv.cpp` to print the version string from `imr_core`.
- Since `imr_cv` depends on the library from `imr_core`, it should check the version before compiling.

It is important that you understand:

- How text replacement works.
- Where the generated files are placed.

```
imr-pp/  # imr or root-imr
├── ...
├── 05_show_image/
├── 06_cmake_config/
└── 07_file_generation/
    ├── imr_core/
    │   ├── build/
    │   │   └── <build binaries>
    │   ├── cmake/
    │   │   └── <.in-files>
    │   ├── include/
    │   │   └── imr_core/
    │   │       └── <.hpp-files>
    │   ├── src/
    │   │   ├── apps/
    │   │   │   └── <.cpp-files>
    │   │   └── imr_core/
    │   │       └── <.cpp-files>
    │   ├── CMakeLists.txt
    │   └── Readme.md
    │
    └── imr_cv/
        ├── build/
        │   └── <build binaries>
        ├── include/
        │   └── imr_cv/
        │       └── <.hpp-files>
        ├── src/
        │   └── <.cpp-files>
        ├── CMakeLists.txt
        └── Readme.md
```

### 1.1.8 Task 8 - Presets

Make a copy of __07_file_generation__ and name it __08_presets__. Using LLMs now makes perfect sense :-)
Next to `src`, add a folder `tests` containing a copy of `test_dummy.cpp`.

The challenges you have to solve in this task are:

- Use only one `CMakeLists.txt` in the project root for simplicity.
- `imr_core` should generate a `version.hpp` file (see CMake).
- `imr_core` should generate a package configuration file `IMRCoreConfig.cmake`.  
- `imr_core` should generate a package export file `IMRCoreTargets.cmake`.  
- `imr_core` should generate a package version file `IMRCoreConfigVersion.cmake`.  
- `imr_core` should build the unit tests (hint: use [GoogleTest](https://github.com/google/googletest.git)).  
- Add a `CMakePresets.json` configuration with a debug and release config to `imr_core`, creating an `install/{debug|release}` folder in the project.
- `imr_cv` can be built with `cmake -DCMAKE_PREFIX_PATH=$(realpath ../../imr_core/install/debug) ..  && make`
- `imr_cv` should check the version of `imr_core` during build time.  
- Add a `CMakePresets.json` configuration with a debug and release config to `imr_cv` defining the `CMAKE_PREFIX_PATH`
- Add a workflow option to the presets
- Add a preset configuration which installs your stuff into `~/opt/local`.

It is important that you understand:

- Do the tests run?
- What is the benefit of using a CMakePresets.json, and what are useful commands?
- How does a project find the generated `*.cmake` files? 
- What options do you have to give cmake a hint where to find other projects needed.

```
imr-pp/  # imr or root-imr
├── ...
├── 05_show_image/
├── 06_cmake_config/
├── 07_file_generation/
└── 08_presets/
    ├── imr_core/
    │   ├── build/
    │   │   └── {debug|release}
    │   ├── cmake/
    │   │   └── <.in-files>
    │   ├── include/
    │   │   └── imr_core/
    │   │       └── <.hpp-files>
    │   ├── install/
    │   │   └── {debug|release}
    │   ├── src/
    │   │   ├── apps/
    │   │   │   └── <.cpp-files>
    │   │   └── imr_core/
    │   │       └── <.cpp-files>
    │   ├── tests/
    │   │   └── <.cpp-files>
    │   ├── CMakeLists.txt
    │   ├── CMakePresets.json
    │   └── Readme.md
    │
    ├── imr_cv/
    │   ├── build/
    │   │   └── {debug|release}
    │   │       └── <build binaries>
    │   ├── src/
    │   │   └── <.cpp-files>
    │   ├── CMakeLists.txt
    │   ├── CMakePresets.json
    │   └── Readme.md
    ├── install/
    │   └── {debug|release}   <finished binaries and header files configs>
    │       ├── bin/
    │       ├── include/
    │       └── lib/
    └── ...
```

## 1.3 Submission

Create a `tar.gz` archive of your project using `tar`, but **exclude any `build` and `install` folders**.  
Then, upload the archive **next to your documentation**.

```bash
# step outside of your imr-pp folder
tar --exclude='install' --exclude='build'  -zcvf imr-pp.tar.gz imr-pp
```
