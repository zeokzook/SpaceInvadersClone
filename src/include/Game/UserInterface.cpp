#include "UserInterface.h"

UserInterface::UserInterface()
{
    texts.push_back(std::make_shared<Text>("SCORE", "Square.ttf", Vector2f(10, 10), Colour::RED, 35));
}

UserInterface::~UserInterface()
{
    texts.empty();
}

void UserInterface::Render()
{
    for(auto text : texts)
    {
        text->Render();
    }
}
