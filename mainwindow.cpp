#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QThread>
#include <QDebug>

#include "SortMerge.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->lePathFile->setReadOnly(true);


/////////////test_8



}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_pbLoadFile_clicked() {
//    mFileThread   = new QThread;
    mFileTxt      = new FileTxt(ui->lePathFile->text());

    mFileTxt->loading_file();

//    mFileTxt->moveToThread(mFileThread);
//    connect(mFileTxt,    SIGNAL(loading_error()), this,     SLOT(show_loading_error()));
//    connect(mFileThread, SIGNAL(started()),       mFileTxt, SLOT(loading_file()));
//    mFileThread->start();

    qDebug() << "idealThreadCount = " << QThread::idealThreadCount();
}




void MainWindow::on_pbRun_clicked() {
    QList<int> items = mFileTxt->get_num(0);

    lSortMerge  = new SortMerge();
    lSortMerge->mMaxThread = QThread::idealThreadCount();
    lSortMerge->items = items;
    connect(lSortMerge, SIGNAL(finished()), this, SLOT(aaaaaa()));
    lSortMerge->sort();



//    QList<int> items = mFileTxt->get_num(0);

//    SortMerge *lSortMerge  = new SortMerge();
//    QThread   *lThreadSort = new QThread;
//    lSortMerge->items = items;
//    lSortMerge->moveToThread(lThreadSort);
//    connect(lThreadSort, SIGNAL(started()), lSortMerge, SLOT(sort()));
//    lThreadSort->start();
//    lThreadSort->wait();

//    qDebug() << items;
}

void MainWindow::aaaaaa() {
    qDebug() << "Obshee = " << lSortMerge->items;
}


bool MainWindow::writing_to_file() {

//    QString lFilepathTest = mDirFile.absolutePath() + "temp_test_1.txt";
//    mFileOut.setFileName(lFilepathTest);
//    if (mFileOut.exists())
//        mFileOut.remove();
//    if(!mFileOut.open(QIODevice::WriteOnly)) {
//        QMessageBox::warning(this, tr("Error"), tr("Error opening file Test"));
//        return false;
//    }

//    QTextStream lTextStreamOut(&mFileOut);

//    for (int row = 0; row < 100000; ++row)
//        lTextStreamOut << std::rand() << " " << std::rand();

//    mFileOut.close();
//    return true;
    return true;
}

void MainWindow::on_pushButton_clicked()
{
    ui->progressBar->setValue(500);
}

void MainWindow::show_loading_error() {
    QMessageBox::warning(this, tr("Error"), tr("Error loading file"));
}
