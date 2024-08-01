#include "treewidget.hpp"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

/**
 * @brief Constructor to initialize the TreeWidget.
 * @param parent Parent widget.
 */
TreeWidget::TreeWidget(QWidget* parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    this->setScene(scene);
}

/**
 * @brief Displays the tree in the GUI.
 * @param t The tree to display.
 */
void TreeWidget::displayTree(const Tree<double>& t) {
    scene->clear();
    std::queue<std::pair<Node<double>*, int>> q;
    q.push({t.get_root(), 0});
    int y = 0;
    while (!q.empty()) {
        auto [node, x] = q.front();
        q.pop();
        if (node) {
            QGraphicsTextItem* item = scene->addText(QString::number(node->get_value()));
            item->setPos(x * 50, y * 50);
            y++;
            for (size_t i = 0; i < node->children.size(); ++i) {
                q.push({node->children[i], x * 2 + i});
            }
        }
    }
}

/**
 * @brief Main function to run the application.
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    TreeWidget w;
    w.show();
    return a.exec();
}
