#ifndef __FENEMYTYPES_H__
#define __FENEMYTYPES_H__

#include <cstdint>
#include <random>

enum class EEnemyType : uint8_t
{
    GREEN,
    YELLOW,
    RED,
    EXTRA
};

struct FEnemyData
{
    FEnemyData(EEnemyType enemyType)
    {
        switch(enemyType)
        {
            default:
            case EEnemyType::GREEN:
                spriteName = "Alien_Green";
                spritePath = "assets/green.png";
                score = 100;
                break;
            case EEnemyType::YELLOW:
                spriteName = "Alien_Yellow";
                spritePath = "assets/yellow.png";
                score = 250;
                break;
            case EEnemyType::RED:
                spriteName = "Alien_Red";
                spritePath = "assets/red.png";
                score = 500;
                break;
            case EEnemyType::EXTRA:
                spriteName = "Alien_Extra";
                spritePath = "assets/extra.png";
                score = 500;
                break;
        }
    }

    const char* spriteName;
    const char* spritePath;
    int score = 0;
};

#endif // __FENEMYTYPES_H__