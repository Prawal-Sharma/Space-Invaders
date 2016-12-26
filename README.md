# Space-Invaders-
Final Project for the Intro to Embedded Systems course at UT Austin 

Created a Space Invaders game on the TM4C123 from ground up implementing many data acquisition systems, timers, interrupts, drivers, and hardware interfacing. 

Game Engine : Created a Game Engine in C that creates sprites and player profiles in the game. Game Engine also keeps track of all connections within the game itself - such as, collision detection, player and sprite movement, death and firing detection and more. The Game Engine is the brain of the entire project as it has data regarding all parts of movements. 

Interrupts and Timers: In order to sample the ADC and create sound through systematic voltage interruptions, many interrupts were implemented in the creation of the game. Timers were also used in order to create certain events at certain intervals. 

ADC: The Analog to Digital Converter was used in the form of the Potentiometer. The sliding of the Potentiometer created a voltage divider that was accessed through the software in order to move the player ship.

DAC: The Digital to Analog Converter was used in order to play sounds of firing missiles, enemy sprite movement, player death, and intro music. 

LCD: The Sitronix St7735 was interfaced using drivers in order to view the bitmaps on screen. The bitmaps were controlled through the Game Engine, but printed using functions implemented in the St7735 software. 
