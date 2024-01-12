#ifndef WHITE_ENEMIES_CONTROL_H
#define WHITE_ENEMIES_CONTROL_H

#include <list>
#include <memory>
#include "threads/thread.h"
#include "threads/traits.h"

#include "Sprite.h"
#include "Window.h"
#include "Collision.h"
#include "GameConfigs.h"
#include "WhiteEnemy.h"

__BEGIN_API
class WhiteEnemy;

class WhiteEnemiesControl
{
public:
    WhiteEnemiesControl();
    ~WhiteEnemiesControl();
    void setWindowReference(Window *window);
    void setCollisionReference(Collision *collision);
    void setPlayerReference(PlayerShip *playerShip);
    void removeShip(WhiteEnemy *enemy);

    void run();

private:
    void loadSprites();
    void createShips();
    void processLoop();
    void handleShips();
    int DELAY_SHIPS_SPAWN;

    // Referências de Window e Collision para passar para as Ships
    Window *_window;
    Collision *_collision;
    PlayerShip *_playerShip;

    // Sprites
    std::list<WhiteEnemy *> ships;
    std::shared_ptr<Timer> shipsSpawnTimer;
    std::shared_ptr<Sprite> whiteShipSprite;
    std::shared_ptr<Sprite> enemyExplosionSprite;
};

__END_API

#endif