#include <iostream>
#include <vector>
#include "gtest/gtest.h"

using namespace std;



template <typename T>
class BSTree;

template <typename T>
class Node;

template <typename T>
class Duo
{
public:
    bool succes;
    Node<T>* pointer;
};

template <typename T>
class Node
{
public:
    T value;
    Node<T>* rightPointer;
    Node<T>* leftPointer;
    int height;
public:
    Node(T value);
    ~Node();
    Node<T>* rotateRight(Node<T>* root);
    Node<T>* rotateLeft(Node<T>* root);
    Node<T>* correct(Node<T>* root);
    bool grow(T val, Node<T>* root);
    bool check(T val);
    Node<T>* locate(T val, Node<T>* rootL);
    bool shrink(T targetValue, Node<T>* root);
    vector<T> nextInOrder ();
    vector<T> nextPreOrder ();
    vector<T> nextPostOrder ();

friend BSTree<T>;
};

template <typename T>
Node<T>::Node(T value)
    :value{value}
{
    height = 0;
    rightPointer = nullptr;
    leftPointer = nullptr;
}

template <typename T>
Node<T>* Node<T>::rotateRight(Node<T>* target)
{
    Node<T>* firstNode = target;
    Node<T>* secondNode = firstNode->leftPointer;
    //rotates the stuff
    firstNode->leftPointer = secondNode->rightPointer ? secondNode->rightPointer : nullptr;
    secondNode->rightPointer = firstNode;

    firstNode->height = (firstNode->leftPointer ? firstNode->leftPointer->height : -1) > (firstNode->rightPointer ? firstNode->rightPointer->height : -1) ? (firstNode->leftPointer ? firstNode->leftPointer->height : -1) + 1 : (firstNode->rightPointer ? firstNode->rightPointer->height : -1) + 1;

    secondNode->height = (secondNode->leftPointer ? secondNode->leftPointer->height : -1) > (secondNode->rightPointer ? secondNode->rightPointer->height : -1) ? (secondNode->leftPointer ? secondNode->leftPointer->height : -1)+1 : (secondNode->rightPointer ? secondNode->rightPointer->height : -1)+1;

    return secondNode;
}

template <typename T>
Node<T>* Node<T>::rotateLeft(Node<T>* target)
{
    Node<T>* firstNode = target;
    Node<T>* secondNode = firstNode->rightPointer;
    //rotates the stuff
    firstNode->rightPointer = secondNode->leftPointer ? secondNode->leftPointer : nullptr;
    secondNode->leftPointer = firstNode;

    firstNode->height = (firstNode->leftPointer ? firstNode->leftPointer->height : -1) > (firstNode->rightPointer ? firstNode->rightPointer->height : -1) ? (firstNode->leftPointer ? firstNode->leftPointer->height : -1) + 1 : (firstNode->rightPointer ? firstNode->rightPointer->height : -1) + 1;

    secondNode->height = (secondNode->leftPointer ? secondNode->leftPointer->height : -1) > (secondNode->rightPointer ? secondNode->rightPointer->height : -1) ? (secondNode->leftPointer ? secondNode->leftPointer->height : -1)+1 : (secondNode->rightPointer ? secondNode->rightPointer->height : -1)+1;

    return secondNode;
}

