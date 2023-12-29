/********************************************
B+TreeNode.h header file
********************************************/

#define BTNode_H
#include"IOBuffer.h"
#include"FixFieldBuffer.h"
#include"SimpleIndex.h"
using namespace std;
/********************************************
B+Tree class declaration
********************************************/
template <class keyType>
class BTreeNode: public SimpleIndex<keyType>

{
    public:
        BTreeNode(int maxKeys, int unique = 1);
        ~BTreeNode();
        //Insert and remove return
        //0 for failure
        //-1 for overflow
        // 1 for success
        int Insert(const keyType key, int recAddr);
        int Remove(const keyType key, int recAddr = -1);
        //int Search)const keyType key) const;
        int LargestKey(); //returns largest key value
        int Split(BTreeNode<keyType> *newNode);//move into newNode
        int Merge(BTreeNode<keyType> *fromNode);//move from fromNode
        int UpdateKey(keyType oldKey, keyType newKey, int recAddr = -1);
        int Pack(IOBuffer& buffer) const;
        int Unpack(IOBuffer& buffer);
        static int InitBuffer (FixedFieldBuffer & buffer, int maxKeys, int keySize = sizeof(keyType));
    protected:
        int NextNode; //address of next node same level
        int RecAddr; // address of this node in the BTree file
        int MinKeys;// min number of keys in a node
        int MaxBKeys; //max number of keys in a node
        int Init();
        void Clear() { MinKeys = 0, RecAddr = -1;}
//        friend class BTree<keyType>;
};
#include "BTNode.cpp"
