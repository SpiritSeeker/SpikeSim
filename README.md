# SpikeSim
A modular neuronal network simulator

## Cloning the repo
```shell
git clone --recurse-submodules https://github.com/SpiritSeeker/SpikeSim
```

## Linux

### Dependencies
A working installation of Python and matplotlib is required. Please update the Python version and path in ```premake5.lua``` before you run premake.

### Compiling and running
From inside the root SpikeSim directory, run
```shell
vendor/bin/premake/premake5 gmake2
make
./bin/SpikeSim
```
## Windows

### Compiling and running
From inside the root SpikeSim directory, run the ```GenerateProjects.bat``` file by double clicking it.
This should generate a Visual Studio 2019 solution file. Open the solution with Visual Studio and compile.
