#include "../header.h"
#include <cairomm/context.h>
#include <iostream>

using namespace std;

Board::Board()
{
    // Défine tuiles
    tuile T0 = tuile(0, 598, 466, Resources::desert);
    //T0.set_de(7);
    tuile T1 = tuile(1, 496, 664, Resources::desert);
    tuile T2 = tuile(2, 392, 471, Resources::mouton);
    tuile T3 = tuile(3, 500, 404, Resources::bois);
    tuile T4 = tuile(4, 498, 538, Resources::argile);
    tuile T5 = tuile(5, 295, 540, Resources::argile);
    tuile T6 = tuile(6, 296, 397, Resources::bois);
    tuile T7 = tuile(7, 399, 346, Resources::ble);
    tuile T8 = tuile(8, 496, 282, Resources::ble);
    tuile T9 = tuile(9, 598, 341, Resources::pierre);
    tuile T10 = tuile(10, 695, 405, Resources::argile);
    tuile T11 = tuile(11, 699, 538, Resources::ble);
    tuile T12 = tuile(12, 592, 602, Resources::mouton);
    tuile T13 = tuile(13, 393, 601, Resources::pierre);
    tuile T14 = tuile(14, 297, 665, Resources::mouton);
    tuile T15 = tuile(15, 199, 602, Resources::pierre);
    tuile T16 = tuile(16, 198, 472, Resources::ble);
    tuile T17 = tuile(17, 200, 346, Resources::argile);
    tuile T18 = tuile(18, 296, 277, Resources::mouton);
    tuile T19 = tuile(19, 399, 214, Resources::pierre);
    tuile T20 = tuile(20, 498, 148, Resources::argile);
    tuile T21 = tuile(21, 596, 208, Resources::mouton);
    tuile T22 = tuile(22, 698, 272, Resources::bois);
    tuile T23 = tuile(23, 794, 346, Resources::ble);
    tuile T24 = tuile(24, 801, 471, Resources::bois);
    tuile T25 = tuile(25, 795, 601, Resources::mouton);
    tuile T26 = tuile(26, 703, 667, Resources::pierre);
    tuile T27 = tuile(27, 595, 732, Resources::ble);
    tuile T28 = tuile(28, 498, 793, Resources::bois);
    tuile T29 = tuile(29, 400, 729, Resources::bois);

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
    node I14 = node(14, 464, 215, {T20, T19, T8});
    node I15 = node(15, 531, 216, {T20, T21, T8});
    node I16 = node(16, 561, 275, {T21, T8, T9});
    node I17 = node(17, 528, 341, {T9, T8, T3});
    node I18 = node(18, 564, 405, {T3, T0, T9});
    node I19 = node(19, 529, 472, {T3, T0, T4});
    node I20 = node(20, 561, 536, {T4, T0, T12});
    node I21 = node(21, 531, 600, {T4, T12, T1});
    node I22 = node(22, 463, 597, {T13, T4, T1});
    node I23 = node(23, 431, 662, {T13, T1, T29});
    node I24 = node(24, 363, 666, {T14, T13, T29});
    node I25 = node(25, 330, 602, {T14, T5, T13});
    node I26 = node(26, 264, 599, {T15, T5, T14});
    node I27 = node(27, 229, 537, {T15, T16, T5});
    node I28 = node(28, 630 , 279, {T21 ,T9  ,T22 });
    node I29 = node(29,662 , 343 , {T9 ,T10 ,T22 });
    node I30 = node(30,728 , 341, { T22,T23 ,T10 });
    node I31 = node(31,762 , 406, { T10,T23 ,T24 });
    node I32 = node(32,732 , 469 , { T10,T11 ,T24 });
    node I33 = node(33,763 , 535 , { T11,T24  ,T25 });
    node I34 = node(34,729 , 597 , { T11,T25  ,T26 });
    node I35 = node(35,662 , 600 , { T11, T26 ,T12 });
    node I36 = node(36,630 , 665 , { T12,T26  ,T27 });
    node I37 = node(37,563 , 664 , { T1,T12  ,T27 });
    node I38 = node(38,531 , 727 , { T1,T27  ,T28 });
    node I39 = node(39,463 , 729 , {T1 , T28 ,T29 });
    node I40 = node(40,630 , 534 , { T0,T11  ,T12 });
    node I41 = node(41,662 , 471 , { T0,T10  ,T11 });
    node I42 = node(42,629 , 408 , { T9,T10  ,T0 });

    /*

    node I43 = node(43, , { ,  , });
    node I44 = node(44, , { ,  , });
    node I45 = node(45, , { ,  , });
    node I46 = node(46, , { ,  , });
    node I47 = node(47, , { ,  , });
    node I48 = node(48, , { ,  , });
    node I49 = node(49, , { ,  , });
    node I50 = node(50, , { ,  , });
    node I51 = node(51, , { ,  , });
    node I52 = node(52, , { ,  , });
    node I53 = node(53, , { ,  , });
    node I54 = node(54, , { ,  , });
    node I55 = node(55, , { ,  , });
    node I56 = node(56, , { ,  , });
    node I57 = node(57, , { ,  , });
    node I58 = node(58, , { ,  , });
    node I59 = node(59, , { ,  , });
    node I60 = node(60, , { ,  , });
    node I61 = node(61, , { ,  , });
    node I62 = node(62, , { ,  , });
    node I63 = node(63, , { ,  , });
    node I64 = node(64, , { ,  , });
    node I65 = node(65, , { ,  , });
    node I66 = node(66, , { ,  , });
    node I67 = node(67, , { ,  , });
    node I68 = node(68, , { ,  , });
    node I69 = node(69, , { ,  , });
    node I70 = node(70, , { ,  , });
    node I71 = node(71, , { ,  , });
    node I72 = node(72, , { ,  , });
    node I73 = node(73, , { ,  , });
    node I74 = node(74, , { ,  , });
    node I75 = node(75, , { ,  , });
    node I76 = node(76, , { ,  , });
    node I77 = node(77, , { ,  , });
    node I78 = node(78, , { ,  , });
    node I79 = node(79, , { ,  , });
    node I80 = node(80, , { ,  , })
    
    */
   
    

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
    route R16 = route(16,I12,I14 );
    route R17 = route(17,I14,I15 );
    route R18 = route(18,I15,I16 );
    route R19 = route(19,I16,I17 );
    route R20 = route(20,I17,I11 );
    route R21 = route(21,I17,I18 );
    route R22 = route(22,I18,I19 );
    route R23 = route(23,I19,I4 );
    route R24 = route(24,I19,I20 );
    route R25 = route(25,I20,I21 );
    route R26 = route(26,I21,I22);
    route R27 = route(27,I22,I5);
    route R28 = route(28,I23,I22);
    route R29 = route(29,I23,I24);
    route R30 = route(30,I24,I25);
    route R31 = route(31,I25,I6);
    route R32 = route(32,I25,I26);
    route R33 = route(33,I26,I27);
    route R34 = route(34,I27,I7);
    route R35 = route(35,I16,I28);
    route R36 = route(36,I28,I29);
    route R37 = route(37,I29,I30);
    route R38 = route(38,I30,I31);
    route R39 = route(39,I31,I32);
    route R40 = route(40,I32,I33);
    route R41 = route(41,I33,I34);
    route R42 = route(42,I34,I35);
    route R43 = route(43,I35,I36);
    route R44 = route(44,I36,I37);
    route R45 = route(45,I37,I38);
    route R46 = route(46,I38,I39);
    route R47 = route(47,I39,I23);
    route R48 = route(48,I21,I37);
    route R49 = route(49,I40,I35);
    route R50 = route(50,I41,I32);
    route R51 = route(51,I42,I29);
    route R52 = route(52,I18,I42);
    route R53 = route(53,I42,I41);
    route R54 = route(54,I40,I41);
    route R55 = route(55,I20,I40);
    
    /*
    route R56 = route(56,);
    route R57 = route(57,);
    route R58 = route(58,);
    route R59 = route(59,);
    route R60 = route(60,);
    route R61 = route(61,);
    route R62 = route(62,);
    route R63 = route(63,);
    route R64 = route(64,);
    route R65 = route(65,);
    route R66 = route(66,);
    route R67 = route(67,);
    route R68 = route(68,);
    route R69 = route(69,);
    route R70 = route(70,);
    route R71 = route(71,);
    route R72 = route(72,);
    route R73 = route(73,);
    route R74 = route(74,);
    route R75 = route(75,);
    route R76 = route(76,);
    route R77 = route(77,);
    route R78 = route(78,);
    route R79 = route(79,);
    route R80 = route(80,);
    route R81 = route(81,);
    route R82 = route(82,);
    route R83 = route(83,);
    route R84 = route(84,);
    route R85 = route(85,);
    route R86 = route(86,);
    route R87 = route(87,);
    route R88 = route(88,);
    route R89 = route(89,);
    route R90 = route(90,);
    route R91 = route(91,);
    route R92 = route(92,);
    route R93 = route(93,);
    route R94 = route(94,);
    route R95 = route(95,);
    route R96 = route(96,);
    route R97 = route(97,);
    route R98 = route(98,);
    route R99 = route(99,);
    */
    
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
    intersection_map.insert(R16);
    intersection_map.insert(R17);
    intersection_map.insert(R18);
    intersection_map.insert(R19);
    intersection_map.insert(R20);
    intersection_map.insert(R21);
    intersection_map.insert(R22);
    intersection_map.insert(R23);
    intersection_map.insert(R24);
    intersection_map.insert(R25);
    intersection_map.insert(R26);
    intersection_map.insert(R27);
    intersection_map.insert(R28);
    intersection_map.insert(R29);
    intersection_map.insert(R30);
    intersection_map.insert(R31);
    intersection_map.insert(R32);
    intersection_map.insert(R33);
    intersection_map.insert(R34);


    
    intersection_map.insert(R35);
    intersection_map.insert(R36);
    intersection_map.insert(R37);
    intersection_map.insert(R38);
    intersection_map.insert(R39);
    intersection_map.insert(R40);
    intersection_map.insert(R41);
    intersection_map.insert(R42);
    intersection_map.insert(R43);
    intersection_map.insert(R44);
    intersection_map.insert(R45);
    intersection_map.insert(R46);
    intersection_map.insert(R47);
    intersection_map.insert(R48);
    intersection_map.insert(R49);
    intersection_map.insert(R50);
    intersection_map.insert(R51);
    intersection_map.insert(R52);
    intersection_map.insert(R53);
    intersection_map.insert(R54);
    intersection_map.insert(R55);
    /*
    intersection_map.insert(R56);
    intersection_map.insert(R57);
    intersection_map.insert(R58);
    intersection_map.insert(R59);
    intersection_map.insert(R60);
    intersection_map.insert(R61);
    intersection_map.insert(R62);
    intersection_map.insert(R63);
    intersection_map.insert(R64);
    intersection_map.insert(R65);
    intersection_map.insert(R66);
    intersection_map.insert(R67);
    intersection_map.insert(R68);
    intersection_map.insert(R69);
    intersection_map.insert(R70);
    intersection_map.insert(R71);
    intersection_map.insert(R72);
    intersection_map.insert(R73);
    intersection_map.insert(R74);
    intersection_map.insert(R75);
    intersection_map.insert(R76);
    intersection_map.insert(R77);
    intersection_map.insert(R78);
    intersection_map.insert(R79);
    intersection_map.insert(R80);
    intersection_map.insert(R81);
    intersection_map.insert(R82);
    intersection_map.insert(R83);
    intersection_map.insert(R84);
    intersection_map.insert(R85);
    intersection_map.insert(R86);
    intersection_map.insert(R87);
    intersection_map.insert(R88);
    intersection_map.insert(R89);
    intersection_map.insert(R90);
    intersection_map.insert(R91);
    intersection_map.insert(R92);
    intersection_map.insert(R93);
    intersection_map.insert(R94);
    intersection_map.insert(R95);
    intersection_map.insert(R96);
    intersection_map.insert(R97);
    intersection_map.insert(R98);
    intersection_map.insert(R99);
    intersection_map.insert(R100);
    intersection_map.insert(R101);
    intersection_map.insert(R102);
    intersection_map.insert(R103);
    intersection_map.insert(R104);
    intersection_map.insert(R105);
    intersection_map.insert(R106);
    intersection_map.insert(R107);
    intersection_map.insert(R108);
    intersection_map.insert(R109);
    intersection_map.insert(R110);
    intersection_map.insert(R111);
    intersection_map.insert(R112);
    intersection_map.insert(R113);
    intersection_map.insert(R114);
    intersection_map.insert(R115);
    intersection_map.insert(R116);
    intersection_map.insert(R117);
    intersection_map.insert(R118);
    intersection_map.insert(R119);
    */
    
    // for testing purposes
    intersection_map.update_intersection_state(1, States::p1);
    intersection_map.update_intersection_state(4, States::p2);
    intersection_map.update_intersection_state(14, States::p3);
}
