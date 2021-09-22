// TestList.cpp: определяет точку входа для консольного приложения.
//

// AbstractClassList.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

bool vowels(const char x)
{
	std::vector<char> alphabet = { 'A', 'E', 'I', 'O', 'U', 'Y',
								  'a', 'e', 'i', 'o', 'u', 'y' };
	for (char element : alphabet)
	{
		if (element == x) return true;
	}
	return false;
}

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
	bool operator>(book a)
    {
        if(a.tirazh > tirazh) return false;

        else if (a.tirazh == tirazh)
        {
            if (a.year > year) return false;

            else if (a.year == year)
            {
                if (a.name > name) return false;
            }
        }
        return true;
    }
	book()
	{
		first_name = "nofirstname";
		second_name = "nosecname";
		name = "nobookname";
		year = std::rand() % 100 + 1920;
		izdatelstvo = "nonameizd";
		sheets = std::rand() % 1000 + 20;
		vid = static_cast<Vid>(rand() % VID_AUDIO);
		tirazh = rand() % 10000 + 20000;
	}
	friend std::ostream& operator<<(std::ostream& s, book& el)
	{
		s << el.first_name << '\t' << el.second_name << '\t' << el.name << '\t' << el.year << '\t' << el.izdatelstvo << '\t' << el.sheets << '\t' << el.vid << '\t' << el.tirazh << std::endl;
		return s;
	}
};

template <class T>
class Element
{
	//элемент связного списка
private:
	//указатель на предыдущий и следующий элемент
	Element* next;
	Element* prev;

	//информация, хранимая в поле
	T field;
public:
	//доступ к полю *next
	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }

	//доступ к полю *prev
	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }

	//доступ к полю с хранимой информацией field
	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }

	Element() { next = prev = NULL; }
	Element(T value) { next = prev = NULL; field = value; }

	friend ostream& operator<< (ostream& ustream, Element<T>& obj)
	{
		ustream << obj.field;
		return ustream;
	}
};



template <class T>
class LinkedListParent
{
protected:
	//достаточно хранить начало и конец
	Element<T>* head;
	Element<T>* tail;
	//для удобства храним количество элементов
	int num;
public:
	virtual int Number() { return num; }

	virtual Element<T>* getBegin() { return head; }

	virtual Element<T>* getEnd() { return tail; }

	LinkedListParent()
	{
		//конструктор без параметров
		cout << "\nParent constructor";
		head = NULL;
		num = 0;
	}

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element<T>* push(T value) = 0;

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual Element<T>* pop() = 0;

	virtual ~LinkedListParent()
	{
		//деструктор - освобождение памяти
		cout << "\nParent destructor";
	}

	//получение элемента по индексу - какова асимптотическая оценка этого действия?
	virtual Element<T>* operator[](int i)
	{
		//индексация
		if (i<0 || i>num) return NULL;
		int k = 0;

		//ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element<T>* cur = head;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}

	friend ostream& operator<< (ostream& ustream, LinkedListParent<T>& obj)
	{
		if (typeid(ustream).name() == typeid(ofstream).name())
		{
			ustream << obj.num << "\n";
			for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext())
				ustream << current->getValue() << " ";
			return ustream;
		}

		ustream << "\nLength: " << obj.num << "\n";
		int i = 0;
		for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
			ustream << "arr[" << i << "] = " << current->getValue() << "\n";

		return ustream;
	}
	friend istream& operator>> (istream& ustream, LinkedListParent<T>& obj)
	{
		//чтение из файла и консоли совпадают
		int len;
		ustream >> len;
		//здесь надо очистить память под obj, установить obj.num = 0
		double v = 0;
		for (int i = 0; i < len; i++)
		{
			ustream >> v;
			obj.push(v);
		}
		return ustream;
	}
};

template <class T>
class Queue;

template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
public:
	//конструкторы
	ListIterator() { ptr = NULL; }
	ListIterator(Element<ValueType>* p) { ptr = p; }
	ListIterator(const ListIterator& it) { ptr = it.ptr; }

	ListIterator(Queue<ValueType>& Q, bool flagBeginEnd = true)
	{
		if (flagBeginEnd)
			ptr = Q.getBegin();
		else
			ptr = Q.getEnd();
	}

	Element<ValueType>* getValue() { return ptr; }

	//методы работы с итераторами
	//присваивание
	ListIterator&& operator=(const ListIterator& it) { ptr = it.ptr; return *this; }
	ListIterator& operator=(Element<ValueType>* p) { ptr = p; return *this; }

	//проверка итераторов на равенство
	bool operator!=(ListIterator const& other) const { return ptr != other.ptr; }
	bool operator==(ListIterator const& other) const { return ptr == other.ptr; }
	Element<book>* getBook()
	{
		return ptr;
	}
	//получить значение
	Element<ValueType>& operator*()
	{
		return *ptr;
	}
	//перемещение с помощью итераторов
	ListIterator& operator++()
	{
		if (ptr != NULL)
			ptr = ptr->getNext();
		return *this;
	}
	ListIterator& operator++(int v)
	{
		if (ptr != NULL)
			ptr = ptr->getNext();
		return *this;
	}
	ListIterator& operator--()
	{
		if (ptr != NULL)
			ptr = ptr->getPrevious();
		return *this;
	}
	ListIterator& operator--(int v)
	{
		if (ptr != NULL)
			ptr = ptr->getPrevious();
		return *this;
	}


	friend ostream& operator<< (ostream& ustream, ListIterator<ValueType>& obj)
	{
		ustream << *obj.getValue();
		return ustream;
	}

