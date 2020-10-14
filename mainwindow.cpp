#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->actionSelect_folder, SIGNAL(triggered()), this, SLOT(Button_selectfolder_clicked()));
    connect(ui->actionGenerate_label, SIGNAL(triggered()), this, SLOT(Button_generatelabel_clicked()));
    connect(ui->actionZoom_in, SIGNAL(triggered()), this, SLOT(Button_zoomin_clicked()));
    connect(ui->actionZoom_out, SIGNAL(triggered()), this, SLOT(Button_zoomout_clicked()));
    connect(ui->actionNext_image, SIGNAL(triggered()), this, SLOT(Button_nextimg_clicked()));
    connect(ui->actionPrev_image, SIGNAL(triggered()), this, SLOT(Button_previmg_clicked()));
    connect(ui->actionDelete_line,SIGNAL(triggered()), this, SLOT(Button_deleteline_clicked()));

    connect(ui->openfolder_pushButton, SIGNAL(clicked()), this, SLOT(Button_openfolder_clicked()));
    connect(ui->deleteline_pushButton, SIGNAL(clicked()), this, SLOT(Button_deleteline_clicked()));
    //connect(ui->ccw_rotation_pushButton, SIGNAL(clicked()), this, SLOT(Button_ccwrotation_clicked()));
    //connect(ui->cw_rotation_pushButton, SIGNAL(clicked()), this, SLOT(Button_cwrotation_clicked()));
    //connect(ui->saveimg_pushButton, SIGNAL(clicked()), this, SLOT(Button_saveimg_clicked()));

    connect(ui->files_treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(SelectImgFile(QTreeWidgetItem *, int)));
    connect(ui->lines_treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(SelectLine(QTreeWidgetItem *, int)));
    connect(ui->zoom_SpinBox, SIGNAL(valueChanged(double)), this, SLOT(ZoomImage(double)));

    //connect(ui->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(on_scroll_v(int)));
    //connect(ui->scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(on_scroll_h(int)));




    ui->imageLabel->setBackgroundRole(QPalette::Base);
    ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->imageLabel->setScaledContents(true);


    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    ui->scrollArea->setWidget(ui->imageLabel);
    ui->scrollArea->setVisible(true);
    ui->scrollArea->setWidgetResizable(false); //  if set true the image will very small, and no scrollbar
    //setCentralWidget(ui->scrollArea);

    //ui->imageLabel->installEventFilter(this);
    qApp->installEventFilter(this);

    //currentlyOpenedDir=QDir::currentPath()+QDir::separator()+"labeltest";
    //currentlyOpenedDir="/home/okuboali/nattaon_ws/_0room_dataset/beike/beike-ply/aligned/histograme";
    //currentlyOpenedDir=QString("../labeltest");
    currentlyOpenedDir="/home/nattaon/ply/aligned-beike/histograme";
    ui->foldername_lineEdit->setText(currentlyOpenedDir);
    ListImgInFolder();

    isLineWidgetEditable=false;
    dstate=none;
    isLoadingLabel=false;
    //dstate=start;
    zoomFactor=1.0;

    currentSelectingImageIndex=-1;
    currentSelectingLineIndex=-1;

    ui->lines_treeWidget->header()->resizeSection(0, 60);
    ui->lines_treeWidget->header()->resizeSection(1, 45);
    ui->lines_treeWidget->header()->resizeSection(2, 45);

    //txtfile = new ReadWriteFile();
    QPoint p = ui->scrollArea->geometry().topLeft();
    qDebug() << "ui->scrollArea topLeft " << p;

    isMouseinLabellingArea=false;

    QCursor cursor(Qt::CrossCursor);
    QApplication::setOverrideCursor(cursor);
    QApplication::changeOverrideCursor(cursor);

}
void MainWindow::resizeEvent(QResizeEvent *e)
{
    //undoView->move(e->size().width(),undoView->y());
    qDebug() << "resize window " << e->size().width() << "*" << e->size().height();
    //
    QPoint p = ui->scrollArea->geometry().topLeft();
    int newwidth = e->size().width()-p.x()-30;
    int newheight = e->size().height()-p.y()-70;
    qDebug() << "new scollarea size " << newwidth << "*" << newheight;
    //ui->scrollArea->adjustSize();
    ui->scrollArea->resize(newwidth,newheight);
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    if( (dynamic_cast<QMouseEvent*>(event)) && (obj==ui->imageLabel))
    {
        isMouseinLabellingArea=true;

        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        int mousex=mouseEvent->pos().x();
        int mousey=mouseEvent->pos().y();

        //QString mouseposition = QString("(%1,%2)").arg(mousex).arg(mousey);
        //ui->mousepos_label->setText(mouseposition);
        QString mouseposition = QString("%1,%2").arg((int)round(mousex/zoomFactor)).arg((int)round(mousey/zoomFactor));


        switch(dstate)
        {
            case none: break;
            case start: ui->mousepos_label->setText("start"); TempMarkPixel(mousex,mousey);  ui->x1y1_label->setText(mouseposition); break;
            case end : ui->mousepos_label->setText("end");  TempDrawLine(mousex,mousey); ui->x2y2_label->setText(mouseposition); break;
        }
        //qDebug() << "current draw state: " << dstate;


        if (event->type() == QEvent::MouseButtonPress)
        {
            //QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            qDebug()<< obj->metaObject()->className() << ", clicked at " << mousex << "," << mousey;
            isLineWidgetEditable=false;


            switch(dstate)
            {
                case none: break;
                case start: SetStartLine(mousex,mousey); dstate=end;  break;
                case end :
                {
                    SetEndLine(mousex,mousey); dstate=start;
                    if(ui->drawnext_checkBox->isChecked())
                    {
                        //set at the previous line end pixel
                        SetStartLine(ix2*zoomFactor,iy2*zoomFactor); dstate=end;
                    }
                    break;
                }
            }

        }
    }


  return false;
}
void MainWindow::TempMarkPixel(int mousex, int mousey)
{
    tempimage = currentimage;
    //QPainter painter(&tempimage);
    QPainter *painter = new QPainter(&tempimage);

    QPen myPen(Qt::red, 1, Qt::SolidLine);
    painter->setPen(myPen);
    painter->drawPoint((int)round(mousex/zoomFactor),(int)round(mousey/zoomFactor));
    delete painter;
    ui->imageLabel->setPixmap(tempimage);
}

