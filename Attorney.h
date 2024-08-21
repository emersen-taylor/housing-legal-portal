#ifndef ATTORNEY_H
#define ATTORNEY_H

#include "User.h"
#include "PracticeAreas.h"

class Attorney : public User {
private:
     PracticeAreas practice;
public:
     virtual void insertData();
     PracticeAreas getPractice() {
          return practice;
     }
};

#endif
