#include "tagsviewer.h"

TagsViewer::TagsViewer(QWidget *parent) : QWidget{parent},
    database(Database::instance()),
    m_mainLay(new QFlowLayout()),
    plusButton(nullptr)
{
    setupAddTagButton();
    setLayout(m_mainLay);
}

void TagsViewer::addTag(int tagId) {
    if (m_tags.contains(tagId)) {
        qDebug() << "TagsViewer::addTag - тег уже есть";
        return;
    }

    QString title = database.getTagTitleById(tagId);
    if (title.isEmpty()) {
        qDebug() << "TagsViewer::addTag - тег не найден";
        return;
    }

    QPushButton *tagBtn = new QPushButton();
    tagBtn->setText(title);

    m_tags.insert(tagId, tagBtn);
    m_mainLay->addWidget(tagBtn);

    connect(tagBtn, &QPushButton::clicked, [this, tagId](){
        emit tagClicked(tagId);
    });
}

void TagsViewer::removeTag(int tagId) {
    if (!m_tags.contains(tagId)) {
        qDebug() << "TagsViewer::addTag - тега нет";
        return;
    }

    m_mainLay->removeWidget(m_tags[tagId]);
    delete m_tags[tagId];
    m_tags.remove(tagId);

    emit tagRemoved(tagId);
}

void TagsViewer::clearAll() {
    for (auto it = m_tags.begin(); it != m_tags.end(); ++it) {
        m_mainLay->removeWidget(it.value());
        delete it.value();
    }
    m_tags.clear();
}

QVector<int> TagsViewer::getTagIds() {
    QVector<int> ids;
    for (auto it = m_tags.begin(); it != m_tags.end(); ++it) {
        ids.append(it.key());
    }
    return ids;
}

void TagsViewer::setupAddTagButton() {
    if (plusButton != nullptr) return;

    plusButton = new QPushButton(this);
    plusButton->setText("+");
    plusButton->setDisabled(true);
    plusButton->hide();
    plusButton->setFixedWidth(25);
    connect(plusButton, &QPushButton::clicked, this, [this](){
        emit addTagClicked();
    });
    m_mainLay->addWidget(plusButton);
}

void TagsViewer::unlockAddButton() {
    if (plusButton != nullptr) plusButton->setDisabled(false);
}

void TagsViewer::showAddTagButton() {
    if (plusButton != nullptr) plusButton->show();
}
