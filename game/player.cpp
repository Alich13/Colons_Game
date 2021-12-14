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

void Player::append_to_ressources( Resources ressource)
{
    player_ressources.push_back(ressource);
}

int Player::count_X_ressources(Resources ressource)
{
    int count =0 ;
    for (unsigned j=0;j<player_ressources.size();j++)
    {
        if (player_ressources[j]==ressource)
        {
            count+=1;
        }
    }
     return count ;
}

int Player::get_score()
{
    return total_points;
}
void Player::set_score(int N_score)
{
    this->total_points=N_score ;
}


int Player::get_number_of_routes()
{
    return number_of_routes;
}

void Player::set_route_number(int N_count)
{
    this->number_of_routes = N_count ;
}

vector<Resources> Player::get_resources()
{
  return player_ressources;
}

void Player::set_resources(vector<Resources> N_ressources)
{ 
  this->player_ressources=N_ressources;
}