void MainWindow::SetStartLine(int mousex, int mousey)
{
    ui->x1y1_label->setText("0,0");
    ui->x2y2_label->setText("0,0");

    x1=mousex;
    y1=mousey;
    QString mouseposition = QString("%1,%2").arg((int)round(mousex/zoomFactor)).arg((int)round(mousey/zoomFactor));
    ui->x1y1_label->setText(mouseposition);
    //ui->x1y1_label->setText(QString::number(diffx) +", "+ QString::number(diffy));

    tempimage = currentimage;

}
void MainWindow::TempDrawLine(int mousex, int mousey)
{
    QString mouseposition = QString("%1,%2").arg((int)round(mousex/zoomFactor)).arg((int)round(mousey/zoomFactor));
    ui->x2y2_label->setText(mouseposition);
    //ui->x2y2_label->setText(QString::number(diffx) +", "+ QString::number(diffy));

    tempimage = currentimage;
    //QPainter painter(&tempimage);
    QPainter *painter = new QPainter(&tempimage);
    QPen myPen(Qt::red, 1, Qt::SolidLine);
    painter->setPen(myPen);

    painter->drawLine(round(x1/zoomFactor), round(y1/zoomFactor), round(mousex/zoomFactor), round(mousey/zoomFactor));
    //qDebug() << "draw from " << x1 << ","  << y1 << " to " << mousex << "," << mousey;

    delete painter;
    ui->imageLabel->setPixmap(tempimage);
}

