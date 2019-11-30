make clean

rm pickinsticks.cdi
rm pickinsticks.iso
rm 1ST_READ.bin
rm IP.bin
rm pickinsticks.bin
rm romdisk_boot.img
rm romdisk_boot.o

make
sh-elf-objcopy.exe -R .stack -O binary pickinsticks.elf pickinsticks.bin
scramble pickinsticks.bin 1ST_READ.BIN
makeip ip.txt IP.BIN
mkisofs -V TEST_ISO -G IP.BIN -joliet -rock -l -o pickinsticks.iso 1ST_READ.bin
cdi4dc pickinsticks.iso pickinsticks.cdi -d

rm 1ST_READ.bin
rm IP.bin
rm pickinsticks.bin
rm romdisk_boot.img
rm romdisk_boot.o
rm *.o
rm *.elf
