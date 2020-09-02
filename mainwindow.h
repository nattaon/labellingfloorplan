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
    void TempMarkPixel(int mousex, int mouse);
    void print_scrollbar_value();
    void AddLinePositionToTreeWidget(int px1, int py1, int px2, int py2);
    void DrawImageLabel();

    bool isconnectScrollbarEvent;
    int x1,y1,x2,y2; // mouse position
    int ix1,iy1,ix2,iy2; //image position
    enum drawlinestate { none, start, end };
    drawlinestate dstate = none;

    int currentSelectingLineIndex;


private slots:
    void on_drawline_pushButton_clicked();
    void on_deleteline_pushButton_clicked();
    void on_openfolder_pushButton_clicked();
    void SelectImgFile(QTreeWidgetItem *item, int col);
    void SelectLine(QTreeWidgetItem *item, int col);

    void ZoomImage(double f);
    void on_scroll_h(int value);
    void on_scroll_v(int value);
};

#endif // MAINWINDOW_H
