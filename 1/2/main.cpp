#include <list>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
/*Вариант 7 КТСО-03-20*/
// Книга. Тираж. Год. Название.

struct book
{
private:
    enum Vid
    {
        VID_ELEC = 0,
        VID_PAPER,
        VID_AUDIO,
    };
public:
    std::string first_name;
    std::string second_name;
    std::string name;
    unsigned short int year;
    std::string izdatelstvo;
    unsigned short int sheets;
    Vid vid;
    unsigned int tirazh;
    book()
    {
        first_name = "nofirstname";
        second_name = "nosecname";
        name = "nobookname";
        year = std::rand()%100+1920;
        izdatelstvo = "nonameizd";
        sheets = std::rand()%1000+20;
        vid = static_cast<Vid>(rand() % VID_AUDIO);
        tirazh = rand()%10000+20000;
    }
    friend std::ostream &operator<<(std::ostream &s, book &el)
    {
        s << el.first_name << '\t' << el.second_name << '\t' << el.name << '\t' << el.year << '\t' << el.izdatelstvo << '\t' << el.sheets << '\t' << el.vid << '\t' << el.tirazh << std::endl;
        return s;
    }
};

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
void push(std::list<book> &lst,book a)
{
    std::list<book>::iterator p = lst.begin();
    while (p != lst.end())
    {
        if(a.tirazh > (*p).tirazh) break;

        else if (a.tirazh == (*p).tirazh)
        {
            if (a.year > (*p).year) break;

            else if (a.year == (*p).year)
            {
                if (a.name > (*p).name) break;
            }
        }
        p++;
    }
    lst.insert(p,a);
}

template<class T>
T pop(std::list<book> &lst)
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
std::list<T> filtr(std::list<T> &lst, bool(*func)(const char x))
{
    std::list<T> newlst;
    for (char element : lst)
    {
        if(func(element)) {newlst.push_back(element);}
    }
    return newlst;
}



int main()
{
    std::srand(std::time(nullptr));
    std::list<book> lst;
    book a,b,c,d;
    
    push<book>(lst,a);
    push<book>(lst,b);
    push<book>(lst,c);
    push<book>(lst,d);
    for (auto el : lst)
    {
        std::cout << el << std::endl;
    }
    std::cout << std::endl;
    book q = pop<book>(lst);
    std::cout << q << std::endl << std::endl;

    for (auto el : lst)
    {
        std::cout << el << std::endl;
    }

    system("PAUSE");
    return 0;
}