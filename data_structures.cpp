#include "data_structures.h"

//----------------------------------------------------------------------------------------------//
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& T_map methodes &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
//----------------------------------------------------------------------------------------------//

//--------------------get elements by id----------//
int T_map::get_tuile_de_num(int id)
{
    for (unsigned int i = 0; i < map.size(); i++)
    {
        if (map[i].get_id() == id)
            return map[i].get_de();
    }
}
int T_map::get_tuile_x(int id)
{
    for (unsigned int i = 0; i < map.size(); i++)
    {
        if (map[i].get_id() == id)
            return map[i].get_x();
    }
}

int T_map::get_tuile_y(int id)
{
    for (unsigned int i = 0; i < map.size(); i++)
    {
        if (map[i].get_id() == id)
            return map[i].get_y();
    }
}

Ressouces T_map::get_tuile_ressource(int id)
{
    for (unsigned int i = 0; i < map.size(); i++)
    {
        if (map[i].get_id() == id)
            return map[i].get_ressource();
    }
}

void T_map::randomize_tuiles_de()
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

void T_map::insert(tuile tuile)
{
    map.push_back(tuile);
    this->size = map.size();
}

//----------------------------------------------------------------------------------------------//
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& I_map methodes &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
//-----------------------------------------------------------------------------------------------//

void I_map::insert(route RX)
{
    map.push_back(RX);
    size = map.size();
}

node I_map::get_node(int id)
// return a node by its id
{
    for (unsigned int i = 0; i < map.size(); i++)
    {
        if (map[i].get_pos1().id == id) // iterate trough routes
            return map[i].get_pos1();
        else if (map[i].get_pos2().id == id)
            return map[i].get_pos2();
    }
}

void I_map::update_intersection_state(int id, States new_state)

{
    // we have to update both positions

    for (unsigned int i = 0; i < map.size(); i++)
    {
        if (map[i].get_pos1().id == id) // iterate trough routes
            map[i].set_pos1_state(new_state);
    }
    for (unsigned int i = 0; i < map.size(); i++)
    {
        if (map[i].get_pos2().id == id) // iterate trough routes
            map[i].set_pos2_state(new_state);
    }
}

void I_map::update_route_state(node updated_route_pos_1, node updated_route_pos_2, States new_state)
{
    // we have to consider that order can change

    for (unsigned int i = 0; i < map.size(); i++)
    {
        route my_route = map[i];
        node pos_1 = my_route.get_pos1();
        node pos_2 = my_route.get_pos2();
        if ((pos_1.id == updated_route_pos_1.id && pos_2.id == updated_route_pos_2.id) || (pos_1.id == updated_route_pos_2.id && pos_2.id == updated_route_pos_1.id))
        {
            map[i].set_route_state(new_state);
        }
    }
}

void I_map::print_map()
{
    // prints the map

    for (unsigned int i = 0; i < map.size(); i++)
    {
        route my_route = map[i];
        node pos_1 = my_route.get_pos1();
        node pos_2 = my_route.get_pos2();
        States pos_1_state = pos_1.get_state();
        States pos_2_state = pos_2.get_state();
        States route_state = my_route.get_route_state();
        cout
            << pos_1.id << " "
            << " "
            << "(state=" << static_cast<int>(pos_1_state) << ") "
            << "------> "
            << pos_2.id << " "
            << " " 
            << "(state=" << static_cast<int>(pos_2_state) << ") "
            << "Route_state=" << static_cast<int>(route_state) << endl;
    }
}
/**
 * @brief 
 * check if a node has an adjacent route (incident route)
 * 
 * @param click 
 * @param player 
 * @return true  yes
 * @return false  no
 */
bool I_map::check_node_has_adj_route(node click, States player) 
{
    bool adjacent_route_or_house = false;
        
    for (unsigned int i = 0; i < map.size(); i++)
    {
        route my_route = map[i];
        node pos_1 = my_route.get_pos1();
        node pos_2 = my_route.get_pos2();

        if ( (pos_1.id == click.id || pos_2.id == click.id) )
        {
            adjacent_route_or_house = (adjacent_route_or_house || (map[i].get_route_state()== player));
        }
    }
    return adjacent_route_or_house;
    

}



/** ----------------------------------------------------------------------------------------
 * @brief
 * check whether a route construnction is possible or not ?
 * check if there's an adjacent construction or route
 *
 * @param first_click  is the node selected  with the first click
 * @param second_click  is the node selected with the second click
 * @param player is the player doing the action (tryng to build the route )
 * @return true if route construction is possible
 * @return false if route construction is not possible
 */
bool I_map::check_possible_route(node first_click, node second_click, States player)
{
    
    bool route_exist;
    bool neighboor = false;
    bool adjacent_route_or_house = false; // to the first click

    // check if  the route the user chose isn't occupied
    for (unsigned int i = 0; i < map.size(); i++)
    {
        route my_route = map[i];
        node pos_1 = my_route.get_pos1();
        node pos_2 = my_route.get_pos2();
        if ((pos_1.id == first_click.id && pos_2.id == second_click.id) || (pos_1.id == second_click.id && pos_2.id == first_click.id))
            route_exist = (map[i].get_route_state() == player);
    
    }


    //check if the route the user chose has an adjacent house or route
    if ((first_click.get_state() == player)||(second_click.get_state() == player))
    {
        adjacent_route_or_house = true;
    }
    else
    {
        adjacent_route_or_house=(check_node_has_adj_route(first_click ,player)||check_node_has_adj_route(second_click ,player)); 
    }


    // check if the two nodes selected are nodes
    for (unsigned int i = 0; i < map.size(); i++)
    {
        route my_route = map[i];
        node pos_1 = my_route.get_pos1();
        node pos_2 = my_route.get_pos2();

        // we have to consider that order can change (given that route object is unidirectional)
        if ((pos_1.id == first_click.id && pos_2.id == second_click.id) || (pos_1.id == second_click.id && pos_2.id == first_click.id))
        {
            neighboor = true;
        }
    }
    cout << " neib = " << neighboor << endl;
    cout << " adj = " << adjacent_route_or_house << endl;
    cout << " results = " << (neighboor && adjacent_route_or_house) << endl;

    return (neighboor && adjacent_route_or_house && !route_exist); //&& !route_exist
}
/**
 * @brief 
 * 
 * @return vector<node> containing all the intersection with theirs updated states 
 */
vector<node> I_map::get_all_nodes()
{
    vector<node> all_nodes ={};
    for (unsigned int i=0;i < map.size(); i++)
    {
        bool first_element_exists=false;
        bool second_element_exists=false;

        for  (unsigned int k=0;k < all_nodes.size(); k++)
        {
            first_element_exists  =first_element_exists || ((map[i].get_pos1().id)==(all_nodes[k].id));
            second_element_exists = second_element_exists || ((map[i].get_pos2().id)==(all_nodes[k].id));
        }

        if (!first_element_exists)
        {
            all_nodes.push_back(map[i].get_pos1());
        }
        if (!second_element_exists)
        {
            all_nodes.push_back(map[i].get_pos2());
        }    
    }
    return all_nodes ;

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