#pragma once
#ifndef FLIPPER_H
#define FLIPPER_H

class Flipper {
private:
    float positionX;
    float positionY;
    float rotation;

public:
    Flipper(float posX, float posY, float rot);

    float getPositionX() const;
    float getPositionY() const;
    float getRotation() const;
};

#endif // FLIPPER_H


