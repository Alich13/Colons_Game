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

//-------------------------- T_map (Tuiles data structure)----------------------------------------------//
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
  *&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//-----------------------------------------------------------------------------------------------------------*/
/*
THis his class is a data structure enabling tuiles objects storing  and accessing
*/
//-------------------------------------------------------------------------------------------------------------//

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

//--------------------------------------------T_map----------------------------------------------------

class T_map
{
private:
    vector<tuile> map;
    tuile thief = tuile(2, 598, 466, Ressouces::desert); // thief is initially in 2 desert
public:
    int size;
    //---------------------constructor-----------------//

    T_map() { ; }

    void set_thief(tuile new_thief) { this->thief = new_thief; }
    int get_tuile_de_num(int id);
    int get_tuile_x(int id);
    int get_tuile_y(int id);
    void randomize_tuiles_de();
    void insert(tuile tuile);

    tuile get_thief() { return thief; }
    Ressouces get_tuile_ressource(int id);
};

//-----------------------------------------------------------------------------------------------//

//-------------------------- I_map (intersection data structure)----------------------------------------------//
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
 *&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
 //-----------------------------------------------------------------------------------------------------------*/
/*
THis his class is a data structure enabling tuiles objects storing  and accessing
*/

class node
{

public:
    int id; // tuile_id public
    node(int id, int x, int y, vector<tuile> adj_ressource)
    {
        this->id = id;
        this->x = x;
        this->y = y;
        this->adj_ressource = adj_ressource;
    };
    void set_state(States state) { this->state = state; }
    int  get_x(){return x;}
    int  get_y(){return y;} 
    States get_state() { return state; }

private:
    int x, y;
    States state = States::empty;     // state of the intersection (empty or  player id)
    std::vector<tuile> adj_ressource; // list of maximum 3 tuiles
};

class route
{
public:
    route();
    route(node N_p1, node N_p2) : pos1(N_p1), pos2(N_p2) {}
    node get_pos1() { return pos1; }
    node get_pos2() { return pos2; }
    States get_route_state() { return state; }
    void set_route_state(States state) { this->state = state; }
    void set_pos1_state(States state) { pos1.set_state(state); }
    void set_pos2_state(States state) { pos2.set_state(state); }
    route reverse_route(){};

private:
    node pos1;
    node pos2;
    States state = States::empty;
};

class I_map
{
private:
    vector<route> map;

public:
    I_map() { ; }
    int size;
    vector<node> get_all_nodes();
    void insert(route RX);
    void update_intersection_state(int id, States new_state);
    void update_route_state(node updated_route_pos_1, node updated_route_pos_2, States new_state);
    void print_map();
    node get_node(int id);
    bool check_possible_route(node first_click, node second_click, States player); // faut lui passer un map[i].pos_1 ou map[i].pos[2] !!!!!!!!!!!!!
    bool check_possible_house();
    bool check_node_has_adj_route(node click ,States adj) ;
};

#endif // GTKMM_MYAREA_H
