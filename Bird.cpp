#include "Bird.h"

Bird::Bird()
{
    this->initVariables();
    this->initSprite();
}

void Bird::mutate(float mr)
{
    brain.mutate(mr);
}

void Bird::look()
{
    this->vision[0] = calcYDistanceToTopPipe();
    this->vision[1] = calcYDistanceToBotPipe();
    this->vision[2] = calcYDistanceToGround();
    this->vision[3] = calcYDistanceToCeiling();
    this->vision[4] = calcXDistanceToPipes();
    this->vision[5] = this->vel;
}

void Bird::think()
{
    decision = brain.output(vision);
    float max = 0;
    int maxIndex = 0;
    int size = 2;
    for (int i = 0; i < size; i++) {
        if (max < decision(i, 0)) {
            max = decision(i, 0);
            maxIndex = i;
        }
    }

    if (maxIndex == 0)
        this->flap();

}

void Bird::Collision()
{
    if (this->pos.second >= 700 || this->pos.second <= 0) {
        alive = false;
    }

    if (getRect().intersects(pipe->getUpperRect()) ||
        getRect().intersects(pipe->getLowerRect())) {
        alive = false;
    }

    if (getRect().left > pipe->x + pipe->upperPipe.getSize().x &&
        pipe->scored == false) {
        pipe->scored = true;
        this->score++;
    }
}

void Bird::updateMovement()
{
    this->lifeTime += 1;
    if (this->alive) {
        vel += 0.1 * 1200;
        this->pos.second += vel * 0.1;
        this->look();
        this->think();
        this->Collision();
    }
}

FloatRect Bird::getRect()
{
    this->y = this->pos.second;
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

void Bird::update()
{
    this->updateMovement();
    birdSprite.setRotation(8 * (vel / 400));
    birdSprite.setPosition(this->pos.first, this->pos.second);
}

int Bird::calcFitness()
{
    this->fitness = this->lifeTime + this->score;
    return fitness;
}

Bird Bird::crossover(Bird partner)
{
    Bird child = Bird();
    child.brain = brain.crossover(partner.brain);
    return child;
}

Bird Bird::clone()
{
    Bird clone = Bird();
    clone.brain = brain.clone();
    clone.alive = true;
    return clone;
}

void Bird::render(RenderTarget& target)
{
    target.draw(birdSprite);
}

void Bird::initVariables()
{
    this->pos.first = 50;
    this->pos.second = 400;
    this->y = this->pos.second;
    this->vel = 0;
    this->alive = true;
    this->pipe = NULL;

    this->lifeTime = 0;
    this->fitness = 0;
    this->score = 0;
    this->brain = NeuralNet(6, 4, 2);
}

void Bird::initSprite()
{
    //birdSprite.setTexture(birdTexture);
    birdSprite.setPosition(this->pos.first, this->pos.second);
}

float Bird::calcYDistanceToTopPipe()
{
    float distance = this->pos.second - (pipe->getUpperRect().top + pipe->getUpperRect().height);
    return distance;
}

float Bird::calcYDistanceToBotPipe()
{
    float distance = this->pos.second - (pipe->getLowerRect().top);
    return distance;
}

float Bird::calcYDistanceToGround()
{
    float distance = 700 - this->pos.second;
    return distance;
}

float Bird::calcYDistanceToCeiling()
{
    return this->pos.second;
}

float Bird::calcXDistanceToPipes()
{
    float distance = this->pipe->x - this->pos.first;
    return distance;
}
