#include <iostream>
#include "gtest/gtest.h"

using namespace std;

template <typename T>
class Deque
{
private:
    T* values;
    int backIndex;
    int frontIndex;
    int dequeSize;
    int filledSlots;

public:
    Deque();
    void pushBack (T val = T{});
    void pushFront (T val = T{});
    T popBack ();
    T popFront ();
    T back ();
    T front ();
    int size ();
    bool isEmpty ();
    ~Deque();

};

template <typename T>
Deque<T>::Deque()
{
    dequeSize = 1;
    values = new T [dequeSize];
    values[0] = T{};
    backIndex = -1;
    frontIndex = -1;
    filledSlots = 0;
}

template <typename T>
void Deque<T>::pushBack (T val)
{
    //cout << "Pushed this to the back: " << val << endl;
    if (backIndex == -1) { backIndex = 0;} else {backIndex -=1;}
    if (backIndex < 0 || backIndex == frontIndex)
    {
        if (frontIndex == dequeSize-1)
        {
            T* tempValues = new T [dequeSize*2];
            for (int i = 0; i < dequeSize; i++)
            {
                tempValues[i] = values[i];
            }
            tempValues[(dequeSize*2)-1] = val;
            for (int i = (dequeSize*2)-2; i >= dequeSize; i--)
            {
                tempValues[i] = T{};
            }
            delete[] values;
            values = tempValues;
            dequeSize = dequeSize *2;
            backIndex = dequeSize-1;
        } else
        {
            if (backIndex == frontIndex)
            {
                T* tempValues = new T [dequeSize*2];
                for (int i = 0; i <= frontIndex; i++)
                {
                    tempValues[i] = values[i];
                }
                for (int i = (dequeSize*2)-1; i > (dequeSize*2) - dequeSize + backIndex - 1; i--)
                {
                    tempValues[i] = values[i-dequeSize];
                }
                for (int i = frontIndex + 1; i <= (dequeSize*2) - dequeSize + backIndex - 1; i++)
                {
                    tempValues[i] = T{};
                }
                tempValues[(dequeSize*2)-dequeSize+backIndex] = val;
                delete[] values;
                values = tempValues;
                backIndex = (dequeSize*2)-dequeSize+backIndex;
                dequeSize = dequeSize *2;
            } else
            {
                backIndex = dequeSize-1;
                values[backIndex] = val;
            }
        }
    } else
    {
        values[backIndex] = val;
    }
    if (frontIndex == -1) { frontIndex = 0;}
    filledSlots += 1;
//    for (int s = 0; s < dequeSize; s++)
//    {
//        cout << values[s] << endl;
//    }
}

template <typename T>
void Deque<T>::pushFront (T val)
{
    //cout << "Pushed this to the front: " << val << endl;
    if (frontIndex == -1) { frontIndex = 0;} else {frontIndex +=1;}
    if (frontIndex == dequeSize || frontIndex == backIndex)
    {
        if (backIndex == 0)
        {
            T* tempValues = new T [dequeSize*2];
            for (int i = 0; i < dequeSize; i++)
            {
                tempValues[i] = values[i];
            }
            tempValues[dequeSize] = val;
            for (int i = (dequeSize*2)-1; i > dequeSize; i--)
            {
                tempValues[i] = T{};
            }
            delete[] values;
            values = tempValues;
            dequeSize = dequeSize *2;
        } else
        {
            if (backIndex == frontIndex)
            {
                T* tempValues = new T [dequeSize*2];
                for (int i = 0; i < frontIndex; i++)
                {
                    tempValues[i] = values[i];
                }
                for (int i = (dequeSize*2)-1; i > (dequeSize*2)-dequeSize+backIndex - 1; i--)
                {
                    tempValues[i] = values[i];
                }
                for (int i = frontIndex + 1; i < (dequeSize*2)-dequeSize+backIndex - 1; i++)
                {
                    tempValues[i] = T{};
                }
                tempValues[frontIndex] = val;
                delete[] values;
                values = tempValues;
                dequeSize = dequeSize *2;
            } else
            {
                frontIndex = 0;
                values[frontIndex] = val;
            }
        }
    } else
    {
        values[frontIndex] = val;
    }
    if (backIndex == -1) { backIndex = 0;}

    filledSlots += 1;
//    for (int s = 0; s < dequeSize; s++)
//    {
//        cout << values[s] << endl;
//    }
}

template <typename T>
T Deque<T>::popBack ()
{
    if (filledSlots == 0)
    {
        return T{};
    }
    T returnVal = values[backIndex];
    values[backIndex] = T{};
    if (backIndex == dequeSize-1)
    {
        backIndex = -1;
    }
    backIndex += 1;
    filledSlots -= 1;
    //cout << "popped this: " << returnVal << endl;
    return returnVal;
}