template <typename T>
Node<T>* Node<T>::correct(Node<T>* root)
{
    Node<T>* returnRoot = root;
    int a = leftPointer ? leftPointer->height : - 1; //-1
    int b = rightPointer ? rightPointer->height : - 1; //height
    int bf = a-b;
    bool left = false;
    if (a - b > 1)
    {
        a = leftPointer->leftPointer ? leftPointer->leftPointer->height : - 1;
        b = leftPointer->rightPointer ? leftPointer->rightPointer->height : - 1;
        //first rotate
        if (a - b > 1)
        {
            leftPointer = leftPointer->rotateRight(leftPointer);
        } else
        {
            if (a - b < -1)
            {
                leftPointer = leftPointer->rotateLeft(root);
            }
        }
        //second rotation
        while (returnRoot->value != value)
        {
            if (value > returnRoot->value)
            {
                returnRoot = returnRoot->rightPointer;
            } else
            {
                returnRoot = returnRoot->leftPointer;
            }
        }

        return rotateRight(returnRoot);
    } else
    {
        if (a - b < -1)
        {
            a = rightPointer->leftPointer ? rightPointer->leftPointer->height : - 1;
            b = rightPointer->rightPointer ? rightPointer->rightPointer->height : - 1;
            //first rotate
            if (a - b > 1)
            {
                rightPointer->rotateRight(root);
            } else
            {
                if (a - b < -1)
                {
                    rightPointer->rotateLeft(root);
                }
            }
            //second rotation
            while (returnRoot->value != value)
            {
                if (value > returnRoot->value)
                {
                    returnRoot = returnRoot->rightPointer;
                } else
                {
                    returnRoot = returnRoot->leftPointer;
                }
            }

            return rotateLeft(root);
        }
    }

    return nullptr;
}

template <typename T>
bool Node<T>::grow(T val, Node<T>* root)
{
    if (val < value && leftPointer == nullptr)
    {
        leftPointer = new Node(val);
        //changes height
        if (rightPointer)
        {
            height = rightPointer->height > leftPointer->height ? rightPointer->height+1 : leftPointer->height+1;
        } else
        {
            height = leftPointer->height+1;
        }
        return true;
    }  else
    {
        if (val < value)
        {
            bool i = leftPointer->grow(val, root);
            //changes height
            if (i)
            {
                if (rightPointer)
                {
                    height = rightPointer->height > leftPointer->height ? rightPointer->height+1 : leftPointer->height+1;
                } else
                {
                    height = leftPointer->height+1;
                }
                Node<T>* s = leftPointer->correct(root);
                if (s)
                {
                    leftPointer = s;
                }
            }
            return i;
        }
    }
    if (val > value && rightPointer == nullptr)
    {
        rightPointer = new Node(val);
        //changes height
        if (leftPointer)
        {
            height = leftPointer->height > rightPointer->height ? leftPointer->height+1 : rightPointer->height+1;
        } else
        {
            height = rightPointer->height+1;
        }
        return true;
    } else
    {
        if (val > value)
        {
            bool i = rightPointer->grow(val, root);
            //changes height
            if (i)
            {
                if (leftPointer)
                {
                    height = leftPointer->height > rightPointer->height ? leftPointer->height+1 : rightPointer->height+1;
                } else
                {
                    height = rightPointer->height+1;
                }
                Node<T>* s = rightPointer->correct(root);
                if (s)
                {
                    rightPointer = s;
                }
            }
            return i;
        }
    }
    return false;
}

template <typename T>
bool Node<T>::check(T val)
{
    if (value == val)  {return true;}  else
    {
        return val > value ? (rightPointer == nullptr ? false : rightPointer->check(val))
                           : (leftPointer  == nullptr ? false : leftPointer->check(val));}
}

template <typename T>
Node<T>* Node<T>::locate(T val, Node<T>* rootL)
{
    if (val == value && rootL) {return rootL;}
    Node<T>* returnN = val > value ?
        (rightPointer == nullptr ? nullptr :
            rightPointer->value == val ? rightPointer : rightPointer->locate(val, nullptr)) :
        (leftPointer  == nullptr ? nullptr :
            leftPointer->value == val ? leftPointer : leftPointer->locate(val, nullptr));
    return returnN;
}

//template <typename T>
//bool Node<T>::shrink(T targetValue, Node<T>* root)
//{


//    return 0;
//}

