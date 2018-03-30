#ifndef TREEITERATOR_H
#define TREEITERATOR_H

#include <iterator>
#include <assert.h>

template <class AllocatorType>
class TreeIterator : public std::iterator<std::input_iterator_tag, AllocatorType>
{
    template<class ValueType, template<class C, class Alloc> class Container> friend class Tree;
public:
    TreeIterator() {}
    TreeIterator(AllocatorType *p) : p(p){}

    typedef typename AllocatorType::value_type value_type;

    bool operator==(const TreeIterator& rhs) const {return p==rhs.p;}
    bool operator!=(const TreeIterator& rhs) const {return p!=rhs.p;}
    value_type& operator*() {return p->value;}
    value_type *operator->() { return &p->value; }

    static TreeIterator end() { return TreeIterator(); }

protected:
    TreeIterator& operator++() { assert(false); return *this; }   // 本类不知道如何遍历
    TreeIterator operator++(int) { assert(false); return TreeIterator(); }

protected:
    AllocatorType *p = nullptr;
};

#endif // TREEITERATOR_H
