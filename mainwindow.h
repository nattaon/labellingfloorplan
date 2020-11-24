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
#include <QLineF>

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
    bool isLineWidgetEditable;
    bool isLoadingLabel;
    bool lineConnectMode;


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
    void Add_Line_to_TreeWidget(int px1, int py1, int px2, int py2);
    void Add_Line_to_Textfile(int px1, int py1, int px2, int py2);
    void Delete_Textfile();
    void DrawImageLabel_WriteLabelFile_fromWidgetItem();
    void LoadLabelTxtFile(QString filename);
    void Select_last_line();
    void ConnectLines(int lineindex1, int lineindex2);

    bool isconnectScrollbarEvent;
    int x1,y1,x2,y2; // mouse position
    int ix1,iy1,ix2,iy2; //image position
    int diffx,diffy;
    enum drawlinestate { none, start, end };
    drawlinestate dstate = none;

    int currentSelectingImageIndex;
    int currentSelectingLineIndex;
    int LineIndex1_to_connect;

    bool isMouseinLabellingArea;


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
    void on_actionCancel_line_triggered();
    void on_bt_x_minus_clicked();
    void on_bt_x_plus_clicked();
    void on_bt_y_minus_clicked();
    void on_bt_y_plus_clicked();
    void on_files_treeWidget_itemSelectionChanged();
    void on_lines_treeWidget_itemSelectionChanged();
    void on_lines_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_lines_treeWidget_itemChanged(QTreeWidgetItem *item, int column);
    void on_actionToggle_AlignXY_triggered();
    void on_actionToggle_DrawNext_triggered();
    void on_actionSee_shortcut_triggered();
    void on_bt_save_label_clicked();
    void on_bt_dup_label_clicked();
    void on_lines_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_pushButton_clicked();
    void on_bt_delete_label_clicked();
    void on_bt_straight_line_clicked();
    void on_bt_connect_lines_clicked();
};

#endif // MAINWINDOW_H
