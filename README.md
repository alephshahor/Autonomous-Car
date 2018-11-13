# Autonomous Car

This program simulates the behaviour of an autonomous car  picking-up passengers and its path finding algorythms on a grid with obstacles.

We simulate an M x N grid with free cells and occupied cells (obstacles). Our car can move freely between free cells on a NSEW movement (no diagonal movements). We also can put freely obstacles in the grid (and remove them) with the mouse.

We are using c++ for general programing, and for the graphics we are using the open source [SFML libraries](https://www.sfml-dev.org).

## How to execute the program

Once you've installed SFML library in your computer using the comand:
```sudo apt-get install libsfml-dev```<br>
 you should be able to execute the program after running ```make``` and executing ```./bin/AutonomousCar``` or using the alias ```make run``` ( It's important to run this executable from outside the bin directory, otherwise you'll get an error loading the textures )

 **In case of any question about using the simulator please read the report.**

Authors:
* Adrián Álvarez León
* Andrés Concepción Afonso
* Brian Samir Santamaría Valero
