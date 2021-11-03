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
    int id; // tuile_id public
    node(int id ,int x, int y, vector<tuile> adj_ressource )
    {
        this->id=id;
        this-> x = x;
        this-> y = y;
        this-> adj_ressource = adj_ressource;
    };
    void set_state(States state){this->state =state; }
    States get_state(){return state;}

private:
    int x, y;
    States state = States::empty;                     // state of the intersection (empty or  player id)
    std::vector<tuile> adj_ressource; // list of maximum 3 tuiles
};



class route
{
public:
    route();
    route(node N_p1, node N_p2): pos1(N_p1) , pos2(N_p2)
    {

    }
    node get_pos1(){return pos1; }
    node get_pos2(){return pos2; }
    States get_route_state(){return state;}
    void set_route_state(States state){this->state = state ;}
    void set_pos1_state(States state){pos1.set_state(state);}
    void set_pos2_state(States state){pos2.set_state(state);}
    route reverse_route(){};
private:
    node pos1 ;
    node pos2 ;
    States state= States::empty;


};


class I_map
{
public:
    I_map(){;}
    int size;
    void insert(route RX)
    {
        map.push_back(RX);
        size = map.size();
    }

    node get_node(int id)
    // return a node by its id 
    {
        for (unsigned int i = 0; i < map.size(); i++)
        {   
            if ( map[i].get_pos1().id == id) //iterate trough routes
                return map[i].get_pos1();
            else if ( map[i].get_pos2().id == id)
                return map[i].get_pos2();
        }
    }

    void update_intersection_state(int id, States new_state)
    {        
        //we have to update both positions

        for (unsigned int i = 0; i < map.size(); i++)
        {   
            if ( map[i].get_pos1().id == id) //iterate trough routes
                map[i].set_pos1_state(new_state);
        }
        for (unsigned int i = 0; i < map.size(); i++)
        {   
            if ( map[i].get_pos2().id == id) //iterate trough routes
                map[i].set_pos2_state(new_state);
        }



    }

    void update_route_state(node updated_route_pos_1 , node updated_route_pos_2 , States new_state)
    {        
        //we have to consider that order can change

        for (unsigned int i = 0; i < map.size(); i++)
        {   
            route my_route=map[i];
            node pos_1 = my_route.get_pos1();
            node pos_2 = my_route.get_pos2();
            if (( pos_1.id == updated_route_pos_1.id && pos_2.id == updated_route_pos_2.id ) 
                ||( pos_1.id == updated_route_pos_2.id && pos_2.id == updated_route_pos_1.id ))
                {
                    map[i].set_route_state(new_state);
                }

        }

    }


    void print_map ()
    {        
        //we have to consider that order can change

        for (unsigned int i = 0; i < map.size(); i++)
        {   
            route my_route=map[i];
            node pos_1 = my_route.get_pos1();
            node pos_2 = my_route.get_pos2();
            States pos_1_state = pos_1.get_state();
            States pos_2_state = pos_2.get_state();
            States route_state = my_route.get_route_state() ; 
            cout 
                << pos_1.id <<"  "
                << " " << "state="<< static_cast<int> (pos_1_state) << " "   
                << "------> " 
                << pos_2.id << " "
                << " " << "state="<< static_cast<int>(pos_2_state) << " "
                << "Route_state=" <<static_cast<int>(route_state) <<endl ;
        }

    }
    
    // faut lui passer un map[i].pos_1 ou map[i].pos[2] !!!!!!!!!!!!!
    bool check_possible_route(node first_click, node second_click, States player)
    {

        // must also check if there's an adjacent construction or route 
        // ad alert widget to specify that the first click must begin from the construction or routr
        //(prolongement ) 
        bool  route_exist;
        bool  neighboor = false ;
        bool  adjacent_route_or_house = false ; //to the first click  

        
        
        route_exist= false; /// !!!!!!!!!!!!!!!!!!!!!!!!
        
        cout << first_click.id <<endl;
        cout << static_cast<int>(first_click.get_state()) <<endl;
        cout << static_cast<int>(player) <<endl;
        
        if (first_click.get_state() == player)
        {
            adjacent_route_or_house = true;
        }
        else 
        {
            for (unsigned int i = 0; i < map.size(); i++)
                {
                    route my_route=map[i];
                    node pos_1 = my_route.get_pos1();
                    node pos_2 = my_route.get_pos2();

                    if (( pos_1.id == first_click.id && pos_2.id == second_click.id ) 
                        || ( pos_1.id == second_click.id && pos_2.id == first_click.id ))
                        {
                            // if ther is an adjacent route belonging to the same player 
                            //this var adjacent_route gets True

                            //adjacent_route_or_house = (my_route.get_route_state()== player) ;
                        }

                }
        }

        for (unsigned int i = 0; i < map.size(); i++)
        {   
            route my_route =map[i];
            node pos_1 = my_route.get_pos1();
            node pos_2 = my_route.get_pos2();

            //we have to consider that order can change (given that route object is unidirectional)

            if  (  (pos_1.id == first_click.id && pos_2.id == second_click.id)
                   ||(pos_1.id == second_click.id && pos_2.id == first_click.id) 
                ) 
                {
                    neighboor=true;
                }
            
        }

        cout << " neib"<< neighboor<<endl;
        cout << " adj"<< adjacent_route_or_house<<endl;

        return (neighboor && adjacent_route_or_house ); //&& !route_exist


         
    }

/*
    bool check_2_routes_exist(node to_build_constuction , States player_id)
    {        
        // States are either empty or a player id
        //we have to consider that order can change

        for (unsigned int i = 0; i < map.size(); i++)
        {   
            if ( map[i].get_pos1().id == to_build_constuction.id)
            {
                if (map[i].get_route_state() == player_id)  // player_id normalement 

                   
            }

            if ( map[i].get_pos2().id == to_build_constuction.id)
            {

            }

        }

        return false

    }
*/


private:
    vector<route> map;
};

#endif // GTKMM_MYAREA_H