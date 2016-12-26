#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "ADC.h"
#include "images.h" 
#include "Sound.h"

#define MAX_REG_MISS 100
#define MAX_ENEM_MISS 100
#define MAX_SPEC_MISS 1

unsigned char Enemies; // Keep track of the enemies for Random()
unsigned char RegMissCount;  // Number of missiles on screen 
unsigned char EnemMissCount; // Number of enem missiles on screen 
unsigned char SpecMissCount; // Number of spec missiles on screen 
unsigned long Score; // Keep track of the score for the player 
 
unsigned long x; // Flag for main to check if game is over 

// Conversion for ADC
uint32_t Convert(uint32_t input){
 return ((56*(input))+27891)/128;
}

// *** Struct Declaration for the Objects ***

struct Player {
	unsigned long x; // x coordinate
	unsigned long y; // y coordinate
	unsigned char life; // if dead, life = 0, anything else is alive
	const unsigned short *image; // points to image 
	unsigned char explode; // if value is greater than 0, explode the player 
}; 
typedef struct Player p1; 

struct Enemy {
	unsigned long x; // x coordinate
	unsigned long y; // y coordinate
	unsigned char life; // if dead, life = 0, anything else is alive
	const unsigned short *image; // points to image 
	unsigned char explode; // if value is greater than 0, explode the player 
	unsigned long points; 
};
typedef struct Enemy e1; 

struct RegMiss {
unsigned long x; // x coordinate
unsigned long y; // y coordinate
unsigned char life; // if dead, life = 0, anything else is alive
const unsigned short *image; // points to image 

};
typedef struct RegMiss rm1; 

struct EnemMiss {
unsigned long x; // x coordinate
unsigned long y; // y coordinate
unsigned char life; // if dead, life = 0, anything else is alive
const unsigned short *image; // points to image 	
}; 
typedef struct EnemMiss em1; 

struct SpecMiss {
unsigned long x; // x coordinate
unsigned long y; // y coordinate
unsigned char life; // if dead, life = 0, anything else is alive
const unsigned short *image; // points to image 	
}; 
typedef struct SpecMiss sm1; 

p1 Player; 
e1 Enemy[6]; 
rm1 RegMiss[MAX_REG_MISS]; 
em1 EnemMiss[MAX_ENEM_MISS]; 
sm1 SpecMiss[MAX_SPEC_MISS]; 
// Random Number Generator between 0 and number of enemies on screen
unsigned long RandomGen(unsigned long enemies){
 return ((Random32()% enemies)); 

}


//*** Movement Functions ***

// Move all enemies that are alive, 2 pixels to the right
// if the enemy happens to reach the end of the screen than start from left again
void Enemy_Move(void){
unsigned char i; 
for(i=0; i<6; i++){
if(Enemy[i].x < 127){
Enemy[i].x +=2; // Right two pixels

} 
else{
Enemy[i].x = 0; // Start from left again
//Enemy[i].y += 9; 	
}

}	

}

// Move Player based on ADC input
void Player_Move(void){
	Player.x = (Convert(ADC_In())*55) >> 10; 
}

// Move the shot that's been fired
void RegMiss_Move(void){
unsigned char i; 
for(i=0; i<MAX_REG_MISS; i++){
if(RegMiss[i].life == 1){

if(RegMiss[i].y == 0){
RegMiss[i].life = 0;
RegMissCount--; 
}
else{
RegMiss[i].y -= 2; // Move up two pixels 
}
}		
}
}

void SpecMiss_Move(void){
unsigned char i;
for(i=0; i<MAX_SPEC_MISS; i++){
if(SpecMiss[i].life == 1){

if(SpecMiss[i].y == 0){
SpecMiss[i].life = 0;
SpecMissCount--; 
}
else{
SpecMiss[i].y -=2; // Move up two pixels 
}
}
}
	
}

void EnemMiss_Move(void){
unsigned char i; 
for(i=0; i<MAX_ENEM_MISS; i++){
if(EnemMiss[i].life == 1){
if(EnemMiss[i].y == 160){
EnemMiss[i].life = 0; 
EnemMissCount--; 	
}
else{
EnemMiss[i].y += 2; // Move down two pixels 
}
}
}
}

// Move all of the objects that need to be moved 
void MoveThings(void){
Enemy_Move(); 
Player_Move(); 
RegMiss_Move(); 
EnemMiss_Move(); 
SpecMiss_Move(); 
}




