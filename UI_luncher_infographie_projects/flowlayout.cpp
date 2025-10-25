#include "flowlayout.h"

#include <QtWidgets>

FlowLayout::FlowLayout(QWidget *parent, int margin, int hSpacing, int vSpacing)
    : QLayout(parent), m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::FlowLayout(int margin, int hSpacing, int vSpacing)
    : m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::~FlowLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void FlowLayout::addItem(QLayoutItem *item)
{
    itemList.append(item);
}

int FlowLayout::horizontalSpacing() const
{
    if (m_hSpace >= 0) return m_hSpace;
    return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
}

int FlowLayout::verticalSpacing() const
{
    if (m_vSpace >= 0) return m_vSpace;
    return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
}

int FlowLayout::count() const
{
    return itemList.size();
}

QLayoutItem *FlowLayout::itemAt(int index) const
{
    return itemList.value(index);
}

QLayoutItem *FlowLayout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size())
        return itemList.takeAt(index);
    return nullptr;
}

Qt::Orientations FlowLayout::expandingDirections() const
{
    return Qt::Orientations();
}

bool FlowLayout::hasHeightForWidth() const
{
    return true;
}

int FlowLayout::heightForWidth(int width) const
{
    return doLayout(QRect(0, 0, width, 0), true);
}

void FlowLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

QSize FlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize FlowLayout::minimumSize() const
{
    QSize size;
    for (QLayoutItem *item : itemList)
        size = size.expandedTo(item->minimumSize());

    QMargins m = contentsMargins();
    size += QSize(m.left() + m.right(), m.top() + m.bottom());
    return size;
}

int FlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int hSpace = horizontalSpacing();
    if (hSpace == -1) hSpace = 6;
    int vSpace = verticalSpacing();
    if (vSpace == -1) vSpace = 6;

    // First pass: compute rows and their minimal heights
    QVector<QVector<QLayoutItem*>> rows;
    QVector<int> rowHeights;

    int x = rect.x();
    int y = rect.y();
    int lineHeight = 0;
    QVector<QLayoutItem*> currentRow;

    int right = rect.right();

    for (QLayoutItem *item : itemList) {
        int nextX = x + item->sizeHint().width() + hSpace;
        if (!currentRow.isEmpty() && nextX - hSpace > right) {
            // finalize current row
            rows.push_back(currentRow);
            rowHeights.push_back(lineHeight);
            currentRow.clear();
            x = rect.x();
            y = y + lineHeight + vSpace;
            lineHeight = 0;
        }
        currentRow.push_back(item);
        x = (currentRow.size() == 1) ? rect.x() + item->sizeHint().width() + hSpace : nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
    }
    if (!currentRow.isEmpty()) {
        rows.push_back(currentRow);
        rowHeights.push_back(lineHeight);
    }

    // Minimal total height of content
    int minimalTotalHeight = 0;
    for (int h : rowHeights) minimalTotalHeight += h;
    if (!rows.isEmpty()) minimalTotalHeight += vSpace * (rows.size() - 1);

    if (testOnly) {
        // Return minimal height needed given the width
        return minimalTotalHeight;
    }

    // Second pass: lay out items, distributing extra vertical space per row
    int extra = rect.height() - minimalTotalHeight;
    int rowCount = rows.size();
    int extraPerRow = (rowCount > 0 && extra > 0) ? (extra / rowCount) : 0;

    int curY = rect.y();
    for (int r = 0; r < rowCount; ++r) {
        const auto &row = rows[r];
        int targetHeight = rowHeights[r] + extraPerRow;
        int curX = rect.x();
        for (QLayoutItem *item : row) {
            QSize hint = item->sizeHint();
            QRect g(curX, curY, hint.width(), targetHeight);
            item->setGeometry(g);
            curX += hint.width() + hSpace;
        }
        curY += targetHeight + vSpace;
    }

    return qMax(rect.y() + rect.height(), curY) - rect.y();
}

int FlowLayout::smartSpacing(QStyle::PixelMetric pm) const
{
    QObject *parent = this->parent();
    if (!parent) return -1;
    if (parent->isWidgetType()) {
        QWidget *pw = static_cast<QWidget *>(parent);
        return pw->style()->pixelMetric(pm, nullptr, pw);
    }
    return static_cast<QLayout *>(parent)->spacing();
}
