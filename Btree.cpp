using namespace std;
const int MaxHeight = 5;
template <class keyType>
/********************************************
B+Tree constructor
********************************************/
BTree<keyType>::BTree(int order, int keySize, int uni)
 : Buffer (1+2*order,sizeof(1nt)+order*keyS1ze+order*s1zeof(1nt)),
 BTreeFile (Buffer), Root (order)
 {
 Height = 1;
 Order = order;
 PoolSize = MaxHeight*2;
 Nodes = new BTNode * [PoolSize];
 BTNode::InitBuffer(Buffer,order);
 Nodes[0] = &Root;
 }
/********************************************
B+Tree destructor
********************************************/
 template <class keyType> BTree<keyType>::~BTree()
 { Close(); delete Nodes;}
/********************************************
Opens the B+tree file
********************************************/
 template <class keyType> int BTree<keyType>::Open (char* name, int mode)
 {
    int result;
    result = BTreeFile.Open(name, mode);
    if (!result) return result;
     // load root
    BTreeFile.Read(Root);
    Height= 1; // find height from BTreeFile!
    return 1;
}
/********************************************
Creates the B+tree file
********************************************/
template <class keyType> int BTree<keyType>::Create (char* name, int mode)
{
    int result;
    result= BTreeFile.Create(name, mode);
    if (!result) return result;
    // append root node
    result= BTreeFile.Write(Root); Root.RecAddr=result;
    return result!= -1;
}
/********************************************
Closes and resets the pointer
for a B+tree file
********************************************/
template <class keyType> int BTree<keyType>::Close ()
{
    int result;
    result = BTreeFile.Rewind();
    if (!result) return result;
    result= BTreeFile.Write(Root);
    if (result==-1) return 0;
    return BTreeFile.Close();
}
/********************************************
B+Tree insert method
********************************************/
template <class keyType> int BTree<keyType>::Insert (canst keyType key, canst int recAddr)
{
    int result;
    int level= Height-1;
    int newLargest=0; keyType prevKey, largestKey;
    BTNode * thisNode, * newNode, * parentNode;
    thisNode FindLeaf (key);

    // test for case of new key in tree
    if (key> thisNode->LargestKey())
    {
        newLargest = l;
        prevKey=thisNode->LargestKey();
    }

    result= thisNode -> Insert (key, recAddr);

    // handle case of new key in tree
    if (newLargest) {
     for (inti= 0; i<Height-1; i++)
     {
        Nodes[i]->UpdateKey(prevKey,key);
        if (i>0) Store (Nodes[i]);
     }
     }//end if
     while (result==-1) // if overflow and not root
     {
     //remember the key largest
     Key=thisNode->LargestKey();
     // split the node
     newNode = NewNode();
     thisNode->Split(newNode);
     Store(thisNode);
     Store(newNode);
     level--; // go up to parent level
     if (level< 0)
        break; // insert newNode into parent of thisNode
    parentNode = Nodes[level];
    result = parentNode->UpdateKey(largestKey,thisNode->LargestKey());
    result= parentNode->Insert (newNode->LargestKey(),newNode->RecAddr);
    thisNode=parentNode;
    }

    Store(thisNode);
    if (level>= 0) return l;// insert complete
    // else we just the root
    int newAddr = BTreeFile.Append(Root);
    // put previous root into file
    // insert 2 keys in new root node
    Root.Keys[0]=thisNode->LargestKey();
    Root.RecAddrs[0]=newAddr;
    Root.Keys[l]=newNode->LargestKey();
    Root.RecAddrs[l]=newNode->RecAddr;
    Root.NumKeys=2;
    Height++;
    return l;
}
/********************************************
B+Tree remove - unimplemented
********************************************/
template <class keyType>
int BTree<keyType>::Remove (const keyType key, canst int recAddr)
{ // left for exercise
    return -1;
}
/********************************************
B+Tree initalization
********************************************/
template <class keyType>
void BTree<keyType>::Print
    (ostream& stream, int nodeAddr, int level)
{
    BTNode* thisNode = Fetch(nodeAddr);
    stream<<"Node at level " << level << "address " << nodeAddr << ' ';
    thisNode->Print(stream);
    if(Height > level)
    {
        level++;
        for(int i = 0; i < thisNode->numKeys(); i++)
        {
            Print(stream, thisNode->RecAddrs[i], level);
        }
        stream << "End of level " << level << endl;
    }
}
/********************************************
Finds the B+tree leaf from given key
********************************************/
template <class keyType>
BTreeNode<keyType> * BTree<keyType>::FindLeaf(const keyType key)
//load a branch into memory down to the leaf with key
{
    int recAddr, level;
    for(level = 1, level < Height; level++)
    {
        recAddr = Nodes[level-1]->Search(key,-1,0);//inexact search
        Nodes[level] = Fetch(recAddr);
    }
    return Nodes[level-1];
}
/********************************************
Creates a new node for the B+tree
********************************************/
template <class keyType>
BTreeNode<keyType> * BTree<keyType>::NewNode()
{// create fresh node, insert into tree and set RecAddr member
    BTNode* newNode = new BTNode(order);
    int recAddr = BTreeFile.Append(*newNode);
    newNode-> RecAddr = recAddr;
    return newNode;
}
/********************************************
B+Tree Fetche the node from the file
********************************************/
template <class keyType>
BtreeNode<keyType> * BTree<keyType>::Fetch(const int recaddr)
{//load this node from File into a new BTreeNode
    int result;
    BTNode * newNode = new BTNode(Order);
    result = BTreeFile.Read(*newNode, recaddr);
    if(result == -1) return NULL;
    newNode-> RecAddr = result;
    return newNode;
}
/********************************************
Stores the B+tree to file
********************************************/
template <class keyType>
int BTree<keyType>::Store(BTreeNode<keyType> * thisNode)
{
    return BTreeFile.Write(*thisNode, thisNode->RecAddr);
}
