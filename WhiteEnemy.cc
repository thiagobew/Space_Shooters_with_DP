#include "include/WhiteEnemy.h"

__BEGIN_API

int WhiteEnemy::DELAY_BETWEEN_SHOTS = 30;

WhiteEnemy::WhiteEnemy(Point point, Vector vector, std::shared_ptr<Sprite> shipSprite, std::shared_ptr<Sprite> deathSprite, WhiteEnemiesControl *control) : Enemy(point, vector, 1)
{
    this->_shipSprite = shipSprite;
    this->_deathSprite = deathSprite;
    this->_control = control;
    this->deathSpriteTimer = 5;

    this->color = al_map_rgb(255, 255, 255);
    this->shotsTimer = std::make_shared<Timer>(GameConfigs::fps);
    this->shotsTimer->create();
    this->shotsTimer->startTimer();
}

// Quando o inimigo morre ele manda uma mensagem para o controle falando que ele morreu, isso é necessário
// para removermos a referência ao objeto que vai ser destruído que está no controle
// É necessário pq não tem como o objeto Collision passar essa informação diretamente
WhiteEnemy::~WhiteEnemy()
{
    if (this->_control != nullptr && GameConfigs::finished == false)
        this->_control->removeShip(this);

    this->shotsTimer.reset();
    this->_shipSprite.reset();
    this->_deathSprite.reset();
}

void WhiteEnemy::draw()
{
    if (this->_dead)
        return;

    if (this->life <= 0)
    {
        this->deathSpriteTimer -= 1;
        this->_deathSprite->draw_death_anim(this->deathSpriteTimer, this->_point, 0);
        if (this->deathSpriteTimer <= 0)
            this->_dead = true;
        }
    else
    {
        this->_shipSprite->draw_tinted(this->_point, this->color, 0);
    }
}

void WhiteEnemy::update(double diffTime)
{
    if (_dead)
    {
        return;
    }

    this->_point = this->_point + this->_speed * diffTime;

    if (this->getPosition().x <= 7 * GameConfigs::windowWidth / 8 && this->getPosition().y == GameConfigs::windowHeight / 2) {
        _speed.flip();
    }

    // std::cout << "Vector: " << this->_speed.x << " " << this->_speed.y << std::endl;
    // check y bound and adjust if out
    if (this->getPosition().y >= GameConfigs::windowHeight - this->getSize() && _speed.y > 0) {
        _speed.flip();
    }
    if (this->getPosition().y <= 0 - this->getSize() && _speed.y < 0) {
        _speed.flip();
    }

    if ((this->getPosition().x < 0 - this->getSize()) && _speed.x < 0) {
        std::cout << "flip2" << std::endl;
        _speed.flip();
    }

    if (this->shotsTimer->getCount() > WhiteEnemy::DELAY_BETWEEN_SHOTS)
    {
        this->_canFire = true;
        this->shotsTimer->srsTimer();
    }
}

int WhiteEnemy::getSize() { return 20; }

bool WhiteEnemy::isOutside() { return this->_point.x < -40; }

void WhiteEnemy::attack() { this->_canFire = false; }

__END_API