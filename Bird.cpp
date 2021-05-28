#include "Bird.h"

FloatRect Bird::getRect()
{
    auto size = birdTexture.getSize();
    return{
        50, y, (float)size.x, (float)size.y
    };
}

void Bird::flap()
{
    if (!alive) return;
    vel = -420;
}

void Bird::draw(RenderWindow& window)
{
    birdSprite = Sprite(birdTexture);
    birdSprite.setRotation(8 * (vel / 400));
    birdSprite.setPosition(50, y);

    pipe->draw(window);

    window.draw(birdSprite);
}

void Bird::update()
{
    if (alive) {
        vel += 0.1 * 1200;
        y += vel * 0.1;

        pipe->update();

        if (getRect().intersects(pipe->getUpperRect()) ||
            getRect().intersects(pipe->getLowerRect())) {
            alive = false;

        }

        if (getRect().left > pipe->x + pipe->upperPipe.getSize().x &&
            pipe->scored == false) {
            pipe->scored = true;

            cout << "score";
        }
        if (pipe->x + pipe->upperPipe.getSize().x <= 0) {
            free(pipe);
            pipe = new Pipe();
        }
    }
}