template <typename T>
bool Node<T>::shrink(T targetValue, Node<T>* root)
{
    Node<T>* targetNode = nullptr;
    Node<T>* replacementLocation = nullptr;
    bool success = false;
    //left side
    if(targetValue <= value)
    {
        if (leftPointer)
        {
            if (leftPointer->value == targetValue)
            {
                targetNode = leftPointer;
                if(targetNode->leftPointer)
                {
                    //left pointer exists
                    //finds replacement location
                    replacementLocation = targetNode->leftPointer;
                    while (replacementLocation->rightPointer)
                    {
                        replacementLocation = replacementLocation->rightPointer;
                    }
                    //replaces the target nodes value
                    targetNode->value = replacementLocation->value;

                    success = targetNode->shrink(replacementLocation->value, root);
                    correct(root);
                    if (success)
                    {
                        if (leftPointer)
                        {
                            if (rightPointer)
                            {
                                height = leftPointer->height >= rightPointer->height ? leftPointer->height + 1 : rightPointer->height + 1;
                            } else
                            {
                                height = leftPointer->height + 1;
                            }
                        } else
                        {
                            if (rightPointer)
                            {
                                height = rightPointer->height;
                            } else
                            {
                                height = 0;
                            }
                        }
                    }
                    return success;
                } else
                {
                    //at most one right pointer
                    leftPointer = targetNode->rightPointer;
                    targetNode->rightPointer = nullptr;
                    delete targetNode;
                    height = rightPointer->height + 1;
                    return true;
                }
            } else
            {
                success = leftPointer->shrink(targetValue, root);
            }
        }
    } else //right side
    {
        if (rightPointer)
        {
            if (rightPointer->value == targetValue)
            {
                cout << "found: " << targetValue << endl;
                targetNode = rightPointer;
                if(targetNode->leftPointer)
                {
                    cout << "left pointer exist" << endl;
                    //left pointer exists
                    //finds replacement location

                    replacementLocation = targetNode->leftPointer;
                    while (replacementLocation->rightPointer)
                    {
                        replacementLocation = replacementLocation->rightPointer;
                    }
                    //replaces the target nodes value
                    targetNode->value = replacementLocation->value;
                    cout << "replaced with: " << rightPointer->value << endl;

                    success = targetNode->shrink(replacementLocation->value, root);
                    correct(root);
                    if (success)
                    {
                        if (leftPointer)
                        {
                            if (rightPointer)
                            {
                                height = leftPointer->height >= rightPointer->height ? leftPointer->height + 1 : rightPointer->height + 1;
                            } else
                            {
                                height = leftPointer->height + 1;
                            }
                        } else
                        {
                            if (rightPointer)
                            {
                                height = rightPointer->height;
                            } else
                            {
                                height = 0;
                            }
                        }
                    }
                    return success;
                } else
                {
                    //at most one right pointer
                    rightPointer = targetNode->rightPointer;
                    cout << "replaced with 2: " << rightPointer->value << endl;
                    targetNode->rightPointer = nullptr;
                    delete targetNode;
                    height = rightPointer->height + 1;
                    return true;
                }
            } else
            {
                success = rightPointer->shrink(targetValue, root);
                if (success)
                {
                    if (leftPointer)
                    {
                        if (rightPointer)
                        {
                            height = leftPointer->height >= rightPointer->height ? leftPointer->height + 1 : rightPointer->height + 1;
                        } else
                        {
                            height = leftPointer->height + 1;
                        }
                    } else
                    {
                        if (rightPointer)
                        {
                            height = rightPointer->height;
                        } else
                        {
                            height = 0;
                        }
                    }
                }
                return success;
            }
        }
    }

    return false;
}


//template <typename T>
//void Node<T>::shrink(Node<T>* self, Node<T>* root)
//{
//    Node<T>* upperBranch = root;
//    Node<T>* targetNode = self;
//    Node<T>* replacementLocation = nullptr;
//    //finds where upper branch is
//    while (((upperBranch->leftPointer && upperBranch->leftPointer != targetNode) || (!upperBranch->leftPointer)) && ((upperBranch->rightPointer && upperBranch->rightPointer != targetNode) || (!upperBranch->rightPointer)))
//    {
//        if (value > upperBranch->value)
//        {
//            upperBranch = upperBranch->rightPointer;
//        } else
//        {
//            upperBranch = upperBranch->leftPointer;
//        }
//    }
//    //there is 2 pointers
//    if (leftPointer)
//    {
//        //finds replacement location
//        replacementLocation = targetNode->leftPointer;
//        while (replacementLocation->rightPointer)
//        {
//            replacementLocation = replacementLocation->rightPointer;
//        }
//        //replaces the target nodes value
//        targetNode->value = replacementLocation->value;

