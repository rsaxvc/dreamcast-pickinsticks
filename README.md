# Overbearing Burgers for the Sega Dreamcast

**Overbearing Burgers** is a **Sega Dreamcast** homebrew game featuring a hungry brown bear. The bear must jump at the right time to not only not hit the rocks on the ground, but also to not miss any of the hamburgers.

**Overbearing Burgers** is very easy to play; the only button used is `A`, which will make the bear jump. 

This mini-game was developed by [Sebastian Mihai](http://sebastianmihai.com) and was released the **December 20, 2016**.

# Compiling

To compile **Overbearing Burgers**, you will need a modern [KallistiOS](http://gamedev.allusion.net/softprj/kos/) environment, like [DreamSDK](https://www.dreamsdk.org/) or any other modern [KallistiOS](http://gamedev.allusion.net/softprj/kos/) 2.0.0+ environment.

Basically the procedure to build this mini-game is pretty simple:

1. Open your shell prompt.
2. Enter the `src/` directory.
3. Enter `make && make dist`.

You will get an `overbearing.elf` file. Follow the standard procedure to generate a selfboot disc image. Basically, if you are under [DreamSDK](https://www.dreamsdk.org/):

	mkdir cd_root
	elf2bin overbearing.elf
	scramble overbearing.bin cd_root/1ST_READ.BIN
	ipcreate -silent -m "SEBASTIANMIHAI" -a "OVERBEARING BURGERS"
	makedisc overbearing.cdi cd_root IP.BIN
	
You'll have a ready-to-use `overbearing.cdi` file, that you can burn or use with [Demul](http://demul.emulation64.com/).

# Credits

All credits goes to [Sebastian Mihai](http://sebastianmihai.com).
