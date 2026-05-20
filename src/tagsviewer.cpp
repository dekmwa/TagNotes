#include "tagsviewer.h"

TagsViewer::TagsViewer(QWidget *parent) : QWidget{parent},
    database(Database::instance()),
    scrollArea(new QScrollArea()), m_mainLay(new QVBoxLayout()), flowLay(new QFlowLayout()), contentWidget(new QWidget()),
    plusButton(nullptr)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("TagsViewer");

    contentWidget->setLayout(flowLay);
    contentWidget->setProperty("type", "contentWidget");
    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setFrameStyle(QFrame::NoFrame);

    m_mainLay->addWidget(scrollArea);

    setupAddTagButton();

    connect(&database, &Database::onConnectDb, this, &TagsViewer::lockAddButton);

    m_mainLay->setContentsMargins(0, 0, 0, 0);
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
    flowLay->addWidget(tagBtn);

    connect(tagBtn, &QPushButton::clicked, [this, tagId](){
        emit onTagClicked(tagId);
    });
}

void TagsViewer::removeTag(int tagId) {
    if (!m_tagsButtons.contains(tagId)) {
        qDebug() << "TagsViewer::addTag - тега нет";
        return;
    }

    flowLay->removeWidget(m_tagsButtons[tagId]);
    delete m_tagsButtons[tagId];
    m_tagsButtons.remove(tagId);

    emit tagRemoved(tagId);
}

void TagsViewer::clearAll() {
    for (auto it = m_tagsButtons.begin(); it != m_tagsButtons.end(); ++it) {
        flowLay->removeWidget(it.value());
        delete it.value();
    }
    m_tagsButtons.clear();
}

void TagsViewer::setupAddTagButton() {
    if (plusButton != nullptr) return;

    plusButton = new QPushButton(this);
    plusButton->setDisabled(true);
    plusButton->hide();
    plusButton->setIcon(QIcon(":/icons/add.svg"));
    plusButton->setFixedSize(40, 40);
    plusButton->setIconSize(QSize(28, 28));
    plusButton->setProperty("type", "addCategory");
    connect(plusButton, &QPushButton::clicked, this, [this](){
        emit addTagClicked();
    });
    plusButton->setObjectName("PlusButton");
    flowLay->addWidget(plusButton);
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