void MainWindow::SetEndLine(int mousex, int mousey)
{
    x2=mousex;
    y2=mousey;

    if(ui->alignedxy_checkBox->isChecked())
    {
        diffx = qFabs(x1-x2);
        diffy = qFabs(y1-y2);
        //qDebug() << "diffx " <<diffx;
        //qDebug() << "diffy " <<diffy;

        if(diffx < diffy) // draw vertical line
        {
            x2=x1;
        }
        else if(diffy < diffx)//draw horizontal line
        {
            y2=y1;
        }

    }
    ix1=(int)round(x1/zoomFactor);
    iy1=(int)round(y1/zoomFactor);
    ix2=(int)round(x2/zoomFactor);
    iy2=(int)round(y2/zoomFactor);

    //QPainter painter(&currentimage);
    QPainter *painter = new QPainter(&currentimage);
    QPen myPen(Qt::red, 1, Qt::SolidLine);
    painter->setPen(myPen);
    painter->drawLine(ix1,iy1,ix2,iy2);
    delete painter;
    ui->imageLabel->setPixmap(currentimage);

    Add_Line_to_TreeWidget(ix1,iy1,ix2,iy2);
    Add_Line_to_Textfile(ix1,iy1,ix2,iy2);

    diffx = qFabs(ix1-ix2);
    diffy = qFabs(iy1-iy2);
    ui->linewide_label->setText(QString::number(diffx) +", "+ QString::number(diffy));

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

    currentSelectingImageIndex=-1;
    //Button_nextimg_clicked();

}
void MainWindow::Button_nextimg_clicked()
{

    int totalimgs = ui->files_treeWidget->topLevelItemCount();
    int toSelectImageIndex = currentSelectingImageIndex+1;
    qDebug() << "toSelectImageIndex " << toSelectImageIndex <<"/"<<totalimgs;
    if(toSelectImageIndex >=0 && toSelectImageIndex < totalimgs)
    {
        QTreeWidgetItem *item = ui->files_treeWidget->topLevelItem(toSelectImageIndex);
        ui->files_treeWidget->setCurrentItem(item);
        SelectImgFile(item,0); //item is the row, column=0
    }
}
void MainWindow::Button_previmg_clicked()
{
    int totalimgs = ui->files_treeWidget->topLevelItemCount();
    int toSelectImageIndex = currentSelectingImageIndex-1;
    qDebug() << "toSelectImageIndex " << toSelectImageIndex <<"/"<<totalimgs;
    if(toSelectImageIndex >=0 && toSelectImageIndex < totalimgs)
    {
        QTreeWidgetItem *item = ui->files_treeWidget->topLevelItem(toSelectImageIndex);
        ui->files_treeWidget->setCurrentItem(item);
        SelectImgFile(item,0);
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
    dstate=start;

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
        // # Read line by line
        QString line = in.readLine();
        while (!line.isNull())
        {
            isLoadingLabel=true;
            //qDebug() << line;

            if(line.isEmpty()) return; // for last line = ""

            ix1 = line.section(' ',0,0).toInt();
            iy1 = line.section(' ',1,1).toInt();
            ix2 = line.section(' ',2,2).toInt();
            iy2 = line.section(' ',3,3).toInt();
            //qDebug() << "line from" << ix1 << ","  << iy1 << " to " << ix2 << "," << iy2;

            //QPainter painter(&currentimage);
            QPainter *painter = new QPainter(&currentimage);
            QPen myPen(Qt::red, 1, Qt::SolidLine);
            painter->setPen(myPen);
            painter->drawLine(ix1,iy1,ix2,iy2);
            delete painter;

            // # Draw image
            ui->imageLabel->setPixmap(currentimage);
            // # Add a line parameter to widget
            Add_Line_to_TreeWidget(ix1,iy1,ix2,iy2);

            line = in.readLine();

        }
        isLoadingLabel=false;
    }
    else
    {
        qDebug() << "cannot open " << filename;
    }
}
void MainWindow::Add_Line_to_Textfile(int px1, int py1, int px2, int py2)
{
    QTextStream stream( &currentlabeltxtfile );
    stream << px1 << " " << py1 << " " << px2 << " " << py2 << endl;
}

void MainWindow::Add_Line_to_TreeWidget(int px1, int py1, int px2, int py2)
{
    QTreeWidgetItem *currentLine = new QTreeWidgetItem(ui->lines_treeWidget);
    currentLine->setText(0, QString::number(px1));
    currentLine->setText(1, QString::number(py1));
    currentLine->setText(2, QString::number(px2));
    currentLine->setText(3, QString::number(py2));

    currentLine->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    //currentLine->setTextAlignment(0, Qt::AlignLeft);



}

void MainWindow::SelectLine(QTreeWidgetItem *item, int col)
{

    //qDebug() << "mousePressEvent " << ui->lines_treeWidget->currentIndex().row();
    //QTreeWidgetItem* item = ui->files_treeWidget->currentIndex();
    //QTreeWidgetItem* item = ui->treeWidget->topLevelItem(last_select_item_index);

    //QString imagename = currentlyOpenedDir+QDir::separator()+item->text(0);
    //qDebug() << item->text(0);

    currentSelectingLineIndex=ui->lines_treeWidget->currentIndex().row();
    TempHilightLine(item->text(0).toInt(),item->text(1).toInt(),item->text(2).toInt(),item->text(3).toInt());

}

