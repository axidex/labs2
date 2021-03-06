#include <iostream>
#include <cmath>
using namespace std;

template <class V, class T>
class TreeIterator;

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
        if (a.name > name) return false;

        return true;
    }
    bool operator<(book a)
    {
        if (a.name < name) return false;

        return true;
    }
    bool operator==(book a)
    {
        if ((a.tirazh == tirazh) && (a.year == year) && (a.name == name)) return true;

        return false;
    }
    bool operator!=(book a)
    {
        if ((a.tirazh == tirazh) && (a.year == year) && (a.name == name))  return false;

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


    friend ostream& operator<<(ostream& s, book el)
    {
        s << el.first_name << '\t' << el.second_name << '\t' << el.name << '\t' << el.year << '\t' << el.izdatelstvo << '\t' << el.sheets << '\t' << el.vid << '\t' << el.tirazh << std::endl;
        return s;
    }
};

template <class V, class T>
class Node
{
protected:
    //закрытые переменные Node N; N.data = 10 вызовет ошибку
    T data;
    V key;

    //не можем хранить Node, но имеем право хранить указатель
    Node* left;
    Node* right;
    Node* parent;

    //переменная, необходимая для поддержания баланса дерева
    int height;

public:
    //доступные извне переменные и функции
    virtual void setData(T d) { data = d; }
    virtual T getData() { return data; }
    int getHeight() { return height; }
    virtual V getKey() { return key; }

    virtual Node* getLeft() { return left; }
    virtual Node* getRight() { return right; }
    virtual Node* getParent() { return parent; }

    virtual void setLeft(Node* N) { left = N; }
    virtual void setRight(Node* N) { right = N; }
    virtual void setParent(Node* N) { parent = N; }

    //Конструктор. Устанавливаем стартовые значения для указателей
    Node<V, T>(T n)
    {
        data = n;
        left = right = parent = NULL;
        height = 1;
    }

    Node<V, T>()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        height = 1;
    }
    Node<V, T> operator=(const Node<V, T> a)
    {
        left = a.left;
        right = a.right;
        parent = a.parent;
        height = a.height;
        data = a.data;
        key = a.key;
        return *this;
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

    friend ostream& operator<<(ostream& stream, Node<V, T>& N)
    {
        stream << "\nNode data: " << N.data << ", height: " << N.height;
        return stream;
    }
};

template <class V, class T>
void print(Node<V, T>* N) {
    cout << "\n"
        << N->getData();
}

template <class V, class T>
class Tree
{
protected:
    //корень - его достаточно для хранения всего дерева
    Node<V, T>* root;

    virtual void clear(Node<V, T>* p)
    {
        if (p != nullptr)
        {
            clear(p->getLeft());
            clear(p->getRight());

            delete p;
            p = nullptr;
        }
    }

public:
    virtual ~Tree()
    {
        clear(Tree<V, T>::root);
    }
    //доступ к корневому элементу
    virtual Node<V, T>* getRoot() { return root; }

    //конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
    Tree<V, T>() { root = NULL; }

    //рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
    virtual Node<V, T>* Add_R(Node<V, T>* N)
    {
        return Add_R(N, root);
    }

    virtual Node<V, T>* Add_R(Node<V, T>* N, Node<V, T>* Current)
    {
        if (N == NULL)
            return NULL;
        if (root == NULL)
        {
            root = N;
            return N;
        }

        if (Current->getData() > N->getData())
        {
            //идем влево
            if (Current->getLeft() != NULL)
                Current->setLeft(Add_R(N, Current->getLeft()));
            else
                Current->setLeft(N);
            Current->getLeft()->setParent(Current);
        }
        if (Current->getData() < N->getData())
        {
            //идем вправо
            if (Current->getRight() != NULL)
                Current->setRight(Add_R(N, Current->getRight()));
            else
                Current->setRight(N);
            Current->getRight()->setParent(Current);
        }
        if (Current->getData() == N->getData())
            //нашли совпадение
            ;
        //для несбалансированного дерева поиска
        return Current;
    }

    //функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
    virtual Node<V, T>* Add(T n)
    {
        Node<V, T>* N = new Node<V, T>;
        N->setData(n);
        return Add_R(N);
    }

