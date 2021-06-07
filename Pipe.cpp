#include "Pipe.h"

void Pipe::initVariables()
{
    //Set x value far right of screen
    x = (float)(450 + upperPipe.getSize().x);
    //Set a random height
    y = 100.0f + (float)(rand() % 5 - 3) * 50;
    scored = false;
}

void Pipe::initTexture()
{
    //Load texture of pipe from file
    Image pipeImage;
    if (!pipeImage.loadFromFile(path)) {
        cout << "Error";
    }
    upperPipe.loadFromImage(pipeImage);
    pipeImage.flipVertically();
    lowerPipe.loadFromImage(pipeImage);
}

void Pipe::initSprite()
{
    //Set sprites with distance of 340 between them
    lowerPipeSp.setTexture(lowerPipe);
    upperPipeSp.setTexture(upperPipe);

    upperPipeSp.setPosition(x, y + 340);
    lowerPipeSp.setPosition(x, y - 340);
}

Pipe::Pipe()
{
    //Initialize everything for the pipe
    this->initTexture();
    this->initVariables();
    this->initSprite();
}

FloatRect Pipe::getUpperRect() const
{
    //Return the hitbox of the top pipe
    auto size = upperPipe.getSize();
    return{
        x,y + 340,(float)size.x,(float)size.y
    };
}

FloatRect Pipe::getLowerRect() const
{
    //Return the hitbox of the bottom pipe
    auto size = upperPipe.getSize();
    return{
        x,y - 340,(float)size.x,(float)size.y
    };
}

void Pipe::draw(RenderWindow& window) 
{
    //Draw both pipes to the window
    lowerPipeSp = Sprite(lowerPipe);
    upperPipeSp = Sprite(upperPipe);

    upperPipeSp.setPosition(x, y + 340);
    lowerPipeSp.setPosition(x, y - 340);

    window.draw(lowerPipeSp);
    window.draw(upperPipeSp);
}

void Pipe::update()
{
    //Update the position of both pipes
    x -= 100 * 0.2; 
    upperPipeSp.setPosition(x, y + 340);
    lowerPipeSp.setPosition(x, y - 340);
}

void Pipe::render(RenderTarget& target)
{
    //Draw both pipes to the screen
    target.draw(lowerPipeSp);
    target.draw(upperPipeSp);
}
