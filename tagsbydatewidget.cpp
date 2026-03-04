#include "tagsbydatewidget.h"

TagsByDateWidget::TagsByDateWidget(QWidget *parent) : QWidget{parent},
    tagsByDate(new QFlowLayout()),
    database(Database::instance())
{
    setLayout(tagsByDate);
}

void TagsByDateWidget::updateTagsByDate(QDate date) {
    clearDisplayedTags();

    QMap<int, QString> tags = database.getTagsByDate(date);

    for (const auto& tagId : tags.keys()) {
        QPushButton *tag = new QPushButton(tags[tagId]);

        tagsByDate->addWidget(tag);
        displayedTagsIds.append(tagId);
        displayedTagsBtns.append(tag);

        connect(tag, &QPushButton::clicked, this, [this, tag, tagId](){
            tagsByDate->removeWidget(tag);
            displayedTagsIds.removeAll(tagId);
            displayedTagsBtns.removeAll(tag);
            delete tag;

            qDebug() << "";
            qDebug() << "Текущие теги";
            for (int id : displayedTagsIds) {
                qDebug() << id;
            }
        });
    }

    qDebug() << "";
    qDebug() << "Текущие теги";
    for (int id : displayedTagsIds) {
        qDebug() << id;
    }
}

void TagsByDateWidget::clearDisplayedTags() {
    for (const auto& tag : displayedTagsBtns) {
        tagsByDate->removeWidget(tag);
        delete tag;
    }
    displayedTagsBtns.clear();
    displayedTagsIds.clear();
}

void TagsByDateWidget::addTagToSelected(int tagId) {
    QString title = database.getTagTitleById(tagId);

    if (title.isEmpty() || displayedTagsIds.contains(tagId)) {
        return;
    }

    QPushButton *tag = new QPushButton(title);

    displayedTagsIds.append(tagId);
    displayedTagsBtns.append(tag);
    tagsByDate->addWidget(tag);

    qDebug() << "";
    qDebug() << "Текущие теги";
    for (int id : displayedTagsIds) {
        qDebug() << id;
    }

    connect(tag, &QPushButton::clicked, this, [this, tag, tagId](){
        tagsByDate->removeWidget(tag);
        displayedTagsIds.removeAll(tagId);
        displayedTagsBtns.removeAll(tag);
        delete tag;

        qDebug() << "";
        qDebug() << "Текущие теги";
        for (int id : displayedTagsIds) {
            qDebug() << id;
        }
    });
}

void TagsByDateWidget::saveTags(QDate date) {
    database.updateAllTagsByDate(date, displayedTagsIds);
    qDebug() << "";
    qDebug() << "Текущие теги";
    for (int id : displayedTagsIds) {
        qDebug() << id;
    }
}
