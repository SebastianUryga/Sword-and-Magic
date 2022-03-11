# Open Arena of Swords and Magic

---

## Executing and Compile application 

To execute application on local machine we can use CMake version 3.0 or newer.
The CMakeList.txt we can find in catalog Sword-and-Magic/OpenArena.

or

### Windows
 - [DOWNLOAD PACKAGE ZIP](https://github.com/SebastianUryga/Sword-and-Magic/releases/download/v0.1.1/Release.zip)
 - unzip package
 - execute file OpenArena.exe
 
### Linux
 - clone repo       ```git clone https://github.com/SebastianUryga/Sword-and-Magic.git```
 - install SFML library ```sudo apt install libsfml-dev```
 - go to catalog with source code ```cd Sword-and-Magic/OpenArena/src/```
 - compile program          ```g++ -std=c++17 *.cpp -I. -o OASM $(pkg-config --libs sfml-all)```
 - execute program            ```./OASM```


---
## About Application
Open Arena of Swords is an original strategy game implemented fully in C++ and uses graphical SFML library.
Game is inspired by classic titles such as Heroes of Might and Magic 3 or Age of Empires.

---
## Description
#### Main Menu
After executing application  we will be shown a Main Menu.
Here we can decide to start a campain, play custom game, go to scenario editor, settings or we can trun off application .
#### Editor
Here we can set garnisons which define two armys that will be fight with each other when plaing custom scenario. Double clicking slots, show the window which we can set our unit - type and quantity.
#### Game Mode
Now we can manage our units which will apper on the left site of battlefield, by giving them orders.
To do so you have to select units using mouse, and now you can:
- give them attack order by Right-Click place, where enemy is standing
- give move order to place them on tile you Right-Click
- give them aggressive position using button below
- give them defence position using button below

As a commander you can also cast spell which you can find opening your spell book. Click button below. 

#### Campain Mode
There are defined nine scenario which eight is block. To unblock them you have to win available levels.

---
## Author:
Sebastian Uryga
sebastian.uryga@gmail.com
