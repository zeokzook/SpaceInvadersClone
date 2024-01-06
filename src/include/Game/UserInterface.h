#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#include "Sprite.h"
#include "Text.h"
#include "Colour.h"
#include <memory>
#include <list>

class UserInterface
{
private:
    std::list<std::shared_ptr<Text>> texts;
public:
    UserInterface();
    ~UserInterface();

    void Render();
};

#endif // __USERINTERFACE_H__