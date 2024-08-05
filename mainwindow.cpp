#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->zeldaBtn, &QPushButton::clicked, this, &MainWindow::ShowGameInfo);
    connect(ui->returnToMainBtn, &QPushButton::clicked, this, &MainWindow::GoBackToMain);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateProcStatusLabel(QString label){
    ui->procStatus->setText(label);
}

void MainWindow::setAchievements(const std::list<Achievement>& achievements) {
    this->achievements = achievements;
}

void MainWindow::ShowGameInfo()
{
    ui->stackedWidgetView->setCurrentIndex(1);

    QGridLayout *gridLayout = ui->achievementsLayout;

    int row = 0;
    int column = 0;
    qDebug("1");
    for (const auto& achievement : achievements) {
        qDebug() << "Achievement Name:" << QString::fromStdString(achievement.name);
        QLabel *achievementLabel = new QLabel(this);
        achievementLabel->setFixedWidth(100);
        achievementLabel->setFixedHeight(100);
        QPixmap pix(":/new/prefix1/zeldaCover.png");
        int w = achievementLabel->width ();
        int h = achievementLabel->height ();
        achievementLabel->setPixmap (pix.scaled (w,h,Qt::KeepAspectRatio));

        achievementLabel->setToolTip(QString::fromStdString(achievement.name));

        gridLayout->addWidget(achievementLabel, row, column);
        column++;
        if (column >= 4) {
            column = 0;
            row++;
        }
        //Add a tooltip
    }
}

void MainWindow::GoBackToMain(){
    ui->stackedWidgetView->setCurrentIndex(0);
}
