# Main AHDK Source Code
This contains the main source code for AHDK - the program  
that is loaded onto the camera.

- Files related to the build process have their first letter capitalized.

- The `.S` file extension means the file is first preprocessed
by the C preprocessor, then the ARM preprocessor.

## Building
Make parameters:  
- file: file to compile. (default test.c)
- d: output directory (where camera is mounted)
- p: platform (see ../platform) (default activeondx)
- f: Ashp flags (see Loader.ash) (optional)

```
# Initialize files on camera
make init font d=/media/user/mycameradir

# Compile test.c for your camera model
make minimal file=test.c p=activeondx d=/media/user/mycameradir
```

## Windows Compilation
See `Make.bat` (buggy)  

## loader.S
Initial program written into memory by an `autoexec.ash` file made by `ashp`.  
It loads the code into code where a useless command resides, and calls that  
command to trigger the loader.

## main.S
The main assembly file to help with the C code.  
(with both targets `minimal` and `ahdk`)

## ambarella.h
Contains function headers and information for Ambarella code, as well  
as how to use it.  