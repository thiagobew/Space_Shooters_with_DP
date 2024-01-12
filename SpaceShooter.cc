#include "include/SpaceShooter.h"

__BEGIN_API

Thread *SpaceShooter::playerShipThread;
Thread *SpaceShooter::windowThread;
Thread *SpaceShooter::keyboardThread;
Thread *SpaceShooter::collisionThread;
Thread *SpaceShooter::purpleShipsControlThread;
Thread *SpaceShooter::minesControlThread;
Thread *SpaceShooter::bossSpawnThread;
Thread *SpaceShooter::whiteShipsControlThread;

PlayerShip *SpaceShooter::playerShipObj;
Window *SpaceShooter::windowObj;
Keyboard *SpaceShooter::kBoardObj;
Collision *SpaceShooter::collisionObj;
PurpleEnemiesControl *SpaceShooter::purpleShipsControlObj;
MinesControl *SpaceShooter::minesControlObj;
BossControl *SpaceShooter::bossControlObj;
WhiteEnemiesControl *SpaceShooter::whiteShipsControlObj;

__END_API
