#include <string>
#include <vector>
#include <iostream>

using namespace std;


//-------------------------- I_map (intersections data structure)----------------------------------------------//
/*
 * this class is a data structure enabling intersection objects storing  and accessing
 *
 *
 */
class I_HashKeyValue
{
private:
    string hash;
    string key;
    string value;

public:
    I_HashKeyValue() {}
    I_HashKeyValue(string h, string k, string v)
    {
        hash = h;
        key = k;
        value = v;
    }
    string getHash() { return hash; }
    string getKey() { return key; }
    string getValue() { return value; }
};

class I_map
{
private:
    vector<I_HashKeyValue> hkv;

public:
    
    I_map() {}

    void set(string h, string k, string v)
    {
        hkv.push_back(I_HashKeyValue(h, k, v));
    }
    string getV(string h, string k)
    {
        for (unsigned int i = 0; i < hkv.size(); i++)
        {
            if (hkv[i].getHash() == h && hkv[i].getKey() == k)
                return hkv[i].getValue();
        }
        return "n/a";
    }
    string getByColValue(string col1, string val, string col2)
    {
        string hash;
        int got = 0;
        for (unsigned int i = 0; i < hkv.size() && !got; i++)
        {
            if (hkv[i].getKey() == col1 && hkv[i].getValue() == val)
            {
                hash = hkv[i].getHash();
                got = 1;
            }
        }
        if (got)
        {
            for (unsigned int i = 0; i < hkv.size(); i++)
            {
                if (hkv[i].getHash() == hash && hkv[i].getKey() == col2)
                    return hkv[i].getValue();
            }
            return "n/a";
        }
        else
            return "n/a";
    }
};
//---------------------------------------------------------------------------//
