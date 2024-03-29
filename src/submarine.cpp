#include "submarine.hpp"

Submarine::Submarine(Vector2 position, int team) : Ship(position, team) {
    this->sprite = LoadTexture("assets/gfx/submarine.png");
    this->dimensions = Vector2{static_cast<float>(this->sprite.width), static_cast<float>(this->sprite.height)};
    this->position = position;
    this->targetPosition = position;
    this->team = team;
    this->velocity = Vector2{0, 0};
    this->rotation = 0;
    this->hp = 50;
    this->maxHp = 50;
    this->fuel = 100;
    this->maxFuel = 100;

    this->hasDeckBattery = false;
    this->deckBatteryDamage = 0;

    this->hasAAGun = false;
    this->AAGunDamage = 0;

    this->hasTorpedo = true;
    this->torpedoDamage = 20;

    this->hasDepthCharge = false;
    this->depthChargeDamage = 0;
}

Submarine::~Submarine() {
    
}

void Submarine::Draw() {
    if(!active) return;
    Vector2 drawPosition = this->position;
    Vector2 origin = { static_cast<float>(this->sprite.width) / 2.0f, static_cast<float>(this->sprite.height) / 2.0f };
    Rectangle sourceRec = { 0.0f, 0.0f, (float)this->sprite.width, (float)this->sprite.height };
    Rectangle destRec = { drawPosition.x, drawPosition.y, (float)this->sprite.width, (float)this->sprite.height };
    float rotationInDegrees = this->rotation +180;
    DrawTexturePro(this->sprite, sourceRec, destRec, origin, rotationInDegrees, WHITE);

    if (this == selectedShip) {

        DrawLineV(this->position, this->targetPosition, YELLOW);

        float barWidth = 20.0f; // Set a fixed width for the bars

        // Draw health bar
        float currentHealthWidth = barWidth * (this->hp / this->maxHp);
        Color healthBarColor = RED;
        Color currentHealthColor = GREEN;
        DrawRectangle(drawPosition.x - barWidth/2, drawPosition.y + this->sprite.height - 20, barWidth, 2, healthBarColor);
        DrawRectangle(drawPosition.x - barWidth/2, drawPosition.y + this->sprite.height - 20, currentHealthWidth, 2, currentHealthColor);

        // Draw fuel bar
        float currentFuelWidth = barWidth * (this->fuel / this->maxFuel);
        Color fuelBarColor = RED;
        Color currentFuelColor = YELLOW;
        DrawRectangle(drawPosition.x - barWidth/2, drawPosition.y + this->sprite.height - 15, barWidth, 2, fuelBarColor);
        DrawRectangle(drawPosition.x - barWidth/2, drawPosition.y + this->sprite.height - 15, currentFuelWidth, 2, currentFuelColor);
    }
}