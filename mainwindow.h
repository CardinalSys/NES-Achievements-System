#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "getachievements.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void UpdateProcStatusLabel(QString label);
    void setAchievements(const std::list<Achievement>& achievements);
    void GoBackToMain();

private slots:
    void ShowGameInfo();


private:
    Ui::MainWindow *ui;
    std::list<Achievement> achievements;
};



#endif // MAINWINDOW_H
