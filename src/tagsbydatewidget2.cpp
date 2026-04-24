#include "tagsbydatewidget2.h"

TagsByDateWidget2::TagsByDateWidget2(QWidget *parent) : QWidget{parent},
    m_mainLay(new QHBoxLayout(this)),
    database(Database::instance()),
    m_tagsViewer(new TagsViewer(this))
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("TagsByDateWidget");

    m_mainLay->addWidget(m_tagsViewer);
    connect(m_tagsViewer, &TagsViewer::onTagClicked, this, &TagsByDateWidget2::onTagClicked);
}

void TagsByDateWidget2::updateTagsByDate(QDate date) {
    m_tagsViewer->clearAll();

    QMap<int, QString> tags = database.getTagsByDate(date);

    for (const auto& tagId : tags.keys()) {
        //m_tagsViewer->addTag(tagId);
    }
}

void TagsByDateWidget2::addTagToSelected(QMap<int, MarkValue> tagAndValue) {
    //m_tagsViewer->addTag(tagAndValue);
}

void TagsByDateWidget2::saveTags(QDate date) {
    //database.updateAllTagsByDate(date, m_tagsViewer->getTagIds());
}

void TagsByDateWidget2::onTagClicked(int tagId) {
    m_tagsViewer->removeTag(tagId);
}
