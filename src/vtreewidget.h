#ifndef VTREEWIDGET_H
#define VTREEWIDGET_H

#include <QTreeWidget>

#include "vsimplesearchinput.h"

class QDropEvent;
class VStyledItemDelegate;
class QTimer;
class QGraphicsOpacityEffect;

// QTreeWidget won't emit the rowsMoved() signal after drag-and-drop.
// VTreeWidget will emit rowsMoved() signal.
class VTreeWidget : public QTreeWidget, public ISimpleSearch
{
    Q_OBJECT
public:
    explicit VTreeWidget(QWidget *p_parent = nullptr, bool searchToggle = true);

    // Clear tree widget as well as other data.
    void clearAll();

    void setSimpleSearchMatchFlags(Qt::MatchFlags p_flags);

    Qt::MatchFlags getSimpleSearchMatchFlags() const;

    // Implement ISimpleSearch.
    virtual QList<void *> searchItems(const QString &p_text,
                                      Qt::MatchFlags p_flags) const Q_DECL_OVERRIDE;

    virtual void highlightHitItems(const QList<void *> &p_items) Q_DECL_OVERRIDE;

    virtual void clearItemsHighlight() Q_DECL_OVERRIDE;

    virtual void selectHitItem(void *p_item) Q_DECL_OVERRIDE;

    virtual int totalNumberOfItems() Q_DECL_OVERRIDE;

    virtual void selectNextItem(bool p_forward) Q_DECL_OVERRIDE;

    virtual void selectParentItem();

    void setFitContent(bool p_enabled);

    QTreeWidgetItem *getItemFromIndex(const QModelIndex &p_index) const;

    // Next visible item.
    static QTreeWidgetItem *nextItem(const QTreeWidget* p_tree,
                                     QTreeWidgetItem *p_item,
                                     bool p_forward);

    // Whether @p_tree is expanded.
    static bool isTreeExpanded(const QTreeWidget *p_tree);

    static void expandCollapseAll(QTreeWidget *p_tree);

    static const QTreeWidgetItem *topLevelTreeItem(const QTreeWidgetItem *p_item);

    static int childIndexOfTreeItem(const QTreeWidgetItem *p_item);

protected:
    void keyPressEvent(QKeyEvent *p_event) Q_DECL_OVERRIDE;

    void resizeEvent(QResizeEvent *p_event) Q_DECL_OVERRIDE;

    void dropEvent(QDropEvent *p_event) Q_DECL_OVERRIDE;

signals:
    // Rows [@p_first, @p_last] were moved to @p_row.
    void rowsMoved(int p_first, int p_last, int p_row);

    void itemExpandedOrCollapsed();

private slots:
    void handleSearchModeTriggered(bool p_inSearchMode, bool p_focus);

    void handleSearchInputTextChanged(const QString &p_text);

private:
    // Show or hide search input.
    void setSearchInputVisible(bool p_visible);

    QGraphicsOpacityEffect *getSearchInputEffect() const;

    static QTreeWidgetItem *nextSibling(const QTreeWidget *p_widget,
                                        QTreeWidgetItem *p_item,
                                        bool p_forward);

    bool m_searchToggle = true;
    VSimpleSearchInput *m_searchInput;

    VStyledItemDelegate *m_delegate;

    QTimer *m_searchColdTimer;
    QTimer *m_expandTimer;

    bool m_fitContent;
};

inline void VTreeWidget::setSimpleSearchMatchFlags(Qt::MatchFlags p_flags)
{
    m_searchInput->setMatchFlags(p_flags);
}

inline Qt::MatchFlags VTreeWidget::getSimpleSearchMatchFlags() const
{
    return m_searchInput->getMatchFlags();
}

inline void VTreeWidget::setFitContent(bool p_enabled)
{
    m_fitContent = p_enabled;
    setSizeAdjustPolicy(m_fitContent ? QAbstractScrollArea::AdjustToContents
                                     : QAbstractScrollArea::AdjustIgnored);
}

inline QTreeWidgetItem *VTreeWidget::getItemFromIndex(const QModelIndex &p_index) const
{
    return itemFromIndex(p_index);
}
#endif // VTREEWIDGET_H
