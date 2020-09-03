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
    //ReadWriteFile *txtfile;
    QFile currentlabeltxtfile;

    double zoomFactor;
    bool drawlinemode;

    void ListImgInFolder();
    void ShowImage(const QString &fileName);
    bool eventFilter(QObject *obj, QEvent *event);
    void resizeEvent(QResizeEvent *e);

    void SetEndLine(int mousex, int mousey);
    void SetStartLine(int mousex, int mousey);
    void TempDrawLine(int mousex, int mousey);
    void TempMarkPixel(int mousex, int mouse);
    void TempHilightLine(int tx1, int ty1, int tx2, int ty2);
    void print_scrollbar_value();
    void AddLinePositionToTreeWidget(int px1, int py1, int px2, int py2);
    void AddLinePositionToLabelTxtFile(int px1, int py1, int px2, int py2);
    void WriteNewAllLinePositiontoLabelTxtFile();
    void DrawImageLabel();
    void LoadLabelTxtFile(QString filename);

    bool isconnectScrollbarEvent;
    int x1,y1,x2,y2; // mouse position
    int ix1,iy1,ix2,iy2; //image position
    enum drawlinestate { none, start, end };
    drawlinestate dstate = none;

    int currentSelectingImageIndex;
    int currentSelectingLineIndex;


private slots:
    void Button_deleteline_clicked();
    void Button_openfolder_clicked();
    void Button_selectfolder_clicked();
    void Button_generatelabel_clicked();
    void Button_zoomin_clicked();
    void Button_zoomout_clicked();
    void Button_nextimg_clicked();
    void Button_previmg_clicked();
    void Button_ccwrotation_clicked();
    void Button_cwrotation_clicked();
    void Button_saveimg_clicked();

    void SelectImgFile(QTreeWidgetItem *item, int col);
    void SelectLine(QTreeWidgetItem *item, int col);

    void ZoomImage(double f);
    void on_scroll_h(int value);
    void on_scroll_v(int value);
};

#endif // MAINWINDOW_H
