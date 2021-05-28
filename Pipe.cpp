#include "Pipe.h"

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

}
