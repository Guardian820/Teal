// Copyright (C) 2016 Samy Bensaid
// This file is part of the Teal game.
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QPushButton>
#include <QPointer>
#include <QFrame>

#include "graphicsscene.h"
#include "buttons.h"

class MainWindow : public QFrame
{
public:
    MainWindow(QWidget* parent, const QSize& scenesize, const QSize& winsize);
    ~MainWindow() = default;

private:
    anax::World m_world;
    GraphicsScene m_scene;
    Buttons m_buttonBar;
    QGraphicsView* m_view{};
};

#endif // MAINWINDOW_H
