# Chess-Cpp (C++ & SFML)

Chess engine made with C++ and SFML library.

### Requirements
- SFML 2.5.1 [Download Page]()
- GNU Cross Compiler (Must be the same compiler that build SFML)

### Steps to compile
- Add SFML bin path to the system environment **PATH**
- Run command: `g++ -o Game.exe main.cpp -L"<SFML_LIBRARY_PATH>" -I"<SFML_INCLUDE_PATH>" -D"SFML_STATIC" -lsfml-graphics -lsfml-window -lsfml-system`
  - For Linux or Mac, remove extension from **Game.exe**

### Step to run
- Start **Game.exe** or **./Game** for Mac and Linux

### Credits
- Board and pieces graphics were taken from FamTrinlity's YouTube videos
