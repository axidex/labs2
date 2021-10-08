#include <list>
#include <iostream>
#include <vector>
/*Вариант 7 КТСО-03-20*/
// тип - char, только гласные 

template <class T>
void insert(std::list<char> &lst, T element)
{
    std::list<char>::iterator p = lst.begin();
    while (p != lst.end())
    {
        if (*p > element)
            break;
        p++;

    }
    lst.insert(p, element);
}

template<class T>
void push(std::list<T> &lst,char element)
{
    std::list<char>::iterator p = lst.begin();
    while (p != lst.end() && element > *p) p++;
    lst.insert(p,element);
}

template<class T>
T pop(std::list<T> &lst)
{
    T tmp = *(--lst.end());
    lst.pop_back();
    return tmp;
}


bool vowels(const char x) 
{
    std::vector<char> alphabet = {'A', 'E', 'I', 'O', 'U', 'Y',
                                  'a', 'e', 'i', 'o', 'u', 'y' };   
    for (char element : alphabet) 
    {
        if (element==x) return true;
    }
    return false;
}

template <class T>
std::list<T> filtr(std::list<T> &lst, bool(*func)(const T x))
{
    std::list<T> newlst;
    for (T element : lst)
    {
        if(func(element)) {newlst.push_back(element);}
    }
    return newlst;
}

int main()
{
    std::list<char> lst;
    lst.sort();

    lst.push_back('a');
    lst.push_back('b');
    lst.push_back('c');
    lst.push_back('d');
    push<char>(lst,'A');
    lst.push_back('A');

    for(char element : lst)
    {
        std::cout << element << std::endl;
    }
    std::cout << '\n' << pop<char>(lst) << std::endl;

    std::list<char> newlst = filtr<char>(lst,vowels);  

    for(char element : newlst)
    {
        std::cout << element << '\t';
    }         


    system("PAUSE");
    return 0;
}