//        replacementLocation->shrink(replacementLocation,upperBranch);
//    //there is at most 1 (right) pointer
//    } else
//    {

//            if (value > upperBranch->value)
//            {
//                upperBranch->rightPointer = targetNode->rightPointer;
//            } else
//            {
//                upperBranch->leftPointer = targetNode->rightPointer;
//            }
//            targetNode->rightPointer = nullptr;
//            delete targetNode;
//    }
//}

template <typename T>
vector<T> Node<T>::nextInOrder ()
{
    vector<T> localReturn = {};
    if (leftPointer)
    {
        vector<T> smallerReturn = leftPointer ? leftPointer->nextInOrder() : vector<T> {};
        for (int o = 0; o < smallerReturn.size(); o++)
        {
            localReturn.push_back(smallerReturn[o]);
        }
    }
    localReturn.push_back(value);
    if (rightPointer)
    {
        vector<T> smallerReturn = rightPointer ? rightPointer->nextInOrder() : vector<T> {};
        for (int o = 0; o < smallerReturn.size(); o++)
        {
            localReturn.push_back(smallerReturn[o]);
        }
    }
    return localReturn;
}

template <typename T>
vector<T> Node<T>::nextPreOrder ()
{
    vector<T> localReturn = {};
    localReturn.push_back(value);
    if (leftPointer)
    {
        vector<T> smallerReturn = leftPointer ? leftPointer->nextPreOrder() : vector<T> {};
        for (int o = 0; o < smallerReturn.size(); o++)
        {
            localReturn.push_back(smallerReturn[o]);
        }
    }
    if (rightPointer)
    {
        vector<T> smallerReturn = rightPointer ? rightPointer->nextPreOrder() : vector<T> {};
        for (int o = 0; o < smallerReturn.size(); o++)
        {
            localReturn.push_back(smallerReturn[o]);
        }
    }
    return localReturn;
}

template <typename T>
vector<T> Node<T>::nextPostOrder ()
{
    vector<T> localReturn = {};
    if (leftPointer)
    {
        vector<T> smallerReturn = leftPointer ? leftPointer->nextPostOrder() : vector<T> {};
        for (int o = 0; o < smallerReturn.size(); o++)
        {
            localReturn.push_back(smallerReturn[o]);
        }
    }
    if (rightPointer)
    {
        vector<T> smallerReturn = rightPointer ? rightPointer->nextPostOrder() : vector<T> {};
        for (int o = 0; o < smallerReturn.size(); o++)
        {
            localReturn.push_back(smallerReturn[o]);
        }
    }
    localReturn.push_back(value);
    return localReturn;
}

template <typename T>
Node<T>::~Node()
{
    if (rightPointer) {delete rightPointer;}
    if (leftPointer) {delete leftPointer;}
}

template <typename T>
class BSTree
{
public:
    Node<T>* rootPointer;
    int numberOfNodes;

public:
    BSTree();
    ~BSTree();
    void insert(T val);       // add an element to the tree
    void remove(T val);       // remove an element from the tree
    bool includes(T val);     // return true if the given value is in the tree
    vector<T> inOrder();      // no tests for these yet
    vector<T> preOrder();     // no tests for these yet
    vector<T> postOrder();    // no tests for these yet
    int size();               // number of elements in the tree
    bool isEmpty();           // is the tree empty

friend Node<T>;
};

template <typename T>
BSTree<T>::BSTree()
{
    rootPointer = nullptr;
    numberOfNodes = 0;
}

template <typename T>
void BSTree<T>::insert (T val)
{
    if (!rootPointer)
    {
        rootPointer = new Node(val);
        numberOfNodes += 1;
    } else
    {
        numberOfNodes += (rootPointer->grow(val, rootPointer) ? 1 : 0);
    }
}

