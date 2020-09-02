#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionSelect_folder, SIGNAL(triggered()), this, SLOT(Button_selectfolder_clicked()));
    connect(ui->openfolder_pushButton, SIGNAL(clicked()), this, SLOT(Button_openfolder_clicked()));
    connect(ui->deleteline_pushButton, SIGNAL(clicked()), this, SLOT(Button_deleteline_clicked()));

    connect(ui->files_treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(SelectImgFile(QTreeWidgetItem *, int)));
    connect(ui->lines_treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(SelectLine(QTreeWidgetItem *, int)));
    connect(ui->zoom_SpinBox, SIGNAL(valueChanged(double)), this, SLOT(ZoomImage(double)));

    connect(ui->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(on_scroll_v(int)));
    connect(ui->scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(on_scroll_h(int)));




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
    dstate=start;
    zoomFactor=1.0;

    currentSelectingImageIndex=-1;
    currentSelectingLineIndex=-1;

    ui->lines_treeWidget->header()->resizeSection(0, 60);
    ui->lines_treeWidget->header()->resizeSection(1, 45);
    ui->lines_treeWidget->header()->resizeSection(2, 45);

    //txtfile = new ReadWriteFile();

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    if( (dynamic_cast<QMouseEvent*>(event)) && (obj==ui->imageLabel))
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        int mousex=mouseEvent->pos().x();
        int mousey=mouseEvent->pos().y();

        QString mouseposition = QString("(%1,%2)").arg(mousex).arg(mousey);
        ui->mousepos_label->setText(mouseposition);

        switch(dstate)
        {
            case none: break;
            case start: ui->mousepos_label->setText("start"); TempMarkPixel(mousex,mousey);  break;
            case end : ui->mousepos_label->setText("end");  TempDrawLine(mousex,mousey); break;
        }



        if (event->type() == QEvent::MouseButtonPress)
        {
            //QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            qDebug()<< obj->metaObject()->className() << ", clicked at " << mousex << "," << mousey;



            switch(dstate)
            {
                case none: break;
                case start: SetStartLine(mousex,mousey); dstate=end;  break;
                case end : SetEndLine(mousex,mousey); dstate=start;  break;
            }

        }
    }

  return false;
}
void MainWindow::TempMarkPixel(int mousex, int mousey)
{
    tempimage = currentimage;
    QPainter painter(&tempimage);
    QPen myPen(Qt::red, 1, Qt::SolidLine);
    painter.setPen(myPen);
    painter.drawPoint(int(mousex/zoomFactor),int(mousey/zoomFactor));
    ui->imageLabel->setPixmap(tempimage);
}

void MainWindow::SetStartLine(int mousex, int mousey)
{
    ui->x1y1_label->setText("0,0");
    ui->x2y2_label->setText("0,0");

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
    ix1=int(x1/zoomFactor);
    iy1=int(y1/zoomFactor);
    ix2=int(x2/zoomFactor);
    iy2=int(y2/zoomFactor);

    QPainter painter(&currentimage);
    QPen myPen(Qt::red, 1, Qt::SolidLine);
    painter.setPen(myPen);
    painter.drawLine(ix1,iy1,ix2,iy2);
    ui->imageLabel->setPixmap(currentimage);

    AddLinePositionToTreeWidget(ix1,iy1,ix2,iy2);
    AddLinePositionToLabelTxtFile(ix1,iy1,ix2,iy2);

}

void MainWindow::Button_selectfolder_clicked()
{
    currentlyOpenedDir = QFileDialog::getExistingDirectory(this, "Choose a directory to be read in");

    if (currentlyOpenedDir.isEmpty())
        return;

    ui->foldername_lineEdit->setText(currentlyOpenedDir);

   ListImgInFolder();

}
void MainWindow::Button_openfolder_clicked()
{
    ListImgInFolder();
}

