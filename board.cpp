#include "header.h"
#include <cairomm/context.h>
#include <iostream>
#define SCALE 1.25
using namespace std;

Board::Board()
{
     /* set tuiles */
     tuile(1, 392, 471, Ressouces::mouton);
     tuile(2, 500, 404, Ressouces::bois);
     tuile(3, 598, 466, Ressouces::desert);
     tuile(4, 498, 538, Ressouces::argile);

     /*set intersctions*/
}
