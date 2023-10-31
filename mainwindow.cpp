#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);
    ui->label->setAcceptDrops(false);
    ui->label->setAlignment(Qt::AlignCenter);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }

    QString filePath = urls.first().toLocalFile();
    if (filePath.isEmpty()) {
        return;
    }

    // ここでfilePathに対する画像の読み込みを行い、ラベルに表示する
    QImage image(filePath);
    ui->label->setText("FilePath : " + filePath);

    //pixmapSize : 画像のサイズ, size : Pictureラベル
    QPixmap pixmap(filePath);
    QSize   size = ui->Picture->size();
    QSize   pixmapSize = pixmap.size();

    if(pixmapSize.width() > pixmapSize.height()){
        pixmap = pixmap.scaled(QSize(size.width(), int(pixmapSize.height() * size.width() / pixmapSize.width())), Qt::KeepAspectRatio);
    } else if(pixmapSize.width() < pixmapSize.height()){
        pixmap = pixmap.scaled(QSize(int(pixmapSize.width() * size.height() / pixmapSize.height()), size.height()), Qt::KeepAspectRatio);
    } else if(pixmapSize.width() == pixmapSize.height()){
        pixmap = pixmap.scaled(size, Qt::KeepAspectRatio);
    }

    // 画像を読み込んで、Pictureに表示する
    ui->Picture->setPixmap(pixmap);

    // 中心に表示する
    int x = (size.width()  - pixmap.width())  / 2;
    int y = (size.height() - pixmap.height()) / 2;
    ui->Picture->setContentsMargins(x, y, x, y);


}
