//单链表
#ifndef __FORWARDLIST_HPP__
#define __FORWARDLIST_HPP__


class ForwardList
{
public:
    class Node
    {
        void * data;
        Node * next = nullptr;
    public:
        Node(void * data);
        void * Setdata(void * data);//设置data并且返回原data
        void Setnext(Node * next);
        void * Getdata();
        Node * Getnext();
    };

    //写一个迭代
    class Iterator
    {
        Node * ptr;
    public:
        Iterator(Node * nptr);
        bool end();
        void * operator*();
        Iterator operator++(int);//后++
        //这里没有深拷贝需求，因此不需要自己实现深拷贝构造以及赋值重载
    };


    //返回指向第一个元素的迭代器
    Iterator begin();
    Iterator end();

    ForwardList();//


    //删除一个data之前的节点 删除之后返回新的迭代器()
    //删除一个节点  remove
    //接口可以参照forward_list



    //增加节点  尾插
    void Push_back(void * data);

    //清空链表
    void Clean();
    ~ForwardList();
private:
    Node * first = nullptr;
    Node * last = nullptr;
    int num = 0;

};




#endif