    //удаление узла
    Node<V, T>* Remove(Node<V, T>* N)
    {
        if (N == NULL)
            return NULL;
        if (root == NULL)
            return NULL;

        TreeIterator<V, T> it = Min();
        while (it != NULL)
        {
            if (it == N) break;
            it++;
        }
        if (*it == NULL)
            return NULL;

        Node<V, T>* node = *it;
        Node<V, T>* parent = nullptr;
        Node<V, T>* left = nullptr;
        Node<V, T>* right = nullptr;
        Node<V, T>* rightleft = nullptr;

        if (node->getParent() != NULL)
            parent = node->getParent();
        if (node->getLeft() != NULL)
            left = node->getLeft();
        if (node->getRight() != nullptr)
            right = node->getRight();
        if (node->getRight() != nullptr)
        {
            if (right->getLeft() != nullptr)
                rightleft = right->getLeft();
        }
        if (parent->getRight() == node)
        {
            if (parent != nullptr)
                parent->setRight(right);
            if (right != nullptr)
                right->setParent(parent);
            if (left != nullptr)
                left->setParent(right);
            if (right != nullptr)
                right->setLeft(left);
            if (rightleft != nullptr)
                this->Add(rightleft->getData());
        }
        else if (parent->getLeft() == node)
        {
            if (parent != nullptr)
                parent->setLeft(right);
            if (right != nullptr)
                right->setParent(parent);
            if (left != nullptr)
                left->setParent(right);
            if (right != nullptr)
                right->setLeft(left);
            if (rightleft != nullptr)
                this->Add(rightleft->getData());
        }
        return *it;

    }
     Node <V, T>* RemoveByKey(V key)
    {
        if (root == NULL)
            return nullptr;

        TreeIterator<V, T> it = Min();
        while (it != nullptr)
        {
            if ((*it)->getKey() == key) break;
            it++;
        }
        if (*it == nullptr)
            return nullptr;
        Remove(*it);
        return *it;
    }
    Node <V, T>* RemoveByValue(T value)
    {
        if (root == NULL)
            return nullptr;

        TreeIterator<V, T> it = Min();
        while (it != nullptr)
        {
            if ((*it)->getData() == value) break;
            it++;
        }
        if (*it == nullptr)
            return nullptr;
        Remove(*it);
        return *it;
    }
    virtual Node<V, T>* Min(Node<V, T>* Current = NULL)
    {
        //минимум - это самый "левый" узел. Идём по дереву всегда влево
        if (root == NULL)
            return NULL;

        if (Current == NULL)
            Current = root;
        while (Current->getLeft() != NULL)
            Current = Current->getLeft();

        return Current;
    }

    virtual Node<V, T>* Max(Node<V, T>* Current = NULL)
    {
        //минимум - это самый "правый" узел. Идём по дереву всегда вправо
        if (root == NULL)
            return NULL;

        if (Current == NULL)
            Current = root;
        while (Current->getRight() != NULL)
            Current = Current->getRight();

        return Current;
    }

    //поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
    virtual Node<V, T>* Find(T data, Node<V, T>* Current)
    {
        return  Current == nullptr ? nullptr :
            Current->getData() == data ? Current :
            Current->getData() > data ? Find(data, Current->getLeft()) :
            Current->getData() < data ? Find(data, Current->getRight()) : nullptr;
    }

    //три обхода дерева
    virtual void PreOrder(Node<V, T>* N, void (*f)(Node<V, T>*))
    {
        if (N != NULL)
            f(N);
        if (N != NULL && N->getLeft() != NULL)
            PreOrder(N->getLeft(), f);
        if (N != NULL && N->getRight() != NULL)
            PreOrder(N->getRight(), f);
    }

    //InOrder-обход даст отсортированную последовательность
    virtual void InOrder(Node<V, T>* N, void (*f)(Node<V, T>*))
    {
        if (N != NULL && N->getLeft() != NULL)
            InOrder(N->getLeft(), f);
        if (N != NULL)
            f(N);
        if (N != NULL && N->getRight() != NULL)
            InOrder(N->getRight(), f);
    }

    virtual void PostOrder(Node<V, T>* N, void (*f)(Node<V, T>*))
    {
        if (N != NULL && N->getLeft() != NULL)
            PostOrder(N->getLeft(), f);
        if (N != NULL && N->getRight() != NULL)
            PostOrder(N->getRight(), f);
        if (N != NULL)
            f(N);
    }
};


template <class V, class T>
class IteratedTree : public Tree<V, T>
{
public:
    IteratedTree<V, T>() : Tree<V, T>() {}

    TreeIterator<V, T> iterator; // Можно просто убрать итератор из member'ов этогого класса тк TreeIterator прекрасно работает и отдельно.

    TreeIterator<V, T> begin()
    {
        TreeIterator<V, T> it = Tree<V, T>::Max();
        return it;
    }
    TreeIterator<V, T> end()
    {
        TreeIterator<V, T> it = Tree<V, T>::Min();
        return it;
    }
};

template <class V, class T>
class TreeIterator : public std::iterator<std::input_iterator_tag, T>
{
protected:
    Node<V, T>* node;

