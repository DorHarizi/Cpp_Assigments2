#pragma once

#include <QGraphicsView>
#include "tree.hpp"

/**
 * @brief A class to represent the GUI for displaying the k-ary tree.
 */
class TreeWidget : public QGraphicsView {
    Q_OBJECT

public:
    /**
     * @brief Constructor to initialize the TreeWidget.
     * @param parent Parent widget.
     */
    TreeWidget(QWidget* parent = nullptr);

    /**
     * @brief Displays the tree in the GUI.
     * @param t The tree to display.
     */
    void displayTree(const Tree<double>& t);

private:
    QGraphicsScene* scene;  ///< Scene to display the tree nodes.
};