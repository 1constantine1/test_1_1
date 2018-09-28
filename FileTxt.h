#ifndef FILETXT_H
#define FILETXT_H

#include <QObject>
#include <QList>
#include <QDir>

class QString;
class QFile;


class FileTxt : public QObject {
    Q_OBJECT

public:
    FileTxt(const QString &aPathFileIn);
    ~FileTxt();

    QList<int> get_num(int aIndex);
    QList<int> lItems;

private:
    QString mPathFileIn;
    QString mPathFileOut;
    QDir    mDirFileIn;
    QFile   mFileIn;
    QFile   mFileOut;

    bool open_file_out();


public slots:
    void loading_file();

signals:
    void loading_error();

};

#endif // FILETXT_H