    Node<V, T>* findInOrderSuccessor(Node<V, T>* t)
    {
        Node<V, T>* temp;

        if (t->getRight() != NULL)
        {
            temp = t->getRight();
            while (temp->getLeft() != NULL)
            {
                temp = temp->getLeft();
            }
            return temp;
        }

        if (t->getParent()->getLeft() == t)
        {
            temp = t->getParent();
            return temp;
        }

        temp = t->getParent();
        while (temp->getParent() && temp->getParent()->getLeft() != temp)
        {
            temp = temp->getParent();
        }

        temp = temp->getParent();
        return temp;
    }

    Node<V, T>* findNinO(Node<V, T>* t)
    {
        Node<V, T>* temp;
        if (t->getLeft() != NULL)
        {
            temp = t->getLeft();

            while (temp->getRight() != NULL)
            {
                temp = temp->getRight();
            }
            return temp;
        }

        if (t->getParent()->getRight() == t)
        {

            temp = t->getParent();
            return temp;
        }

        temp = t->getParent();
        while (temp->getParent() && temp->getParent()->getRight() != temp)
        {
            temp = temp->getParent();
        }

        temp = temp->getParent();
        return temp;
    }

public:
    TreeIterator(Node<V, T>* n)
    {
        node = n;
    }

    TreeIterator() {}

    Node<V, T>* operator*()
    {
        return node;
    }

    TreeIterator operator++(int)
    {
        node = findInOrderSuccessor(node);
        return TreeIterator(node);
    }

    TreeIterator operator--(int)
    {
        node = findNinO(node);
        return TreeIterator(node);
    }

    bool operator==(Node<V, T>* rhs)
    {
        return node == rhs;
    }

    bool operator!=(Node<V, T>* rhs)
    {
        return !(node == rhs);
    }
};

template <class V, class T>
class AVL_Tree : public IteratedTree<V, T>
{
protected:
    //определение разности высот двух поддеревьев
    int bfactor(Node<V, T>* p)
    {
        int hl = 0;
        int hr = 0;
        if (p->getLeft() != NULL)
            hl = p->getLeft()->getHeight();
        if (p->getRight() != NULL)
            hr = p->getRight()->getHeight();
        return (hr - hl);
    }

    //при добавлении узлов в них нет информации о балансе, т.к. не ясно, куда в дереве они попадут
    //после добавления узла рассчитываем его высоту (расстояние до корня) и редактируем высоты в узлах, где это
    //значение могло поменяться
    void fixHeight(Node<V, T>* p)
    {
        int hl = 0;
        int hr = 0;
        if (p->getLeft() != NULL)
            hl = p->getLeft()->getHeight();
        if (p->getRight() != NULL)
            hr = p->getRight()->getHeight();
        p->setHeight((hl > hr ? hl : hr) + 1);
    }

    //краеугольные камни АВЛ-деревьев - процедуры поворотов
    Node<V, T>* RotateRight(Node<V, T>* p) // правый поворот вокруг p
    {
        Node<V, T>* q = p->getLeft();
        if (p->getParent() != nullptr)
        {
            if (p->getParent()->getLeft() == p)
                p->getParent()->setLeft(q);
            else
                p->getParent()->setRight(q);
        }
        q->setParent(p->getParent());
        p->setParent(q);
        if (p == Tree<V, T>::root)
            Tree<V, T>::root = q;

        p->setLeft(q->getRight());
        q->setRight(p);

        fixHeight(p);
        fixHeight(q);
        return q;
    }

    Node<V, T>* RotateLeft(Node<V, T>* q) // левый поворот вокруг q
    {
        Node<V, T>* p = q->getRight();

        if (q->getParent() != nullptr)
        {
            if (q->getParent()->getLeft() == q)
                q->getParent()->setLeft(p);
            else
                q->getParent()->setRight(p);
        }

        p->setParent(q->getParent());
        q->setParent(p);
        if (q == Tree<V, T>::root)
            Tree<V, T>::root = p;

        q->setRight(p->getLeft());
        p->setLeft(q);

        fixHeight(q);
        fixHeight(p);
        return p;
    }

    //балансировка поддерева узла p - вызов нужных поворотов в зависимости от показателя баланса
    Node<V, T>* Balance(Node<V, T>* p) // балансировка узла p
    {
        fixHeight(p);
        if (bfactor(p) == 2)
        {
            if (bfactor(p->getRight()) < 0)
            {
                p->setRight(RotateRight(p->getRight()));
                p->getRight()->setParent(p);
            }
            return RotateLeft(p);
        }
        if (bfactor(p) == -2)
        {
            if (bfactor(p->getLeft()) > 0)
            {
                p->setLeft(RotateLeft(p->getLeft()));
                p->getLeft()->setParent(p);
            }
            return RotateRight(p);
        }

        return p; // балансировка не нужна
    }

