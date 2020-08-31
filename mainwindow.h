#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QImage>
#include <QMessageBox>
#include <QImageReader>
#include <QtWidgets>
#include <QtMath>
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString currentlyOpenedDir;
    QImage image;
    QPixmap rawimage,tempimage,currentimage;
    double zoomFactor;
    bool drawlinemode;

    void refreshImgView();
    void loadImage(const QString &fileName);
    bool eventFilter(QObject *obj, QEvent *event);
    void SetEndLine(int mousex, int mousey);
    void SetStartLine(int mousex, int mousey);
    void TempDrawLine(int mousex, int mousey);
    int x1,y1,x2,y2;
    enum drawlinestate { none, start, end };
    drawlinestate dstate = none;


private slots:
    void on_drawline_pushButton_clicked();
    void on_openfolder_pushButton_clicked();
    void PressedTreeItem(QTreeWidgetItem *item, int col);
    void setZoomFactor(double f);

};

#endif // MAINWINDOW_H
