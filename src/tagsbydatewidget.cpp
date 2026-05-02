#include "tagsbydatewidget.h"

TagsByDateWidget::TagsByDateWidget(QWidget *parent) : QWidget{parent},
    m_mainLay(new QHBoxLayout(this)),
    m_database(Database::instance()),
    m_tagsViewer(new TagsViewer(this))
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("TagsByDateWidget");

    m_mainLay->addWidget(m_tagsViewer);
    connect(m_tagsViewer, &TagsViewer::onTagClicked, this, &TagsByDateWidget::onTagClicked);
}

void TagsByDateWidget::clearDisplayedTags() {
    m_tagsViewer->clearAll();
    m_tagsAndValues.clear();
}

void TagsByDateWidget::updateTagsByDate(QDate date) {
    clearDisplayedTags();

    QMap<int, MarkValue> tags = m_database.getTagsWithMarkValue(date);

    for (const auto& tagId : tags.keys()) {
        QString tagTitle = m_database.getTagTitleById(tagId);

        int markType = m_database.getTagMarkTypeById(tagId);
        switch (markType) {
        case MarkType::WITHOUT:
            break;
        case MarkType::NUMBER:
            tagTitle += (" " + QString::number(tags[tagId].valueInt));
            break;
        }

        QMap<int, QString> tagIdAndTitle;
        tagIdAndTitle.insert(tagId, tagTitle);
        m_tagsViewer->addTag(tagIdAndTitle);

        m_tagsAndValues.insert(tagId, tags[tagId]);
    }
}

void TagsByDateWidget::addTagToSelected(QMap<int, MarkValue> tagAndValue) {
    int tagId = tagAndValue.firstKey();
    if (m_tagsAndValues.contains(tagId)) {
        qDebug() << "TagsByDateWidget::addTagToSelected: тег уже есть " << tagId;
        return;
    }

    QMap<int, QString> tagAndTitle;
    int markType = m_database.getTagMarkTypeById(tagId);
    QString tagTitle = m_database.getTagTitleById(tagId);

    switch (markType) {
    case MarkType::WITHOUT:
        break;
    case MarkType::NUMBER:
        tagTitle += (" " + QString::number(tagAndValue[tagId].valueInt));
        break;
    }

    m_tagsAndValues.insert(tagId, tagAndValue[tagId]);
    tagAndTitle.insert(tagId, tagTitle);
    m_tagsViewer->addTag(tagAndTitle);
}

void TagsByDateWidget::saveTags(QDate date) {
    m_database.updateAllTagsByDate(date, m_tagsAndValues);
}

void TagsByDateWidget::onTagClicked(int tagId) {
    m_tagsAndValues.remove(tagId);
    m_tagsViewer->removeTag(tagId);
}
