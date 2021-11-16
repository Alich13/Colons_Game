#include "data_structures.h"
#include <cmath>

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
/**
 * @brief 
 * this function allows us to read !! get all infos concerning a particular 
 * node  
 * @param id 
 * @return node*
 * returns a pointer referencing a node object that contains or object or node of intrest
 * which we want to visualize 
 * // a pointer to a memory case where we will put the node we want to read
 */
node* I_map::get_node(int id)
// return a node by its id
{ 
    all_nodes = get_all_nodes() ;
    
    for (unsigned int i = 0; i < all_nodes.size(); i++)
    {
        if (all_nodes[i].id == id) // iterate trough routes
        {
            return &all_nodes[i];
        }

    }
    return nullptr;
}

/**
 * @brief
 * return a pointer referencing the route object we are looking for
 *
 * @param id
 * @return route*
 *  nullptr is returned if no route corresponding to the passed id is found
 */
route* I_map::get_route(int id)
{
    for (unsigned int i = 0; i < map.size(); i++)
    {
        if (map[i].id == id) // iterate trough routes
        {
            return &map[i];
        }
    }
    return nullptr;
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

/**
 * @brief
 * updates the state of route
 * @param id  the id of the route we want to change
 * @param new_state
 */
void I_map::update_route_state(int id, States new_state)
{
    // we have to consider that order can change
    for (unsigned int i = 0; i < map.size(); i++)
    {
        route my_route = map[i];
        node pos_1 = my_route.get_pos1();
        node pos_2 = my_route.get_pos2();
        if (my_route.id == id)
        {
            map[i].set_route_state(new_state);
        }
    }
}

/**
 * @brief
 * makes humain readable prints of the I_map
 */
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
            << "Route_state=" << static_cast<int>(route_state) << "  "
            << "(route ID " << my_route.id << " ) " << endl;
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
bool I_map::check_node_has_adj_route(node my_node, States player_id)
{
    bool adjacent_route = false;

    for (unsigned int i = 0; i < map.size(); i++)
    {
        route my_route = map[i];
        node pos_1 = my_route.get_pos1();
        node pos_2 = my_route.get_pos2();

        if ((pos_1.id == my_node.id || pos_2.id == my_node.id))
        {
            adjacent_route = (adjacent_route || (map[i].get_route_state() == player_id));
        }
    }
    return adjacent_route;
}
/**
 * @brief checks if a given node has direct neighboor
 * 
 * @param my_node 
 * @return true  if the given node has a neighboor (of any player )
 * @return false if the given node dont have a neighboor (of any player )
 */
bool I_map::check_node_has_adj_node(node my_node)
{
    bool adjacent_house = false;

    for (unsigned int i = 0; i < map.size(); i++)
    {
        route my_route = map[i];
        node pos_1 = my_route.get_pos1();
        node pos_2 = my_route.get_pos2();

        if ((pos_1.id == my_node.id || pos_2.id == my_node.id))
        {
            node neighboor_to_check = my_route.get_neighboor_in_route(my_node);
            cout << "neighboor" <<neighboor_to_check.id << endl;
            adjacent_house = (adjacent_house || (neighboor_to_check.get_state() != States::empty));
            cout << "adjacent_house" <<adjacent_house << endl;
        }
    }
    return adjacent_house;
}





/** ----------------------------------------------------------------------------------------
 * @brief
 * check whether a route construnction is possible or not ?
 *
 * 1/check if there's an adjacent construction or route
 * 2/check if  the route the user chose isn't occupied
 * 3/check if the two nodes selected are neighboor or form a route
 *
 * @param first_click  is the node selected  with the first click
 * @param second_click  is the node selected with the second click
 * @param player is the player doing the action (trying to build the route )
 * @return true if route construction is possible
 * @return false if route construction is not possible
 */
bool I_map::check_possible_route(int id, States player)
{
    bool result=false;
    
    route* route_to_check_ptn = get_route(id);
    // check if element exist in route vector
    // nullptr =  null pointeur referencing null object
    
    if (route_to_check_ptn != nullptr)
    {
        route route_to_check = *route_to_check_ptn;
        node first_click = route_to_check.get_pos1();
        node second_click = route_to_check.get_pos2();

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

        // check if the route the user chose has an adjacent house or route
        if ((first_click.get_state() == player) || (second_click.get_state() == player))
        {
            adjacent_route_or_house = true;
        }
        else
        {
            adjacent_route_or_house = (check_node_has_adj_route(first_click, player) || check_node_has_adj_route(second_click, player));
        }

        // check if the two nodes selected are neighboor or form a route
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
            /*
            cout << " ------------route constuction debug------------- "  << endl;
            cout << " are neighboor = " << neighboor << endl;
            cout << " adjacent construction exist (route/house) = " << adjacent_route_or_house << endl;
            cout << " route already exists = " << route_exist << endl;
            cout << " results = " << (neighboor && adjacent_route_or_house && !route_exist) << endl;
            */
           
        result = (neighboor && adjacent_route_or_house && !route_exist);
        return result;
    }

    
    return result;

}

/**
 * @brief
 * return unique values of all intersections present in I_map
 *
 * @return vector<node> containing all the intersection with theirs updated states
 */
vector<node> I_map::get_all_nodes()
{
    vector<node> all_nodes;
    for (unsigned int i = 0; i < map.size(); i++)
    {
        bool first_element_exists = false;
        bool second_element_exists = false;

        for (unsigned int k = 0; k < all_nodes.size(); k++)
        {
            first_element_exists = first_element_exists || ((map[i].get_pos1().id) == (all_nodes[k].id));
            second_element_exists = second_element_exists || ((map[i].get_pos2().id) == (all_nodes[k].id));
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
    return all_nodes;
}

/**
 * @brief
 * return all routes a given player have
 * @param player_id
 * @return vector<route>
 */
vector<route> I_map::get_all_occupied_routes()
{
    vector<route> all_routes;
    for (unsigned int i = 0; i < map.size(); i++)
    {
        if (map[i].get_route_state() != States::empty)
        {
            all_routes.push_back(map[i]);
        }
    }
    return all_routes;
}

/**
 * @brief
 * return all possible routes
 * @return vector<route>  vector containing all possible routes
 */
vector<route> I_map::get_all_possible_routes(States player_id)
{
    vector<route> all_possible_routes;
    for (unsigned int i = 0; i < map.size(); i++)
    {
        route my_route = map[i];
        if (check_possible_route(my_route.id, player_id))
        {
            all_possible_routes.push_back(my_route);
        }
    }
    return all_possible_routes;
}

/**
 * @brief
 * checks if there's 2 adjacent routes to our to_build_constuction
 *
 * @param to_build_constuction
 * @param player_id
 * @return true
 * @return false
 */
bool I_map::check_2_routes_exist(node to_build_constuction, States player_id)
{
    bool two_adjacent_route_or_house = false;

    for (unsigned int i = 0; i < map.size(); i++)
    {
        route my_route = map[i];
        node pos_1 = my_route.get_pos1();
        node pos_2 = my_route.get_pos2();

        if ((pos_1.id == to_build_constuction.id || pos_2.id == to_build_constuction.id))
        {
            if ((my_route.get_route_state() == player_id)) // if first adjacent route exist
            {
                // get the neighboor node of our to_build_const in the **adjacent route**
                node NeighboorNode = my_route.get_neighboor_in_route(to_build_constuction);
                cout << NeighboorNode.id << endl;
                // look for 2nd  adjacent route !!! must be diffrent of the first , if there's another adjacent route
                // belonging to the same with player player_id
                for (unsigned int k = 0; k < map.size(); k++)
                {
                    route my_sec_route = map[k];
                    node sec_pos_1 = my_sec_route.get_pos1();
                    node sec_pos_2 = my_sec_route.get_pos2();
                    if ((sec_pos_1.id == NeighboorNode.id || sec_pos_2.id == NeighboorNode.id) && (my_route.id != my_sec_route.id))
                    {
                        two_adjacent_route_or_house = (two_adjacent_route_or_house || (my_sec_route.get_route_state() == player_id));
                    }
                }
            }
        }
    }

    return two_adjacent_route_or_house;
}

/**
 * @brief
 * checks if our house constuction is possible
 *
 * 1/check if check_2_routes_exist(...) methode return true
 * 2/check if the node is not occupied .(must be empty)
 * 3/check no neighboor exist
 *
 * @param to_build_constuction  // will be returned by render_node()
 * @param player_id
 * @return true
 * @return false
 */
bool I_map::check_house_construction_possible(int id, States player_id)
{
    bool has_neighboor;
    bool two_route_exist = false;
    bool not_occupied = false;
    node* to_build_constuction_ptr= get_node(id);
    
    if (to_build_constuction_ptr != nullptr)  
    {
        node to_build_constuction = *to_build_constuction_ptr;
        if (check_2_routes_exist(to_build_constuction, player_id))
        {
            two_route_exist = true;
        }

        if (to_build_constuction.get_state() == States::empty)
        {
            not_occupied = true;
        }

        has_neighboor=check_node_has_adj_node(to_build_constuction);
        

        cout << " ------------House constuction debug-------------  " << endl;
        cout << " two route exists = " << two_route_exist << endl;
        cout << " not_occupied = " << not_occupied << endl;
        cout << " has_neighboor = " << has_neighboor << endl;
        cout << " results = " << (two_route_exist && not_occupied) << endl;

        return (not_occupied && two_route_exist && !has_neighboor);
       
    }
    
    return false;
}

/**
 * @brief
 * return an exact node object from I_map  the closest to the user choice
 * @param click_x   x cordonate of the user click
 * @param click_y   y cordonate of the user click
 * @param sensibilty
 * @return node object from the map corresponding to the user choice
 */
int I_map::render_node(int click_x, int click_y, int sensibility)
{
    int returned_id = -1;
    vector<node> all_nodes = get_all_nodes();

    for (unsigned i = 0; i < all_nodes.size(); i++)
    {
        if (
            ((click_x < all_nodes[i].get_x() + sensibility) && (click_x > all_nodes[i].get_x() - sensibility)) &&
            ((click_y < all_nodes[i].get_y() + sensibility) && (click_y > all_nodes[i].get_y() - sensibility)))
        {
            returned_id = all_nodes[i].id;
            return returned_id;
        }
    }
}

/**
 * @brief
 *
 * @param click_x
 * @param click_y
 * @return int
 */
int I_map::render_route(int click_x, int click_y)
{
    int id_returned = -1;
    for (unsigned int i = 0; i < map.size(); i++)
    {
        route my_route = map[i];
        node pos_1 = my_route.get_pos1();
        node pos_2 = my_route.get_pos2();
        int pos1_x = pos_1.get_x(),
            pos1_y = pos_1.get_y(),

            pos2_x = pos_2.get_x(),
            pos2_y = pos_2.get_y();

        if (abs(pos1_y - pos2_y) < 10)
        {

            if (
                (click_x < max(pos1_x, pos2_x)) && (click_x > min(pos1_x, pos2_x)) &&
                (click_y < pos1_y + 10) && (click_y > pos1_y - 10))
            {
                id_returned = my_route.id;
                return id_returned;
            }
        }
        else if (
            ((click_x < max(pos1_x, pos2_x)) && (click_x > min(pos1_x, pos2_x))) &&
            ((click_y < max(pos1_y, pos2_y)) && (click_y > min(pos1_y, pos2_y))))

        {
            id_returned = my_route.id;
            return id_returned;
        }
    }
}
