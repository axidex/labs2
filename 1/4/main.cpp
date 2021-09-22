// TestList.cpp: определяет точку входа для консольного приложения.
//

// AbstractClassList.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
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
		cout << "\nParent destructor";
		Element<T>* current = nullptr;
		while (LinkedListParent<T>::head != nullptr)
		{
			if (LinkedListParent<T>::head == LinkedListParent<T>::tail)
			{
				if (LinkedListParent<T>::head != nullptr)
				{
					delete LinkedListParent<T>::head;
				}

				LinkedListParent<T>::head = LinkedListParent<T>::tail = nullptr;
			}
			else
			{
				current = LinkedListParent<T>::head;
				LinkedListParent<T>::head = LinkedListParent<T>::head->getNext();
				if (current != nullptr)
				{
					delete current;
				}
				current = nullptr;
			}
			LinkedListParent<T>::num--;
		}
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

template<class T>
class ListIterator;

template <class T>
class Queue : public LinkedListParent<T>
{
public:
	Queue() { cout << "\nQueue constructor"; }
	virtual ~Queue() { cout << "\nQueue destructor"; }

	virtual Element<T>* push(T value)
	{
		if (LinkedListParent<T>::num > 0)
		{
			Element<T>* newElem = new Element<T>(value);
			LinkedListParent<T>::tail->setNext(newElem);
			newElem->setPrevious(LinkedListParent<T>::tail);
			LinkedListParent<T>::tail = LinkedListParent<T>::tail->getNext();
		}
		else
		{
			LinkedListParent<T>::tail = new Element<T>(value);
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

	virtual Queue<T> filter(bool(*func)(const char x))
	{
		Queue<T> newQ;

		ListIterator<T> iterator = LinkedListParent<T>::head;
		while (iterator != nullptr)
		{
			if (func((*iterator).getValue()))
			{
				newQ.push((*iterator).getValue());
				newQ.LinkedListParent<T>::num++;
			}
			iterator++;
		}
		return newQ;
	}
};

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

int main()
{
	Queue<char> Q;
	Queue<char> W;
	cout << endl;

	W.push('z');
	W.push('x');
	W.push('c');

	Q.push('a');
	Q.push('b');
	Q.push('c');
	Q.push('e');

	ListIterator<char> qwe (Q,0);
	while (qwe != nullptr)
	{
		cout << qwe << endl;
		qwe--;
	}
	qwe = W.getBegin();
	while (qwe != nullptr)
	{
		cout << qwe << endl;
		qwe++;
	}
	return 0;
}

