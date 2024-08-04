#include "mainwindow.h"
#include "proc.c"
#include <QApplication>
#include "getachievements.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    struct Process proc = GetProcessByName("Mesen.exe");
    if(proc.pid != 0){
        w.UpdateProcStatusLabel("Mesen.exe was hooked");

        std::list<Achievement> achievements;
        GetAchievements getAchievements(achievements);
        for (const auto& achievement : achievements) {
            qDebug() << "Achievement Name:" << QString::fromStdString(achievement.name);

        }

    }
    return a.exec();
}


