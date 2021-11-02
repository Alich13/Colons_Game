#ifndef GTKMM_MYAREA_H
#define GTKMM_MYAREA_H
#include <string>
#include <vector>
#include <iostream>
#include <string>
#include <time.h>
#include <algorithm>
#include <random>

using namespace std;

enum class Ressouces
{
    ble,
    bois,
    argile,
    desert,
    mouton,
    pierre
};
enum class States
{
    empty,
    p1,
    p2,
    p3,
    p4,
    p5,
    p6
};

// possible heritage

//-------------------------- T_map (tuiles data structure)----------------------------------------------//
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 * &&&&&&&&&&&& this class is a data structure enabling tuiles objects storing  and accessing
 *&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
//-----------------------------------------------------------------------------------------------

class tuile
{

public:
    int tuile_id; // tuile_id public

    tuile();
    tuile(int tuile_id, int x, int y, Ressouces ressource)
    {

        this->tuile_id = tuile_id;
        this->x = x;
        this->y = y;
        this->ressource = ressource;
        // this->num_de = num_de; // a random number between 2 and 12 is affected to de
    }
    void set_de(int num_de) { this->num_de = num_de; }
    int get_de() { return num_de; }
    int get_id() { return tuile_id; }
    int get_x() { return x; }
    int get_y() { return y; }
    Ressouces get_ressource() { return ressource; }

private:
    int x, y; // cordonates
    Ressouces ressource;
    int num_de;
};

//------------------------------------------------------------------------------------------------

class T_map
{
public:
    int size;
    //---------------------constructor-----------------//
    T_map(){ ; }
    void set_thief(tuile new_thief) { this->thief = new_thief; }
    tuile get_thief() { return thief; }

    //--------------------get elements by id----------//
    int get_tuile_de_num(int id)
    {
        for (unsigned int i = 0; i < map.size(); i++)
        {
            if (map[i].get_id() == id)
                return map[i].get_de();
        }
    }
    int get_tuile_x(int id)
    {
        for (unsigned int i = 0; i < map.size(); i++)
        {
            if (map[i].get_id() == id)
                return map[i].get_x();
        }
    }

    int get_tuile_y(int id)
    {
        for (unsigned int i = 0; i < map.size(); i++)
        {
            if (map[i].get_id() == id)
                return map[i].get_y();
        }
    }

    Ressouces get_tuile_ressource(int id)
    {
        for (unsigned int i = 0; i < map.size(); i++)
        {
            if (map[i].get_id() == id)
                return map[i].get_ressource();
        }
    }

    void randomize_tuiles_de()
    //  assign random values to tuiles (vinignette)
    //  following this distribution below {0,1,2,3,3,3,3,0,3,3,3,3,2}
    {
        vector<int> all_vigniettes = {2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12};
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(std::begin(all_vigniettes), std::end(all_vigniettes), g);
        for (unsigned int i = 0; i < all_vigniettes.size(); i++)
        {
            map[i + 2].set_de(all_vigniettes[i]);
        }
    }

    void insert(tuile tuile)
    {
        map.push_back(tuile);
        this->size = map.size();
    }

private:
    vector<tuile> map;
    tuile thief = tuile(2, 598, 466, Ressouces::desert); // thief is initially in 2 desert
};

//-------------------------- I_map (intersection data structure)----------------------------------------------//
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 * this class is a data structure enabling tuiles objects storing  and accessing
 *&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
//-----------------------------------------------------------------------------------------------




class node
{

public:
    int tuile_id; // tuile_id public
    node(int x, int y, vector<tuile> adj_ressource )
    {
        this-> x = x;
        this-> y = y;
        this-> adj_ressource = adj_ressource;
    };

private:
    int x, y;
    States state = States::empty;                     // state of the intersection (empty or  player id)
    std::vector<tuile> adj_ressource; // list of maximum 3 tuiles
};



class route
{
public:
    route();
    route(node N_p1, node N_p2): p1(N_p1) , p2(N_p2)
    {

    }

private:

    node p1 ;
    node p2 ;
    States state= States::empty;
};


class I_map
{
public:

    I_map();
    int size;
    void insert(route RX)
    {
        map.push_back(RX);
        size = map.size();
    }

private:
    vector<route> map;
};

#endif // GTKMM_MYAREA_H