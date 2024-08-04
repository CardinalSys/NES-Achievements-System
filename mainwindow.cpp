#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->zeldaBtn, &QPushButton::clicked, this, &MainWindow::ShowGameInfo);

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
        QPushButton *achievementButton = new QPushButton(this);
        achievementButton->setStyleSheet("border-image: url(':/new/prefix1/zeldaCover.png') 0 0 0 0 stretch stretch;"
                                         "height: 100px; width: 80px;"
                                         "min-width: 80px; max-width: 80px;"
                                         "min-height: 100px; max-height: 100px;");
        achievementButton->setToolTip(QString::fromStdString(achievement.name));  // Tooltip with achievement name

        gridLayout->addWidget(achievementButton, row, column);
        column++;
        if (column >= 4) {  // Assuming 4 columns
            column = 0;
            row++;
        }
    }
}
