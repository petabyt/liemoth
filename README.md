# Ambarella Hack Development Kit
Unofficial documentation and hacks for Ambarella based cameras.  

# Goals
- Extensive Ambsh documentation
- Magic lantern like program (written in C)
- Quick introduction document to Ambarella software/hardware
- Ambsh interpreter/minimizer (with macros and stuff?) (parse/)
- If absolutely necessary, a custom firmware (for newer GoPros)

# File Structure:
## [ahdk](ahdk/)
Contains the main AHDK UI and source code that is injected into the  
device.
## [ashp](ashp/)
Ambsh parser. It adds extra features and generates a smaller ASH file.
## [emulate](emulate/)
Stupid "emulator". Probably will be deleted one day.
## [loader](loader/)
Ambsh script chooser, written in Ambsh.
## [platform](platform/)
Contains model information and addresses/stubs.
## [test](test/)
Bare bones assembly injection test. Generates ASH file.
## [ambsh.md](ambsh.md)
Contains extensive documentation on the Ambsh programming language.

# Help Needed
- Testing on new devices

# Thanks to
- http://spritesmods.com/?art=zx3hack&page=4 for the work done back in 2010.
- The entire Autoexec.ash/Ambarella hacking community.

## Other
- Currently, I'm working with the Activeon DX, but I also have a Gopro Hero 3+.  
- Any help and/or questions are welcome.

![Screen hacks](screen.jpg)
