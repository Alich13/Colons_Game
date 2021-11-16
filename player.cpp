#include "header.h"
#include <cairomm/context.h>
#include <iostream>
#include <string> // for string class
#define SCALE 1.25
using namespace std;

/**
 * @brief Construct a new Player:: Player object
 * 
 * @param N_id 
 * @param N_nickname 
 */
Player::Player(States N_id,string N_nickname)
{
    this->id =N_id ;
    this->Nickname = N_nickname;

}

int Player::get_player_INT_id()
{
    return static_cast<int>(id);
}

States Player::get_player_STATE_id()
{
    return id;
}

string Player::get_name()
{
    return Nickname;
}