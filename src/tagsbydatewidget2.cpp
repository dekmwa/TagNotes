#include "tagsbydatewidget2.h"

TagsByDateWidget2::TagsByDateWidget2(QWidget *parent) : QWidget{parent},
    m_mainLay(new QHBoxLayout(this)),
    database(Database::instance()),
    m_taskViewer(new TagsViewer(this))
{
    m_mainLay->addWidget(m_taskViewer);
    connect(m_taskViewer, &TagsViewer::tagClicked, this, &TagsByDateWidget2::onTagClicked);
}

void TagsByDateWidget2::updateTagsByDate(QDate date) {
    m_taskViewer->clearAll();

    QMap<int, QString> tags = database.getTagsByDate(date);

    for (const auto& tagId : tags.keys()) {
        m_taskViewer->addTag(tagId);
    }
}

void TagsByDateWidget2::addTagToSelected(int tagId) {
    m_taskViewer->addTag(tagId);
}

void TagsByDateWidget2::saveTags(QDate date) {
    database.updateAllTagsByDate(date, m_taskViewer->getTagIds());
}

void TagsByDateWidget2::onTagClicked(int tagId) {
    m_taskViewer->removeTag(tagId);
}
