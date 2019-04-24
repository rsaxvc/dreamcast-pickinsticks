make clean

rm overbearing.cdi
rm overbearing.iso
rm 1ST_READ.bin
rm IP.bin
rm overbearing.bin
rm romdisk_boot.img
rm romdisk_boot.o

make
sh-elf-objcopy.exe -R .stack -O binary overbearing.elf overbearing.bin
scramble overbearing.bin 1ST_READ.BIN
makeip ip.txt IP.BIN
mkisofs -V TEST_ISO -G IP.BIN -joliet -rock -l -o overbearing.iso 1ST_READ.bin
cdi4dc overbearing.iso overbearing.cdi -d

rm 1ST_READ.bin
rm IP.bin
rm overbearing.bin
rm romdisk_boot.img
rm romdisk_boot.o
rm *.o
rm *.elf
