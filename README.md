# <p id="beast-the-build-system"></p> ***Beast*** - The Build System
<p align="center">
<img style="align: center;" src="resources/logo/logo.png" title="Logo" height="600px"  /></p>
Beast is a build system designed for the purpose of power,
speed and productivity. This build system tries to combine ease 
of use with high efficiency. It is very easy to use syntactically,
and also provides great build times!

The complete documentation for ***Beast*** can be found [here](https://gauravdawra.github.io/Beast-docs/).

---

[![MacOS](https://github.com/GauravDawra/Beast/actions/workflows/mac_build.yml/badge.svg)](https://github.com/GauravDawra/Beast/actions?query=workflow%3AMacOS)
[![Ubuntu](https://github.com/GauravDawra/Beast/actions/workflows/ubuntu_build.yml/badge.svg)](https://github.com/GauravDawra/Beast/actions?query=workflow%3AUbuntu)

Beast builds projects based on the information provided in a *beast build file*. In this build file, the user defines what all items need to be built (*targets*), how they should be built (*build rules*), and what all targets need to be ready to build a particular target (*dependencies*). In this way, Beast works on a comprehensive and easy to use target-dependency model. For more information about the particular aspects of a build file, see [**Writing a Beast File**](https://gauravdawra.github.io/Beast-docs/mainDocs/writingABeastFile).

Not only does Beast provide you with an easy to understand structure for all your build needs, it comes with a super-easy and intuitive syntax. This causes Beast to be a tool suitable for both highly experienced programmers and beginners.

In addition, Beast has a highly optimized build procedure which works well for multiple threads too. Understanding the build procedure can further help you write optimized beast build files. See [**Build procedure**](https://gauravdawra.github.io/Beast-docs/mainDocs/buildProcedure).

- [Introduction](#beast-the-build-system)
- [Installation](#installation)
- [Quickstart](#quickstart)

## <p id="installation"></p>Installation


Installing Beast is super-easy. You can either download your *system binaries* directly or you can compile it from source yourself. 

### Pre-compiled binaries
You can directly download your system specific binaries from the release section on github.

Once you have downloaded the binaries, make sure that the location of this executable is present in the *PATH* environment variable. */usr/local/bin* is the preferred position to place the *beast* executable.

### Compiling from source
For compiling the souce, you would require:
- make
- GNU G++ (>= 10.0) or Clang
- flex
- bison

Note: flex and bison are required only if the *parser.cpp/hpp* and *scanner.cpp/h* files are not present in your source code or is outdated.

Follow these steps to compile:
1. Clone the github Beast repository with the following command:
   ```
   git clone https://github.com/GauravDawra/Beast Beast --recursive
   ``` 
   Make sure you use the *--recursive* flag since the code has some submodule dependencies
    
2. Move into the *Beast* directory using 

        cd Beast
3. Now we will compile the source code using *make*. If your *g++* points to one of the suitable compilers listed above the simply run 
    
        make MODE=RELEASE 

    Otherwise, you should point *CXX* environment variable to a suitable compiler and then run the above command. Your command will then look like: `CXX=<path_to_compiler> make MODE=RELEASE`.
4. An executable named *beast* should then appear in rhe main working directory if the compilation was successful. To add it to the $PATH at */usr/local/bin*, run 
    
        make install
    
    This is a root action so you will have to enter your password for this step. If you don't want to install this to your /usr/local/bin, you can directly use the *beast* binary.


## <p id="quickstart">Beast quickstart</p>
While the specifics of Beast build file are not required for the purpose of this quickstart, it is highly recommended to read [**Writing a Beast File**](https://gauravdawra.github.io/Beast-docs/mainDocs/writingABeastFile).

We will build a sample project available at https://github.com/GauravDawra/Beast-quickstart, with the help of Beast. A Beast build file has already been provided with this repository.
Make sure that Beast has already been installed before moving forward. See [Installation](#installation).

Follow these steps to build the repository:
### Step 1: Clone the repository
First we will clone this repository locally to test out Beast. To do this, open a terminal and type:
```
git clone https://github.com/GauravDawra/Beast-quickstart.git beast-quickstart
```
This will clone the repository in a *beast-quickstart* folder.

### Step 2: Open the folder
Next, navigate to the cloned repository by typing:
```
cd beast-quickstart
```
Open the *beast.build* file to check out it's contents. For the purpose of this tutorial, it is not important to understand what this beast file does. You can check out the [**Writing a Beast File**](https://gauravdawra.github.io/Beast-docs/mainDocs/writingABeastFile) page in the documentation.

The folder structure will be:

    beast-quickstart
    ├── sub
    │   ├── beast.build
    │   └── subMain.cpp
    ├── README.md
    ├── beast.build
    ├── main.cpp
    ├── util.cpp
    └── util.h

Broadly speaking, this build file defines 3 targets: *main*: our final executable, *util.o*: an object file for utility functions and *buildSub*: a target to build subdirectory *sub*. The executable is dependent on the object file.
Note that the *sub* folder itself contains a *beast.build* file to build targets specific to the folder.

Remember to use tabs inside the build rules when giving commands, and not just spaces. If the shell commands inside the build rules, commands followed '!' (exclamation mark), are indented using spaces instead of a tab, make sure to convert these spaces into a single tab indent.

### Step 3: Building via *Beast*
Now that we have setup everything, we are ready to build our project. To start the build, simply run the following command:
```
beast
```
This will start your build process and will also tell you which target is being currently built. Once the build is complete, you will see two new files in *beast-quickstart* (current) folder, *main* and *util.o*.

### Step 4: Running the executable
To run the newly created executable, run the following command:
```
./main
```
You should also try running the executable *subMain* created in the folder *sub*:
```
./sub/subMain
```
---
Great!!! You have completed the quickstart tutorial for Beast. Move on to the [documentation](https://gauravdawra.github.io/Beast-docs/) for learning more about Beast and build files to start creating your own projects!!

## Licensing
Beast project uses the Apache Licencse 2.0 and it can be found [here](https://github.com/GauravDawra/Beast/blob/master/LICENSE) in the repository.