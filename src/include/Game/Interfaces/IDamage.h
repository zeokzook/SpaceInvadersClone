#ifndef __IDAMAGE_H__
#define __IDAMAGE_H__

#include "ITeam.h"

enum class EDamageType : uint8_t
{
    DEFAULT
};

class IDamage
{
public:
    virtual ~IDamage() {};

    virtual void Damage(ETeam team, int damage, EDamageType damageType = EDamageType::DEFAULT);
    
};

#endif // __IDAMAGE_H__