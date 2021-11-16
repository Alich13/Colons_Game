#include "data_structures.h"
#include "header.h"
#include <iostream>
#include <list>
#include <iterator>
#include <vector>
using namespace std;

class Board
{

public:
    Board();
    // I_map board_map;
    T_map tuile_map;
    I_map intersection_map;
    /*
    bool check_route_exist();
    bool check_construction_exist();
    bool check_possible_route();
    bool check_possible_construction();
    void update_board();
    */
private:
};

Board::Board()
{
    // Défine tuiles
    tuile T0 = tuile(0, 598, 466, Ressouces::desert);
    tuile T1 = tuile(1, 496, 664, Ressouces::desert);
    tuile T2 = tuile(2, 392, 471, Ressouces::mouton);
    tuile T3 = tuile(3, 500, 404, Ressouces::bois);
    tuile T4 = tuile(4, 498, 538, Ressouces::argile);
    tuile T5 = tuile(5, 295, 540, Ressouces::argile);
    tuile T6 = tuile(6, 296, 397, Ressouces::bois);
    tuile T7 = tuile(7, 399, 346, Ressouces::ble);
    tuile T8 = tuile(8, 496, 282, Ressouces::ble);
    tuile T9 = tuile(9, 598, 341, Ressouces::pierre);
    tuile T10 = tuile(10, 695, 405, Ressouces::argile);
    tuile T11 = tuile(11, 699, 538, Ressouces::ble);
    tuile T12 = tuile(12, 592, 602, Ressouces::mouton);
    tuile T13 = tuile(13, 393, 601, Ressouces::pierre);
    tuile T14 = tuile(14, 297, 665, Ressouces::mouton);
    tuile T15 = tuile(15, 199, 602, Ressouces::pierre);
    tuile T16 = tuile(16, 198, 472, Ressouces::ble);
    tuile T17 = tuile(17, 200, 346, Ressouces::argile);
    tuile T18 = tuile(18, 296, 277, Ressouces::mouton);
    tuile T19 = tuile(19, 399, 214, Ressouces::pierre);
    tuile T20 = tuile(20, 498, 148, Ressouces::argile);
    tuile T21 = tuile(21, 596, 208, Ressouces::mouton);
    tuile T22 = tuile(22, 698, 272, Ressouces::bois);
    tuile T23 = tuile(23, 794, 346, Ressouces::ble);
    tuile T24 = tuile(24, 801, 471, Ressouces::bois);
    tuile T25 = tuile(25, 795, 601, Ressouces::mouton);
    tuile T26 = tuile(26, 703, 667, Ressouces::pierre);
    tuile T27 = tuile(27, 595, 732, Ressouces::ble);
    tuile T28 = tuile(28, 498, 793, Ressouces::bois);
    tuile T29 = tuile(29, 400, 729, Ressouces::bois);

    // Insert tuiles into tuiles map
    tuile_map.insert(T0);
    tuile_map.insert(T1);
    tuile_map.insert(T2);
    tuile_map.insert(T3);
    tuile_map.insert(T4);
    tuile_map.insert(T5);
    tuile_map.insert(T6);
    tuile_map.insert(T7);
    tuile_map.insert(T8);
    tuile_map.insert(T9);
    tuile_map.insert(T10);
    tuile_map.insert(T11);
    tuile_map.insert(T12);
    tuile_map.insert(T13);
    tuile_map.insert(T14);
    tuile_map.insert(T15);
    tuile_map.insert(T16);
    tuile_map.insert(T17);
    tuile_map.insert(T18);
    tuile_map.insert(T19);
    tuile_map.insert(T20);
    tuile_map.insert(T21);
    tuile_map.insert(T22);
    tuile_map.insert(T23);
    tuile_map.insert(T24);
    tuile_map.insert(T25);
    tuile_map.insert(T26);
    tuile_map.insert(T27);
    tuile_map.insert(T28);
    tuile_map.insert(T29);

    // Randomize and set up tuiles
    tuile_map.randomize_tuiles_de();

    // set intersections
    node I1 = node(1, 332, 472, {T2, T5, T6});
    node I2 = node(2, 364, 409, {T6, T2, T7});
    node I3 = node(3, 429, 409, {T3, T2, T7});
    node I4 = node(4, 463, 471, {T2, T3, T4});
    node I5 = node(5, 429, 536, {T4, T2, T13});
    node I6 = node(6, 363, 537, {T5, T2, T13});
    node I7 = node(7, 263, 471, {T5, T16, T6});
    node I8 = node(8, 330, 344, {T18, T7, T6});
    node I9 = node(9, 263, 342, {T17, T18, T6});
    node I10 = node(10, 230, 408, {T17, T16, T5});
    node I11 = node(11, 463, 343, {T7, T3, T8});
    node I12 = node(12, 430, 280, {T19, T8, T7});
    node I13 = node(13, 363, 278, {T18, T19, T7});

    // set routes
    route R1 = route(1, I1, I2);
    route R2 = route(2, I2, I3);
    route R3 = route(3, I3, I4);
    route R4 = route(4, I4, I5);
    route R5 = route(5, I5, I6);
    route R6 = route(6, I6, I1);
    route R7 = route(7, I7, I1);
    route R8 = route(8, I7, I10);
    route R9 = route(9, I10, I9);
    route R10 = route(10, I9, I8);
    route R11 = route(11, I8, I2);
    route R12 = route(12, I8, I13);
    route R13 = route(13, I13, I12);
    route R14 = route(14, I12, I11);
    route R15 = route(15, I11, I3);
    




    // insert routes in I_map

    intersection_map.insert(R1);
    intersection_map.insert(R2);
    intersection_map.insert(R3);
    intersection_map.insert(R4);
    intersection_map.insert(R5);
    intersection_map.insert(R6);
    intersection_map.insert(R7);
    intersection_map.insert(R8);
    intersection_map.insert(R9);
    intersection_map.insert(R10);
    intersection_map.insert(R11);
    intersection_map.insert(R12);
    intersection_map.insert(R13);
    intersection_map.insert(R14);
    intersection_map.insert(R15);
}

