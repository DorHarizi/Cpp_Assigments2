#pragma once

#include <QWidget>
#include <QTreeWidget>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

/**
 * @class TreeWidget
 * @brief A Qt widget for displaying a tree structure.
 */
class TreeWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructor to initialize the TreeWidget.
     * @param parent The parent widget.
     */
    TreeWidget(QWidget *parent = nullptr);

private:
    /**
     * @brief Setup the user interface.
     */
    void setupUi();

    /**
     * @brief Display the tree structure.
     */
    void displayTree();

    QTreeWidget *treeWidget;  ///< The QTreeWidget to display the tree.
    Tree<Complex> complexTree;  ///< The tree of complex numbers.
};
