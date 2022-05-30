# <p id="beast-the-build-system"></p> ***Beast*** - The Build System
<p align="center">
<img style="align: center;" src="./logoLight.png" title="Logo" height="500px"  />
</p>
Beast is a build system designed for the purpose of power,
speed and productivity. This build system tries to combine ease 
of use with high efficiency. It is very easy to use syntactically,
and also provides great build times!

[![MacOS](https://github.com/GauravDawra/Beast/actions/workflows/mac_build.yml/badge.svg)](https://github.com/GauravDawra/Beast/actions?query=workflow%3AMacOS)
[![Ubuntu](https://github.com/GauravDawra/Beast/actions/workflows/ubuntu_build.yml/badge.svg)](https://github.com/GauravDawra/Beast/actions?query=workflow%3AUbuntu)

Beast builds projects based on the information provided in a *beast build file*. In this build file, the user defines what all items need to be built (*targets*), how they should be built (*build rules*), and what all targets need to be ready to build a particular target (*dependencies*). In this way, Beast works on a comprehensive and easy to use target-dependency model. For more information about the particular aspects of a build file, see [**Writing a Beast File**](writingABeastFile.md).

Not only does Beast provide you with an easy to understand structure for all your build needs, it comes with a super-easy and intuitive syntax. This causes Beast to be a tool suitable for both highly experienced programmers and beginners.

In addition, Beast has a highly optimized build procedure which works well for multiple threads too. Understanding the build procedure can further help you write optimized beast build files. See [**Build procedure**](buildProcedure.md).

- [Introduction](#beast-the-build-system)
- [Installation](#installation)

## <p id="installation"></p>Installation

Installation of beast is super-easy.
You can either download your *system binaries* directly or you can compile it from source yourself.

For compiling the souce, you would require:
- make
- GNU G++ (>= 10.0) or Clang
- flex
- bison

Note: flex and bison are required only if the *parser.cpp/hpp* and *scanner.cpp/h* files are not present in your source code or is outdated.

Follow these steps to compile:
1. Clone the github Beast repository with the following command:
   `git clone https://github.com/GauravDawra/Beast Beast --recursive`.
   Make sure you use the *--recursive* flag since the code has some submodule dependencies
2. Move into the *Beast* directory using `cd Beast`.
3. Now we will compile the source code using *make*. If your *g++* points to one one of the suitable compilers listed above the simply run `make MODE=RELEASE`. Otherwise, you should point *CXX* environment variable to a suitable compiler and then run the above command. Your command will then look like: `CXX=<path_to_compiler> make MODE=RELEASE`.
4. An executable named *beast* should then appear in the main working directory if the compilation was successful. To add it to the $PATH at */usr/local/bin*, simply run `make install`. This is a root action so you will have to enter your password for this step. If you don't want to install this to your /usr/local/bin, you can directly use the *beast* binary.