int main()
{

    Board board;
    I_map intersection_map = board.intersection_map;

    /*set states*/
    intersection_map.update_intersection_state(1, States::p1);
    intersection_map.update_intersection_state(2, States::p1);

    node* I1 = intersection_map.get_node(1);
    node* I2 = intersection_map.get_node(2);
    node* I3 = intersection_map.get_node(3);
    node* I4 = intersection_map.get_node(4);
    node* I5 = intersection_map.get_node(5);
    node* I6 = intersection_map.get_node(6);
    // node I7 = intersection_map.get_node(7);
    // node I8 = intersection_map.get_node(8);
    // node I9 = intersection_map.get_node(9);
    // node I10 = intersection_map.get_node(10);
    // node I11 = intersection_map.get_node(11);
    // node I12 = intersection_map.get_node(12);
    // node I13 = intersection_map.get_node(13);

    // intersection_map.update_route_state(I8, I13, States::p1);
    // intersection_map.update_route_state(I13, I12, States::p1);

    /*----------------------- test -------------------------------------------*/
    // node first_click = I6;
    // node second_click = I1;
    // node click = I12;
    // int id = 6;
    /*checks*/

    // //check houses
    // if (intersection_map.check_house_construction_possible(click, States::p1))
    //     {
    //             cout <<"----------updated----------"<<endl;
    //     }
    // else
    //     {
    //             cout <<"---------house construction not possible-------"<<endl;
    //     }

    // check routes

    // if (intersection_map.check_possible_route(id, States::p1))
    // {
    //     intersection_map.update_route_state(id, States::p1);
    //     cout << "----------updated----------" << endl;
    // }
    // else
    // {
    //     cout << "---------route construction not possible-------" << endl;
    // }

    /* set  only route state */
    // intersection_map.print_map();

    // /*prints all nodes */
    // vector<node> all_nodes = intersection_map.get_all_nodes();

    // for (unsigned i =0 ;i < all_nodes.size();i++)
    // {
    //     cout <<" id = "<<all_nodes[i].id << " state = "<< static_cast<int>(all_nodes[i].get_state())<< endl;
    // }

    /*prints all possible routes */
    // vector<route> all_routes = intersection_map.get_all_possible_routes(States::p1);

    // for (unsigned i = 0; i < all_routes.size(); i++)
    // {
    //     cout << " id = " << all_routes[i].id << endl;
    // }

    // for (unsigned i = 35; i < 100; i++)
    //  {
    //      cout << "route R"<<i<<" = route("<<i<<",);" << endl;
    //  }

    
    Player P1 = Player(States::p1,"ALi");
	Player P2 = Player(States::p2,"Louai");
	Player P3 = Player(States::p3,"jalil");
    
    //player management 
    vector<Player> player_list ={P1,P2,P3};
    vector<Player>::iterator current_player = player_list.begin();
    current_player=next(current_player,2);
    // //if (button pressed )
     if (current_player == player_list.end())
        {
            cout <<"yes";
        }

    
    // //i
    // std::cout << *it << ' ' << *nx << '\n';



    
}
