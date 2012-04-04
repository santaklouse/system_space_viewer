#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDir>
#include <QtCore>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    QString root_path;
    
private:
    Ui::MainWindow *ui;
    QFileInfoList readRoot();
    QFileInfoList getSubDirs( QString path );
    QVariantList readDir(const QFileInfo &dir );
    quint32 listFolder ( QString path );
};

#endif // MAINWINDOW_H
