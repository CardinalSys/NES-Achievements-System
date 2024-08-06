#include "mainwindow.h"
#include "proc.c"
#include <QApplication>
#include "getachievements.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    char outPath[MAX_PATH];
    HANDLE handle = OpenProcessByName("Mesen.exe", outPath);
    if (handle != NULL) {
        w.UpdateProcStatusLabel("Mesen.exe was hooked");
    } else {
        w.UpdateProcStatusLabel("Failed to hook Mesen.exe");
    }
    std::list<Achievement> achievements;
    GetAchievements getAchievements(achievements);
    w.setAchievements(achievements);

    return a.exec();
}


