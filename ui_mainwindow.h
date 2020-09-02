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
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionSelect_folder = new QAction(MainWindow);
        actionSelect_folder->setObjectName(QStringLiteral("actionSelect_folder"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        files_treeWidget = new QTreeWidget(centralWidget);
        files_treeWidget->setObjectName(QStringLiteral("files_treeWidget"));
        files_treeWidget->setGeometry(QRect(10, 30, 191, 181));
        openfolder_pushButton = new QPushButton(centralWidget);
        openfolder_pushButton->setObjectName(QStringLiteral("openfolder_pushButton"));
        openfolder_pushButton->setGeometry(QRect(10, 0, 89, 25));
        foldername_lineEdit = new QLineEdit(centralWidget);
        foldername_lineEdit->setObjectName(QStringLiteral("foldername_lineEdit"));
        foldername_lineEdit->setGeometry(QRect(110, 0, 281, 25));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 235, 41, 17));
        zoom_SpinBox = new QDoubleSpinBox(centralWidget);
        zoom_SpinBox->setObjectName(QStringLiteral("zoom_SpinBox"));
        zoom_SpinBox->setGeometry(QRect(60, 230, 51, 26));
        zoom_SpinBox->setDecimals(1);
        zoom_SpinBox->setMinimum(1);
        zoom_SpinBox->setMaximum(10);
        imageLabel = new QLabel(centralWidget);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setGeometry(QRect(400, 0, 51, 21));
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
        mousepos_label->setGeometry(QRect(10, 320, 61, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 210, 67, 17));
        imgsize_label = new QLabel(centralWidget);
        imgsize_label->setObjectName(QStringLiteral("imgsize_label"));
        imgsize_label->setGeometry(QRect(80, 210, 91, 17));
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
        alignedxy_checkBox->setGeometry(QRect(10, 250, 141, 23));
        alignedxy_checkBox->setChecked(true);
        lines_treeWidget = new QTreeWidget(centralWidget);
        lines_treeWidget->setObjectName(QStringLiteral("lines_treeWidget"));
        lines_treeWidget->setGeometry(QRect(10, 350, 201, 192));
        lines_treeWidget->setIndentation(20);
        lines_treeWidget->setItemsExpandable(false);
        lines_treeWidget->setHeaderHidden(false);
        lines_treeWidget->setExpandsOnDoubleClick(false);
        lines_treeWidget->header()->setVisible(true);
        lines_treeWidget->header()->setCascadingSectionResizes(false);
        lines_treeWidget->header()->setDefaultSectionSize(20);
        lines_treeWidget->header()->setMinimumSectionSize(20);
        lines_treeWidget->header()->setStretchLastSection(true);
        deleteline_pushButton = new QPushButton(centralWidget);
        deleteline_pushButton->setObjectName(QStringLiteral("deleteline_pushButton"));
        deleteline_pushButton->setGeometry(QRect(110, 320, 91, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionSelect_folder);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionSelect_folder->setText(QApplication::translate("MainWindow", "Select folder", Q_NULLPTR));
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
        alignedxy_checkBox->setText(QApplication::translate("MainWindow", "force aligned xy", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem1 = lines_treeWidget->headerItem();
        ___qtreewidgetitem1->setText(3, QApplication::translate("MainWindow", "y2", Q_NULLPTR));
        ___qtreewidgetitem1->setText(2, QApplication::translate("MainWindow", "x2", Q_NULLPTR));
        ___qtreewidgetitem1->setText(1, QApplication::translate("MainWindow", "y1", Q_NULLPTR));
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "x1", Q_NULLPTR));
        deleteline_pushButton->setText(QApplication::translate("MainWindow", "delete line", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
