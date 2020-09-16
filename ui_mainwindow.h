/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSelect_folder;
    QAction *actionGenerate_label;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QAction *actionNext_image;
    QAction *actionPrev_image;
    QAction *actionSee_shortcut;
    QAction *actionDelete_line;
    QAction *actionCancel_line;
    QWidget *centralWidget;
    QTreeWidget *files_treeWidget;
    QPushButton *openfolder_pushButton;
    QLineEdit *foldername_lineEdit;
    QLabel *label;
    QDoubleSpinBox *zoom_SpinBox;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *mousepos_label;
    QLabel *label_2;
    QLabel *imgsize_label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *x1y1_label;
    QLabel *x2y2_label;
    QCheckBox *alignedxy_checkBox;
    QTreeWidget *lines_treeWidget;
    QPushButton *deleteline_pushButton;
    QLineEdit *rotation_lineEdit;
    QPushButton *cw_rotation_pushButton;
    QPushButton *ccw_rotation_pushButton;
    QLabel *label_5;
    QPushButton *saveimg_pushButton;
    QCheckBox *drawnext_checkBox;
    QLabel *linewide_label;
    QLabel *label_6;
    QPushButton *bt_x_plus;
    QPushButton *bt_x_minus;
    QPushButton *bt_y_plus;
    QPushButton *bt_y_minus;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuLabel;
    QMenu *menuShortcut;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionSelect_folder = new QAction(MainWindow);
        actionSelect_folder->setObjectName(QStringLiteral("actionSelect_folder"));
        actionGenerate_label = new QAction(MainWindow);
        actionGenerate_label->setObjectName(QStringLiteral("actionGenerate_label"));
        actionZoom_in = new QAction(MainWindow);
        actionZoom_in->setObjectName(QStringLiteral("actionZoom_in"));
        actionZoom_out = new QAction(MainWindow);
        actionZoom_out->setObjectName(QStringLiteral("actionZoom_out"));
        actionNext_image = new QAction(MainWindow);
        actionNext_image->setObjectName(QStringLiteral("actionNext_image"));
        actionPrev_image = new QAction(MainWindow);
        actionPrev_image->setObjectName(QStringLiteral("actionPrev_image"));
        actionSee_shortcut = new QAction(MainWindow);
        actionSee_shortcut->setObjectName(QStringLiteral("actionSee_shortcut"));
        actionDelete_line = new QAction(MainWindow);
        actionDelete_line->setObjectName(QStringLiteral("actionDelete_line"));
        actionCancel_line = new QAction(MainWindow);
        actionCancel_line->setObjectName(QStringLiteral("actionCancel_line"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        files_treeWidget = new QTreeWidget(centralWidget);
        files_treeWidget->setObjectName(QStringLiteral("files_treeWidget"));
        files_treeWidget->setGeometry(QRect(10, 0, 191, 181));
        openfolder_pushButton = new QPushButton(centralWidget);
        openfolder_pushButton->setObjectName(QStringLiteral("openfolder_pushButton"));
        openfolder_pushButton->setGeometry(QRect(210, 0, 89, 25));
        foldername_lineEdit = new QLineEdit(centralWidget);
        foldername_lineEdit->setObjectName(QStringLiteral("foldername_lineEdit"));
        foldername_lineEdit->setGeometry(QRect(310, 0, 351, 25));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 200, 41, 17));
        zoom_SpinBox = new QDoubleSpinBox(centralWidget);
        zoom_SpinBox->setObjectName(QStringLiteral("zoom_SpinBox"));
        zoom_SpinBox->setGeometry(QRect(50, 195, 51, 26));
        zoom_SpinBox->setDecimals(1);
        zoom_SpinBox->setMinimum(1);
        zoom_SpinBox->setMaximum(10);
        imageLabel = new QLabel(centralWidget);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setGeometry(QRect(610, 0, 51, 21));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(220, 30, 500, 500));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 498, 498));
        scrollArea->setWidget(scrollAreaWidgetContents);
        mousepos_label = new QLabel(centralWidget);
        mousepos_label->setObjectName(QStringLiteral("mousepos_label"));
        mousepos_label->setGeometry(QRect(10, 320, 71, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 180, 67, 17));
        imgsize_label = new QLabel(centralWidget);
        imgsize_label->setObjectName(QStringLiteral("imgsize_label"));
        imgsize_label->setGeometry(QRect(80, 180, 91, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 280, 67, 17));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 300, 67, 17));
        x1y1_label = new QLabel(centralWidget);
        x1y1_label->setObjectName(QStringLiteral("x1y1_label"));
        x1y1_label->setGeometry(QRect(70, 280, 67, 17));
        x2y2_label = new QLabel(centralWidget);
        x2y2_label->setObjectName(QStringLiteral("x2y2_label"));
        x2y2_label->setGeometry(QRect(70, 300, 67, 17));
        alignedxy_checkBox = new QCheckBox(centralWidget);
        alignedxy_checkBox->setObjectName(QStringLiteral("alignedxy_checkBox"));
        alignedxy_checkBox->setGeometry(QRect(10, 220, 91, 23));
        alignedxy_checkBox->setChecked(true);
        lines_treeWidget = new QTreeWidget(centralWidget);
        lines_treeWidget->setObjectName(QStringLiteral("lines_treeWidget"));
        lines_treeWidget->setGeometry(QRect(10, 340, 201, 192));
        lines_treeWidget->setIndentation(20);
        lines_treeWidget->setItemsExpandable(false);
        lines_treeWidget->setHeaderHidden(true);
        lines_treeWidget->setExpandsOnDoubleClick(false);
        lines_treeWidget->header()->setVisible(false);
        lines_treeWidget->header()->setCascadingSectionResizes(false);
        lines_treeWidget->header()->setDefaultSectionSize(20);
        lines_treeWidget->header()->setMinimumSectionSize(20);
        lines_treeWidget->header()->setStretchLastSection(true);
        deleteline_pushButton = new QPushButton(centralWidget);
        deleteline_pushButton->setObjectName(QStringLiteral("deleteline_pushButton"));
        deleteline_pushButton->setGeometry(QRect(130, 310, 81, 25));
        rotation_lineEdit = new QLineEdit(centralWidget);
        rotation_lineEdit->setObjectName(QStringLiteral("rotation_lineEdit"));
        rotation_lineEdit->setGeometry(QRect(700, 10, 31, 20));
        rotation_lineEdit->setAlignment(Qt::AlignCenter);
        cw_rotation_pushButton = new QPushButton(centralWidget);
        cw_rotation_pushButton->setObjectName(QStringLiteral("cw_rotation_pushButton"));
        cw_rotation_pushButton->setGeometry(QRect(730, 10, 31, 20));
        ccw_rotation_pushButton = new QPushButton(centralWidget);
        ccw_rotation_pushButton->setObjectName(QStringLiteral("ccw_rotation_pushButton"));
        ccw_rotation_pushButton->setGeometry(QRect(660, 10, 41, 20));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(660, 0, 91, 17));
        saveimg_pushButton = new QPushButton(centralWidget);
        saveimg_pushButton->setObjectName(QStringLiteral("saveimg_pushButton"));
        saveimg_pushButton->setGeometry(QRect(760, 10, 31, 20));
        drawnext_checkBox = new QCheckBox(centralWidget);
        drawnext_checkBox->setObjectName(QStringLiteral("drawnext_checkBox"));
        drawnext_checkBox->setGeometry(QRect(10, 240, 91, 23));
        drawnext_checkBox->setChecked(true);
        linewide_label = new QLabel(centralWidget);
        linewide_label->setObjectName(QStringLiteral("linewide_label"));
        linewide_label->setGeometry(QRect(70, 260, 67, 17));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 260, 67, 17));
        bt_x_plus = new QPushButton(centralWidget);
        bt_x_plus->setObjectName(QStringLiteral("bt_x_plus"));
        bt_x_plus->setGeometry(QRect(180, 250, 31, 25));
        bt_x_minus = new QPushButton(centralWidget);
        bt_x_minus->setObjectName(QStringLiteral("bt_x_minus"));
        bt_x_minus->setGeometry(QRect(140, 250, 31, 25));
        bt_y_plus = new QPushButton(centralWidget);
        bt_y_plus->setObjectName(QStringLiteral("bt_y_plus"));
        bt_y_plus->setGeometry(QRect(180, 280, 31, 25));
        bt_y_minus = new QPushButton(centralWidget);
        bt_y_minus->setObjectName(QStringLiteral("bt_y_minus"));
        bt_y_minus->setGeometry(QRect(140, 280, 31, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuLabel = new QMenu(menuBar);
        menuLabel->setObjectName(QStringLiteral("menuLabel"));
        menuShortcut = new QMenu(menuBar);
        menuShortcut->setObjectName(QStringLiteral("menuShortcut"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuLabel->menuAction());
        menuBar->addAction(menuShortcut->menuAction());
        menuFile->addAction(actionSelect_folder);
        menuFile->addAction(actionZoom_in);
        menuFile->addAction(actionZoom_out);
        menuLabel->addAction(actionGenerate_label);
        menuLabel->addAction(actionNext_image);
        menuLabel->addAction(actionPrev_image);
        menuLabel->addAction(actionDelete_line);
        menuLabel->addAction(actionCancel_line);
        menuShortcut->addAction(actionSee_shortcut);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionSelect_folder->setText(QApplication::translate("MainWindow", "Select folder", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionSelect_folder->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionGenerate_label->setText(QApplication::translate("MainWindow", "Generate label", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionGenerate_label->setShortcut(QApplication::translate("MainWindow", "Ctrl+G", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoom_in->setText(QApplication::translate("MainWindow", "Zoom in", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionZoom_in->setShortcut(QApplication::translate("MainWindow", "+", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoom_out->setText(QApplication::translate("MainWindow", "Zoom out", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionZoom_out->setShortcut(QApplication::translate("MainWindow", "-", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionNext_image->setText(QApplication::translate("MainWindow", "Next image", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionNext_image->setShortcut(QApplication::translate("MainWindow", ">", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionPrev_image->setText(QApplication::translate("MainWindow", "Prev image", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionPrev_image->setShortcut(QApplication::translate("MainWindow", "<", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSee_shortcut->setText(QApplication::translate("MainWindow", "See shortcut", Q_NULLPTR));
        actionDelete_line->setText(QApplication::translate("MainWindow", "Delete line", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionDelete_line->setShortcut(QApplication::translate("MainWindow", "Del", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionCancel_line->setText(QApplication::translate("MainWindow", "Cancel line", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionCancel_line->setShortcut(QApplication::translate("MainWindow", "Esc", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        QTreeWidgetItem *___qtreewidgetitem = files_treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Files", Q_NULLPTR));
        openfolder_pushButton->setText(QApplication::translate("MainWindow", "Open folder", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Zoom", Q_NULLPTR));
        imageLabel->setText(QString());
        mousepos_label->setText(QApplication::translate("MainWindow", "mousepos", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Img size:", Q_NULLPTR));
        imgsize_label->setText(QApplication::translate("MainWindow", "0 x 0", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "(x1,y1)", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "(x2,y2)", Q_NULLPTR));
        x1y1_label->setText(QApplication::translate("MainWindow", "0,0", Q_NULLPTR));
        x2y2_label->setText(QApplication::translate("MainWindow", "0,0", Q_NULLPTR));
        alignedxy_checkBox->setText(QApplication::translate("MainWindow", "aligned xy", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem1 = lines_treeWidget->headerItem();
        ___qtreewidgetitem1->setText(3, QApplication::translate("MainWindow", "y2", Q_NULLPTR));
        ___qtreewidgetitem1->setText(2, QApplication::translate("MainWindow", "x2", Q_NULLPTR));
        ___qtreewidgetitem1->setText(1, QApplication::translate("MainWindow", "y1", Q_NULLPTR));
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "x1", Q_NULLPTR));
        deleteline_pushButton->setText(QApplication::translate("MainWindow", "delete line", Q_NULLPTR));
        rotation_lineEdit->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        cw_rotation_pushButton->setText(QApplication::translate("MainWindow", "CW", Q_NULLPTR));
        ccw_rotation_pushButton->setText(QApplication::translate("MainWindow", "CCW", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Rotate img", Q_NULLPTR));
        saveimg_pushButton->setText(QApplication::translate("MainWindow", "save", Q_NULLPTR));
        drawnext_checkBox->setText(QApplication::translate("MainWindow", "draw next", Q_NULLPTR));
        linewide_label->setText(QApplication::translate("MainWindow", "0,0", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "linewide", Q_NULLPTR));
        bt_x_plus->setText(QApplication::translate("MainWindow", "x +1", Q_NULLPTR));
        bt_x_minus->setText(QApplication::translate("MainWindow", "x -1", Q_NULLPTR));
        bt_y_plus->setText(QApplication::translate("MainWindow", "y +1", Q_NULLPTR));
        bt_y_minus->setText(QApplication::translate("MainWindow", "y -1", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuLabel->setTitle(QApplication::translate("MainWindow", "Label", Q_NULLPTR));
        menuShortcut->setTitle(QApplication::translate("MainWindow", "Shortcut", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
