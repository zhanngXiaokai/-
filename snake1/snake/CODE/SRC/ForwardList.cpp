#include "ForwardList.hpp"


//节点的构造函数
ForwardList::Node::Node(void * data):data(data),next(nullptr){}

//设置data并且返回原data
void * ForwardList::Node::Setdata(void * data)
{
    void * d = this ->data;//先保存原来的data
    this ->data = data;//设置新的data
    return d;//返回原data
}

//设置节点的下一个
void ForwardList::Node::Setnext(ForwardList::Node * next)
{
    this ->next = next;
}
//获取data
void * ForwardList::Node::Getdata()
{
    return this ->data;
}
//获取节点的下一个
ForwardList::Node * ForwardList::Node::Getnext()
{
    return this ->next;
}

//无参构造
ForwardList::ForwardList():first(nullptr),last(nullptr),num(0){}


//增加节点  尾插
void ForwardList::Push_back(void * data)
{
    Node * pnew = new Node{data};
    if(this ->first == nullptr)//链表不存在
    {
        this ->first = this ->last = pnew;    
    }
    else//插入在尾部
    {
        this ->last ->Setnext(pnew);
        this ->last = pnew;
    }
    this ->num++;
}

    
void ForwardList::Clean()
{
    while(this ->first != nullptr)
    {
        ForwardList::Node * ptr = this ->first;
        this ->first = this ->first ->Getnext();
        ptr ->Setnext(nullptr);
        delete ptr;
    }
    this ->last = nullptr;
    this ->num = 0;
}

//返回指向第一个元素的迭代器
ForwardList::Iterator ForwardList::begin()
{
    return Iterator(this ->first);
}

//返回指向最后一个元素的下一个的迭代器
ForwardList::Iterator ForwardList::end()
{
    return Iterator(nullptr);
}



ForwardList::~ForwardList()
{
    Clean();
}


ForwardList::Iterator::Iterator(Node * nptr):ptr(nptr){}

bool ForwardList::Iterator::end()
{
    if(ptr == nullptr)
        return true;
    return false;
}

void * ForwardList::Iterator::operator*()
{
    return this ->ptr ->Getdata();
}

ForwardList::Iterator ForwardList::Iterator::operator++(int)//后++
{
    Iterator it = *this;//以自己创建一个新的迭代器
    this ->ptr = this ->ptr ->Getnext();//再让自己指向下一个
    return it;//返回原来的迭代器
}
