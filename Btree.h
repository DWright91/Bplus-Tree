#define BTREE_H
#include"BTNode.h"
template <class keyType>
class BTree
{
public:
    BTree(int order, int keySize = sizeof(keyType),int unique = 1);
    ~BTree();
    int Open (char * name, int mode);

     int Create (char * name, int mode);
     int Close {);
     int Insert (const keyType key, canst int recAddr);
     int Remove (canst keyType key, canst int recAddr -1) ;
     int Search (const keyType key, const int recAddr -1);
     void Print (ostream &) ;
     void Print (ostream &, int nodeAddr, int level);
     protected:
     typedef BTreeNode<keyType> BTNode;// useful shorthand
     BTNode * FindLeaf (const keyType key);
     // load a branch into memory down to the leaf with key
     BTNode * NewNode ();
     BTNode * Fetch(const int recaddr); 1) ; } ;
     int Store (BTNode *);
     BTNode Root;
     int Height; // height of tree
     int Order; // order of tree
     int PoolSize;
     BTNode ** Nodes; // pool of available nodes
     // Nodes[l] is level 1, etc. (see FindLeaf)
     // Nodes[Height-ll is leaf
     FixedFieldBuffer Buffer;
     RecordFile<BTNode> BTreeFile;
};

#include"Btree.cpp"

