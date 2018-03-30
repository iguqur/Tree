#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include <list>
#include <assert.h>
#include "TreeIterator.h"
#include "DepthFirstIterator.h"
#include "BreadthFirstIterator.h"

template <class ValueType, template<class C, class Alloc> class Container = std::list>
class Tree
{
public:
    Tree(){}
    ~Tree(){}

    // Member types:
    typedef ValueType value_type;
    typedef TreeNode<ValueType, Container> node_type;
    typedef TreeIterator<node_type> iterator;
    typedef DepthFirstIterator<node_type> depth_frist_iterator;
    typedef BreadthFirstIterator<node_type> breadth_frist_iterator;

    // Iterators:
    depth_frist_iterator dbegin() const noexcept { return depth_frist_iterator(m_pRoot); }
    depth_frist_iterator dend() const noexcept {
        auto e = depth_frist_iterator::end();
        return e;
    }

    breadth_frist_iterator bbegin() const noexcept { return breadth_frist_iterator(m_pRoot); }
    breadth_frist_iterator bend() const noexcept {
        auto e = breadth_frist_iterator::end();
        return e;
    }

    // operations:
    iterator root() const { return m_pRoot; }
    void setRoot(TreeNode<ValueType, Container> * const &val) { m_pRoot = val; }
    void setRoot(ValueType val);

    // Modifiers:
    void append(iterator position, const ValueType &val);
    void insert(iterator position, const ValueType &val);
    void erase(iterator position);
    void clear();

protected:
    TreeNode<ValueType, Container> *m_pRoot = nullptr;
};

template<class ValueType, template<class C, class Alloc> class Container>
void Tree<ValueType, Container>::setRoot(ValueType val)
{
    TreeNode<ValueType, Container> *pNode = new TreeNode<ValueType, Container>(val);
    pNode->parent = nullptr;
    m_pRoot = pNode;
}

template<class ValueType, template<class C, class Alloc> class Container>
void Tree<ValueType, Container>::append(iterator position, const ValueType &val)
{
    node_type *pNode = new node_type(val);
    pNode->parent = position.p;
    position.p->children.insert(position.p->children.begin(), pNode);
}

template<class ValueType, template<class C, class Alloc> class Container>
void Tree<ValueType, Container>::insert(iterator position, const ValueType &val)
{
    assert(position->parent != nullptr);   // 只允许一个root

    node_type *pNode = new node_type(val);
    pNode->parent = position->parent;
    position->children.insert(position->children.begin(), pNode);
}

template<class ValueType, template<class C, class Alloc> class Container>
void Tree<ValueType, Container>::erase(iterator position)
{
    if (!position->isRootNode())
    {
        position->parent->children.removeOne(position);
    }

    delete position;    // 析构函数会删除其所有的子类
}

template<class ValueType, template<class C, class Alloc> class Container>
void Tree<ValueType, Container>::clear()
{
    if (m_pRoot != nullptr)
    {
        m_pRoot->clear();

        delete m_pRoot;
        m_pRoot = nullptr;
    }
}

#endif // TREE_H
