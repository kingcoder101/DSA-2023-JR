#include <iostream>
#include "gtest/gtest.h"

using namespace std;

template <typename T>
class Stack
{
private:
    T* values;
    int stackSize;
public:
    Stack();
    void push (T val = T{});
    T pop ();
    T top ();
    int size ();
    bool isEmpty ();
    ~Stack();

};

template <typename T>
Stack<T>::Stack()
{
    values = new T [0];
    stackSize = 0;
}

template <typename T>
void Stack<T>::push (T val)
{
    stackSize += 1;
    T* tempValues = new T [stackSize];
    for (int s = 0; s < stackSize - 1; s++)
    {
        tempValues[s] = values[s];
    }
    tempValues[stackSize - 1] = val;
    delete[] values;
    values = tempValues;
}

template <typename T>
T Stack<T>::pop ()
{
    stackSize -= 1;
    T popVal;
    T* tempValues = new T [stackSize];
    for (int s = 0; s < stackSize; s++)
    {
        tempValues[s] = values[s];
    }
    popVal = values[stackSize];
    delete[] values;
    values = tempValues;
    return popVal;
}

template <typename T>
T Stack<T>::top ()
{
    return stackSize <= 0 ? T{} : values[stackSize - 1];
}

template <typename T>
int Stack<T>::size()
{
    return stackSize;
}

template <typename T>
bool Stack<T>::isEmpty()
{
    return stackSize == 0 ?  true : false;
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] values;
}

// tests
// HENRY'S TESTS:

TEST(TestStack, EmptySizeIsZero) {
    Stack<int> s;
    ASSERT_TRUE(s.size()==0);
}

TEST(TestStack, EmptySizeIsZeroRedux) {
    Stack<int> s;
    ASSERT_EQ(s.size(),0);
}

TEST(TestStack, TopIsThree) {
    Stack<int> s;
    s.push(3);
    ASSERT_EQ(s.top(),3);
}

TEST(TestStack, ReEmptying) {
    Stack<int> s;
    s.push(3);
    s.pop();
    ASSERT_TRUE(s.isEmpty());
}

TEST(TestStack, EmptyStackIsEmpty) {
   Stack<int> s;
   ASSERT_TRUE(s.isEmpty());
}




// Charley’s Tests:
TEST(TestStack, CharleyEmptyStackIsEmpty) {
   Stack<int> s;
   ASSERT_TRUE(s.isEmpty());
}

TEST(TestStack, CharleyNonEmptyStackIsNotEmpty) {
   Stack<int> s;
   s.push(1);
   ASSERT_FALSE(s.isEmpty());
}

TEST(TestStack, CharleyStackPushAndPop) {
   Stack<int> s;
   s.push(1);
   ASSERT_EQ(s.pop(), 1);
}

TEST(TestStack, CharleyStackPushAndTop) {
   Stack<int> s;
   s.push(1);
   ASSERT_EQ(s.top(), 1);
}

TEST(TestStack, CharleyStackSize) {
   Stack<int> s;
   for(int i = 0; i < 12; i++) {
       s.push(i);
   }
   ASSERT_EQ(s.size(), 12);
}

TEST(TestStack, CharleyStackReSizeSize) {
   Stack<int> s;
   for(int i = 0; i < 120; i++) {
       s.push(i);
   }
   ASSERT_EQ(s.size(), 120);
}

TEST(TestStack, CharleyStackReSizePop) {
   Stack<int> s;
   for(int i = 0; i < 120; i++) {
       s.push(i);
   }
   for(int i = 0; i < 120; i++) {
       ASSERT_EQ(s.pop(), 119 - i);
   }
}

TEST(TestStack, CharleyStackReSizeTop) {
   Stack<int> s;
   for(int i = 0; i < 120; i++) {
       s.push(i);
   }
   for(int i = 0; i < 120; i++) {
       ASSERT_EQ(s.top(), 119 - i);
       s.pop();
   }
}
//JR's Tests
TEST(JR_Stack_Tests, EmptyStack_IsEmpty)
{
    Stack<int> s;
    ASSERT_TRUE(s.isEmpty());
}

TEST(JR_Stack_Tests, EmptyStack_TopIsDefalt)
{
    Stack<int> s;
    ASSERT_EQ(s.top(),int{});
}

TEST(JR_Stack_Tests, StackHandlesThousand)
{
    Stack<int> s;
    for (int i = 0; i < 999; i++)
    {
        s.push();
    }
    s.push(5);
    ASSERT_EQ(s.top(),5);
}

TEST(JR_Stack_Tests, StackHandlesMillion)
{
    Stack<int> s;
    for (int i = 0; i < 999999; i++)
    {
        s.push();
    }
    s.push(5);
    ASSERT_EQ(s.top(),5);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int res = RUN_ALL_TESTS();

    return res;
}
