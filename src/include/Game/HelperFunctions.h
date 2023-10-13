#ifndef __HELPERFUNCTIONS_H__
#define __HELPERFUNCTIONS_H__

#include <iostream>
#include <string>

namespace HelperFunction
{
    static void SplitString(std::string str, std::string split, std::string& left, std::string& right)
    {
        size_t pos = str.find(split);
        
        if(pos == std::string::npos)
            return;
        
        left = str.substr(0, pos);
        right = str.substr(pos + split.length());
    }

    static bool AABB(SDL_FRect rectOne, SDL_FRect rectTwo)
    {
        return rectOne.x + rectOne.w >= rectTwo.x && 
               rectTwo.x + rectTwo.w >= rectOne.x && 
               rectOne.y + rectOne.h >= rectTwo.y && 
               rectTwo.y + rectTwo.h >= rectOne.y;
    }

    static bool IsWithinBounds(SDL_FRect rect, SDL_Rect bounds)
    {
        return rect.x >= bounds.x &&
               rect.x + rect.w <= bounds.x + bounds.w && 
               rect.y >= bounds.y &&
               rect.y + rect.h <= bounds.y + bounds.h;
    }
}

#endif // __HELPERFUNCTIONS_H__