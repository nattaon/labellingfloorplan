#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->openfolder_pushButton, SIGNAL(clicked()), this, SLOT(on_openfolder_pushButton_clicked()));
    // this line is connected , dont know where, and it double the call function if I connect it here...
    connect(ui->files_treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(PressedTreeItem(QTreeWidgetItem *, int)));
    //connect(pixmapWidget, SIGNAL(drawEvent(QImage *)), this, SLOT(onMaskDraw(QImage *)));
    connect(ui->zoom_SpinBox, SIGNAL(valueChanged(double)), this, SLOT(setZoomFactor(double)));
    //connect(maskTypeComboBox, SIGNAL(currentIndexChanged(int)), pixmapWidget, SLOT(setMaskEditColor(int)));
    //connect(pixmapWidget, SIGNAL(zoomFactorChanged(double)), zoomSpinBox, SLOT(setValue(double)));


    //connect(ui->drawline_pushButton, SIGNAL(clicked()), this, SLOT(on_drawline_pushButton_clicked()));



    ui->imageLabel->setBackgroundRole(QPalette::Base);
    ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->imageLabel->setScaledContents(true);


    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    ui->scrollArea->setWidget(ui->imageLabel);
    ui->scrollArea->setVisible(true);
    ui->scrollArea->setWidgetResizable(false);
    //setCentralWidget(ui->scrollArea);

    //ui->imageLabel->installEventFilter(this);
    qApp->installEventFilter(this);

    currentlyOpenedDir=QDir::currentPath()+QDir::separator()+"labeltest";
    ui->foldername_lineEdit->setText(currentlyOpenedDir);

    drawlinemode=false;
    dstate=none;
    zoomFactor=1.0;
    //ui->zoom_SpinBox->setValue(1.0);
    connect(ui->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(on_scroll_v(int)));
    connect(ui->scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(on_scroll_h(int)));

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    if( (dynamic_cast<QMouseEvent*>(event)) && (obj==ui->imageLabel))
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        int mousex=mouseEvent->pos().x();
        int mousey=mouseEvent->pos().y();


        if(drawlinemode)
        {
            switch(dstate)
            {

                case start: ui->mousepos_label->setText("start");  break;
                case end : ui->mousepos_label->setText("end");  TempDrawLine(mousex,mousey); break;
            }
        }
        else
        {
            QString mouseposition = QString("(%1,%2)").arg(mousex).arg(mousey);
            ui->mousepos_label->setText(mouseposition);
        }


        if (event->type() == QEvent::MouseButtonPress)
        {
            //QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            qDebug()<< obj->metaObject()->className() << ", clicked at " << mousex << "," << mousey;


            if(drawlinemode)
            {
                switch(dstate)
                {

                    case start: SetStartLine(mousex,mousey); dstate=end;  break;
                    case end : SetEndLine(mousex,mousey); dstate=start;  break;
                }

            }
        }
    }

  return false;
}
void MainWindow::SetStartLine(int mousex, int mousey)
{
    x1=mousex;
    y1=mousey;
    QString mouseposition = QString("%1,%2").arg(mousex).arg(mousey);
    ui->x1y1_label->setText(mouseposition);

    tempimage = currentimage;

}
void MainWindow::TempDrawLine(int mousex, int mousey)
{
    QString mouseposition = QString("%1,%2").arg(mousex).arg(mousey);
    ui->x2y2_label->setText(mouseposition);

    tempimage = currentimage;
    QPainter painter(&tempimage);
    QPen myPen(Qt::red, 1, Qt::SolidLine);
    painter.setPen(myPen);

    painter.drawLine(x1/zoomFactor, y1/zoomFactor, mousex/zoomFactor, mousey/zoomFactor);
    qDebug() << "draw from " << x1 << ","  << y1 << " to " << mousex << "," << mousey;


    ui->imageLabel->setPixmap(tempimage);
}

void MainWindow::SetEndLine(int mousex, int mousey)
{
    x2=mousex;
    y2=mousey;

    if(ui->alignedxy_checkBox->isChecked())
    {
        int diffx = qFabs(x1-x2);
        int diffy = qFabs(y1-y2);
        qDebug() << "diffx " <<diffx;
        qDebug() << "diffy " <<diffy;

        if(diffx < diffy) // draw vertical line
        {
            x2=x1;
        }
        else if(diffy < diffx)//draw horizontal line
        {
            y2=y1;
        }

    }

    QPainter painter(&currentimage);
    QPen myPen(Qt::red, 1, Qt::SolidLine);
    painter.setPen(myPen);
    painter.drawLine(x1/zoomFactor, y1/zoomFactor, x2/zoomFactor, y2/zoomFactor);
    ui->imageLabel->setPixmap(currentimage);

    ui->x1y1_label->setText("0,0");
    ui->x2y2_label->setText("0,0");
}


