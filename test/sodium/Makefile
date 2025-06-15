.PHONY: watch

windows:
	x86_64-w64-mingw32-gcc main.c -o hello_sodim_64.exe
windows32:
	i686-w64-mingw32-gcc main.c -o helloc_sodium_32.exe
linux:
	gcc  main.c -o hello_sodium_linux -lsodium
default: linux
