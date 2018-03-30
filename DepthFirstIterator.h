#ifndef DEPTHFIRSTITERATOR_H
#define DEPTHFIRSTITERATOR_H

#include "TreeIterator.h"

template<class AllocatorType>
class DepthFirstIterator : public TreeIterator<AllocatorType>
{
public:
    DepthFirstIterator() {}
    DepthFirstIterator(AllocatorType *p) : TreeIterator<AllocatorType>(p) {}

    DepthFirstIterator operator++();
    DepthFirstIterator operator++(int);

    static DepthFirstIterator end() { return DepthFirstIterator(); }
protected:
    inline bool moveToNextSibling();    // 此处不是严格意义上的亲兄弟，有可能找到的都不是同辈分的。
    inline bool moveToChildren();
};

template<class AllocatorType>
DepthFirstIterator<AllocatorType> DepthFirstIterator<AllocatorType>::operator++()
{
    if (moveToChildren()
            || moveToNextSibling())
    {
    }
    else    // 既找不到子节点，又找不到兄弟
    {
        *this = DepthFirstIterator<AllocatorType>::end();
    }

    return *this;
}

template<class AllocatorType>
DepthFirstIterator<AllocatorType> DepthFirstIterator<AllocatorType>::operator++(int)
{
    DepthFirstIterator tmp(*this); operator++(); return tmp;
}

template<class AllocatorType>
bool DepthFirstIterator<AllocatorType>::moveToNextSibling()
{
    while (true)
    {
        if (this->p->isRootNode())    // 根节点是不会有亲兄弟的
        {
            return false;
        }

        auto it = this->p->parent->children.rbegin();
        if (*it == this->p)    // p已经是最后一个了,再去找父亲的下一个亲兄弟
        {
            this->p = this->p->parent;
            continue;
        }

        for (; it != this->p->parent->children.rend(); ++it)
        {
            if (*it == this->p)
            {
                this->p = *(--it);    // 由于我们用的是反向迭代器，所以此处是--
                return true;
            }
        }

         assert(false); // UNREACHABLE，
    }
}

template<class AllocatorType>
bool DepthFirstIterator<AllocatorType>::moveToChildren()
{
    if (this->p->children.empty())
    {
        return false;
    }

    this->p = this->p->children.front();
    return true;
}

#endif // DEPTHFIRSTITERATOR_H