// *** Game Changing States ***
void Game_Over(void){

 // ST7735_FillScreen(0x0000);            // set screen to black
  ST7735_SetCursor(1, 1);
  ST7735_OutString("GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_OutString("Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString("Earthling!");
  ST7735_SetCursor(2, 4);
	ST7735_OutString("Score:");
  LCD_OutDec(Score);

}

void Game_Init(void){
	// Start game with 6 enemies
	Enemies = 6; 
	
	EnemMissCount = 0; 
	RegMissCount = 0; 
	SpecMissCount = 0; 
	Player.x = 52; 
	Player.y = 159; 
	Player.life = 1; 
	//Player.image = PlayerShip0; 
	Player.image = PlayerShipNew; 
	Player.explode = 0; 
	
	Enemy[0].x = 0; 
	Enemy[0].y = 9;
	Enemy[0].life = 1;
	Enemy[0].image = SmallEnemy10pointA;
	Enemy[0].explode = 0;
	Enemy[0].points = 10;
	
	Enemy[1].x = 20; 
	Enemy[1].y = 9;
	Enemy[1].life = 1;
	Enemy[1].image = SmallEnemy10pointB;
	Enemy[1].explode = 0;
	Enemy[1].points = 10;
	
	Enemy[2].x = 40; 
	Enemy[2].y = 9;
	Enemy[2].life = 1;
	Enemy[2].image = SmallEnemy20pointA;
	Enemy[2].explode = 0;
	Enemy[2].points = 20;
	
	Enemy[3].x = 60; 
	Enemy[3].y = 9;
	Enemy[3].life = 1;
	Enemy[3].image = SmallEnemy20pointB;
	Enemy[3].explode = 0;
	Enemy[3].points = 20;
	
	Enemy[4].x = 80; 
	Enemy[4].y = 9;
	Enemy[4].life = 1;
	Enemy[4].image = SmallEnemy30pointA;
	Enemy[4].explode = 0;
	Enemy[4].points = 30;
	
	Enemy[5].x = 100; 
	Enemy[5].y = 9;
	Enemy[5].life = 1;
	Enemy[5].image = SmallEnemy30pointB;
	Enemy[5].explode = 0;
	Enemy[5].points = 30;

	ST7735_FillScreen(0x0000);            // set screen to black
  
 

  ST7735_DrawBitmap(Enemy[0].x, Enemy[0].y, Enemy[0].image, 16,10);
  ST7735_DrawBitmap(Enemy[1].x, Enemy[1].y, Enemy[1].image, 16,10);
  ST7735_DrawBitmap(Enemy[2].x, Enemy[2].y, Enemy[2].image, 16,10);
  ST7735_DrawBitmap(Enemy[3].x, Enemy[3].y, Enemy[3].image, 16,10);
  ST7735_DrawBitmap(Enemy[4].x, Enemy[4].y, Enemy[4].image, 16,10);
  ST7735_DrawBitmap(Enemy[5].x, Enemy[5].y, Enemy[5].image, 16,10);
	
}

// *** Drawing Functions ***

// Draw the Player at the respective locations, if player has been hit, display explosion
void DrawPlayer(void){
if(Player.life > 0){

//ST7735_DrawBitmap(Player.x, Player.y, Player.image, 18, 8); 
	ST7735_DrawBitmap(Player.x, Player.y, Player.image, 28, 12); 
}
else if(Player.explode){
ST7735_DrawBitmap(Player.x, Player.y, BigExplosion0, 28, 12); 
}
	
}

// Draw the enemies if they are alive 
void DrawEnemies(void){
unsigned char i; 
for(i=0; i<6; i++){
if(Enemy[i].life > 0){
ST7735_DrawBitmap(Enemy[i].x, Enemy[i].y, Enemy[i].image, 16, 10); 
}
else{
if(Enemy[i].explode){
ST7735_DrawBitmap(Enemy[i].x, Enemy[i].y, smallexplosion0, 16, 10); 
}
}
}	
}

// Draw the regular missiles 
void DrawRegMiss(void){
unsigned char i; 
for(i=0; i<MAX_REG_MISS; i++){
if(RegMiss[i].life == 1){
ST7735_DrawBitmap(RegMiss[i].x, RegMiss[i].y, RegMiss[i].image, 4, 14); 
}
 
} 
	
}

//Draw the special missile
void DrawSpecMiss(void){
unsigned char i; 
for(i=0; i<MAX_SPEC_MISS; i++){
if(SpecMiss[i].life ==1){
ST7735_DrawBitmap(SpecMiss[i].x, SpecMiss[i].y, SpecMiss[i].image, 20, 20); 
}

}

}

void DrawEnemMiss(void){
unsigned char i; 
for(i=0; i<MAX_ENEM_MISS; i++){
if(EnemMiss[i].life == 1){
ST7735_DrawBitmap(EnemMiss[i].x, EnemMiss[i].y, EnemMiss[i].image, 4, 14); 
}
}

}

// Draw Everything

void Draw_Game(void){

DrawPlayer(); 
DrawEnemies(); 
DrawRegMiss(); 
DrawEnemMiss(); 
DrawSpecMiss(); 
}

void RegMiss_Fire(void){
 
if(RegMissCount < MAX_REG_MISS){

RegMiss[RegMissCount].x = Player.x + 14; 
RegMiss[RegMissCount].y = 155; 
RegMiss[RegMissCount].life = 1;
RegMiss[RegMissCount].image = Missile0New; 	
RegMissCount++; 
}	
}

void SpecMiss_Fire(void){
if(SpecMissCount < MAX_SPEC_MISS){
SpecMiss[SpecMissCount].x = Player.x + 6; 
SpecMiss[SpecMissCount].y = 155; 
SpecMiss[SpecMissCount].life = 1;
SpecMiss[SpecMissCount].image = bomb; 
SpecMissCount++; 
}
	
}

void EnemMiss_Fire(void){
unsigned long z = RandomGen(Enemies);
if(EnemMissCount < MAX_ENEM_MISS){
EnemMiss[EnemMissCount].x = Enemy[z].x; 
EnemMiss[EnemMissCount].y = Enemy[z].y + 2; 	
EnemMiss[EnemMissCount].life = 1; 
EnemMiss[EnemMissCount].image = Missile0New2;
EnemMissCount++; 	
}	

	
}

// Collision Check Functions 

// Check if  the enemy shots hit any of the players
void EnemMiss_Collision(void){
 
unsigned char j; 
	
for(j=0; j<MAX_ENEM_MISS; j++){
if(EnemMiss[j].life == 1){
if((EnemMiss[j].x > Player.x) && (EnemMiss[j].x < Player.x + 28) && (EnemMiss[j].y == Player.y)){
EnemMiss[j].life = 0;
Player.life = 0; 
Player.explode = 1;
EnemMissCount--; 
}
	
}
}

}

// Check if the player missile hits any of the enemies
void RegMiss_Collision(void){	

unsigned char i; 
unsigned char j; 
for(j=0; j<MAX_REG_MISS; j++){
if(RegMiss[j].life == 1){
for(i=0; i<6; i++){
if((RegMiss[j].x > Enemy[i].x - 8) && (RegMiss[j].x < Enemy[i].x + 8) && (RegMiss[j].y == Enemy[i].y)){
RegMiss[j].life = 0; 
Score += Enemy[i].points; 
Enemy[i].life = 0; 
Enemy[i].explode = 1; 	
Enemy[i].points = 0; 
RegMissCount--; 
Enemies--; 
Sound_Killed(); 
}
}
}

}

}

void SpecMiss_Collision(void){	

unsigned char i; 
unsigned char j; 
for(j=0; j<MAX_SPEC_MISS; j++){
if(SpecMiss[j].life == 1){
for(i=0; i<6; i++){
if((SpecMiss[j].x > Enemy[i].x -20 ) && (SpecMiss[j].x < Enemy[i].x + 20 ) && (SpecMiss[j].y == Enemy[i].y)){
SpecMiss[j].life = 0; 
Score += Enemy[i].points; 
Enemy[i].life = 0; 
Enemy[i].explode = 1; 	
Enemy[i].points = 0; 
//SpecMissCount--; If you want more missiles to show up on screen, uncomment this 
Enemies--; 
Sound_Killed(); 
}
}
}

}

}


// Check all of the collisions 
void Check_Coll(void){
RegMiss_Collision(); 
SpecMiss_Collision(); 	
EnemMiss_Collision(); 
	
}


// Check Game Over

void Check_GameOver(void){
unsigned char i;
unsigned char count; 
count = 0; 	
for(i=0; i <6; i++){
if(Enemy[i].life == 0){
count++; 
}

}
if(count==6 || Player.life == 0){

x = 1;  
}

else{
x = 0;  
}
}





