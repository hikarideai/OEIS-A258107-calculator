# OEIS-A258107-calculator
This application can compute any member of [OEIS A258107 sequence](https://oeis.org/A258107).

If you have powerful computer, you can give it a try and become famous :)

### Libraries
This application uses:
 * [SFML](https://github.com/SFML/SFML) library
 * [panks BigInteger](https://github.com/panks/BigInteger) implementation

### Generated files
This application generates two files:
 * stateSave to store latest checked value
 * result.txt - n-th member of sequence

### Compiling
To compile the source code you will need a CMake at least version 2.8, then you can use cmakeGUI or command-prompt to generate build files.

Here is an example of how to compile the source with Make and the GCC compiler on the command-prompt:
```bash
cd build/
cmake ..
make
```

If you want to use exactly MingGW generator:
```bash
cmake -G "MingGW Makefiles" ..
```

