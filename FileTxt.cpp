#include "FileTxt.h"

#include <QString>
#include <QList>
#include <QFileDialog>
#include <QStringList>
#include <QTextStream>
#include <QMessageBox>

#include <QDebug>


FileTxt::FileTxt(const QString &aPathFileIn) :
    mPathFileIn(aPathFileIn), mPathFileOut(QString()), mDirFileIn(QString()) {

}

FileTxt::~FileTxt() {

}

void FileTxt::loading_file() {
    bool isOk = false;
    QFileDialog lFileDlg;
    lFileDlg.setAcceptMode(QFileDialog::AcceptOpen);
    lFileDlg.setFileMode(QFileDialog::ExistingFile);
    lFileDlg.setNameFilter(tr("*.txt"));
    lFileDlg.setViewMode(QFileDialog::Detail);
    if (mDirFileIn.isEmpty())
        lFileDlg.setDirectory(QDir::currentPath());
    else
        lFileDlg.setDirectory(mDirFileIn);

    if (lFileDlg.exec() == QDialog::Accepted) {
        QStringList lFiles = lFileDlg.selectedFiles();
        if (lFiles.length() == 1) {
            mPathFileIn = lFiles.at(0);
            mDirFileIn = lFileDlg.directory();
            isOk = open_file_out();
        } else {
            isOk = false;
        }
    } else {
        isOk = false;
    }
    if (!isOk)
        emit loading_error();
}

bool FileTxt::open_file_out() {
    QString lFilePathOut = mPathFileIn.remove(mPathFileIn.lastIndexOf("."), 4) + "_test_1.txt";
    if (mFileOut.exists())
        mFileOut.remove();
    QFile::copy(mPathFileIn.append(".txt"), lFilePathOut);
    mFileOut.setFileName(lFilePathOut);
    if(!mFileOut.open(QIODevice::ReadWrite))
        return false;
    else
        return true;

    return true;

    //    mFileIn.setFileName(mPathFileIn);
    //    if(!mFileIn.open(QIODevice::ReadOnly)) {
    //        return false;
    //    } else {
    //        QTextStream lTextStreamOut(&mFileIn);
    //        QChar   lChar   = ' ';
    //        QString lNumStr = QString();
    //        int     lNumInt = 0;

    //        while (!lTextStreamOut.atEnd()) {
    //            lTextStreamOut >> lChar;
    //            if (lChar == ' ') {
    //                lItems.push_back(lNumInt);
    //                lNumStr = QString();
    //            } else {
    //                lNumStr += QString(lChar);
    //                lNumInt = lNumStr.toInt();
    //                QString aa1(lChar);
    //            }
    //        }
    //        lItems.push_back(lNumInt);

    //        return true;
    //    }
}



QList<int> FileTxt::get_num(int aIndex) {
    QTextStream lTextStream(&mFileOut);
    QChar   lChar   = ' ';
    QString lNumStr = QString();
    int     lNumInt = 0;

    bool lSpace = true;
    while (!lTextStream.atEnd()) {
        lTextStream >> lChar;

        if (!lChar.isDigit()) {
            if (!lSpace) {
                lItems.push_back(lNumInt);
                lNumStr = QString();
                lSpace = true;
            }
        } else {
            lNumStr += QString(lChar);
            lNumInt = lNumStr.toInt();
            QString aa1(lChar);
            lSpace = false;
        }
    }
    lItems.push_back(lNumInt);

//    qDebug() << lItems;

    return lItems;
}
