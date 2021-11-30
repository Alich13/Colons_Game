#include "../header.h"

Dice::Dice(){};

/**
 * @brief 
 * return a Random int from the following discrete distribution {0, 0, 2, 3, 3, 3, 3, 4, 3, 3, 3, 3, 2}
 * simulating real probabilites for having each dice value 
 * 
 * @return int random dice value 
 */
int Dice::randomize_dice()
{
    random_device rd;
    unsigned long seed = rd();
    mt19937 engine(seed);
    discrete_distribution<int> distribution{0, 0, 2, 3, 3, 3, 3, 4, 3, 3, 3, 3, 2};
    return distribution(engine);
}
/**
 * @brief get the state of the dice  
 * 
 * @return true   player can play the dice
 * @return false  player can not play the dice
 */
bool Dice::get_dice_state() 
{ 
    return canPlayDice; 
}
/**
 * @brief set the dice sate fixing the number of times a player can play the dice 
 *  
 */
void Dice::set_dice_state(bool new_state) 
{
     this->canPlayDice = new_state; 

}