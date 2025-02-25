#pragma once
#include <QPaintEvent>
#include <QtWidgets/QWidget>
#include "ui_VampireSurvivors.h"
#include "Game1.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VampireSurvivorsClass; };
QT_END_NAMESPACE

class VampireSurvivors : public QWidget
{
    Q_OBJECT

public:
    friend class Game1;
    friend class Shop;
    VampireSurvivors(QWidget *parent = nullptr);
    ~VampireSurvivors();


private: 
    Ui::VampireSurvivorsClass *ui;
    Game1* game;
    Settings* set_window;
    int player_type;
    int finished_setting;

protected:
    void paintEvent(QPaintEvent*);
};
