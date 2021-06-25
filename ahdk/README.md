# Main AHDK Source Code
This contains the main source code for AHDK - the program  
that is loaded onto the camera.

- Files related to the build process have the first letter capitalized.

- The `.S` file extension means the file is first preprocessed
by the C preprocessor, then the ARM preprocessor.

## Building
Make parameters:  
- file: file to compile in `make minimal`
- d: output directory (where camera is mounted)
- p: platform (see ../platform)
- f: Ashp flags (see Loader.ash)

```
# Initialize files on camera
make init d=/media/user/mycameradir

# Compile test.c for your camera model
make minimal file=test.c p=activeondx d=/media/user/mycameradir
```

It may work on Windows but Ambsh needs unix file endings,  
so good luck.

## loader.S
Initial program written into memory by an `autoexec.ash` file made by `ashp`.  
It loads the code into code where a useless command resides, and calls that  
command to trigger the loader.

## main.S
The main assembly file to help with the C code.  

## ambarella.h
Contains function headers and information for Ambarella code, as well  
as how to use it.  