suspend 18
[writeBin "loader.o" MEM_LOADER]

# Patch for GPIO function (only works on Activeon DX)
# This is temporary. A better solution will be found later.
writeb 0xc0108018 0x04
writeb 0xc0108019 0x98
writeb 0xc010801a 0x07
writeb 0xc010801b 0xb0

touch a.ash
cardmgr > a.ash
a.ash
resume 18
