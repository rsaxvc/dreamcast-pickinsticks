all: rm-elf pickinsticks.elf

include $(KOS_BASE)/Makefile.rules

OBJS = pickinsticks.o wfont.o textoutput.o utilities.o scrollingbackground.o gamelogic.o player.o overlays.o

KOS_LOCAL_CFLAGS = -I$(KOS_BASE)/addons/zlib
	
clean:
	-rm -f pickinsticks.elf $(OBJS)
	-rm -f romdisk_boot.*

dist:
	-rm -f $(OBJS)
	-rm -f romdisk_boot.*
	$(KOS_STRIP) pickinsticks.elf
	
rm-elf:
	-rm -f pickinsticks.elf
	-rm -f romdisk_boot.*

pickinsticks.elf: $(OBJS) romdisk_boot.o 
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $@ $(KOS_START) $^ -lpng -lz -lm $(KOS_LIBS)

wfont.o: wfont.bin
	$(KOS_BASE)/utils/bin2o/bin2o $< wfont $@

romdisk_boot.img:
	$(KOS_GENROMFS) -f $@ -d romdisk_boot -v

romdisk_boot.o: romdisk_boot.img
	$(KOS_BASE)/utils/bin2o/bin2o $< romdisk_boot $@

run: pickinsticks.elf
	$(KOS_LOADER) $<