template <typename T>
T Deque<T>::popFront ()
{
    if (filledSlots == 0)
    {
        return T{};
    }
    T returnVal = values[frontIndex];
    values[frontIndex] = T{};
    if (frontIndex == 0)
    {
        frontIndex = dequeSize;
    }
    frontIndex -= 1;
    filledSlots -= 1;
    //cout << "popped this: " << returnVal << endl;
    return returnVal;
}

template <typename T>
T Deque<T>::back ()
{
    if (backIndex == -1)
    {
        return T{};
    }
    return values[backIndex];
}

template <typename T>
T Deque<T>::front ()
{
    if (frontIndex == -1)
    {
        return T{};
    }
    return values[frontIndex];
}

template <typename T>
int Deque<T>::size()
{
    return filledSlots;
}

template <typename T>
bool Deque<T>::isEmpty()
{
    return filledSlots == 0 ? true : false;
}

template <typename T>
Deque<T>::~Deque()
{
    delete[] values;
}

//// tests
////JR's
////size tests
//TEST(JR_Deque_Tests, EmptyDeque_Size)
//{
//    Deque<int> s;
//    ASSERT_EQ(s.size(),0);
//}

//TEST(JR_Deque_Tests, FullDeque_PushFrontPopBackSize)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    s.pushFront(2);
//    s.pushFront(3);
//    s.pushFront(4);
//    s.popBack();
//    s.popBack();
//    ASSERT_EQ(s.size(),2);
//}

//TEST(JR_Deque_Tests, FullDeque_PushFrontPopFrontSize)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    s.pushFront(2);
//    s.pushFront(3);
//    s.pushFront(4);
//    s.popFront();
//    s.popFront();
//    ASSERT_EQ(s.size(),2);
//}

//TEST(JR_Deque_Tests, FullDeque_PushBackPopBackSize)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    s.pushBack(2);
//    s.pushBack(3);
//    s.pushBack(4);
//    s.popBack();
//    s.popBack();
//    ASSERT_EQ(s.size(),2);
//}

//TEST(JR_Deque_Tests, FullDeque_PushBackPopFrontSize)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    s.pushBack(2);
//    s.pushBack(3);
//    s.pushBack(4);
//    s.popFront();
//    s.popFront();
//    ASSERT_EQ(s.size(),2);
//}

////is empty tests
//TEST(JR_Deque_Tests, EmptyDeque_IsEmpty)
//{
//    Deque<int> s;
//    ASSERT_TRUE(s.isEmpty());
//}

//TEST(JR_Deque_Tests, FullDeque_PushFrontIsEmptyFails)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    ASSERT_TRUE(!s.isEmpty());
//}

//TEST(JR_Deque_Tests, FullDeque_PushBackIsEmptyFails)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    ASSERT_TRUE(!s.isEmpty());
//}

////back tests
//TEST(JR_Deque_Tests, EmptyDeque_BackIsDefalt)
//{
//    Deque<int> s;
//    ASSERT_EQ(s.back(),int{});
//}

//TEST(JR_Deque_Tests, FullDeque_PushFrontBackReturnsValue)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    ASSERT_EQ(s.back(),1);
//}

//TEST(JR_Deque_Tests, FullDeque_PushBackBackReturnsValue)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    ASSERT_EQ(s.back(),1);
//}

//TEST(JR_Deque_Tests, FullDeque_PushAndPopFrontBackReturnsValue)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    s.pushFront(2);
//    s.pushFront(3);
//    s.popFront();
//    s.popFront();
//    ASSERT_EQ(s.back(),1);
//}

//TEST(JR_Deque_Tests, FullDeque_PushAndPopBackBackReturnsValue)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    s.pushBack(2);
//    s.pushBack(3);
//    s.popBack();
//    s.popBack();
//    ASSERT_EQ(s.back(),1);
//}

//TEST(JR_Deque_Tests, FullDeque_PushFrontPopBackBackReturnsValue)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    s.pushFront(2);
//    s.pushFront(3);
//    s.popBack();
//    s.popBack();
//    ASSERT_EQ(s.back(),3);
//}

//TEST(JR_Deque_Tests, FullDeque_PushBackPopFrontBackReturnsValue)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    s.pushBack(2);
//    s.pushBack(3);
//    s.popFront();
//    s.popFront();
//    ASSERT_EQ(s.back(),3);
//}

////front tests
//TEST(JR_Deque_Tests, EmptyDeque_FrontIsDefalt)
//{
//    Deque<int> s;
//    ASSERT_EQ(s.front(),int{});
//}

//TEST(JR_Deque_Tests, FullDeque_PushFrontFrontReturnsValue)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    ASSERT_EQ(s.front(),1);
//}

