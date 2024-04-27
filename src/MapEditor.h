// MapEditor.h
#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QToolBar>
#include <QGraphicsItem>

class MapEditor : public QWidget {
    Q_OBJECT

public:
    MapEditor(QWidget *parent = nullptr);

private slots:
    void selectTool(); // Выбор инструмента для редактирования
    void addObject(); // Добавить объект на карту
    void removeObject(); // Удалить объект с карты

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QToolBar *toolbar;
    QPushButton *addButton;
    QPushButton *removeButton;
    QGraphicsItem *currentItem; // Текущий выбранный объект на сцене
};

#endif // MAPEDITOR_H