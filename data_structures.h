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
    int tuile_id;
    int x, y; // cordonates
    Ressouces ressource;
    int num_de;
};

//------------------------------------------------------------------------------------------------

class T_map
{

public:
    //---------------------constructor-----------------//
    T_map()
    {
        insert(tuile(0, 392, 471, Ressouces::mouton));
        insert(tuile(1, 500, 404, Ressouces::bois));
        insert(tuile(2, 598, 466, Ressouces::desert));
        insert(tuile(3, 498, 538, Ressouces::argile));
        insert(tuile(4, 295, 540, Ressouces::bois));
        insert(tuile(5, 296, 397, Ressouces::ble));
        insert(tuile(6, 399, 346, Ressouces::ble));
        insert(tuile(7, 496, 282, Ressouces::pierre));
        insert(tuile(8, 598, 341, Ressouces::argile));
        insert(tuile(9, 695, 405, Ressouces::ble));
        insert(tuile(10, 699, 538, Ressouces::mouton));
        insert(tuile(11, 592, 602, Ressouces::desert));
        insert(tuile(12, 496, 664, Ressouces::pierre));
        insert(tuile(13, 393, 601, Ressouces::argile));
        insert(tuile(14,297 ,  665 ,Ressouces::mouton));
        insert(tuile(15,199 ,  602 ,Ressouces::pierre));
        insert(tuile(16,198 ,  472 ,Ressouces::ble));
        insert(tuile(17,200 , 346 ,Ressouces::argile));
        insert(tuile(18,296 , 277,Ressouces::mouton));
        insert(tuile(19,399 , 214,Ressouces::pierre));
        insert(tuile(20,498 , 148,Ressouces::argile));
        insert(tuile(21,596 , 208,Ressouces::mouton));
        insert(tuile(22,698 , 272,Ressouces::bois));
        insert(tuile(23,794 , 346,Ressouces::ble));
        insert(tuile(24,801 , 471,Ressouces::bois));
        insert(tuile(25,795 , 601,Ressouces::mouton));
        insert(tuile(26,703 , 667,Ressouces::pierre));
        insert(tuile(27,595 , 732,Ressouces::ble));
        insert(tuile(28,498 , 793,Ressouces::bois));
        insert(tuile(29,400 , 729,Ressouces::bois));
            
        

        // tuile thief_tuile = tuile(2, 598, 466, Ressouces::desert);
        randomize_tuiles_de();
        set_size(); // update size attribute (the size of our T_map)
    }
    //--------------------get--------------------------//
    int get_size()
    {
        return size;
    }

    void set_thief(tuile new_thief)
    {
        this->thief = new_thief;
    }

    tuile get_thief()
    {
        return thief;
    }

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

private:
    vector<tuile> map;
    int size;
    tuile thief = tuile(2, 598, 466, Ressouces::desert); // thief is initially in 2
    //---------------------used by constructor-------//

    void randomize_tuiles_de()

    //  assign random values to tuiles (vinignette)
    //  following this distribution below {0,1,2,3,3,3,3,0,3,3,3,3,2}
    {

        vector<int> all_vigniettes;
        std::random_device rd;
        std::mt19937 g(rd());
        all_vigniettes = {2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 6, 8, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12};
        std::shuffle(std::begin(all_vigniettes), std::end(all_vigniettes), g);

        for (unsigned int i = 0; i < map.size(); i++)
        {
            map[i].set_de(all_vigniettes[i]);
        }

        //!!!!!!!!!!!!!!!!!!!!!!!!! this function can be used in Dé after !!!!!!!!!!!!////////////////
        // std::random_device rd;
        // unsigned long seed = rd();
        // std::mt19937 engine(seed);
        // std::discrete_distribution<int> distribution {0,1,2,3,3,3,3,4,3,3,3,3,2};
        // for (unsigned int i = 0; i < map.size(); i++)
        //  {
        //      map[i].set_de(distribution(engine));
        // }
    }

    void insert(tuile tuile)
    {
        map.push_back(tuile);
    }

    void set_size()
    {
        this->size = map.size();
    }
};

//---------------------------------------------------------------------------//

//-------------------------- I_map (intersection data structure)----------------------------------------------//
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 * this class is a data structure enabling tuiles objects storing  and accessing
 *&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
//-----------------------------------------------------------------------------------------------

class intersection
{

public:
    intersection();

protected:
private:
    int x, y;
    States state;                     // state of the intersection (empty or  player id)
    std::vector<tuile> adj_ressource; // list of maximum 3 tuiles
};

// class I_map
// {
// private:
//     vector<I_HashKeyValue> hkv;

// public:

//     I_map() {}

//     void set(string h, string k, string v)
//     {
//         hkv.push_back(I_HashKeyValue(h, k, v));
//     }
//     string getV(string h, string k)
//     {
//         for (unsigned int i = 0; i < hkv.size(); i++)
//         {
//             if (hkv[i].getHash() == h && hkv[i].getKey() == k)
//                 return hkv[i].getValue();
//         }
//         return "n/a";
//     }
//     string getByColValue(string col1, string val, string col2)
//     {
//         string hash;
//         int got = 0;
//         for (unsigned int i = 0; i < hkv.size() && !got; i++)
//         {
//             if (hkv[i].getKey() == col1 && hkv[i].getValue() == val)
//             {
//                 hash = hkv[i].getHash();
//                 got = 1;
//             }
//         }
//         if (got)
//         {
//             for (unsigned int i = 0; i < hkv.size(); i++)
//             {
//                 if (hkv[i].getHash() == hash && hkv[i].getKey() == col2)
//                     return hkv[i].getValue();
//             }
//             return "n/a";
//         }
//         else
//             return "n/a";
//     }
// };
//---------------------------------------------------------------------------//