void MainWindow::ListImgInFolder()
{

    currentlyOpenedDir=ui->foldername_lineEdit->text();
    QDir directory(currentlyOpenedDir);

    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" << "*.bmp";

    QStringList images = directory.entryList(nameFilters, QDir::Files);

    qDebug() << " total img in folder =  " << images.size();
    if (images.size() <= 0)
        return;

    ui->files_treeWidget->clear();
    for (int i = 0; i < images.size(); i++)
    {
        QTreeWidgetItem *currentFile = new QTreeWidgetItem(ui->files_treeWidget);
        currentFile->setText(0, images[i]);
    }


}


void MainWindow::SelectImgFile(QTreeWidgetItem *item, int col)
{
    if(currentSelectingImageIndex == ui->files_treeWidget->currentIndex().row()) //select the current one (same one)
    {
        return;
    }
    //save current image label ?



    //
    currentSelectingImageIndex = ui->files_treeWidget->currentIndex().row(); // current index

    //QTreeWidgetItem* item = ui->files_treeWidget->currentIndex();
    //QTreeWidgetItem* item = ui->treeWidget->topLevelItem(last_select_item_index);

    QString imagename = currentlyOpenedDir + QDir::separator() + item->text(0);
    qDebug() << "select " << imagename;

    ui->lines_treeWidget->clear();
    ShowImage(imagename);

    QString txtfilename = imagename.section('.',0,0) + ".txt";
    qDebug() << "txtfilename " << txtfilename;
    //txtfile->OpenTxtFileLabel(txtfilename.toStdString());
    LoadLabelTxtFile(txtfilename);

}

void MainWindow::LoadLabelTxtFile(QString filename)
{
    currentlabeltxtfile.setFileName(filename);
    //QFile file( filename );
    if ( currentlabeltxtfile.open(QIODevice::ReadWrite) ) //create new if not exist
    {
        qDebug() << "opened  " << filename;
        //currentlabeltxtfile = file;
        //QTextStream stream( &file );
        //stream << "something" << endl;
        QTextStream in(&currentlabeltxtfile);
        QString line = in.readLine();
        while (!line.isNull())
        {

            qDebug() << line;

            if(line.isEmpty()) return; // for last line = ""

            ix1 = line.section(' ',0,0).toInt();
            iy1 = line.section(' ',1,1).toInt();
            ix2 = line.section(' ',2,2).toInt();
            iy2 = line.section(' ',3,3).toInt();
            qDebug() << "line from" << ix1 << ","  << iy1 << " to " << ix2 << "," << iy2;

            QPainter painter(&currentimage);
            QPen myPen(Qt::red, 1, Qt::SolidLine);
            painter.setPen(myPen);
            painter.drawLine(ix1,iy1,ix2,iy2);
            ui->imageLabel->setPixmap(currentimage);

            AddLinePositionToTreeWidget(ix1,iy1,ix2,iy2);

            line = in.readLine();

        }
    }
    else
    {
        qDebug() << "cannot open " << filename;
    }
}
void MainWindow::AddLinePositionToLabelTxtFile(int px1, int py1, int px2, int py2)
{
    QTextStream stream( &currentlabeltxtfile );
    stream << px1 << " " << py1 << " " << px2 << " " << py2 << endl;
}

void MainWindow::AddLinePositionToTreeWidget(int px1, int py1, int px2, int py2)
{
    QTreeWidgetItem *currentLine = new QTreeWidgetItem(ui->lines_treeWidget);
    currentLine->setText(0, QString::number(px1));
    currentLine->setText(1, QString::number(py1));
    currentLine->setText(2, QString::number(px2));
    currentLine->setText(3, QString::number(py2));
    //currentLine->setTextAlignment(0, Qt::AlignLeft);



}

