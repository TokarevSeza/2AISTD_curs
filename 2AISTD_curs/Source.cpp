#include <iostream>
#include"Karp.h"

int main()
{
    Karp* t = new Karp();
    t->readList("d:\\input.txt");
    cout << "Максимальный поток: " << t->MaxFlow();
}