void MainWindow::on_openfolder_pushButton_clicked()
{
    //currentlyOpenedDir = QFileDialog::getExistingDirectory(this, "Choose a directory to be read in");

    //if (currentlyOpenedDir.isEmpty())
    //    return;

    //ui->foldername_lineEdit->setText(currentlyOpenedDir);

    //currentlyOpenedDir=ui->foldername_lineEdit->text();
    //qDebug() << "the integer is" << 777;
    refreshImgView();
}

void MainWindow::refreshImgView()
{
    ui->files_treeWidget->clear();
    QDir directory(currentlyOpenedDir);

    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" << "*.bmp";

    QStringList images = directory.entryList(nameFilters, QDir::Files);

    qDebug() << " images.size() " << images.size();
    if (images.size() <= 0)
        return;


    for (int i = 0; i < images.size(); i++)
    {
        QTreeWidgetItem *currentFile = new QTreeWidgetItem(ui->files_treeWidget);
        currentFile->setText(0, images[i]);
    }

}

void MainWindow::PressedTreeItem(QTreeWidgetItem *item, int col)
{

    qDebug() << "mousePressEvent " << ui->files_treeWidget->currentIndex().row();
    //QTreeWidgetItem* item = ui->files_treeWidget->currentIndex();
    //QTreeWidgetItem* item = ui->treeWidget->topLevelItem(last_select_item_index);
    QString imagename = currentlyOpenedDir+QDir::separator()+item->text(0);
    qDebug() << imagename;

    loadImage(imagename);

}

void MainWindow::loadImage(const QString &fileName)
{
    QPixmap img(fileName);
    ui->imageLabel->setPixmap(img);
    ui->imageLabel->adjustSize();
    rawimage=img;
    currentimage=img;

    QString imgsize = QString("%1 x %2").arg(currentimage.width()).arg(currentimage.height());
    ui->imgsize_label->setText(imgsize);


}

void MainWindow::setZoomFactor(double f)
{
    zoomFactor = f;
    qDebug() << "\n zoomFactor = " << zoomFactor;

    if(f>=1.0)
        ui->imageLabel->resize(zoomFactor * ui->imageLabel->pixmap()->size());
    print_scrollbar_value();

}


void MainWindow::print_scrollbar_value()
{
    double hValue = 0, hMin = 0, hMax = 0, hPageStep = 0, hLength = 0;
    double vValue = 0, vMin = 0, vMax = 0, vPageStep = 0, vLength = 0;

    if (ui->scrollArea) {
        QScrollBar *scrollBar;
        scrollBar = ui->scrollArea->horizontalScrollBar();
        if (scrollBar) {
            hValue = scrollBar->value();
            hMin = scrollBar->minimum();
            hMax = scrollBar->maximum();
            hPageStep = scrollBar->pageStep();
            hLength = hMax - hMin + hPageStep;
            qDebug() << "hValue = " << hValue << ", "
                     << "hMin = " << hMin << ", "
                     << "hMax = " << hMax << ", "
                     << "hPageStep = " << hPageStep << ", "
                     << "hLength = " << hLength ;
        }
        scrollBar = ui->scrollArea->verticalScrollBar();
        if (scrollBar) {
            vValue = scrollBar->value();
            vMin = scrollBar->minimum();
            vMax = scrollBar->maximum();
            vPageStep = scrollBar->pageStep();
            vLength = vMax - vMin + vPageStep;
            qDebug() << "vValue = " << vValue << ", "
                     << "vMin = " << vMin << ", "
                     << "vMax = " << vMax << ", "
                     << "vPageStep = " << vPageStep << ", "
                     << "vLength = " << vLength ;
        }
    }

}
void MainWindow::on_scroll_v(int value)
{
    qDebug() << "on_scroll vertical " << value;
    print_scrollbar_value();
}
void MainWindow::on_scroll_h(int value)
{
    qDebug() << "on_scroll horizontal " << value;
    print_scrollbar_value();
}
void MainWindow::on_drawline_pushButton_clicked()
{
    qDebug() << "drawlinemode " << drawlinemode;
    drawlinemode=!drawlinemode;
    if(drawlinemode)
    {
        dstate=start;
        QPalette pal = ui->drawline_pushButton->palette();
        pal.setColor(QPalette::Button, QColor(Qt::blue));
        ui->drawline_pushButton->setAutoFillBackground(true);
        ui->drawline_pushButton->setPalette(pal);
        ui->drawline_pushButton->update();
    }
    else
    {
        dstate=none;
        QPalette pal = ui->drawline_pushButton->palette();
        pal.setColor(QPalette::Button, QColor(Qt::gray));
        ui->drawline_pushButton->setAutoFillBackground(true);
        ui->drawline_pushButton->setPalette(pal);
        ui->drawline_pushButton->update();
    }



}



MainWindow::~MainWindow()
{
    delete ui;
}
