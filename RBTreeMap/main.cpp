using namespace std;

#include <iostream>
#include "RBTree.h"
#include <string>


void Test()
{
    Map<string, double> map;

    for (size_t i = 1; i <= 29; i++)
    {
        map.Insert(to_string(i), i * 5712);
    }
    map.Print();

    cout << "\nnow removing...\n";

    for (size_t i = 1; i < 8; i++)
    {
        map.Remove(to_string(i));
        map.Print();
    }

    map.Clear();

    for (size_t i = 1; i <= 29; i++)
    {
        map.Insert(to_string(i), i * 5712);
    }
    map.Print();

    cout << "\nnow removing...\n";

    for (size_t i = 1; i < 15; i++)
    {
        map.Remove(to_string(i));
        map.Print();
    }
}

void FailingTest()
{
    Map<int, string> map;
    map.Insert(5, "first");
    map.Insert(3, "second");
    map.Insert(7, "third");
    map.Insert(9, "fourth");
    map.Insert(15, "fifth");

    auto keys = map.GetKeys();
    auto values = map.GetValues();

    for (size_t i = 0; i < keys.GetSize(); i++)
    {
        if (map.Find(keys[i]) != values[i])
        {
           
        }
    }

}

int main()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(out, 0x0 | 0x70);
    system("CLS");
    SetConsoleOutputCP(1251);

    FailingTest();

    //TODO: fix rb tree balancing...
    for (int i = 0; i < 20; i++)
    {
        //Test();
        
    }

}


