#include "stdint.h" 
 
// Initializes the game with the enemies and player at neutral locations

void Game_Init(void);


// Displays the "Game Over" Display
void Game_Over(void); 

// Move enemies to the right two pixels until they hit edge
void Enemy_Move(void);

// Move all the things that need to be moved
void MoveThings(void); 

// Draw the things needed to be drawn
void Draw_Game(void); 

// Init the Regular Missile 
void RegMiss_Fire(void);

// Init the Spec Missile
void SpecMiss_Fire(void); 

// Check all of the collisions in the game
void Check_Coll(void); 

// Global Variable that lets main() know if all of the enemies have been killed 
extern unsigned long x; 

// Fire enemy missiles
void EnemMiss_Fire(void);

// Tiimer to fire enemy missiles
void Timer0_Init(void(*task)(void), uint32_t period); 

// Check if all of the enemies are dead or if the player is dead
void Check_GameOver(void); 

