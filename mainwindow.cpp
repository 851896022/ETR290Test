#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("打开TS流"), "C:/", tr("TS流文件(*.ts)"));
    ui->lineEdit->setText(fileName);
}

void MainWindow::on_pushButton_2_clicked()
{
    QFile file(ui->lineEdit->text());
    if(file.open(QIODevice::ReadOnly))
    {
        while (1)
        {
            int count = file.read((char*)test290.packet,TS_PACKET_SIZE);
            if(count < TS_PACKET_SIZE)
            {
                break;
            }
            test290.test(test290.packet);
        }

    }
}
