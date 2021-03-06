//красно-черное (сблансированное) дерево map, есть интерфейс доступа к
//значению по ключу using namespace std;
#include <map>
#include <iostream>

struct Book
{
    int tirazh;
    Book() { tirazh = rand() % 10000 + 20000; }
    bool operator>(int b) { return this->tirazh > b; }
    friend std::ostream& operator<<(std::ostream& s, Book el)
    {
        s << el.tirazh << std::endl;
        return s;
    }
};

bool tirazhmorethan4(Book x)
{
    if (x > 4) return true;
    return false;
}

template<class T, class M>
std::map<T, M> filtr(std::map<T, M>& mp, bool(*func)(M x))
{
    std::map<T, M> newmap;
    for (auto element : mp)
    {
        if (func(element.second)) { newmap[element.first] = element.second; }
    }
    return newmap;
}

template<class T, class M>
std::pair<T, M> SearchByKey(const std::map<T, M>& mp, T Key)
{
    auto search = mp.find(Key);
    
    return search ? std::pair<T, M>(search->first, search->second) : nullptr;
}
template<class T, class M>
std::pair<T, M> SearchByValue(const std::map<T, M>& mp, M Value)
{
    auto it_m = mp.begin();
    while (it_m != mp.end())
    {
        if (it_m->second == Value)
            return std::pair<T, M>(it_m->first, it_m->second);
        it_m++;
    }
}

int main()
{
    std::map<std::string, Book> marks;
    Book a, b, c, d, e, f, g;
    marks["Book1"] = a;
    marks["Book2"] = b;
    marks["Book3"] = c;
    marks["Book4"] = d;
    marks["Book5"] = e;
    marks["Book6"] = f;
    marks["Book7"] = g;
    std::map<std::string, Book> markssorted = filtr<std::string, Book>(marks, tirazhmorethan4);
    std::cout << "\nMap:\n";
    std::pair<std::string, Book> qwe = SearchByKey<std::string, Book>(marks, "Book1");
    std::cout << std::endl << qwe.first << '\t' << qwe.second << std::endl;
    //итератор пробегает по map
    std::map<std::string, Book>::iterator it_m = markssorted.begin();
    while (it_m != markssorted.end())
    {
        //перемещение по списку с помощью итератора, нет операции [i]
        std::cout << "Key: " << it_m->first << ", value: " << it_m->second << "\n";
        it_m++;
    }
}