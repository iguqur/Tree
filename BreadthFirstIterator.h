#ifndef BREADTHFIRSTITERATOR_H
#define BREADTHFIRSTITERATOR_H

#include "TreeIterator.h"

template<class AllocatorType>
class BreadthFirstIterator : public TreeIterator<AllocatorType>
{
public:
    BreadthFirstIterator() {}
    BreadthFirstIterator(AllocatorType *p) : TreeIterator<AllocatorType>(p) {}

    BreadthFirstIterator operator++();
    BreadthFirstIterator operator++(int);

    static BreadthFirstIterator end() { return BreadthFirstIterator(); }
private:
    inline bool moveToNextCousin();    // 找到下一个同级的兄弟
    inline bool moveToNextSibling();    // 此处是严格意义上的亲兄弟
    inline bool moveToParent(); // 移动到父亲
    inline bool moveToCurDepthFristGeneration();    // 从当前的指针找curDepth的第一个
    inline bool moveToNextFristGeneration();    // 从root找下一代的第一个

private:
    int m_curDepth = 0;
};

template<class AllocatorType>
BreadthFirstIterator<AllocatorType> BreadthFirstIterator<AllocatorType>::operator++()
{
    m_curDepth = this->p->curDepth();

    if (moveToNextCousin()
            || moveToNextFristGeneration())
    {

    }
    else
    {
        *this = BreadthFirstIterator::end();
    }

    return *this;
}

template<class AllocatorType>
bool BreadthFirstIterator<AllocatorType>::moveToNextCousin()
{
    while (true)
    {
        if (moveToNextSibling())
        {
            if (moveToNextFristGeneration())
            {
                return true;
            }
        }

        if (moveToParent())
        {
            if (this->p->isRootNode())
            {
                return false;
            }
        }
        else
        {
            assert(false); // UNREACHABLE
        }
    }
}

template<class AllocatorType>
bool BreadthFirstIterator<AllocatorType>::moveToNextSibling()
{
    if (this->p->isRootNode())    // 根节点是不会有亲兄弟的
    {
        return false;
    }

    auto it = this->p->parent->children.rbegin();
    if (*it == this->p)    // p已经是最后一个了,没有下一个了
    {
        return false;
    }

    for (; it != this->p->parent->children.rend(); ++it)
    {
        if (*it == this->p)
        {
            this->p = *(--it);    // 由于我们用的是反向迭代器，所以此处是--
            return true;
        }
    }

    assert(false); // UNREACHABLE
    return false;
}

template<class AllocatorType>
bool BreadthFirstIterator<AllocatorType>::moveToParent()
{
    if (this->p->isRootNode())  // 根节点不会有父亲
    {
        return false;
    }

    this->p = this->p->parent;
    return true;
}

template<class AllocatorType>
bool BreadthFirstIterator<AllocatorType>::moveToCurDepthFristGeneration()
{
    int curDepth = this->p->curDepth();
    while (curDepth != m_curDepth && !this->p->children.empty())
    {
        this->p = this->p->children.front();
        ++curDepth;
    }

    if (curDepth == m_curDepth)
    {
        return true;
    }

    return false;
}

template<class AllocatorType>
bool BreadthFirstIterator<AllocatorType>::moveToNextFristGeneration()
{
    while (!this->p->isRootNode())    // 移动到根节点
    {
        this->p = this->p->parent;
    }

    int curDepth = this->p->curDepth();
    while (curDepth != m_curDepth + 1 && !this->p->children.empty())
    {
        this->p = this->p->children.front();
        ++curDepth;
    }

    if (curDepth == m_curDepth + 1)
    {
        return true;
    }

    return false;
}

#endif // BREADTHFIRSTITERATOR_H
