#ifndef __ITEAM_H__
#define __ITEAM_H__

#include <iostream>

enum class ETeam : uint8_t
{
    NONE,
    PLAYER,
    ENEMY
};

static std::ostream& operator<< (std::ostream& out, ETeam team)
{
    switch(team)
    {
        case ETeam::NONE:
            out << "NONE";
            break;
        case ETeam::PLAYER:
            out << "PLAYER";
            break;
        case ETeam::ENEMY:
            out << "ENEMY";
            break;
        default:
            out << "UNDEFINED";
            break;
    }
}

class ITeam
{
public:
    virtual ~ITeam() {};
    ETeam Team;

    virtual ETeam GetTeam() const;
    virtual void SetTeam(ETeam Team);
    
};

#endif // __ITEAM_H__