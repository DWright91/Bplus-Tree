#define SIMPLEINDEX_H
//#include<iostream>
//#include<iomanip>
using namespace std;
template <class keyType>
class SimpleIndex
{public:
    SimpleIndex (int maxKeys = 100, int unique = 1);
    ~SimpleIndex ();
    void Clear(); // remove allfrom index
    int Insert (const keyType key, int recAddr);
    // for Remove, Search, and Find, if recAddr =~ -1,
    //remove the first instance of key
    int Remove (const keyType key, const int recAddr = -1);
    // for Search and Find, if exact== 1, return -1 if not found
    // if exact== 0, find largest key in node<= argument key
    int Search (const keyType key, const int recAddr = -1, const int exact= 1) const;
    void Print (ostream &) const;
    int numKeys () const {return NumKeys;}
    int NumKeys;
protected:
    int MaxKeys;

    keyType * Keys;
    int* RecAddrs;
    int Find (const keyType key, const int recAddr = -1, const int exact= 1) const;
    int Init (const int maxKeys, const int unique);
    int Unique; // if true, each key value must be unique
    //friend class IndexBuffer<keyType>;
    //friend class BTree<keyType>;

};
#include"SimpleIndex.cpp"