void MainWindow::TempHilightLine(int tx1, int ty1, int tx2, int ty2)
{

    tempimage = currentimage;
    //QPainter painter(&tempimage);
    QPainter *painter = new QPainter(&tempimage);
    QPen myPen(Qt::yellow, 1, Qt::SolidLine);
    painter->setPen(myPen);

    painter->drawLine(tx1, ty1, tx2, ty2);
    delete painter;
    ui->imageLabel->setPixmap(tempimage);

    //show line wide
    diffx = qFabs(tx1-tx2);
    diffy = qFabs(ty1-ty2);
    ui->linewide_label->setText(QString::number(diffx) +", "+ QString::number(diffy));
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
    Delete_Textfile();
    DrawImageLabel_WriteLabelFile_fromWidgetItem();

    //hilight current selecting item
    on_lines_treeWidget_itemSelectionChanged();
}
void MainWindow::Delete_Textfile()
{
    currentlabeltxtfile.close();

    if(currentlabeltxtfile.remove()) // delete file
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

void MainWindow::DrawImageLabel_WriteLabelFile_fromWidgetItem()
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

        //QPainter painter(&currentimage);
        QPainter *painter = new QPainter(&currentimage);
        QPen myPen(Qt::red, 1, Qt::SolidLine);
        painter->setPen(myPen);
        painter->drawLine(ix1,iy1,ix2,iy2);
        delete painter;
        ui->imageLabel->setPixmap(currentimage);

        Add_Line_to_Textfile(ix1,iy1,ix2,iy2);

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
void MainWindow::Button_zoomin_clicked()
{
    double newzoom = ui->zoom_SpinBox->value()+1.0;
    if (newzoom <= ui->zoom_SpinBox->maximum() && newzoom >= ui->zoom_SpinBox->minimum())
    {
        ui->zoom_SpinBox->setValue(newzoom);
        ZoomImage(newzoom);
    }
}
void MainWindow::Button_zoomout_clicked()
{
    double newzoom = ui->zoom_SpinBox->value()-1.0;
    if (newzoom <= ui->zoom_SpinBox->maximum() && newzoom >= ui->zoom_SpinBox->minimum())
    {
        ui->zoom_SpinBox->setValue(newzoom);
        ZoomImage(newzoom);
    }
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
    //qDebug() << "on_scroll vertical " << value;
    print_scrollbar_value();
}
void MainWindow::on_scroll_h(int value)
{
    //qDebug() << "on_scroll horizontal " << value;
    print_scrollbar_value();
}

void MainWindow::Button_generatelabel_clicked()
{
    //QDir dir;
    //dir.mkpath();

    QString path=currentlyOpenedDir + QDir::separator() + "label";
    QDir dir(path);
    if (!dir.exists())
    {
      dir.mkpath(path);
    }


    int totalfiles = ui->files_treeWidget->topLevelItemCount();
    qDebug() << "totalfiles " << totalfiles;

    if(totalfiles==0)
    {
        return;
    }
    for (int i = 0; i < totalfiles; ++i) // run through each image file show in the widget
    {
        QTreeWidgetItem *item = ui->files_treeWidget->topLevelItem(i);
        QString imagename = currentlyOpenedDir + QDir::separator() + item->text(0);
        QPixmap refimg(imagename);

        //create image
        QPixmap pixmap( refimg.width(), refimg.height() );
        pixmap.fill( Qt::black );

        //open txt file
        currentlabeltxtfile.close(); //close the current one

        QString txtfilename = imagename.section('.',0,0) + ".txt";
        //qDebug() << "txtfilename " << txtfilename;

        currentlabeltxtfile.setFileName(txtfilename);
        if ( currentlabeltxtfile.open(QIODevice::ReadOnly) ) //create new if not exist
        {
            qDebug() << "opened  " << txtfilename;
            QTextStream in(&currentlabeltxtfile);
            QString line = in.readLine();
            while (!line.isNull())
            {
                if(line.isEmpty()) return; // for last line = ""

                ix1 = line.section(' ',0,0).toInt();
                iy1 = line.section(' ',1,1).toInt();
                ix2 = line.section(' ',2,2).toInt();
                iy2 = line.section(' ',3,3).toInt();
                qDebug() << "line from" << ix1 << ","  << iy1 << " to " << ix2 << "," << iy2;

                //QPainter painter(&pixmap);
                QPainter *painter = new QPainter(&pixmap);
                painter->setRenderHint( QPainter::Antialiasing );
                QPen myPen(Qt::white, 1, Qt::SolidLine);
                painter->setPen(myPen);
                painter->drawLine(ix1,iy1,ix2,iy2);
                delete painter;
                //QString imgnameonly = imagename.section('/',-1,-1);
                QString outputpath= path + QDir::separator() + imagename.section('/',-1,-1);
                qDebug() << outputpath;
                pixmap.save(outputpath);


                line = in.readLine();

            }

        }
        else
        {
            qDebug() << "not opened  " << txtfilename;

        }


//pixmap.save(QDir->currentPath() + QDir::separator()+ "path.png" );
/*
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

        Add_Line_to_Textfile(ix1,iy1,ix2,iy2);
*/
    }
}
void MainWindow::Button_ccwrotation_clicked()
{/*
    int rotval = ui->rotation_lineEdit->text().toInt() *-1;
    QPixmap rotimg=currentimage;
    QMatrix rm;
    rm.rotate(rotval);
    rotimg = rotimg.transformed(rm);
    ui->imageLabel->setPixmap(rotimg);
    currentimage=rotimg;*/
}
void MainWindow::Button_cwrotation_clicked()
{/*
    int rotval = ui->rotation_lineEdit->text().toInt();

    QPixmap img(fileName);
    ui->imageLabel->setPixmap(img);
    ui->imageLabel->adjustSize();
    ui->zoom_SpinBox->setValue(1.0);
    ZoomImage(1.0);
    rawimage=img;
    currentimage=img;
*/
    /*
    QPixmap rotimg=currentimage;
    QMatrix rm;
    rm.rotate(rotval);
    rotimg = rotimg.transformed(rm);
    ui->imageLabel->setPixmap(rotimg);
    currentimage=rotimg;
*/
}
void MainWindow::Button_saveimg_clicked()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCancel_line_triggered()
{
    dstate=start;
}
void MainWindow::Select_last_line()
{
    int totallines = ui->lines_treeWidget->topLevelItemCount();
    QTreeWidgetItem* item = ui->lines_treeWidget->topLevelItem(totallines-1);
    ui->lines_treeWidget->setCurrentItem(item);
    SelectLine(item,0);  // this will do     TempHilightLine(sx1,sy1,sx2,sy2);
}
void MainWindow::on_bt_x_minus_clicked()
{
    if(currentSelectingLineIndex==-1) return;
    //currentSelectingLineIndex=ui->lines_treeWidget->currentIndex().row();
    QTreeWidgetItem* item = ui->lines_treeWidget->topLevelItem(currentSelectingLineIndex);

    int sx1=item->text(0).toInt();
    int sy1=item->text(1).toInt();
    int sx2=item->text(2).toInt();
    int sy2=item->text(3).toInt();

    if(sx1>0) sx1--;
    if(sx2>0) sx2--;

    //rewrite line widget item
    item->setText(0, QString::number(sx1));
    item->setText(1, QString::number(sy1));
    item->setText(2, QString::number(sx2));
    item->setText(3, QString::number(sy2));

    //clear label img and label txt file, then rewrite all data from line widget
    currentimage=rawimage;
    Delete_Textfile();
    DrawImageLabel_WriteLabelFile_fromWidgetItem();
    SelectLine(item,0); // temphilight line

}

void MainWindow::on_bt_x_plus_clicked()
{
    if(currentSelectingLineIndex==-1) return;
    //currentSelectingLineIndex=ui->lines_treeWidget->currentIndex().row();
    QTreeWidgetItem* item = ui->lines_treeWidget->topLevelItem(currentSelectingLineIndex);

    int sx1=item->text(0).toInt();
    int sy1=item->text(1).toInt();
    int sx2=item->text(2).toInt();
    int sy2=item->text(3).toInt();

    //index range [0,width-1]
    if(sx1<currentimage.width()-1) sx1++;
    if(sx2<currentimage.width()-1) sx2++;

    //rewrite line widget item
    item->setText(0, QString::number(sx1));
    item->setText(1, QString::number(sy1));
    item->setText(2, QString::number(sx2));
    item->setText(3, QString::number(sy2));

    //clear label img and label txt file, then rewrite all data from line widget
    currentimage=rawimage;
    Delete_Textfile();
    DrawImageLabel_WriteLabelFile_fromWidgetItem();
    SelectLine(item,0); // temphilight line


}

void MainWindow::on_bt_y_minus_clicked()
{
    if(currentSelectingLineIndex==-1) return;
    //currentSelectingLineIndex=ui->lines_treeWidget->currentIndex().row();
    QTreeWidgetItem* item = ui->lines_treeWidget->topLevelItem(currentSelectingLineIndex);

    int sx1=item->text(0).toInt();
    int sy1=item->text(1).toInt();
    int sx2=item->text(2).toInt();
    int sy2=item->text(3).toInt();

    if(sy1>0) sy1--;
    if(sy2>0) sy2--;

    //rewrite line widget item
    item->setText(0, QString::number(sx1));
    item->setText(1, QString::number(sy1));
    item->setText(2, QString::number(sx2));
    item->setText(3, QString::number(sy2));

    //clear label img and label txt file, then rewrite all data from line widget
    currentimage=rawimage;
    Delete_Textfile();
    DrawImageLabel_WriteLabelFile_fromWidgetItem();
    SelectLine(item,0); // temphilight line

}

void MainWindow::on_bt_y_plus_clicked()
{
    if(currentSelectingLineIndex==-1) return;
    //currentSelectingLineIndex=ui->lines_treeWidget->currentIndex().row();
    QTreeWidgetItem* item = ui->lines_treeWidget->topLevelItem(currentSelectingLineIndex);

    int sx1=item->text(0).toInt();
    int sy1=item->text(1).toInt();
    int sx2=item->text(2).toInt();
    int sy2=item->text(3).toInt();

    //index range [0,width-1]
    if(sy1<currentimage.height()-1) sy1++;
    if(sy2<currentimage.height()-1) sy2++;

    //rewrite line widget item
    item->setText(0, QString::number(sx1));
    item->setText(1, QString::number(sy1));
    item->setText(2, QString::number(sx2));
    item->setText(3, QString::number(sy2));

    //clear label img and label txt file, then rewrite all data from line widget
    currentimage=rawimage;
    Delete_Textfile();
    DrawImageLabel_WriteLabelFile_fromWidgetItem();
    SelectLine(item,0); // temphilight line

}

void MainWindow::on_files_treeWidget_itemSelectionChanged()
{
    isLineWidgetEditable=false;

    int SelectingIndex = ui->files_treeWidget->currentIndex().row(); //assign a current selecting index
    if(SelectingIndex==-1) return;
    QTreeWidgetItem *item = ui->files_treeWidget->topLevelItem(SelectingIndex);

    SelectImgFile(item,0);
}

void MainWindow::on_lines_treeWidget_itemSelectionChanged()
{
    int SelectingIndex = ui->lines_treeWidget->currentIndex().row(); //assign a current selecting index
    qDebug() <<"SelectingIndex " <<SelectingIndex;

    if(SelectingIndex==-1) return;
    QTreeWidgetItem *item = ui->lines_treeWidget->topLevelItem(SelectingIndex);

    SelectLine(item,0);
}

void MainWindow::on_lines_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    //qDebug() << "column" << QString::number(column) << " selected";
    ui->lines_treeWidget->editItem(item, column); //allow input of new value

}

