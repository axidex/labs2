#include <iostream>
#include <cmath>

using namespace std;
//узел
template <class T>
class Node
{
protected:
    //закрытые переменные Node N; N.data = 10 вызовет ошибку
    T data;

    //не можем хранить Node, но имеем право хранить указатель
    Node *left;
    Node *right;
    Node *parent;

    //переменная, необходимая для поддержания баланса дерева(пока можно забить на нее)
    int height; //сами будем поддерживать ее
public:
    //доступные извне переменные и функции
    virtual void setData(T d) { data = d; }
    virtual T getData() { return data; }
    int getHeight() { return height; }

    virtual Node *getLeft() { return left; }
    virtual Node *getRight() { return right; }
    virtual Node *getParent() { return parent; }

    virtual void setLeft(Node *N) { left = N; }
    virtual void setRight(Node *N) { right = N; }
    virtual void setParent(Node *N) { parent = N; }

    //Конструктор. Устанавливаем стартовые значения для указателей
    Node<T>(T n)
    {
        data = n;
        left = right = parent = NULL;
        height = 1;
    }

    Node<T>()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        data = 0; //произвольный тип, не факт, что будет int.
        height = 1;
    }

    virtual void print()
    {
        cout << "\n"
             << data;
    }

    virtual void setHeight(int h)
    {
        height = h;
    }

    friend ostream &operator<<(ostream &stream, Node<T> &N)
    {
        stream << "\nNode data: " << N.data << ", height: " << N.height;
        return stream;
    }
};



    template <class T>
    void print(Node<T> *N)
{
    cout << "\n"
         << N->getData();
}

template <class T>
class Tree
{
protected:
    //корень - его достаточно для хранения всего дерева
    Node<T> *root;

public:
    //доступ к корневому элементу
    virtual Node<T> *getRoot() { return root; }

    //конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
    Tree<T>() { root = NULL; }

    //(красивая для пользователя)
    //функция добавления узла в дерево
    virtual Node<T> *Add_R(T value)
    {
        Node<T> *N = new Node<T>(value);
        return Add_R(N);
    }

    //функция добавления узла в дерево
    virtual Node<T> *Add_R(Node<T> *N)
    {
        return Add_R(N, root);
    }

    //рекуррентная функция добавления узла. Интерфейс аналогичен (добавляется корень поддерева,
    //куда нужно добавлять узел), но вызывает сама себя - добавление в левое или правое поддерево
    virtual Node<T> *Add_R(Node<T> *N, Node<T> *Current)
    {
        //не передан добавляемый узел
        if (N == NULL)
            return NULL;

        if (Current == NULL)
        {
            Current = root;
        }
        //пустое дерево - добавляем в корень
        if (root == NULL)
        {
            root = N;
            return N;
        }

        if (Current->getData() > N->getData())
        {
            //идем влево
            if (Current->getLeft() != NULL)
            {
                return Add_R(N, Current->getLeft());
            }
            else
            {
                Current->setLeft(N);
                N->setParent(Current);
                return N;
            }
        }
        if (Current->getData() < N->getData())
        {
            //идем вправо
            if (Current->getRight() != NULL)
            {
                return Add_R(N, Current->getRight());
            }
            else
            {
                Current->setRight(N);
                N->setParent(Current);
                return N;
            }
        }
        if (Current->getData() == N->getData())
        {
        }
        //нашли совпадение
        //вернуть добавленный узел
    }

    //функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
    virtual void Add(int n)
    {
        Node<T> *N = new Node<T>(n);
        Add_R(N);
    }

    //удаление узла
    virtual void Remove(Node<T> *N)
    {
    }

    //поиск минимума и максимума в дереве
    virtual Node<T> *Min(Node<T> *Current = NULL) //Самое левое поддерево.
    {                                             //Напишем цикл для разнообразия.
        if (Current == NULL)                      //если пользователь не дал узел, то начинаем с корня.
        {
            Current = root;
        }
        if (root == NULL)
        {
            return NULL;
        }
        while (Current->getLeft() != NULL)
        {
            Current = Current->getLeft();
        }
        return Current;
    }

