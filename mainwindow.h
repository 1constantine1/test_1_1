#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "FileTxt.h"
#include "SortMerge.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    SortMerge *lSortMerge;

private slots:
    void show_loading_error();

    void on_pbLoadFile_clicked();

    void on_pbRun_clicked();

    void on_pushButton_clicked();

    void aaaaaa();

private:
    Ui::MainWindow *ui;

    QThread *mFileThread;
    FileTxt *mFileTxt;


    bool writing_to_file();
};

#endif // MAINWINDOW_H
