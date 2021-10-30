#include <string>
#include <vector>
#include <iostream>
enum class Ressouces {ble,bois,moutons,argile,desert,mouton,pierre};
enum class States {empty,p1,p2,p3,p4,p5,p6};
using namespace std;


class T_HashKeyValue
{
private:
    string hash;
    string key;
    string value;

public:
    T_HashKeyValue() {}
    T_HashKeyValue(string h, string k, string v)
    {
        hash = h;
        key = k;
        value = v;
    }
    string getHash() { return hash; }
    string getKey() { return key; }
    string getValue() { return value; }
};

class T_map
{
private:
    vector<T_HashKeyValue> hkv;

public:
    T_map() {}
    void set(string h, string k, string v)
    {
        hkv.push_back(T_HashKeyValue(h, k, v));
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

int main()
{
    T_map m;
    m.set("1", "Tenor", "1D");
    m.set("3", "Tenor", "3M");
    m.set("3", "Rate", "1.6%");
    cout << "get-1-Tenor(1D): " << m.getV("1", "Tenor") << endl;
    cout << "get-1-Alto(n/a): " << m.getV("1", "Alto") << endl;
    cout << "get-3-Rate(1.6%): " << m.getV("3", "Rate") << endl;
    cout << "getBCV-Tenor-3M-Rate(1.6%): " << m.getByColValue("Tenor", "3M", "Rate") << endl;
    return 0;
}