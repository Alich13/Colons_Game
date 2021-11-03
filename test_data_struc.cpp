#include "data_structures.h"
#include <iostream>
#include<list>
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
        tuile T0 =tuile(0, 598, 466, Ressouces::desert);
        tuile T1 =tuile(1,496, 664, Ressouces::desert);
        tuile T2 = tuile(2, 392, 471, Ressouces::mouton);
        tuile T3 = tuile(3, 500, 404, Ressouces::bois);
        tuile T4 =tuile(4, 498, 538, Ressouces::argile);
        tuile T5 =tuile(5, 295, 540, Ressouces::argile);
        tuile T6 =tuile(6, 296, 397, Ressouces::bois);
        tuile T7 =tuile(7, 399, 346, Ressouces::ble);
        tuile T8 =tuile(8, 496, 282, Ressouces::ble);
        tuile T9 =tuile(9, 598, 341, Ressouces::pierre);
        tuile T10 =tuile(10, 695, 405, Ressouces::argile);
        tuile T11 =tuile(11,699, 538, Ressouces::ble);
        tuile T12 =tuile(12,592, 602, Ressouces::mouton);
        tuile T13 =tuile(13,393, 601, Ressouces::pierre);
        tuile T14 =tuile(14,297 , 665 ,Ressouces::mouton);
        tuile T15 =tuile(15,199 , 602 ,Ressouces::pierre);
        tuile T16 =tuile(16,198 , 472 ,Ressouces::ble);
        tuile T17 =tuile(17,200 , 346 ,Ressouces::argile);
        tuile T18 =tuile(18,296 , 277,Ressouces::mouton);
        tuile T19 =tuile(19,399 , 214,Ressouces::pierre);
        tuile T20 =tuile(20,498 , 148,Ressouces::argile);
        tuile T21 =tuile(21,596 , 208,Ressouces::mouton);
        tuile T22 =tuile(22,698 , 272,Ressouces::bois);
        tuile T23 =tuile(23,794 , 346,Ressouces::ble);
        tuile T24 =tuile(24,801 , 471,Ressouces::bois);
        tuile T25 =tuile(25,795 , 601,Ressouces::mouton);
        tuile T26 =tuile(26,703 , 667,Ressouces::pierre);
        tuile T27 =tuile(27,595 , 732,Ressouces::ble);
        tuile T28 =tuile(28,498 , 793,Ressouces::bois);
        tuile T29 =tuile(29,400 , 729,Ressouces::bois);
    
    
    // Insert tuiles into tuiles map
         tuile_map.insert(T0) ;
         tuile_map.insert(T1) ;
         tuile_map.insert(T2);
         tuile_map.insert(T3) ;
         tuile_map.insert(T4) ;
         tuile_map.insert(T5) ;
         tuile_map.insert(T6) ;
         tuile_map.insert(T7) ;
         tuile_map.insert(T8) ;
         tuile_map.insert(T9) ;
         tuile_map.insert(T10) ;
         tuile_map.insert(T11) ;
         tuile_map.insert(T12) ;
         tuile_map.insert(T13) ;
         tuile_map.insert(T14) ;
         tuile_map.insert(T15);
         tuile_map.insert(T16) ;
         tuile_map.insert(T17) ;
         tuile_map.insert(T18) ;
         tuile_map.insert(T19) ;
         tuile_map.insert(T20) ;
         tuile_map.insert(T21) ;
         tuile_map.insert(T22) ;
         tuile_map.insert(T23) ;
         tuile_map.insert(T24) ;
         tuile_map.insert(T25) ;
         tuile_map.insert(T26) ;
         tuile_map.insert(T27) ;
         tuile_map.insert(T28) ;
         tuile_map.insert(T29) ;

    // Randomize and set up tuiles
        tuile_map.randomize_tuiles_de();


    //set intersections 
        node I1 = node(1,332,472,   {T2,T5,T6});
        node I2 = node(2,364,409,   {T6,T2,T7});
        node I3 = node(3,429 ,409,  {T3,T2,T7});
        node I4 = node(4,463 ,471,{T2,T3,T4});
        node I5 = node(5,429 ,536,{T4,T2,T13});
        node I6 = node(6,363 ,537,{T5,T2,T13});
    
       
 
 
    // set routes
    route R1 = route(I1,I2); 
    route R2 = route(I2,I3);
    route R3 = route(I3,I4);
    route R4 = route(I4,I5);
    route R5 = route(I5,I6);
    route R6 = route(I6,I1);

    //insert routes in I_map
    
    intersection_map.insert(R1);
    intersection_map.insert(R2);
    intersection_map.insert(R3);
    intersection_map.insert(R4);
    intersection_map.insert(R5);
    intersection_map.insert(R6);

}




int main() {



    Board board;
    I_map intersection_map = board.intersection_map;

    
    intersection_map.update_intersection_state(2, States::p1) ;
    node I1=intersection_map.get_node(1);
    node I2=intersection_map.get_node(2);
    node I3=intersection_map.get_node(3);
    
    
    intersection_map.update_route_state(I1,I3 ,States::p1) ;
    
    cout << intersection_map.check_possible_route(I2,I3,States::p1) << endl;

    intersection_map.print_map();

}







