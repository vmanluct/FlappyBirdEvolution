#include "Pipe.h"

void Pipe::initVariables()
{
    x = (float)(450 + upperPipe.getSize().x);
    y = 100.0f + (float)(rand() % 5 - 3) * 50;
    scored = false;
}

void Pipe::initTexture()
{
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
    lowerPipeSp.setTexture(lowerPipe);
    upperPipeSp.setTexture(upperPipe);

    upperPipeSp.setPosition(x, y + 340);
    lowerPipeSp.setPosition(x, y - 340);
}

Pipe::Pipe()
{
    this->initTexture();
    this->initVariables();
    this->initSprite();
}

FloatRect Pipe::getUpperRect() const
{
    auto size = upperPipe.getSize();
    return{
        x,y + 340,(float)size.x,(float)size.y
    };
}

FloatRect Pipe::getLowerRect() const
{
    auto size = upperPipe.getSize();
    return{
        x,y - 340,(float)size.x,(float)size.y
    };
}

void Pipe::draw(RenderWindow& window) 
{
    lowerPipeSp = Sprite(lowerPipe);
    upperPipeSp = Sprite(upperPipe);

    upperPipeSp.setPosition(x, y + 340);
    lowerPipeSp.setPosition(x, y - 340);

    window.draw(lowerPipeSp);
    window.draw(upperPipeSp);
}

void Pipe::update()
{
    x -= 100 * 0.2; 
    upperPipeSp.setPosition(x, y + 340);
    lowerPipeSp.setPosition(x, y - 340);
}

void Pipe::render(RenderTarget& target)
{
    target.draw(lowerPipeSp);
    target.draw(upperPipeSp);
}
