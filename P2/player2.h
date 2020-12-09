#ifndef Player45920887_H
#define Player45920887_H

#include "environment.h"

class Player45920887{
    public:
      Player45920887(int jug);
      Environment::ActionType Think();
      void Perceive(const Environment &env);
    private:
      int jugador_;
      Environment actual_;
};
#endif