//TEST(JR_Deque_Tests, FullDeque_PushBackFrontReturnsValue)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    ASSERT_EQ(s.front(),1);
//}

//TEST(JR_Deque_Tests, FullDeque_PushAndPopFrontFrontReturnsValue)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    s.pushFront(2);
//    s.pushFront(3);
//    s.popFront();
//    s.popFront();
//    ASSERT_EQ(s.front(),1);
//}

//TEST(JR_Deque_Tests, FullDeque_PushAndPopBackFrontReturnsValue)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    s.pushBack(2);
//    s.pushBack(3);
//    s.popBack();
//    s.popBack();
//    ASSERT_EQ(s.front(),1);
//}

//TEST(JR_Deque_Tests, FullDeque_PushFrontPopBackFrontReturnsValue)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    s.pushFront(2);
//    s.pushFront(3);
//    s.popBack();
//    s.popBack();
//    ASSERT_EQ(s.front(),3);
//}

//TEST(JR_Deque_Tests, FullDeque_PushBackPopFrontFrontReturnsValue)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    s.pushBack(2);
//    s.pushBack(3);
//    s.popFront();
//    s.popFront();
//    ASSERT_EQ(s.front(),3);
//}

////pop tests
//TEST(JR_Deque_Tests, FullDeque_PushFrontPopBackReturnsValue)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    s.pushFront(2);
//    s.pushFront(3);
//    s.pushFront(4);

//    ASSERT_EQ(s.popBack(),1);
//}

//TEST(JR_Deque_Tests, FullDeque_PushFrontPopFrontReturnsValue)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    s.pushFront(2);
//    s.pushFront(3);
//    s.pushFront(4);

//    ASSERT_EQ(s.popFront(),4);
//}

//TEST(JR_Deque_Tests, FullDeque_PushBackPopBackReturnsValue)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    s.pushBack(2);
//    s.pushBack(3);
//    s.pushBack(4);

//    ASSERT_EQ(s.popBack(),4);
//}

//TEST(JR_Deque_Tests, FullDeque_PushBackPopFrontReturnsValue)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    s.pushBack(2);
//    s.pushBack(3);
//    s.pushBack(4);

//    ASSERT_EQ(s.popFront(),1);
//}

//TEST(JR_Deque_Tests, EmptyDeque_PopBackIsDefalt)
//{
//    Deque<int> s;

//    ASSERT_EQ(s.popBack(),int{});
//}

//TEST(JR_Deque_Tests, EmptyDeque_PopFrontIsDefalt)
//{
//    Deque<int> s;

//    ASSERT_EQ(s.popFront(),int{});
//}

//TEST(JR_Deque_Tests, FullDeque_PushAndPopFrontPopFrontReturnsValue)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    s.pushFront(2);
//    s.pushFront(3);
//    s.pushFront(4);
//    s.popFront();
//    s.popFront();
//    ASSERT_EQ(s.popFront(),2);
//}

//TEST(JR_Deque_Tests, FullDeque_PushAndPopBackPopFrontReturnsValue)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    s.pushBack(2);
//    s.pushBack(3);
//    s.pushBack(4);
//    s.popBack();
//    s.popBack();
//    ASSERT_EQ(s.popFront(),1);
//}

//TEST(JR_Deque_Tests, FullDeque_PushFrontPopBackPopFrontReturnsValue)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    s.pushFront(2);
//    s.pushFront(3);
//    s.pushFront(4);
//    s.popBack();
//    s.popBack();
//    ASSERT_EQ(s.popFront(),4);
//}

//TEST(JR_Deque_Tests, FullDeque_PushBackPopFrontPopFrontReturnsValue)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    s.pushBack(2);
//    s.pushBack(3);
//    s.pushBack(4);
//    s.popFront();
//    s.popFront();
//    ASSERT_EQ(s.popFront(),3);
//}

//TEST(JR_Deque_Tests, FullDeque_PushAndPopFrontPopBackReturnsValue)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    s.pushFront(2);
//    s.pushFront(3);
//    s.pushFront(4);
//    s.popFront();
//    s.popFront();
//    ASSERT_EQ(s.popBack(),1);
//}

//TEST(JR_Deque_Tests, FullDeque_PushAndPopBackPopBackReturnsValue)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    s.pushBack(2);
//    s.pushBack(3);
//    s.pushBack(4);
//    s.popBack();
//    s.popBack();
//    ASSERT_EQ(s.popBack(),2);
//}

//TEST(JR_Deque_Tests, FullDeque_PushFrontPopBackPopBackReturnsValue)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    s.pushFront(2);
//    s.pushFront(3);
//    s.pushFront(4);
//    s.popBack();
//    s.popBack();
//    ASSERT_EQ(s.popBack(),3);
//}

