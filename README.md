# SFML-SWOOSH-Codeblock-Template
Codeblock project that handles dependencies to run the C++ SFML library for graphics and the SWOOSH library for transitions

## Codeblock 
- Install codeblock 20.03

## Compiler
- Copy Mingw 13 in the codeblock folder
- In the compiler setting of codeblock, link all binaries
- Compile an hello world program to make sure the compiler works
- Try to debug as well, you have to set the debugger executable in the debugger tab

## SFML
- Copy the SFML library in the codeblock folder
- On the compiler settings don't touch anything, those are compiler wide, and you don't want to burden non SFML projects with unnecessary dependencies
- In the project, the build option you have three level, project, debug and release
- In the project, add the SFML_STATIC defile to static link libraries
- Add in the project search directory include and linker, the SFML include and lib folders
- In the debug tab, link all the .a in the lib folder. Remove all not -d .a. Remove the provided freetype.a and just write "freetype" to use the builtin C++ font binaries
- In the release tab, link all the .a in the lib folder. Remove all the -d .a. Remove the provided freetype.a and just write "freetype" to use the builtin C++ font binaries
- In the release target options revove the console and leave GUI application, so when you compile for release the console won't pop up
-In the project folder add the dlls. The release doesn't need the -d dlls, keep them both during develop

## SWOOSH
- Add the SWOOSH source
- In the project, add the SWOOSH folder to properly see the includes

## Resource
- You'll need resources, e.g. images. Make a resource folder in the project.

## Package
- TODO: Make script to package the executable, binaries and proper dll

