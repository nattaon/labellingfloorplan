#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->openfolder_pushButton, SIGNAL(clicked()), this, SLOT(on_openfolder_pushButton_clicked()));
    // this line is connected , dont know where, and it double the call function if I connect it here...
}
void MainWindow::on_openfolder_pushButton_clicked()
{
    //QString text = ui->foldername_lineEdit->text();
    //QMessageBox::information(this, "OK", text);
    //ui->pushButtonOK->setText( tr("(OK. click me)") );
    currentlyOpenedDir = QFileDialog::getExistingDirectory(this, "Choose a directory to be read in");

    if (currentlyOpenedDir.isEmpty())
        return;
    //currentlyOpenedDir=
    ui->foldername_lineEdit->setText(currentlyOpenedDir);

    refreshImgView();
}

void MainWindow::refreshImgView()
{
    ui->files_treeWidget->clear();
    QDir directory(currentlyOpenedDir);

    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" << "*.bmp";

    //QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);
    QStringList images = directory.entryList(nameFilters, QDir::Files);

    if (images.size() <= 0)
        return;

    // construct a new directory entry
    QTreeWidgetItem *currentTreeDir = new QTreeWidgetItem(ui->files_treeWidget);
    ui->files_treeWidget->setItemExpanded(currentTreeDir, true);
    //currentTreeDir->setText(0, images[0]);
    //currentTreeDir->setText(1, images[1]);
    //QTreeWidgetItem* item = ui->treeWidget->topLevelItem(last_select_item_index);
    //item->setText(1, QString::number(item_x_dim_mm));
    //item->setText(2, QString::number(item_y_dim_mm));
    //item->setText(3, QString::number(item_z_dim_mm));

    for (int i = 0; i < images.size(); i++)
    {
        QTreeWidgetItem *currentFile = new QTreeWidgetItem(currentTreeDir);
        currentFile->setText(0, images[i]);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
