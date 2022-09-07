#include <QCoreApplication>
#include <QDir>
#include <QDebug>

int removeObjDir(const QString &strPath)
{
    int nFlag = 0;
    QDir dir(strPath);

    if((dir.entryList(QStringList()
                      << "*.h"
                      << "*.cpp"
                      << "*.ui"
                      << "*.lib"
                      << "*.dll"
                      << "*.exe"
                      << "*.wav"
                      << "*.xml"
                      << "*.qrc"
                      << "*.qss"
                      << "*.png"
                      << "*.jpg"
                      << "*.ico"
                      ,QDir::Files).length() > 0))
    {
        nFlag++;
    }

    QStringList ltDir = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < ltDir.size(); ++i)
    {
        QString strSubPath = QString("%1/%2").arg(dir.absolutePath()).arg(ltDir[i]);
        if( removeObjDir(strSubPath) > 0)
        {
            nFlag++;
        }
    }

    if(nFlag < 1)
    {
        bool bSuccess = QDir(strPath).removeRecursively();
        qDebug() << "delete" << bSuccess << strPath;
    }
    else
    {
        QStringList ltDeleted = dir.entryList(QStringList()
                                              << "*.obj"
                                              << "vc*.pdb"
                                              << "*.tlog"
                                              << "*.ipch"
                                              << "*.VC.db"
                                              ,QDir::Files);
        foreach (QString df, ltDeleted) {
            QString strSubFile = QString("%1/%2").arg(dir.absolutePath()).arg(df);
            bool bSuccess = dir.remove(strSubFile);
            qDebug() << "delete" << bSuccess << strSubFile;
        }
    }

    return nFlag;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.addLibraryPath("D:/Qt/Qt5.9.7/5.9.7/msvc2015/bin");
    for(int i=0; i<argc; i++)
    {
        qDebug() << argv[i];
    }

    QStringList ltDeleteDir;
    ltDeleteDir << "debug" << "release";

    QString strDeleteDir = argc > 1 ? argv[1] : QDir().currentPath();
    removeObjDir(strDeleteDir);

    qDebug() << "done";
    return a.exec();
}
