#include "tagsviewer.h"

TagsViewer::TagsViewer(QWidget *parent) : QWidget{parent},
    database(Database::instance()),
    m_mainLay(new QFlowLayout()),
    plusButton(nullptr)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("TagsViewer");

    setupAddTagButton();

    connect(&database, &Database::onConnectDb, this, &TagsViewer::lockAddButton);

    setLayout(m_mainLay);
}

void TagsViewer::addTag(QMap<int, QString> tagIdAndTitle) {
    int tagId = tagIdAndTitle.firstKey();

    if (m_tagsButtons.contains(tagId)) {
        qDebug() << "TagsViewer::addTag - тег уже есть";
        return;
    }

    QPushButton *tagBtn = new QPushButton();
    tagBtn->setText(tagIdAndTitle[tagId]);

    m_tagsButtons.insert(tagId, tagBtn);
    m_mainLay->addWidget(tagBtn);

    connect(tagBtn, &QPushButton::clicked, [this, tagId](){
        emit onTagClicked(tagId);
    });
}

void TagsViewer::removeTag(int tagId) {
    if (!m_tagsButtons.contains(tagId)) {
        qDebug() << "TagsViewer::addTag - тега нет";
        return;
    }

    m_mainLay->removeWidget(m_tagsButtons[tagId]);
    delete m_tagsButtons[tagId];
    m_tagsButtons.remove(tagId);

    emit tagRemoved(tagId);
}

void TagsViewer::clearAll() {
    for (auto it = m_tagsButtons.begin(); it != m_tagsButtons.end(); ++it) {
        m_mainLay->removeWidget(it.value());
        delete it.value();
    }
    m_tagsButtons.clear();
}

// QMap<int, MarkValue> TagsViewer::getTagIds() {
    //return m_tagsMarks;
// }

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
    plusButton->setObjectName("PlusButton");
    m_mainLay->addWidget(plusButton);
}

void TagsViewer::unlockAddButton() {
    if (plusButton != nullptr) plusButton->setDisabled(false);
}

void TagsViewer::lockAddButton() {
    if (plusButton != nullptr) plusButton->setDisabled(true);
}

void TagsViewer::showAddTagButton() {
    if (plusButton != nullptr) plusButton->show();
}