void MainWindow::SelectLine(QTreeWidgetItem *item, int col)
{

    qDebug() << "mousePressEvent " << ui->lines_treeWidget->currentIndex().row();
    //QTreeWidgetItem* item = ui->files_treeWidget->currentIndex();
    //QTreeWidgetItem* item = ui->treeWidget->topLevelItem(last_select_item_index);

    //QString imagename = currentlyOpenedDir+QDir::separator()+item->text(0);
    qDebug() << item->text(0);

    currentSelectingLineIndex=ui->lines_treeWidget->currentIndex().row();
    TempHilightLine(item->text(0).toInt(),item->text(1).toInt(),item->text(2).toInt(),item->text(3).toInt());

}

void MainWindow::TempHilightLine(int tx1, int ty1, int tx2, int ty2)
{

    tempimage = currentimage;
    QPainter painter(&tempimage);
    QPen myPen(Qt::yellow, 1, Qt::SolidLine);
    painter.setPen(myPen);

    painter.drawLine(tx1, ty1, tx2, ty2);
    ui->imageLabel->setPixmap(tempimage);
}

void MainWindow::Button_deleteline_clicked()
{
    int totallines = ui->lines_treeWidget->topLevelItemCount();
    if(totallines==0) return;

    QTreeWidgetItem* selected_line = ui->lines_treeWidget->currentItem();
    qDebug() << "delete " << selected_line->text(0) <<"," <<selected_line->text(1);

    delete selected_line;




    //reload image
    //QString imagename = currentlyOpenedDir+QDir::separator()+ui->files_treeWidget->currentItem()->text(0);
    //qDebug() << imagename;

    //ShowImage(imagename);

    currentimage=rawimage;
    WriteNewAllLinePositiontoLabelTxtFile();
    DrawImageLabel();
}
void MainWindow::WriteNewAllLinePositiontoLabelTxtFile()
{
    currentlabeltxtfile.close();

    if(currentlabeltxtfile.remove())
    {
        qDebug() << "removed labeltxt" ;
        if ( currentlabeltxtfile.open(QIODevice::ReadWrite) ) //create new if not exist
        {
            qDebug() << "opened(re-create)  " << currentlabeltxtfile.fileName();
        }
        else
        {
            qDebug() << "fail to open(re-create)  " << currentlabeltxtfile.fileName();
        }

    }
    else
    {
        qDebug() << "fail to remove labeltxt" ;
    }

}

void MainWindow::DrawImageLabel()
{
    int totallines = ui->lines_treeWidget->topLevelItemCount();
    qDebug() << "totallines " << totallines;

    if(totallines==0)
    {
        ui->imageLabel->setPixmap(currentimage);
        return;
    }
    for (int i = 0; i < totallines; ++i)
    {
        QTreeWidgetItem *item = ui->lines_treeWidget->topLevelItem(i);
        //item->setText(0, QString::number(i + 1));
        ix1 = item->text(0).toInt();
        iy1 = item->text(1).toInt();
        ix2 = item->text(2).toInt();
        iy2 = item->text(3).toInt();

        QPainter painter(&currentimage);
        QPen myPen(Qt::red, 1, Qt::SolidLine);
        painter.setPen(myPen);
        painter.drawLine(ix1,iy1,ix2,iy2);
        ui->imageLabel->setPixmap(currentimage);

        AddLinePositionToLabelTxtFile(ix1,iy1,ix2,iy2);

    }

}

void MainWindow::ShowImage(const QString &fileName)
{
    QPixmap img(fileName);
    ui->imageLabel->setPixmap(img);
    ui->imageLabel->adjustSize();
    ui->zoom_SpinBox->setValue(1.0);
    ZoomImage(1.0);
    rawimage=img;
    currentimage=img;


    QString imgsize = QString("%1 x %2").arg(currentimage.width()).arg(currentimage.height());
    ui->imgsize_label->setText(imgsize);

    currentSelectingLineIndex=-1;

}

void MainWindow::ZoomImage(double f)
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



MainWindow::~MainWindow()
{
    delete ui;
}
