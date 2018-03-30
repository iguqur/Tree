#include <QCoreApplication>

#include "Tree.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Tree<string> tree;
    tree.setRoot("root");

    tree.append(tree.root(), "frist");

    for (auto it = tree.dbegin(); it != tree.dend(); ++it)
    {
        cout << *it << endl;
    }

//    for (auto it = tree.bbegin(); it != tree.bend(); ++it)
//    {
//        cout << *it << endl;
//    }

    return a.exec();
}
