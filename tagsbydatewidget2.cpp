#include "tagsbydatewidget2.h"

TagsByDateWidget2::TagsByDateWidget2(QWidget *parent) : QWidget{parent}, database(Database::instance()),
    m_taskViewer(new TagsViewer())
{

}

void TagsByDateWidget2::updateTagsByDate(QDate date) {
    m_taskViewer->clearAll();

    QMap<int, QString> tags = database.getTagsByDate(date);

    for (const auto& tagId : tags.keys()) {
        m_taskViewer->addTag(tagId);

        connect(m_taskViewer, &TagsViewer::tagClicked, [this, tagId](){
            m_taskViewer->removeTag(tagId);
        });
    }
}

void TagsByDateWidget2::addTagToSelected(int tagId) {
    m_taskViewer->addTag(tagId);

    connect(m_taskViewer, &TagsViewer::tagClicked, [this, tagId](){
        m_taskViewer->removeTag(tagId);
    });
}

void TagsByDateWidget2::saveTags(QDate date) {
    database.updateAllTagsByDate(date, m_taskViewer->getTagIds());
}
