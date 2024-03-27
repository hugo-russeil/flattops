#include "destroyer.hpp"

Destroyer::Destroyer(Vector2 position, int team) : Ship(position, team) {
    this->sprite = LoadTexture("assets/gfx/destroyer.png");
    this->dimensions = Vector2{this->sprite.width, this->sprite.height};
    this->position = position;
    this->targetPosition = position;
    this->velocity = Vector2{0, 0};
    this->rotation = 0;
    this->hp = 100;
    this->maxHp = 100;
    this->fuel = 100;

    this->hasDeckBattery = true;
    this->deckBatteryDamage = 10;

    this->hasAAGun = true;
    this->AAGunDamage = 10;

    this->hasTorpedo = true;
    this->torpedoDamage = 15;

    this->hasDepthCharge = true;
    this->depthChargeDamage = 15;
}

Destroyer::~Destroyer() {
    
}

void Destroyer::Draw() {
    Vector2 drawPosition = { this->position.x - this->sprite.width / 2, this->position.y - this->sprite.height / 2 };
    DrawTextureEx(this->sprite, drawPosition, this->rotation, 1, WHITE);
}