#include "Bird.h"

Bird::Bird()
{
    //Initialize everything for the bird
    this->initVariables();
    this->initSprite();
}

void Bird::mutate(float mr)
{
    //Mutate the brain of the bird
    brain.mutate(mr);
}

void Bird::look()
{
    //Calculate all the values for what the bird can see
    this->vision[0] = calcYDistanceToTopPipe();
    this->vision[1] = calcYDistanceToBotPipe();
    this->vision[2] = calcYDistanceToGround();
    this->vision[3] = calcYDistanceToCeiling();
    this->vision[4] = calcXDistanceToPipes();
    this->vision[5] = this->vel;
}

void Bird::think()
{
    //Go through the brain given the input nodes
    decision = brain.output(vision);
    float max = 0;
    int maxIndex = 0;
    int size = 2;

    //Find the output node with the highest value
    for (int i = 0; i < size; i++) {
        if (max < decision(i, 0)) {
            max = decision(i, 0);
            maxIndex = i;
        }
    }

    //Whether to flap or not
    if (maxIndex == 0)
        this->flap();

}

void Bird::Collision()
{
    //Bird hits ceiling or floor
    if (this->pos.second >= 700 || this->pos.second <= 0) {
        alive = false;
    }

    //Bird collides with a pipe
    if (getRect().intersects(pipe->getUpperRect()) ||
        getRect().intersects(pipe->getLowerRect())) {
        alive = false;
    }

    //Bird passes the pipes
    if (getRect().left > pipe->x + pipe->upperPipe.getSize().x &&
        pipe->scored == false) {
        pipe->scored = true;
        this->score++;
    }
}

void Bird::updateMovement()
{
    //Adjust position of bird based on velocity
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
    //Get hitbox of the bird
    this->y = this->pos.second;
    auto size = birdTexture.getSize();
    return{
        50, y, (float)size.x, (float)size.y
    };
}

void Bird::flap()
{
    //Apply upward force
    if (!alive) return;
    vel = -420;
}

void Bird::update()
{
    //Move bird, and adjust position on screen
    this->updateMovement();
    birdSprite.setRotation(8 * (vel / 400));
    birdSprite.setPosition(this->pos.first, this->pos.second);
}

int Bird::calcFitness()
{
    //See how well the bird is doing
    this->fitness = this->lifeTime + this->score;
    return fitness;
}

Bird Bird::crossover(Bird partner)
{
    //Create a new bird with a brain that is a mix of both parets
    Bird child = Bird();
    child.brain = brain.crossover(partner.brain);
    return child;
}

Bird Bird::clone()
{
    //Create a deep copy of the bird
    Bird clone = Bird();
    clone.brain = brain.clone();
    clone.alive = true;
    return clone;
}

void Bird::render(RenderTarget& target)
{
    //Draw the bird to the screen
    target.draw(birdSprite);
}

void Bird::initVariables()
{
    //Initialize position of bird
    this->pos.first = 50;
    this->pos.second = 400;
    this->y = this->pos.second;
    this->vel = 0;
    this->alive = true;
    this->pipe = NULL;

    //Initialize Neural network stuff
    this->lifeTime = 0;
    this->fitness = 0;
    this->score = 0;
    this->brain = NeuralNet(6, 4, 2);
}

void Bird::initSprite()
{
    //set position of bird in the window
    birdSprite.setPosition(this->pos.first, this->pos.second);
}

float Bird::calcYDistanceToTopPipe()
{
    //Take the hitbox of the top pipe, subtract from hitbox of the bird
    float distance = this->pos.second - (pipe->getUpperRect().top + pipe->getUpperRect().height);
    return distance;
}

float Bird::calcYDistanceToBotPipe()
{
    //Take hitbox of bird, subtract from top pipe
    float distance = this->pos.second - (pipe->getLowerRect().top);
    return distance;
}

float Bird::calcYDistanceToGround()
{
    //Take ground position subtract from position of the bird
    float distance = 700 - this->pos.second;
    return distance;
}

float Bird::calcYDistanceToCeiling()
{
    //Return y position of the bird
    return this->pos.second;
}

float Bird::calcXDistanceToPipes()
{
    //Take x position of pipes, and subtract by x position of the bird
    float distance = this->pipe->x - this->pos.first;
    return distance;
}