//TEST(JR_Deque_Tests, FullDeque_PushBackPopFrontPopBackReturnsValue)
//{
//    Deque<int> s;
//    s.pushBack(1);
//    s.pushBack(2);
//    s.pushBack(3);
//    s.pushBack(4);
//    s.popFront();
//    s.popFront();
//    ASSERT_EQ(s.popBack(),4);
//}

////Charley’s Tests
//TEST(Charley_Deque_Tests, CharleyEmptyDequeIsEmpty) {
//  Deque<int> d;
//  ASSERT_TRUE(d.isEmpty());
//}

//TEST(Charley_Deque_Tests, CharleyFrontDequeIsNotEmpty) {
//  Deque<int> d;
//  d.pushFront(3);
//  ASSERT_FALSE(d.isEmpty());
//}

//TEST(Charley_Deque_Tests, CharleyBackDequeIsNotEmpty) {
//  Deque<int> d;
//  d.pushBack(3);
//  ASSERT_FALSE(d.isEmpty());
//}

//TEST(Charley_Deque_Tests, CharleyFrontDequeSize) {
//  Deque<int> d;
//  for(int i = 0; i < 3; i++) {
//      d.pushFront(3);
//   }
//  ASSERT_EQ(d.size(), 3);
//}

//TEST(Charley_Deque_Tests, CharleyBackDequeSize) {
//  Deque<int> d;
//  for(int i = 0; i < 3; i++) {
//     d.pushFront(4);
//  }
//  ASSERT_EQ(d.size(), 3);
//}

//TEST(Charley_Deque_Tests, CharleyDequePopFront) {
//  Deque<int> d;
//  for(int i = 0; i < 3; i++) {
//     d.pushFront(8);
//  }
//  ASSERT_EQ(d.popFront(), 8);
//}

//TEST(Charley_Deque_Tests, CharleyDequePopBack) {
//  Deque<int> d;
//  for(int i = 0; i < 3; i++) {
//     d.pushBack(5);
//  }
//  ASSERT_EQ(d.popBack(), 5);
//}

//TEST(Charley_Deque_Tests, CharleyDequePopMixed) {
//  Deque<int> d;
//  for(int i = 0; i < 3; i++) {
//     d.pushBack(9);
//  }
//  ASSERT_EQ(d.popFront(), 9);
//}

//TEST(Charley_Deque_Tests, CharleyDequeFront) {
//  Deque<int> d;
//  for(int i = 0; i < 3; i++) {
//     d.pushFront(8);
//  }
//  ASSERT_EQ(d.front(), 8);
//}

//TEST(Charley_Deque_Tests, CharleyDequeBack) {
//  Deque<int> d;
//  for(int i = 0; i < 3; i++) {
//     d.pushBack(5);
//  }
//  ASSERT_EQ(d.back(), 5);
//}

//TEST(Charley_Deque_Tests, CharleyDequeTopMixed) {
//  Deque<int> d;
//  for(int i = 0; i < 3; i++) {
//     d.pushBack(9);
//  }
//  ASSERT_EQ(d.front(), 9);
//}

//TEST(Charley_Deque_Tests, CharleyDequeWormFront) {
//  Deque<int> d;
//  d.pushFront(0);
//  for(int i = 0; i < 500; i++) {
//     d.pushFront(i);
//     d.popBack();
//  }
//  ASSERT_EQ(d.front(), 499);
//  ASSERT_EQ(d.size(), 1);
//}

//TEST(Charley_Deque_Tests, CharleyDequeWormBack) {
//  Deque<int> d;
//  d.pushBack(0);
//  for(int i = 0; i < 500; i++) {
//     d.pushBack(i);
//     d.popFront();
//  }
//  ASSERT_EQ(d.back(), 499);
//  ASSERT_EQ(d.size(), 1);
//}

//TEST(Charley_Deque_Tests, CharleyDequeWormMixed) {
//  Deque<int> d;
//  d.pushFront(0);
//  for(int i = 0; i < 300; i++) {
//     d.pushFront(i);
//     d.popBack();
//  }
//  for(int i = 0; i < 600; i++) {
//     d.pushBack(i);
//     d.popFront();
//  }
//  ASSERT_EQ(d.back(), 599);
//  ASSERT_EQ(d.size(), 1);
//}
//Doc Ham's tests
//TEST(Hamlin_Deque_Tests, PushWorks)
//{
//    Deque<int> s;
//    s.pushFront(1);
//    s.pushBack(2);
//    ASSERT_EQ(s.back(),2);
//    ASSERT_EQ(s.front(),1);
//    ASSERT_EQ(s.size(),2);
//}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int res = RUN_ALL_TESTS();

    return res;
}