template <typename T>
void BSTree<T>::remove (T val)
{
    if (rootPointer)
    {
        if (rootPointer->value == val)
        {
            if (!rootPointer->leftPointer && !rootPointer->rightPointer)
            {
                delete rootPointer;
                rootPointer = nullptr;

            } else
            {
                if (rootPointer->leftPointer)
                {
                    //finds replacement location
                    Node<T>* replacementLocation = rootPointer->leftPointer;
                    while (replacementLocation->rightPointer)
                    {
                        replacementLocation = replacementLocation->rightPointer;
                    }
                    //replaces the target nodes value
                    rootPointer->value = replacementLocation->value;

                    rootPointer->shrink(replacementLocation->value, rootPointer);
                //there is at most 1 (right) pointer
                } else
                {
                    Node<T>* rootDelete = rootPointer;
                    rootPointer = rootPointer->rightPointer;
                    rootDelete->rightPointer = nullptr;
                    delete rootDelete;
                }

            }
            numberOfNodes -= 1;
        } else
        {
            cout << "shrinking: " << val << endl;
            rootPointer->shrink(val, rootPointer);
            numberOfNodes -= 1;
        }
    }
}

template <typename T>
bool BSTree<T>::includes (T val)
{
    if (rootPointer) {return  rootPointer->check(val);} else {return false;}
}

template <typename T>
vector<T> BSTree<T>::inOrder ()
{
    vector<T> returnVec = {};
    if (rootPointer)
    {
        returnVec = rootPointer->nextInOrder();
    }
    return returnVec;

}

template <typename T>
vector<T> BSTree<T>::preOrder ()
{
    vector<T> returnVec = {};
    if (rootPointer)
    {
        returnVec = rootPointer->nextPreOrder();
    }
    return returnVec;
}

template <typename T>
vector<T> BSTree<T>::postOrder ()
{
    vector<T> returnVec = {};
    if (rootPointer)
    {
        returnVec = rootPointer->nextPostOrder();
    }
    return returnVec;
}

template <typename T>
int BSTree<T>::size()
{
    return numberOfNodes;
}

template <typename T>
bool BSTree<T>::isEmpty()
{
    return rootPointer == nullptr ? true : false;
}

template <typename T>
BSTree<T>::~BSTree()
{
        delete rootPointer;
}

// tests
//JR's

//includes
TEST(JR_BSTree_Tests, FullTreeIsInIncludesWorks)
{
    BSTree<int> s;
    s.insert(5);
    s.insert(3);
    s.insert(4);
    s.insert(2);
    ASSERT_TRUE(s.includes(2));
}

//TEST(JR_BSTree_Tests, FullTreeIsOutIncludesWorks)
//{
//    BSTree<int> s;
//    s.insert(5);
//    s.insert(3);
//    s.insert(4);
//    s.insert(2);
//    ASSERT_TRUE(!s.includes(9));
//}

//TEST(JR_BSTree_Tests, FullTreeIsOutInsertAndRemoveIncludesWorks)
//{
//    BSTree<int> s;
//    s.insert(5);
//    s.insert(3);
//    s.insert(4);
//    s.insert(2);
//    s.remove(2);
//    s.remove(4);
//    s.insert(6);
//    ASSERT_TRUE(!s.includes(2));

//}

//TEST(JR_BSTree_Tests, FullTreeIsInInsertAndRemoveIncludesWorks)
//{
//    BSTree<int> s;
//    s.insert(5);
//    s.insert(3);
//    s.insert(4);
//    s.insert(2);
//    s.remove(2);
//    s.remove(4);
//    s.insert(2);
//    ASSERT_TRUE(s.includes(2));
//}

//TEST(JR_BSTree_Tests, EmptyTreeIncludesWorks)
//{
//    BSTree<int> s;
//    ASSERT_TRUE(!s.includes(2));
//}

////size
//TEST(JR_BSTree_Tests, FullTreeSizeWorks)
//{
//    BSTree<int> s;
//    s.insert(5);
//    s.insert(3);
//    s.insert(4);
//    s.insert(2);
//    ASSERT_EQ(s.size(), 4);
//}

//TEST(JR_BSTree_Tests, EmptyTreeSizeWorks)
//{
//    BSTree<int> s;
//    ASSERT_EQ(s.size(),0);
//}

////isEmpty
//TEST(JR_BSTree_Tests, FullTreeIsEmptyWorks)
//{
//    BSTree<int> s;
//    s.insert(5);
//    s.insert(3);
//    s.insert(4);
//    s.insert(2);
//    ASSERT_TRUE(!s.isEmpty());
//}