// # Trigger this when
//  - modify line position,
//  - adding line read from textfile,
//  - draw a new line.
void MainWindow::on_lines_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    //qDebug() << "column" << QString::number(column) << " changed";
    // updated draw label and label txt file according to the new line value
    if(isLoadingLabel)
    {
        //qDebug() << " on_lines_treeWidget_itemChanged isLoadingLabel " << isLoadingLabel;
    }

    if(isLineWidgetEditable)
    {
        //qDebug() << " on_lines_treeWidget_itemChanged isLoadingLabel " << isLoadingLabel;
        currentimage=rawimage;
        Delete_Textfile();
        DrawImageLabel_WriteLabelFile_fromWidgetItem();
        SelectLine(item,0); // temphilight line
    }


}

void MainWindow::on_actionToggle_AlignXY_triggered()
{
    qDebug() << "alignedxy_checkBox " << ui->alignedxy_checkBox->isChecked();
    if(ui->alignedxy_checkBox->isChecked())
        ui->alignedxy_checkBox->setChecked(false);
    else
        ui->alignedxy_checkBox->setChecked(true);
}

void MainWindow::on_actionToggle_DrawNext_triggered()
{
    qDebug() << "drawnext_checkBox " << ui->drawnext_checkBox->isChecked();
    if(ui->drawnext_checkBox->isChecked())
        ui->drawnext_checkBox->setChecked(false);
    else
        ui->drawnext_checkBox->setChecked(true);
}

