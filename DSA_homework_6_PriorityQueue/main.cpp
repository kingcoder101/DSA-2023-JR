#include <iostream>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

int leftChild(int self)
{
    return (self + 1) * 2 - 1;
}

int rightChild(int self)
{
    return (self + 1) * 2;
}

template <typename T>
class PriorityQueue
{
private:
    int numberOfNodes;
    int arraySize;
    T* values;
public:
    PriorityQueue();
    ~PriorityQueue();
    void insert(T val);       // add an element to the tree
    T remove();               // remove an element from the tree
    bool includes(T val);     // return true if the given value is in the tree
    int size();               // number of elements in the tree
    bool isEmpty();           // is the tree empty
};

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
    numberOfNodes = 0;
    arraySize = 8;
    values = new T[arraySize];
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
    delete[] values;
}

template <typename T>
void PriorityQueue<T>::insert(T val)
{
    int localPos = numberOfNodes;
    //doubles the array size if all the space is used up
    if (arraySize == numberOfNodes)
    {
        T* replacementArray = new T[arraySize*2];
        for (int o = 0; o < arraySize; o++)
        {
            replacementArray[o] = values[o];
        }
        arraySize = arraySize*2;
        values = replacementArray;
    }

    //inserts the value
    //if ()
    values[numberOfNodes] = val;

    //shuffles stuff around
    while (localPos != 0 && values[(localPos-1)/2] < val)
    {
        values[localPos] = values[(localPos-1)/2];
        values[(localPos-1)/2] = val;
        localPos = (localPos-1)/2;
    }

    //increase the size
    numberOfNodes += 1;
}

template <typename T>
T PriorityQueue<T>::remove()
{
    //holds the value for return
    T returnVal = values[0];

    //remove the value
    values[0] = values[numberOfNodes-1];
    int localPos = 0;
    //decrease the size
    numberOfNodes -= 1;

    //(self + 1) * 2, and -1
    //shuffles stuff around
    T m = leftChild(localPos) < arraySize ? values[leftChild(localPos)] : 0;
    T n = rightChild(localPos) < arraySize ? values[rightChild(localPos)] : 0;

    while ((values[localPos] < m && leftChild(localPos) < arraySize) || (values[localPos] < n && rightChild(localPos) < arraySize))
    {
        T hold = values[localPos];
        values[localPos] = m >= n ? m : n;
        if (m >= n)
        {
            values[leftChild(localPos)] = hold;
            localPos = leftChild(localPos);
        } else
        {
            values[rightChild(localPos)] = hold;
            localPos = rightChild(localPos);
        }
        m = leftChild(localPos) < arraySize ? values[leftChild(localPos)] : 0;
        n = rightChild(localPos) < arraySize ? values[rightChild(localPos)] : 0;
    }

    return returnVal;
}

template <typename T>
int PriorityQueue<T>::size()
{
    return numberOfNodes;
}

template <typename T>
bool PriorityQueue<T>::isEmpty()
{
    return numberOfNodes == 0 ? true : false;
}

//tests
//JR's
TEST(JR_PriorityQueue_Tests, IncludesWorksOne)
{
    PriorityQueue<int> s;
    s.insert(5);
    ASSERT_EQ(s.remove(),5);
}

TEST(JR_PriorityQueue_Tests, IncludesWorksThree)
{
    PriorityQueue<int> s;
    s.insert(5);
    s.insert(4);
    s.insert(3);
    ASSERT_EQ(s.remove(),5);
}

TEST(JR_PriorityQueue_Tests, IncludesWorksCaterpillar)
{
    PriorityQueue<int> s;
    for (int i = 0; i < 10; i++)
    {
        s.insert(i);
        s.insert(i-1);
        s.remove();
    }
    ASSERT_EQ(s.remove(),8);
}

TEST(JR_PriorityQueue_Tests, IsEmptyTrue)
{
    PriorityQueue<int> s;
    s.insert(5);
    s.insert(4);
    s.insert(3);
    ASSERT_EQ(s.isEmpty(),false);
}

TEST(JR_PriorityQueue_Tests, IsEmptyFalse)
{
    PriorityQueue<int> s;
    ASSERT_EQ(s.isEmpty(),true);
}

TEST(JR_PriorityQueue_Tests, SizeWorksFull)
{
    PriorityQueue<int> s;
    s.insert(5);
    s.insert(4);
    s.insert(3);
    ASSERT_EQ(s.size(),3);
}

TEST(JR_PriorityQueue_Tests, SizeWorksEmpty)
{
    PriorityQueue<int> s;
    ASSERT_EQ(s.size(),0);
}

TEST(JR_PriorityQueue_Tests, SizeWorksCaterpillar)
{
    PriorityQueue<int> s;
    for (int i = 0; i < 10; i++)
    {
        s.insert(i);
        s.insert(i-1);
        s.remove();
    }
    ASSERT_EQ(s.size(),10);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int res = RUN_ALL_TESTS();

    return res;
}
