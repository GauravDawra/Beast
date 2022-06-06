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
- [Getting started](#getting-started)
- [Using Beast in your project](#using-beast-in-project)
- [Licensing](#licensing)
- [Contribution](#contribution)

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
    
    This is a root action so you will have to enter your password for this step. If you don't want to install this to your */usr/local/bin*, you can directly use the *beast* binary.

## Getting started with ***Beast***
Beast has a very simple to follow Quickstart which helps you use Beast in a sample project. This quickstart can be found in the [quickstart repository](https://github.com/GauravDawra/Beast-quickstart) or in the documentation [Quickstart](https://gauravdawra.github.io/Beast-docs/quickStart/beast-quickstart) page.

It contains a very easy to follow tutorial. To learn more about what is going on in the *beast.build* file provided with the quickstart repository, see [Writing a Beast file](https://gauravdawra.github.io/Beast-docs/mainDocs/writingABeastFile).


## <p id="using-beast-in-project"> Using Beast in your project </p>

Beast is very easy to integrate in your project with the help of just one beast build file, **beast.build**. A beast file can be written with minimal syntax and is very intuitive to use. There are a bunch functionalities that make the file writing process easy and intuitive. Also, Beast command line interface can be easily used to build your project and sub-directories.

1. Place the **beast.build** file in the root working directory of your project. For more information on how to write the build file, look at [Writing a Beast file](https://gauravdawra.github.io/Beast-docs/mainDocs/writingABeastFile).

2. Once you have placed the beast file in your project directory, navigate to this directory on a shell. Simply run `beast` in your terminal to start the build process.

This will start the build process. The necessary build rules will be carried out in the order taking into account the dependencies. For more information on the build procedure, look at [Build procedure](https://gauravdawra.github.io/Beast-docs/mainDocs/buildProcedure).

You can also use beast itself for various directories and sub-directories. If you want to build a subdirectory in your project you can simply use the `-d` CLI option within the beast file at your main directory.

For example, if you have a subfolder called *sub* within the main directory of your project, place a beast file in both, this main working directory and *sub* directory. Now, from within the *beast.build* file in your main directory simply call
```
build sub:
    ! beast -d sub
```

For a hands on tutorial on building a sample project, look at [Quickstart](https://gauravdawra.github.io/Beast-docs/quickStart/beast-quickstart)!

## <p id="contribution">Contribution</p>
Beast is primarily written in C++ for speed and optimizations. You can easily contribute to Beast by making a pull request. Although, it is advised to contact me before making a pull request. For more details about contribution check out [Contribution](https://gauravdawra.github.io/Beast-docs/mainDocs/contribution) in the official documentation.

You can contact me at gaurav19039@iiitd.ac.in.

### *Great!!! You are all set to start using Beast. Go ahead and unleash the Beast!!!*