void MainWindow::on_actionSee_shortcut_triggered()
{
    QString str = "Select folder: Ctrl+O \n"
                  "Generate Label image: Ctrl+G \n"
                  "Zoom in: + \n"
                  "Zoom out: - \n"
                  "Next image: > \n"
                  "Prev image: < \n"
                  "Delete line: Del \n"
                  "Cancel line: Esc \n"
                  "Toggle align xy: Ctrl+A \n"
                  "Toggle draw next: Ctrl+D \n";

    //str = QString("name: %1\nsurname: %2\ndata: %3").arg(...).arg(...).arg(...);
    QMessageBox::information(0, "Shortcut keys", str);
 /*
    QMessageBox::information(
        this,
        tr("Shortcut keys"),
        tr("Select folder: Ctrl+O"),
        tr("Generate Label image: Ctrl+G"),
        tr("Zoom in: +"),
        tr("Zoom out: -"),
        tr("Next image: >"),
        tr("Prev image: <"),
        tr("Delete line: Del"),
        tr("Cancel line: Esc"),
        tr("Toggle align xy: Ctrl+A"),
        tr("Toggle draw next: Ctrl+D")
        );*/
}

void MainWindow::on_bt_save_label_clicked()
{
    Delete_Textfile();
    DrawImageLabel_WriteLabelFile_fromWidgetItem();
}

