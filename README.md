# Liemoth

**Liemoth (formerly AHDK) is a free and open source software add-on for Ambarella based devices.**

Demonstration: https://www.youtube.com/watch?v=8iN3dRujXYc    

![Screen hacks](https://petabyt.dev/filedump/screen.jpg)

## What can it do?
- Run [Magic Lantern](https://www.magiclantern.fm/)/[CHDK](https://chdk.fandom.com/wiki/CHDK) like interactive menu loaded onto camera
- Real time C/C++ code execution over WiFi
- Run Linux shell commands
- [Games](https://www.youtube.com/watch?v=w0OYA6yEK8c) :)
- Also, has an [Ambsh preprocessor + minimizer](https://github.com/petabyt/liemoth/tree/master/ashp) and [Extensive Ambsh documentation](https://github.com/petabyt/liemoth/blob/master/AMBSH.md)

## Goals:
- Module system
- Motion detection photo (in progress)
- Raw photos
- Raw video (?)
- Porting to other models (A9, A12?)
- Reverse engineering sensor functions
- New features

## Building
Liemoth can be built on Windows and Linux.  
Dependencies:  
- Host GCC/TCC
- Arm GCC
- Git bash or msys32 (if on Windows)

Head into a directory and type `make help`.  
It should be pretty straightforward.  

This is the compiler used by Ambarella (I think). You can also    
use it to compile apps that run on the camera's Linux system.  
[arm-none-linux-gnueabi](https://sourcery.mentor.com/public/gnu_toolchain/arm-none-linux-gnueabi/arm-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu.tar.bz2)  
It's older (2009), so it will generate assembly around 2x the size of newer GCCs.  
Personally, I use [gcc-arm-none-eabi-5_4-2016q3](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads/5-2016-q3-update), since it's the same compiler that  
[Magic Lantern](https://www.magiclantern.fm/) uses.  

## Thanks to
- http://spritesmods.com/?art=zx3hack&page=4 for the work done back in 2010
- The GoPrawn community https://www.goprawn.com/
- The entire hacking/reverse engineering community

## Other
- My testing cameras are the Activeon DX and GoPro Hero 3+.
- Any help and/or questions are welcome. Just make an issue. 
- **No warranty - If you break it, you keep both pieces.**
- There is some (possibly leaked) Ambarella source code out there.  
I have decided to not use it, and contributors must not use it either.  
