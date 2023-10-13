#include "ITeam.h"

ETeam ITeam::GetTeam() const
{
    return Team;
}

void ITeam::SetTeam(ETeam Team)
{
    this->Team = Team;
}