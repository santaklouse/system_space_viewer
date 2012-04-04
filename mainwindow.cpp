#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <mntent.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    foreach(const QFileInfo &dir, MainWindow::readRoot())
    {
        if ( ! dir.isDir() || ! dir.isRoot())
            continue;

        QString info = dir.absolutePath() + dir.fileName();
        if (dir.isRoot()) {
            qDebug() << "Disk: " + info.toLocal8Bit();
            MainWindow::readDir(dir);
        }
    }
}

QFileInfoList MainWindow::readRoot() {
    qDebug() << "reading root ...";

    QFileInfoList dirContent;

#ifdef Q_OS_LINUX
    struct mntent *fs;
    FILE *fp;

    if (fopen ("/etc/mtab" , "r") != NULL) {
        fp = setmntent("/etc/mtab","r");
    } else {
        fp = setmntent("/proc/mounts","r");
    }
//    int i = 0;
    while ((fs = getmntent(fp))  !=  NULL)
    {

        if ( ! strstr(fs->mnt_fsname, "/dev"))
            continue;
        qDebug() <<
              " fs_name: " + (QString)fs->mnt_fsname + " "
            + " mount_path: " + (QString)fs->mnt_dir
            + " mnt_type: " + fs->mnt_type;
//            + " mnt_opts: " + (QString)fs->mnt_opts
//            + " mnt_freq: " + (QString)fs->mnt_freq
//            + " mnt_passno: " + (QString)fs->mnt_passno;
//        QFileInfo *file = fs;
//        dirContent.insert(i, file);
//        i++;
    }

#elif defined(Q_OS_WIN32)
    dirContent = QDir::drives()
#endif

    return dirContent;
}

QFileInfoList MainWindow::getSubDirs(QString path) {
    QDir dir;
    dir.cd(path);
    QFileInfoList dirContent = dir.entryInfoList(
        QStringList(),
        QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::NoSymLinks
    );
    return dirContent;
}

QVariantList MainWindow::readDir(const QFileInfo &dir) {
    QVariantList info;
    QString path = dir.absolutePath() + dir.fileName();
    QFileInfoList root_items = MainWindow::getSubDirs(path);

    int i = 0;
    foreach(QFileInfo fs_item, root_items)
    {
        if ( ! fs_item.isDir() || fs_item.isRoot())
            continue;

        QString data = fs_item.absolutePath() + fs_item.fileName();
        qDebug() << data.toLocal8Bit();// << "Size: " + QString::number(listFolder(data.toLocal8Bit()));
        info.insert(i++, data.toLocal8Bit());
    }
    return info;
}

quint32 MainWindow::listFolder ( QString path ) {
    QDir currentFolder( path );

    quint32 totalsize = 0;

    currentFolder.setFilter( QDir::Dirs | QDir::Files | QDir::NoSymLinks );
    currentFolder.setSorting( QDir::Name );

    QFileInfoList folderitems( currentFolder.entryInfoList() );

    foreach ( QFileInfo i, folderitems ) {
        QString iname( i.fileName() );
        if ( iname == "." || iname == ".." || iname.isEmpty() )
            continue;

        if ( i.isDir() )
            totalsize += listFolder( path+"/"+iname );
        else
            totalsize += i.size();
    }
    return totalsize;
}

MainWindow::~MainWindow()
{
    delete ui;
}
