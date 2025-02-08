#include "User.h"

User::User(const string &Uname, int UregN)
{
    regNo=UregN; 
    name = Uname;
}

int User::getRegNo() const
{
    return regNo;
}
