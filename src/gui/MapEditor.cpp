// MapEditor.cpp
#include "MapEditor.h"
#include <QVBoxLayout>

MapEditor::MapEditor(QWidget *parent) : QWidget(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    // Настройка панели инструментов
    toolbar = new QToolBar(this);
    addButton = new QPushButton(tr("Добавить"), this);
    removeButton = new QPushButton(tr("Удалить"), this);
    toolbar->addWidget(addButton);
    toolbar->addWidget(removeButton);

    // Слоты для кнопок
    connect(addButton, &QPushButton::clicked, this, &MapEditor::addObject);
    connect(removeButton, &QPushButton::clicked, this, &MapEditor::removeObject);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(toolbar);
    layout->addWidget(view);
    setLayout(layout);

    // TODO: Реализация функционала выбора инструмента
}

void MapEditor::selectTool() {
    // TODO: Реализовать логику выбора инструмента для добавления или удаления объектов
}

void MapEditor::addObject() {
    // Пример добавления прямоугольника на сцену
    QGraphicsRectItem *rect = new QGraphicsRectItem(QRectF(0, 0, 100, 100));
    rect->setBrush(QBrush(Qt::blue));
    scene->addItem(rect);
    currentItem = rect;
    // TODO: Реализовать добавление различных типов объектов в зависимости от выбранного инструмента
}

void MapEditor::removeObject() {
    if (currentItem) {
        scene->removeItem(currentItem);
        delete currentItem;
        currentItem = nullptr;
    }
    // TODO: Улучшить удаление объектов, возможно, добавить подтверждение перед удалением
}