    virtual Node<T> *Max(Node<T> *Current = NULL) //Самое правое поддерево.
    {                                             //Напишем цикл для разнообразия.
        if (Current == NULL)                      //если пользователь не дал узел, то начинаем с корня.
        {
            Current = root;
        }
        if (root == NULL)
        {
            return NULL;
        }
        while (Current->getRight() != NULL)
        {
            Current = Current->getRight();
        }
        return Current;
    }

    //поиск узла в дереве
    virtual Node<T> *Find(T data)
    {
        if (root == NULL)
            return NULL;
        return Find_R(data, root);
    }

    //поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
    virtual Node<T> *Find_R(T data, Node<T> *Current) //data - что ищем, current - узел, где стоим
    {
        //база рекурсии
        if (Current == NULL)
        {
            return NULL;
        }
        if (data == Current->getData())
        {
            return Current;
        }
        //рекурсивный вызов
        if (data < Current->getData())
        {
            return Find_R(data, Current->getLeft());
        }
        if (data > Current->getData())
        {
            return Find_R(data, Current->getRight());
        }
    }

    //три обхода дерева
    virtual void PreOrder(Node<T> *N, void (*f)(Node<T> *))
    {
        if (N != NULL)
            f(N);
        if (N != NULL && N->getLeft() != NULL)
            PreOrder(N->getLeft(), f);
        if (N != NULL && N->getRight() != NULL)
            PreOrder(N->getRight(), f);
    }

    //InOrder-обход даст отсортированную последовательность
    virtual void InOrder(Node<T> *N, void (*f)(Node<T> *))
    {
        if (N != NULL && N->getLeft() != NULL)
            InOrder(N->getLeft(), f);
        if (N != NULL)
            f(N);
        if (N != NULL && N->getRight() != NULL)
            InOrder(N->getRight(), f);
    }

    virtual void PostOrder(Node<T> *N, void (*f)(Node<T> *))
    {
        if (N != NULL && N->getLeft() != NULL)
            PostOrder(N->getLeft(), f);
        if (N != NULL && N->getRight() != NULL)
            PostOrder(N->getRight(), f);
        if (N != NULL)
            f(N);
    }
};

//класс итератор по дереву
template <typename ValueType>
class TreeIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:
public:
    TreeIterator()
    {
        ptr = NULL;
        T = NULL;
    }
    TreeIterator(Tree<ValueType> *t, Node<ValueType> *p) {}
    TreeIterator(const TreeIterator &it) {}

    TreeIterator &operator=(const TreeIterator &it) {}
    TreeIterator &operator=(Node<ValueType> *p) {}

    bool operator!=(TreeIterator const &other) const {}
    bool operator==(TreeIterator const &other) const {}
    Node<ValueType> &operator*() {}
    TreeIterator &operator++()
    {
    }
    TreeIterator &operator++(int v)
    {
    }

private:
    Node<ValueType> *ptr;
    Tree<ValueType> *T;
};

//класс итерируемое дерево поиска
template <class T>
class IteratedTree : public Tree<T>
{
public:
    IteratedTree<T>() : Tree<T>() {}

    TreeIterator<T> iterator;

    TreeIterator<T> begin() {}
    TreeIterator<T> end() {}
};

//[]-будет принимать ключ и искать по этому ключу.

int main()
{
    Tree<double> T;
    int arr[15];
    int i = 0;
    for (i = 0; i < 15; i++)
        arr[i] = (int)(100 * cos(15 * double(i)));
    for (i = 0; i < 15; i++)
        T.Add(arr[i]);

    Node<double> *M = T.Min();
    cout << "\nMin = " << M->getData() << "\tFind " << arr[3] << ": " << T.Find(arr[3]); //T.Find(arr[3], T.getRoot()

    void (*f_ptr)(Node<double> *);
    f_ptr = print;
    /*cout << "\n-----\nPreorder:";
	T.PreOrder(T.getRoot(), f_ptr);*/
    cout << "\n-----\nInorder:";
    T.InOrder(T.getRoot(), f_ptr);
    /*cout << "\n-----\nPostorder:";
	T.PostOrder(T.getRoot(), f_ptr);*/
    /*cout << "\nIterators:\n";
	T.iterator = T.begin();
	while (T.iterator != T.end())
	{
	cout << *T.iterator << " ";
	T.iterator++;
	}
	cout << *T.iterator << " ";*/

    char c;
    cin >> c;
    return 0;
}
