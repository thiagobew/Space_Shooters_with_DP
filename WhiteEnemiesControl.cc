#include "include/WhiteEnemiesControl.h"

__BEGIN_API

std::shared_ptr<Sprite> whiteShipSprite;

WhiteEnemiesControl::WhiteEnemiesControl()
{
    this->loadSprites();
    this->DELAY_SHIPS_SPAWN = GameConfigs::fps * 5; // 10seg
    this->shipsSpawnTimer = std::make_shared<Timer>(GameConfigs::fps);
    this->shipsSpawnTimer->create();
    this->shipsSpawnTimer->startTimer();
}

WhiteEnemiesControl::~WhiteEnemiesControl() {
    this->shipsSpawnTimer.reset();
    this->whiteShipSprite.reset();
    this->enemyExplosionSprite.reset();
}

void WhiteEnemiesControl::setWindowReference(Window *window) { this->_window = window; }
void WhiteEnemiesControl::setCollisionReference(Collision *collision) { this->_collision = collision; }
void WhiteEnemiesControl::setPlayerReference(PlayerShip *playerShip) { this->_playerShip = playerShip; }
void WhiteEnemiesControl::removeShip(WhiteEnemy *enemy)
{
    if (this->ships.size() > 0)
        this->ships.remove(enemy);
}

void WhiteEnemiesControl::run()
{
    this->loadSprites();
    while (!GameConfigs::finished)
    {
        if (this->_window == nullptr || this->_collision == nullptr)
        {
            Thread::yield();
            continue;
        }

        this->processLoop();
        Thread::yield();
    }
}

void WhiteEnemiesControl::processLoop()
{
    // Há uma dependência aqui do timer ser maior do que o tempo para o ultimo sair da tela por causa de referência de ponteiros
    if (this->shipsSpawnTimer->getCount() > this->DELAY_SHIPS_SPAWN)
    {
        this->createShips();
        // Reset o timer
        this->shipsSpawnTimer->srsTimer();
    }
    this->handleShips();
}

void WhiteEnemiesControl::handleShips()
{
    for (auto shipItem = this->ships.begin(); shipItem != this->ships.end();)
    {
        WhiteEnemy *ship = *shipItem;
        shipItem++;

        if (ship->canFire())
        {
            // Chama o método attack do ship mas essa função aqui que vai lidar com a criação dos vetores
            ship->attack();

            Point position = ship->getPosition();
            Vector v1 = Vector(0, 0);
            v1.Angle(_playerShip->getPosition(), position, 1);

            Laser *laser1 = new Laser(position, ship->getColor(), ship->getVector() * 2, false);
            //Laser *laser2 = new Laser(ship->getPosition(), ship->getColor(), ship->getVector(), false);

            this->_collision->addEnemiesShot(laser1);
            //this->_collision->addEnemiesShot(laser2);

            this->_window->addDrawableItem(laser1);
            //this->_window->addDrawableItem(laser2);
        }
    }
}

void WhiteEnemiesControl::createShips()
{
    if (GameConfigs::bossExists)
        return;

    int height = GameConfigs::windowHeight;
    int width = GameConfigs::windowWidth;
    Point p1 = Point(width, height / 2);
    Point p2 = Point(width + 80, height / 2);
    Point p3 = Point(width + 160, height / 2);

    Vector v1 = Vector(0, 0);
    v1.Angle(_playerShip->getPosition(), p1, 1);

    Vector v2 = Vector(0, 0);
    v2.Angle(_playerShip->getPosition(), p2, 1);

    Vector v3 = Vector(0, 0);
    v3.Angle(_playerShip->getPosition(), p3, 1);


    // Cria os 5 ships white
    WhiteEnemy *ship1 = new WhiteEnemy(p1, Vector(-180, 0), this->whiteShipSprite, this->enemyExplosionSprite, this);
    WhiteEnemy *ship2 = new WhiteEnemy(p2, Vector(-180, 0), this->whiteShipSprite, this->enemyExplosionSprite, this);
    WhiteEnemy *ship3 = new WhiteEnemy(p3, Vector(-180, 0), this->whiteShipSprite, this->enemyExplosionSprite, this);
    //WhiteEnemy *ship4 = new WhiteEnemy(p2, Vector(-180, 0), this->whiteShipSprite, this->enemyExplosionSprite, this);
    //WhiteEnemy *ship5 = new WhiteEnemy(p2, Vector(-180, 0), this->whiteShipSprite, this->enemyExplosionSprite, this);

    // Manda para o objeto collision
    this->_collision->addEnemies(ship1);
    this->_collision->addEnemies(ship2);
    this->_collision->addEnemies(ship3);
    //this->_collision->addEnemies(ship4);
    //this->_collision->addEnemies(ship5);

    // Manda para o objeto window
    this->_window->addDrawableItem(ship1);
    this->_window->addDrawableItem(ship2);
    this->_window->addDrawableItem(ship3);
    //this->_window->addDrawableItem(ship4);
    //this->_window->addDrawableItem(ship5);

    // Guarda na referência dos ships
    this->ships.push_front(ship1);
    this->ships.push_front(ship2);
    this->ships.push_front(ship3);
    //this->ships.push_front(ship4);
    //this->ships.push_front(ship5);
}

void WhiteEnemiesControl::loadSprites()
{
    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    this->whiteShipSprite = std::make_shared<Sprite>("EnemyBasic.png");
    this->enemyExplosionSprite = std::make_shared<Sprite>("explode.png");
    al_destroy_path(path);
}

__END_API