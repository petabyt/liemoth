# Ambarella Hack Development Kit
Basically a CHDK/Magic Lantern clone for Ambarella based cameras.  
Has unofficial documentation and hacks. Don't expect anything  
too polished at the moment.

Demonstration: https://www.youtube.com/watch?v=8iN3dRujXYc

# Goals
- Extensive Ambsh documentation
- Magic lantern/CHDK like GUI program loaded onto camera
- Ambsh interpreter/minimizer

# File Structure:
## [ahdk](ahdk/)
Contains the main AHDK UI and source code that is injected into the  
device.
## [ashp](ashp/)
Ambsh parser. It adds extra features and generates a smaller ASH file.
## [loader](loader/)
Ambsh script chooser, written in Ambsh.
## [platform](platform/)
Contains model information and addresses/stubs.
## [test](test/)
Bare bones assembly injection test. Generates ASH file.
## [ambsh.md](ambsh.md)
Contains extensive documentation on the Ambsh programming language.

# Help Needed
- Porting to other models
- Stabilizing the hack

# Thanks to
- http://spritesmods.com/?art=zx3hack&page=4 for the work done back in 2010.
- The entire Autoexec.ash/Ambarella hacking community.

## Other
- Currently my only camera (with a screen) is the Activeon DX, but I also have a Gopro Hero 3+.  
- Any help and/or questions are welcome.

![Screen hacks](screen.jpg)
