#ifndef TREENODE_H
#define TREENODE_H

#include <list>

template <class ValueType, template<class C, class Alloc = std::allocator<C> > class Container>
class TreeNode
{
public:
    TreeNode();
    TreeNode(ValueType val) : value(val) {}
    ~TreeNode() { clear(); }

    typedef ValueType value_type;

    inline void clear();
    inline bool isRootNode() const { return parent == nullptr; }

    inline int curDepth() const;
public:
    TreeNode *parent = nullptr;
    Container<TreeNode *> children;
    ValueType value;
};

template<class ValueType, template<class C, class Alloc = std::allocator<C> > class Container>
void TreeNode<ValueType, Container>::clear()
{
    for (auto p : children)
    {
        delete p;
    }

    children.clear();
}

template<class ValueType, template<class C, class Alloc = std::allocator<C> > class Container>
int TreeNode<ValueType, Container>::curDepth() const
{
    int depth = 0;
    TreeNode *p = this;
    while (p != nullptr)
    {
        p = p->parent;
        ++depth;
    }

    return depth;
}

#endif // TREENODE_H