private:
	//текущий элемент
	Element<ValueType>* ptr;
};

template <class T>
class Queue : public LinkedListParent<T>
{
public:
	Queue() { cout << "\nQueue constructor"; }
	virtual ~Queue() { cout << "\nQueue destructor"; }

	virtual Element<T>* push(T value)
	{
		Element<T>* newElem = new Element<T>(value);
		if (LinkedListParent<T>::num > 0)
		{
			LinkedListParent<T>::tail->setNext(newElem);
			newElem->setPrevious(LinkedListParent<T>::tail);
			LinkedListParent<T>::tail = LinkedListParent<T>::tail->getNext();
		}
		else
		{
			LinkedListParent<T>::tail = newElem;
			LinkedListParent<T>::head = LinkedListParent<T>::tail;
		}
		LinkedListParent<T>::num++;
		return LinkedListParent<T>::tail;
	}
	virtual Element<T>* pushCondition(book a)
	{
		int counter = 1;
		Element<book>* newElem = new Element<book>(a);
		if (LinkedListParent<T>::num > 0)
		{
			
			ListIterator<book> it = LinkedListParent<T>::getBegin();
			while (it != nullptr)
			{
				if (a > (*it).getValue()) break;
				it++;
				counter++;
			}
			if (LinkedListParent<T>::num == 1)
			{
				bool flag = true;
				ListIterator<book> it1 = LinkedListParent<T>::getBegin();
				if (a.tirazh > (*it1).getValue().tirazh)
					flag = false;
				
				else if (a.tirazh == (*it1).getValue().tirazh)
				{
					if (a.year > (*it1).getValue().year) 
						flag = false;

					else if (a.year == (*it1).getValue().year )
					{
						if (a.name > (*it1).getValue().name) 
							flag = false;
					}
				}
				if (flag)
				{
					newElem->setPrevious(LinkedListParent<T>::tail);
					LinkedListParent<T>::tail->setNext(newElem);
					LinkedListParent<T>::tail = newElem;
					
				}
				else
				{
					newElem->setNext(LinkedListParent<T>::head);
					LinkedListParent<T>::head->setPrevious(newElem);
					LinkedListParent<T>::head = newElem;
				}
			}
			else if (counter == LinkedListParent<T>::num + 1)
			{
				newElem->setPrevious(LinkedListParent<T>::tail);
				LinkedListParent<T>::tail->setNext(newElem);
				LinkedListParent<T>::tail = newElem;
			}
			else
			{
				if (counter == 1)
				{
					LinkedListParent<T>::head->setPrevious(newElem);
					newElem->setNext(LinkedListParent<T>::head);
					LinkedListParent<T>::head = newElem;
				}
				else
				{
					newElem->setPrevious((*it).getPrevious());
					newElem->setNext(it.getBook());
					(*it).setPrevious(newElem);
					it = newElem->getPrevious();
					(*it).setNext(newElem);
				}
			}
		}
		else
		{
			LinkedListParent<T>::tail = newElem;
			LinkedListParent<T>::head = LinkedListParent<T>::tail;
		}
		LinkedListParent<T>::num++;
		return LinkedListParent<T>::tail;
	}


	virtual Element<T>* pop()
	{
		Element<T>* newElem;
		if (LinkedListParent<T>::num > 0)
		{
			newElem = LinkedListParent<T>::head;
			LinkedListParent<T>::head = LinkedListParent<T>::head->getNext();
		}
		else
		{
			newElem = LinkedListParent<T>::head;
			LinkedListParent<T>::head = LinkedListParent<T>::tail = nullptr;
		}
		newElem->setPrevious(nullptr);
		newElem->setNext(nullptr);
		LinkedListParent<T>::num--;
		return newElem;
	}


};


int main()
{
	std::srand(std::time(nullptr));
	Queue<book> lst;
	cout << endl;
	book a, b, c, d;
	ListIterator<book> it(lst);
	
	lst.pushCondition(a);
	it = lst.getBegin();
	cout << endl << endl;
	while (it != nullptr)
	{
		cout << it << endl;
		it++;
	}

	lst.pushCondition(b);
	cout << endl << endl;
	it = lst.getBegin();
	while (it != nullptr)
	{
		cout << it << endl;
		it++;
	}

	cout << endl << endl;
	lst.pushCondition(c);
	it = lst.getBegin();
	while (it != nullptr)
	{
		cout << it << endl;
		it++;
	}

	
	cout << endl << endl;
	lst.pushCondition(d);
	it = lst.getBegin();
	while (it != nullptr)
	{
		cout << it << endl;
		it++;
	}

	cout << endl << endl;
	it = lst.getBegin();
	while (it != nullptr)
	{
		cout << it << endl;
		it++;
	}

	lst.pushCondition(a);
	it = lst.getBegin();
	cout << endl << endl;
	while (it != nullptr)
	{
		cout << it << endl;
		it++;
	}
	lst.pop();
	cout << endl << endl;
	it = lst.getBegin();
	while (it != nullptr)
	{
		cout << it << endl;
		it++;
	}
	cout << endl << endl;
	it = lst.getBegin();

	return 0;
}

