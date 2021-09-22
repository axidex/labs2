//красно-черное (сблансированное) дерево map, есть интерфейс доступа к
//значению по ключу using namespace std;
#include <map>
#include <iostream>

bool tirazhmorethan4(int x) 
{
    if (x>4) return true;
    return false;
}

template<class T, class M>
std::map<T,M> filtr(std::map<T,M> &mp, bool(*func)(int x))
{
    std::map<T,M> newmap;
    for (auto element : mp)
    {
        if(func(element.second)) {newmap[element.first] = element.second;}
    }
    return newmap;
}

int main()
{
    std::map<std::string, int> marks;
    marks["Book1"] = 5;
    marks["Book2"] = 4;
    marks["Book3"] = 5;
    marks["Book4"] = 3;
    marks["Book5"] = 4;
    marks["Book6"] = 5;
    marks["Book7"] = 6;
    std::map<std::string, int> markssorted = filtr<std::string, int>(marks,tirazhmorethan4);
    std::cout << "\nMap:\n";
    //итератор пробегает по map
    std::map<std::string, int>::iterator it_m = markssorted.begin();
    while (it_m != markssorted.end())
    {
        //перемещение по списку с помощью итератора, нет операции [i]
        std::cout << "Key: " << it_m->first << ", value: " << it_m->second << "\n";
        it_m++;
    }
}