    void print_n(Node<V, T>* p, int n, int level, int prob)
    {
        if (p)
        {
            if (level == n)
            {
                for (int i = 1; i <= prob; i++)
                    cout << " ";
                cout << p->getData();
            }
            else
            {
                print_n(p->getLeft(), n, level + 1, prob);
                print_n(p->getRight(), n, level + 1, prob);
            }
        }
    }

public:
    //конструктор AVL_Tree вызывает конструктор базового класса Tree
    AVL_Tree<V, T>() : IteratedTree<V, T>() {}
   
    virtual Node<V, T>* Add_R(Node<V, T>*N)
    {
        return Add_R(N, Tree<V, T>::root);
    }

    //рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
    virtual Node<V, T>* Add_R(Node<V, T>* N, Node<V, T>* Current)
    {
        //вызываем функцию Add_R из базового класса
        Node<V, T>* AddedNode = Tree<V, T>::Add_R(N, Current);
        //применяем к добавленному узлу балансировку
        return Balance(AddedNode);
    }

    //функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
    virtual Node<V, T>* Add(T n)
    {
        Node<V, T>* N = new Node<V, T>;
        N->setData(n);
        return Add_R(N);
    }

    //удаление узла
    void Remove(Node<V, T>* N)
    {
        Tree<V, T>::Remove(N);
        Balance(Tree<V,T>::root);
    }
    void RemoveByKey(V key)
    {
        Node<V, T>* tmp = Tree<V, T>::RemoveByKey(key);
        Balance(Tree<V, T>::root);
    }
    void RemoveByValue(T value)
    {
        Node<V, T>* tmp = Tree<V, T>::RemoveByValue(value);
        Balance(Tree<V, T>::root);
    }
    Node<V, T>* getRoot()
    {
        return Tree<V, T>::root;
    }

    Node<V, T>* operator[](int n) // поиск по индексу inorder
    {
        TreeIterator<V, T> it = Tree<V, T>::root;
        for (int i = 0; i < n; ++i) it++;
        if (it != nullptr)
        {
            return *it;
        }
    }
    Node<V, T>* operator[](V key)
    {
        TreeIterator<V, T> it = Tree<V, T>::root;
        while (it != nullptr)
        {
            if (*it->getKey() == key)
                return *it;

            it++;
        }
    }
    void PrintIn()
    {
        TreeIterator<V, T> it(this->Min());
        while (it != nullptr)
        {
            cout << (*it)->getData() << endl;
            if (it == this->Max())
                break;
            it++;
        }
    }

    void PrintNotIn()
    {
        TreeIterator<V, T> it(this->Max());
        while (true)
        {
            cout << (*it)->getData() << endl;
            if (it == this->Min())
                break;
            it--;
        }
    }
    void printt()
    {
        int h = Tree<V, T>::root->getHeight();
        int prob = 3;
        if (Tree<V, T>::root)
        {
            for (int i = 0; i <= h; i++)
            {
                print_n(Tree<V, T>::root, i, 0, prob * (h - i));
                cout << endl;
            }
        }
    }

    Node<V, T>* SearchByData(T a, Node<V, T>* p)
    {
        return Find(a, p);
    }
    Node<V, T>* SearchByKey(T k, Node<V, T>* p)
    {
        if (p != nullptr)
        {
            SearchByKey(k, p->getLeft());
            SearchByKey(k, p->getRight());

            if (p->getKey() == k)
                return p;
        }
    }
};

//класс итератор по дереву

int main()
{
    AVL_Tree<string, book> T;

    book b1;
    b1.name = 10;
    book b2;
    b2.name = 20;
    book b3;
    b3.name = 30;
    book b4;
    b4.name = 40;
    book b5;
    b5.name = 50;
    book b6;
    b6.name = 60;
    T.Add(b1);
    //T.PrintNotIn();
    cout << endl << endl;
    T.Add(b2);
    //T.PrintNotIn();
    //cout << endl << endl;
    T.Add(b3);
    //T.PrintNotIn();
    //cout << endl << endl;
    T.Add(b4);
    //T.PrintNotIn();
    //cout << endl << endl;
    T.Add(b5);
    //T.PrintNotIn();
    //cout << endl << endl;
    T.RemoveByValue(b5);
    T.RemoveByValue(b1);
    T.PrintNotIn();
       cout << endl
        << endl;
    //T.PrintIn();
    cout << endl
        << endl;

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


    return 0;
}
