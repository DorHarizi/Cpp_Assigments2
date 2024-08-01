#include "treewidget.h"
#include <QVBoxLayout>

TreeWidget::TreeWidget(QWidget *parent)
    : QWidget(parent) {
    setupUi();
    displayTree();
}

void TreeWidget::setupUi() {
    treeWidget = new QTreeWidget(this);
    treeWidget->setColumnCount(1);
    treeWidget->setHeaderLabels(QStringList() << "Tree Structure");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(treeWidget);
    setLayout(layout);
}

void TreeWidget::displayTree() {
    // Example Complex tree setup
    Complex c1(1.0, 2.0);
    Complex c2(2.0, 3.0);
    Complex c3(3.0, 4.0);
    Complex c4(4.0, 5.0);
    Complex c5(5.0, 6.0);
    Complex c6(6.0, 7.0);

    Node<Complex> root_complex(c1);
    complexTree.add_root(root_complex);
    complexTree.add_sub_node(root_complex, Node<Complex>(c2));
    complexTree.add_sub_node(root_complex, Node<Complex>(c3));
    complexTree.add_sub_node(Node<Complex>(c2), Node<Complex>(c4));
    complexTree.add_sub_node(Node<Complex>(c2), Node<Complex>(c5));
    complexTree.add_sub_node(Node<Complex>(c3), Node<Complex>(c6));

    auto rootItem = new QTreeWidgetItem(treeWidget);
    rootItem->setText(0, QString::fromStdString(complexTree.begin_pre_order()->get_value().to_string()));

    std::function<void(QTreeWidgetItem*, std::shared_ptr<Node<Complex>>)> addChildren = 
        [&](QTreeWidgetItem *parentItem, std::shared_ptr<Node<Complex>> node) {
        for (auto &child : node->children) {
            auto childItem = new QTreeWidgetItem(parentItem);
            childItem->setText(0, QString::fromStdString(child->get_value().to_string()));
            addChildren(childItem, child);
        }
    };

    addChildren(rootItem, complexTree.find_node(complexTree.begin_pre_order().operator->(), c1));
}