//TEST(JR_BSTree_Tests, EmptyTreeIsEmptyWorks)
//{
//    BSTree<int> s;
//    ASSERT_TRUE(s.isEmpty());
//}

////insert and remove
//TEST(JR_BSTree_Tests, FullTreeFiftyInsertWorks)
//{
//    BSTree<int> s;
//    for (int i = 0; i < 50; i++)
//    {
//        s.insert(i);
//    }
//    ASSERT_EQ(s.size(),50);
//}

//TEST(JR_BSTree_Tests, FullTreeFiftyRemoveWorks) //fails
//{
//    BSTree<int> s;
//    for (int i = 0; i < 50; i++)
//    {
//        s.insert(i);
//    }

//    for (int i = 0; i < 50; i++)
//    {
//        s.remove(i);
//    }
//    ASSERT_EQ(s.size(), 0);
//}

TEST(JR_BSTree_Tests, FullTreeCatapillarInsertAndRemoveWorks)
{
    BSTree<int> s;
    for (int i = 17; i < 50; i++)
    {
        s.insert(i+1);
        if (i >= 19)
        {
            cout << "m" << endl;
            s.remove(i);
            s.remove(i-1);
            s.insert(i);
        }
    }
    vector<int> t = {49,50};
//    s.insert(2);
//    s.insert(8);
//    s.insert(3);
//    s.insert(5);
//    s.insert(4);
//    s.remove(8);
//    vector<int> t = {2, 3, 4, 5};

    ASSERT_EQ(s.inOrder(), t);
}

//TEST(JR_BSTree_Tests, FullTreeAllInInsertWorks)
//{
//    BSTree<int> s;
//    s.insert(5);
//    s.insert(3);
//    s.insert(4);
//    s.insert(1);
//    s.insert(9);
//    s.insert(6);
//    s.insert(2);
//    s.insert(7);
//    s.insert(8);
//    ASSERT_TRUE(s.includes(1) && s.includes(2) && s.includes(3) && s.includes(4) && s.includes(5) && s.includes(6) && s.includes(7) && s.includes(8) && s.includes(9));
//}

//TEST(JR_BSTree_Tests, FullTreeDoubleInsertWorks)
//{
//    BSTree<int> s;
//    s.insert(5);
//    s.insert(3);
//    s.insert(4);
//    s.insert(1);
//    s.insert(2);
//    int yes = s.size();
//    s.insert(5);
//    ASSERT_EQ(s.size(), yes);
//}

//TEST(JR_BSTree_Tests, InOrderWorks)
//{
//    BSTree<int> s;
//    s.insert(5);
//    s.insert(3);
//    s.insert(4);
//    s.insert(2);
//    s.insert(7);
//    s.insert(8);
//    s.insert(6);

//    vector<int> t {2,3,4,5,6,7,8};
//    ASSERT_EQ(s.inOrder(), t);
//}

//TEST(JR_BSTree_Tests, PreOrderWorks)
//{
//    BSTree<int> s;
//    s.insert(5);
//    s.insert(3);
//    s.insert(4);
//    s.insert(2);
//    s.insert(7);
//    s.insert(8);
//    s.insert(6);

//    vector<int> t {5,3,2,4,7,6,8};
//    ASSERT_EQ(s.preOrder(), t);
//}

//TEST(JR_BSTree_Tests, PostOrderWorks)
//{
//    BSTree<int> s;
//    s.insert(5);
//    s.insert(3);
//    s.insert(4);
//    s.insert(2);
//    s.insert(7);
//    s.insert(8);
//    s.insert(6);

//    vector<int> t {2,4,3,6,8,7,5};
//    ASSERT_EQ(s.postOrder(), t);
//}

TEST(JR_BSTree_Tests, PostOrderWorks)
{
    BSTree<int> s;
    s.insert(1);
    s.insert(5);
    s.insert(3);
    s.insert(7);
    s.insert(8);
    s.insert(6);

    ASSERT_EQ(s.rootPointer->height, 3);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int res = RUN_ALL_TESTS();

    return res;
}


