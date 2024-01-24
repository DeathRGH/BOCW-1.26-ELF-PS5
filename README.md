# Black Ops Cold War PS5 ELF

This is the example project for the custom elf loader built for Black Ops Cold War on PlayStation5.

You can find the loader here:
https://github.com/DeathRGH/BOCW-PS5-ELF-Loader

Contributions of any kind are welcome!
Go make cool stuff :)

## Compilation
The project makes use of the Post-Build-Event in Visual Studio.<br/>
Make sure you have the linux sub system for windows (wsl) installed.<br/>
If you have issues compiling with older version of visual studio (pre 2022) try to replace the path in the Post-Build-Event with the following:
```
powershell.exe /c C:\Windows\sysnative\wsl.exe
```
Take a look at [this](https://github.com/DeathRGH/BOCW-1.26-ELF-PS5/blob/master/Post-Build-Event-VS2015-19.txt) for details.

## Credits

- [Alaix](https://twitter.com/HeyImAlaix) (Unlock All Patch)
- [zhm86](https://twitter.com/JayChou03680255) (12 Classes Patch)
