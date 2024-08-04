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
        char testName[256] = {0}; // Initialize a buffer for the name
        GetAchievements getAchievements(testName);
    }
    return a.exec();
}