void MainWindow::on_bt_dup_label_clicked()
{

    QTreeWidgetItem *item = ui->files_treeWidget->topLevelItem(currentSelectingImageIndex);

    QString imagename = currentlyOpenedDir + QDir::separator() + item->text(0);
    QString current_txtfilename = imagename.section('.',0,0) + ".txt";
    qDebug() << "-current_txtfilename " << current_txtfilename;

    QString file_to_duplicate  = QFileDialog::getOpenFileName(this, "Choose a text to duplicate for "+item->text(0), currentlyOpenedDir,"label(*.txt)");
    qDebug() << "-file_to_duplicate " << file_to_duplicate;

    //QString filePath = QFileDialog::getOpenFileName(this ,
    //                                                QObject::tr("Pdf files"),
    //      "C:/", "books(*.pdf)");



    //QFileInfo fi(filePath);
    //QString fileName= fi.fileName();
    //QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    //QString destinationPath= desktopPath+QDir::separator()+fileName;
    currentlabeltxtfile.close();
    currentlabeltxtfile.remove();

    if(QFile::copy(file_to_duplicate, current_txtfilename))
    {
        qDebug() << "copy success";

        currentimage=rawimage;
        ui->lines_treeWidget->clear();

        ShowImage(imagename);
        dstate=start;
        LoadLabelTxtFile(current_txtfilename);
    }
    else
        qDebug() << "copy failed";

}

void MainWindow::on_lines_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    isLineWidgetEditable=true;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_bt_delete_label_clicked()
{

    QTreeWidgetItem *item = ui->files_treeWidget->topLevelItem(currentSelectingImageIndex);

    QString imagename = currentlyOpenedDir + QDir::separator() + item->text(0);
    QString current_txtfilename = imagename.section('.',0,0) + ".txt";
    qDebug() << "-current_txtfilename " << current_txtfilename;

    QMessageBox msgBox;
    msgBox.setText("Delete label textfile");
    msgBox.setInformativeText("Are you sure to delete "+ item->text(0) +" ?");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Yes:
                currentlabeltxtfile.close();
                currentlabeltxtfile.remove();

                currentimage=rawimage;
                ui->lines_treeWidget->clear();

                ShowImage(imagename);
                dstate=start;
                LoadLabelTxtFile(current_txtfilename);

              break;
          case QMessageBox::No:
              // Don't Save was clicked
              break;
          default:
              // should never be reached
              break;
        }



}
