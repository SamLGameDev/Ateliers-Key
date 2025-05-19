# Adding UE5 Game Project

1. Open the **ROOT** folder of the UE5 project you just created and copy `yourgame.uproject`, `Content`, `Config`, and `Source` into this folder.
2. If your `yourgame.uproject` file and `Content`, `Config`, `Source` folders are in the same directory as the repositories `.gitignore` file, then your setup is correct.

Once you have completed the above steps you're ready to open the project and start working.

# Opening The Project On A New Device

When opening an unreal project on a new machine for the first time,  you should 
1. Right click the `yourgame.uproject` file and select the `Generate Visual Studio project files` option.
2. When this is complete double click the `yourgame.sln` file  to open Visual Studio.
3. Compile the game from Visual Studio by clicking `Local Windows Debugger`. 

## Opening for Code

If you are looking to complete some work in C++ for your project, then it is best to open you project by clicking on the `yourgame.sln` file. You will then need to compile from visual studio each time you wish to then work in the engine environment.

## Opening for other tasks

If you are not performing any programming, then you can easily open the project by double clicking `yourgame.uproject`. Make sure you click yes on the prompt asking to compile. 
