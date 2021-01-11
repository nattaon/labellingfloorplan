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

    connect(ui->files_treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(SelectImgFile_ShowImgLoadlabel(QTreeWidgetItem *, int)));
    //connect(ui->lines_treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(SelectLine(QTreeWidgetItem *, int)));
    connect(ui->zoom_SpinBox, SIGNAL(valueChanged(double)), this, SLOT(ZoomImage(double)));


    ui->files_treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->files_treeWidget->header()->setStretchLastSection(true);

    ui->lines_treeWidget->setHeaderHidden(false); // Show header of treeWidget
    ui->lines_treeWidget->header()->resizeSection(0, 60);
    ui->lines_treeWidget->header()->resizeSection(1, 45);
    ui->lines_treeWidget->header()->resizeSection(2, 45);
    //ui->lines_treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection); // for use ctrl to select multiple item

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

    //currentlyOpenedDir="/home/nattaon/ply/aligned-beike/histograme";
    //currentlyOpenedDir="/home/okuboali/nattaon_ws2/sceneNN_histograme/histograme";
    currentlyOpenedDir = "/home/okuboali/awork_Dec2020/histograme_sceneNNv02";
    //currentlyOpenedDir = "../labeltest"; // by calling a relative path like this, the labeling file failed to load..
    ui->foldername_lineEdit->setText(currentlyOpenedDir);
    ListImgInFolder();

    isLineWidgetEditable=false;
    dstate=none;
    isLoadingLabel=false;
    lineConnectMode=false;
    //dstate=start;
    zoomFactor=1.0;
    isCtrlPress=false;

    currentSelectingImageIndex=-1;
    currentSelectingLineIndex=-1;
    LineIndex1_to_connect=-1;
    ctrl_lock_line_index=-1;


    //txtfile = new ReadWriteFile();
    //QPoint p = ui->scrollArea->geometry().topLeft();
    //qDebug() << "ui->scrollArea topLeft " << p;

    isMouseinLabellingArea=false;

    QCursor cursor(Qt::CrossCursor);
    QApplication::setOverrideCursor(cursor);
    QApplication::changeOverrideCursor(cursor);

}
void MainWindow::resizeEvent(QResizeEvent *e)
{
    // Enter this function, when the window size is changed.

    //qDebug() << "resize window " << e->size().width() << "*" << e->size().height();
    int height_of_treewidget = ( e->size().height() - ui->widget_tools->height())/2;

    ui->files_treeWidget->move(10,0);
    ui->files_treeWidget->resize(ui->files_treeWidget->width(),height_of_treewidget-30);

    ui->widget_tools->move(10,ui->files_treeWidget->geometry().bottom());

    ui->lines_treeWidget->move(10,ui->widget_tools->geometry().bottom());
    ui->lines_treeWidget->resize(ui->lines_treeWidget->width(),height_of_treewidget-30);

    int foldername_width = e->size().width() - ui->foldername_lineEdit->geometry().left() -30;
    ui->foldername_lineEdit->resize(foldername_width, ui->foldername_lineEdit->height());


    QPoint p = ui->scrollArea->geometry().topLeft();
    int newwidth = e->size().width()-p.x()-30;
    int newheight = e->size().height()-p.y()-70;
    ui->scrollArea->resize(newwidth,newheight);
    //qDebug() << "new scollarea size " << newwidth << "*" << newheight;

}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if( (dynamic_cast<QKeyEvent*>(event)))// && (obj==ui->lines_treeWidget))
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent * >(event);
        if (keyEvent->key()==Qt::Key_Control && event->type() == QEvent::KeyPress )
        {
            qDebug() << " CTRL press !!!";
            isCtrlPress = true;
            ctrl_lock_line_index=currentSelectingLineIndex;
        }
        else if (keyEvent->key()==Qt::Key_Control && event->type() == QEvent::KeyRelease )
        {
            qDebug() << " CTRL release !!!";
            isCtrlPress = false;
            //ctrl_lock_line_index=-1;
        }
    }

    //detect mouse click in draawing area
    if( (dynamic_cast<QMouseEvent*>(event)) && (obj==ui->imageLabel))
    {
        isMouseinLabellingArea=true;

        QKeyEvent *keyEvent = static_cast<QKeyEvent * >(event);
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);


        int mousex=mouseEvent->pos().x();
        int mousey=mouseEvent->pos().y();

        //QString mouseposition = QString("(%1,%2)").arg(mousex).arg(mousey);
        //ui->mousepos_label->setText(mouseposition);
        QString mouseposition = QString("%1,%2").arg((int)round(mousex/zoomFactor)).arg((int)round(mousey/zoomFactor));


        switch(dstate)
        {
            case none: break;
            case start: ui->mousepos_label->setText("start");  ui->x1y1_label->setText(mouseposition); break; //TempMarkPixel(mousex,mousey);
            case end : ui->mousepos_label->setText("end");  TempDrawLine(mousex,mousey); ui->x2y2_label->setText(mouseposition); break;
        }
        //qDebug() << "current draw state: " << dstate;


        if (event->type() == QEvent::MouseButtonPress)
        {
            //QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            qDebug()<< obj->metaObject()->className() << ", clicked at " << mousex << "," << mousey;
            isLineWidgetEditable=false;

            // click a mouse when overlay on a line
            if(mouse_overlay_on_line!=-1)
            {
                qDebug()<< "Click on item " << mouse_overlay_on_line;

                QTreeWidgetItem* item = ui->lines_treeWidget->topLevelItem(mouse_overlay_on_line);
                ui->lines_treeWidget->setCurrentItem(item);
                mouse_overlay_on_line=-1;
                //QTreeWidgetItem *item = ui->plyfiles_treeWidget->topLevelItem(currentSelectingPlyIndex);
                //ui->lines_treeWidget->currentIndex().row()
                //item->setSelected(true);
                //on_lines_treeWidget_itemClicked(item,0);

                int SelectingIndex = ui->lines_treeWidget->currentIndex().row(); //assign a current selecting index
                qDebug() <<"MouseButtonPress SelectingIndex " <<SelectingIndex << ", " <<currentSelectingLineIndex;
                return false;
            }


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
        else
        {
            //int x=mousex; //
            int x = (int)round(mousex/zoomFactor);
            //int y=mousey;
            int y = (int)round(mousey/zoomFactor);
            double error =0.1;

            int totallines = ui->lines_treeWidget->topLevelItemCount();
            for (int i = 0; i < totallines; ++i)
            {
                QTreeWidgetItem *item = ui->lines_treeWidget->topLevelItem(i);
                //item->setText(0, QString::number(i + 1));
                int x1 = item->text(0).toInt();
                int y1 = item->text(1).toInt();
                int x2 = item->text(2).toInt();
                int y2 = item->text(3).toInt();

                double AB = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
                double AP = sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
                double PB = sqrt((x2-x)*(x2-x)+(y2-y)*(y2-y));
                //

                if(AP + PB - error < AB && AB< AP + PB + error && mouse_overlay_on_line!=i)
                {
                    TempHilightLine(x1,y1,x2,y2);
                    mouse_overlay_on_line=i;
                    //qDebug() <<"overlay at line" << mouse_overlay_on_line << " . AB  is " << AB << ", AP=" << AP << ", PB=" <<PB;
                    return false;
                    //qDebug() << " Point   " << x << y << "is on line " <<x1 <<y1<<x2<<y2;
                }
                else
                {
                    mouse_overlay_on_line=-1;
                    //qDebug() << "AB  is " << AB << ", AP=" << AP << ", PB=" <<PB;
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
        SelectImgFile_ShowImgLoadlabel(item,0); //item is the row, column=0
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
        SelectImgFile_ShowImgLoadlabel(item,0);
    }
}
void MainWindow::SelectImgFile_ShowImgLoadlabel(QTreeWidgetItem *item, int col)
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

    //QString
    imagename = currentlyOpenedDir + QDir::separator() + item->text(0);
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

    qDebug() << "SelectLine " << ui->lines_treeWidget->currentIndex().row();
    //QTreeWidgetItem* item = ui->files_treeWidget->currentIndex();
    //QTreeWidgetItem* item = ui->treeWidget->topLevelItem(last_select_item_index);

    //QString imagename = currentlyOpenedDir+QDir::separator()+item->text(0);
    //qDebug() << item->text(0);

    currentSelectingLineIndex=ui->lines_treeWidget->currentIndex().row();
    TempHilightLine(item->text(0).toInt(),item->text(1).toInt(),item->text(2).toInt(),item->text(3).toInt());

}

void MainWindow::TempHilightLine(int tx1, int ty1, int tx2, int ty2)
{
    qDebug() << "TempHilightLine " << tx1, ty1, tx2, ty2;
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

    //show line angle
    float angle = Calculate_angle(tx1, ty1, tx2, ty2);
    ui->lineangle_label->setText(QString::number(angle));
}
void MainWindow::TempHilight2ndLine(int tx1, int ty1, int tx2, int ty2)
{
    qDebug() << "TempHilight2ndLine " << tx1, ty1, tx2, ty2;
    //tempimage = currentimage;
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

    //show line angle
    float angle = Calculate_angle(tx1, ty1, tx2, ty2);
    ui->lineangle_label->setText(QString::number(angle));
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
void MainWindow::CalcuatePaddedSize(int &width, int &height)
{
    float divisor = 32.0;
    width = qCeil( width / divisor ) * divisor;
    height = qCeil( height / divisor ) * divisor;
}
void MainWindow::CalcuateShowPaddedSize(int imgwidth, int imgheight)
{
    int new_w = imgwidth;
    int new_h = imgheight;
    CalcuatePaddedSize(new_w,new_h);

    int pad_w = new_w-currentimage.width();
    int pad_h = new_h-currentimage.height();
    QString padimgsize = QString("%1 x %2").arg(pad_w).arg(pad_h);
    ui->paddingsize_label->setText(padimgsize);
    qDebug() << "padimgsize " << padimgsize;

    int pad_top = pad_h*0.5;
    int pad_down = pad_h-pad_top;
    int pad_left = pad_w*0.5;
    int pad_right = pad_w-pad_left;
    Set_pad_value(pad_top, pad_down, pad_left, pad_right);
}

void MainWindow::ShowImage(const QString &fileName)
{
    qDebug() << "ShowImage: " << fileName;
    QPixmap img(fileName);
    ui->imageLabel->setPixmap(img);
    ui->imageLabel->adjustSize();

    double currentzoom = ui->zoom_SpinBox->value();
    ui->zoom_SpinBox->setValue(currentzoom);
    ZoomImage(currentzoom);
    rawimage=img;
    currentimage=img;


    QString imgsize = QString("%1 x %2").arg(currentimage.width()).arg(currentimage.height());
    ui->imgsize_label->setText(imgsize);

    CalcuateShowPaddedSize(currentimage.width(), currentimage.height());



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
                //painter->setRenderHint( QPainter::Antialiasing );// this made the lind fading
                QPen myPen(Qt::white, 1, Qt::SolidLine);
                painter->setPen(myPen);
                painter->drawLine(ix1,iy1,ix2,iy2);
                delete painter;
                //QString imgnameonly = imagename.section('/',-1,-1);
                QString outputpath= path + QDir::separator() + imagename.section('/',-1,-1);
                qDebug() << outputpath;
                pixmap.save(outputpath,"PNG",100);


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

    SelectImgFile_ShowImgLoadlabel(item,0);
}

void MainWindow::on_lines_treeWidget_itemSelectionChanged()
{
    //QModelIndexList indexlist = ui->lines_treeWidget->selectionModel()->selectedRows(); //for multiple selection enable on treewidget
    //qDebug() <<"indexlist " <<indexlist.count();
    /*for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        qDebug() << index.row();
    }*/
    //selectionModel()->clearSelection();




    int SelectingIndex = ui->lines_treeWidget->currentIndex().row(); //assign a current selecting index
    qDebug() <<"on_lines_treeWidget_itemSelectionChanged SelectingIndex " <<SelectingIndex;

    if(SelectingIndex==-1) return;
    QTreeWidgetItem *item = ui->lines_treeWidget->topLevelItem(SelectingIndex);

    SelectLine(item,0);

    if(isCtrlPress && ctrl_lock_line_index>=0)
    {

        QTreeWidgetItem *pitem = ui->lines_treeWidget->topLevelItem(ctrl_lock_line_index);
        if(!pitem->isSelected())
        {
            pitem->setSelected( true );
            TempHilight2ndLine(pitem->text(0).toInt(),pitem->text(1).toInt(),pitem->text(2).toInt(),pitem->text(3).toInt());
        }

    }

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
    /*
    if(lineConnectMode == true)
    {
        //qDebug() << "LineIndex2_to_connect = " << currentSelectingLineIndex;
        ConnectLines(LineIndex1_to_connect,currentSelectingLineIndex);

    }*/
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
float MainWindow::Calculate_angle(int x1,int y1,int x2,int y2)
{
    //int u_x = x2-x1;//the current line
    //int u_y = y2-y1;

    int u_x,u_y,v_x,v_y;

    diffx = qFabs(x1-x2);
    diffy = qFabs(y1-y2);

    if(diffx ==0 || diffy ==0)
    {
        // the line is straight
        return 0.0;
    }
    else if(diffx > diffy)
    {// y is a small number (slant)
        v_x = 1; //horizontal line
        v_y = 0;
    }
    else if(diffy > diffx)
    {// x is a small number (slant)
        v_x = 0; //vertical line
        v_y = 1;
    }
    else
    {
        qDebug() << "error! calculate_angle";
    }
    u_x=diffx;
    u_y=diffy;

    float equa = (u_x*v_x + u_y*v_y) / (qSqrt(u_x*u_x + u_y*u_y) + qSqrt(v_x*v_x + v_y*v_y));
    float angle = qAcos(equa);

    return angle*180/M_PI; //rad to degree


}

void MainWindow::on_bt_straight_line_clicked()
{
    QTreeWidgetItem* selected_line = ui->lines_treeWidget->currentItem();
    int x1=selected_line->text(0).toInt();
    int y1=selected_line->text(1).toInt();
    int x2=selected_line->text(2).toInt();
    int y2=selected_line->text(3).toInt();

    diffx = qFabs(x1-x2);
    diffy = qFabs(y1-y2);

    if(diffx ==0 || diffy ==0)
    {
        // the line is straight
        return;
    }
    else if(diffx > diffy)
    {// y is a small number (slant)
        y1=y2;
    }
    else if(diffy > diffx)
    {// x is a small number (slant)
        x1=x2;
    }
    selected_line->setText(0, QString::number(x1));
    selected_line->setText(1, QString::number(y1));
    selected_line->setText(2, QString::number(x2));
    selected_line->setText(3, QString::number(y2));

    //qDebug() << "straighten " << selected_line->text(0) << "," <<selected_line->text(1)
    //         << "," << selected_line->text(2) <<"," <<selected_line->text(3);
}

void MainWindow::on_bt_connect_lines_clicked()
{
    if(currentSelectingLineIndex==-1) return;

    //QTreeWidgetItem* selected_line = ui->lines_treeWidget->currentItem();
    //int x1=selected_line->text(0).toInt();
    //int y1=selected_line->text(1).toInt();
    //int x2=selected_line->text(2).toInt();
    //int y2=selected_line->text(3).toInt();

    ConnectLines(ctrl_lock_line_index,currentSelectingLineIndex);

/*
    lineConnectMode = !lineConnectMode;

    if (lineConnectMode==true)
    {
        ui->bt_connect_lines->setStyleSheet("background-color:grey;");
        LineIndex1_to_connect=currentSelectingLineIndex;
        //qDebug() << "LineIndex1_to_connect = " << LineIndex1_to_connect;
    }
    else
    {
       ui->bt_connect_lines->setStyleSheet("");
       LineIndex1_to_connect=-1;
    }*/
}
void MainWindow::ConnectLines(int lineindex1, int lineindex2)
{
    //lineConnectMode=false;
    //ui->bt_connect_lines->setStyleSheet("");
    //LineIndex1_to_connect=-1;
    isLineWidgetEditable= true;
    qDebug() << "ConnectLines " <<lineindex1 << lineindex2;


    if(lineindex1==lineindex2) return;
    if(lineindex1 == -1 || lineindex2 == -1) return;

    QTreeWidgetItem* item1 = ui->lines_treeWidget->topLevelItem(lineindex1);
    QTreeWidgetItem* item2 = ui->lines_treeWidget->topLevelItem(lineindex2);

    QLineF l1,l2;  
    l1.setP1(QPointF(item1->text(0).toInt(),item1->text(1).toInt()));
    l1.setP2(QPointF(item1->text(2).toInt(),item1->text(3).toInt()));
    l2.setP1(QPointF(item2->text(0).toInt(),item2->text(1).toInt()));
    l2.setP2(QPointF(item2->text(2).toInt(),item2->text(3).toInt()));

    hist_p1 = l1;
    hist_p2 = l2;
    hist_connect_item1 = lineindex1;
    hist_connect_item2 = lineindex2;

    QPointF intersect;
    l1.intersect(l2,&intersect);
    //qDebug() << "intersect " << intersect;
    //qDebug() << "l1 " << l1.p1() << l1.p2();
    //qDebug() << "l2 " << l2.p1() << l2.p2();

    if(intersect.x() < 0 || intersect.y() <0)
    {
        qDebug() << "intersect error " << intersect;
        return;
    }
    float dist_to_l1p1 = qPow(l1.p1().x()-intersect.x(),2) + qPow(l1.p1().y()-intersect.y(),2);
    float dist_to_l1p2 = qPow(l1.p2().x()-intersect.x(),2) + qPow(l1.p2().y()-intersect.y(),2);
    float dist_to_l2p1 = qPow(l2.p1().x()-intersect.x(),2) + qPow(l2.p1().y()-intersect.y(),2);
    float dist_to_l2p2 = qPow(l2.p2().x()-intersect.x(),2) + qPow(l2.p2().y()-intersect.y(),2);

    //qDebug() << "dist^2_to_l1p1 " << dist_to_l1p1;
    //qDebug() << "dist^2_to_l1p2 " << dist_to_l1p2;
    //qDebug() << "dist^2_to_l2p1 " << dist_to_l2p1;
    //qDebug() << "dist^2_to_l2p2 " << dist_to_l2p2;

    intersect.setX(int(intersect.x()));
    intersect.setY(int(intersect.y()));

    if(dist_to_l1p1 < dist_to_l1p2)
    {//
        qDebug() <<"move line1 (" << lineindex1 << ") p1 to the intersect point" << intersect;
        item1->setText(0, QString::number(intersect.x()));
        item1->setText(1, QString::number(intersect.y()));
    }
    else if(dist_to_l1p1 > dist_to_l1p2)
    {//
        qDebug() <<"move line1 (" << lineindex1 << ")p2 to the intersect point" << intersect;
        item1->setText(2, QString::number(intersect.x()));
        item1->setText(3, QString::number(intersect.y()));
    }

    if(dist_to_l2p1 < dist_to_l2p2)
    {//
        qDebug() <<"move line2 (" << lineindex2 << ")p1 to the intersect point" << intersect;
        item2->setText(0, QString::number(intersect.x()));
        item2->setText(1, QString::number(intersect.y()));
    }
    else if(dist_to_l2p1 > dist_to_l2p2)
    {//
        qDebug() <<"move line2 (" << lineindex2 << ")p2 to the intersect point" << intersect;
        item2->setText(2, QString::number(intersect.x()));
        item2->setText(3, QString::number(intersect.y()));
    }

    //clear selection
    //item1->setSelected( false );
    //item2->setSelected( false );
    currentSelectingLineIndex=-1;
    ctrl_lock_line_index=-1;
}

void MainWindow::on_bt_undo_connect_lines_clicked()
{
    if (!hist_p1.isNull())
    {
        QTreeWidgetItem* item1 = ui->lines_treeWidget->topLevelItem(hist_connect_item1);
        item1->setText(0, QString::number(hist_p1.p1().x()));
        item1->setText(1, QString::number(hist_p1.p1().y()));
        item1->setText(2, QString::number(hist_p1.p2().x()));
        item1->setText(3, QString::number(hist_p1.p2().y()));
        //ConnectLines(ctrl_lock_line_index,currentSelectingLineIndex)
        hist_p1.setP1(QPointF(0,0));
        hist_p1.setP2(QPointF(0,0));
    }
    if (!hist_p2.isNull())
    {
        QTreeWidgetItem* item2 = ui->lines_treeWidget->topLevelItem(hist_connect_item2);
        item2->setText(0, QString::number(hist_p2.p1().x()));
        item2->setText(1, QString::number(hist_p2.p1().y()));
        item2->setText(2, QString::number(hist_p2.p2().x()));
        item2->setText(3, QString::number(hist_p2.p2().y()));
        //ConnectLines(ctrl_lock_line_index,currentSelectingLineIndex)
        hist_p2.setP1(QPointF(0,0));
        hist_p2.setP2(QPointF(0,0));
    }

}
void MainWindow::Set_pad_value(int top, int down, int left, int right)
{
    ui->lineEdit_pad_top->setText(QString::number(top));
    ui->lineEdit_pad_down->setText(QString::number(down));
    ui->lineEdit_pad_left->setText(QString::number(left));
    ui->lineEdit_pad_right->setText(QString::number(right));
}
void MainWindow::on_bt_pad_top_clicked()
{
    int pad = ui->lineEdit_pad_top->text().toInt();

    QPixmap pixmap(rawimage.width(),rawimage.height()+pad);
    pixmap.fill(Qt::black);
    QPainter painter(&pixmap);
    painter.drawPixmap(0,pad,rawimage);

    if(ui->padlabel_checkBox->isChecked())
        PaddingAllLabel(pad, 0, 0, 0);

    Save_padding_image_and_reload(pixmap);
}

void MainWindow::on_bt_pad_down_clicked()
{
    int pad = ui->lineEdit_pad_down->text().toInt();

    QPixmap pixmap(rawimage.width(),rawimage.height()+pad);
    pixmap.fill(Qt::black);
    QPainter painter(&pixmap);
    painter.drawPixmap(0,0,rawimage);


    Save_padding_image_and_reload(pixmap);
}

void MainWindow::on_bt_pad_left_clicked()
{
    int pad = ui->lineEdit_pad_left->text().toInt();

    QPixmap pixmap(rawimage.width()+pad,rawimage.height());
    pixmap.fill(Qt::black);
    QPainter painter(&pixmap);
    painter.drawPixmap(pad,0,rawimage);

    if(ui->padlabel_checkBox->isChecked())
        PaddingAllLabel(0, 0, pad, 0);

    Save_padding_image_and_reload(pixmap);
}

void MainWindow::on_bt_pad_right_clicked()
{
    int pad = ui->lineEdit_pad_right->text().toInt();

    QPixmap pixmap(rawimage.width()+pad,rawimage.height());
    pixmap.fill(Qt::black);
    QPainter painter(&pixmap);
    painter.drawPixmap(0,0,rawimage);


    Save_padding_image_and_reload(pixmap);
}
void MainWindow::on_bt_pad_all_clicked()
{
    int pad_top = ui->lineEdit_pad_top->text().toInt();
    int pad_down = ui->lineEdit_pad_down->text().toInt();
    int pad_left = ui->lineEdit_pad_left->text().toInt();
    int pad_right = ui->lineEdit_pad_right->text().toInt();

    QPixmap pixmap(rawimage.width()+pad_left+pad_right,rawimage.height()+pad_top+pad_down);
    pixmap.fill(Qt::black);
    QPainter painter(&pixmap);
    painter.drawPixmap(pad_left,pad_top,rawimage);

    if(ui->padlabel_checkBox->isChecked())
        PaddingAllLabel(pad_top, pad_down, pad_left, pad_right);

    Save_padding_image_and_reload(pixmap);


}
void MainWindow::PaddingAllLabel(int pad_top, int pad_down, int pad_left, int pad_right)
{
    //pad down and pad right no need for padding the label

    int totallines = ui->lines_treeWidget->topLevelItemCount();
    qDebug() << "PaddingAllLabel " << pad_top << pad_down <<  pad_left <<pad_right;

    if(totallines==0)
    {
        //ui->imageLabel->setPixmap(currentimage);
        return;
    }
    for (int i = 0; i < totallines; ++i)
    {
        QTreeWidgetItem *item = ui->lines_treeWidget->topLevelItem(i);
        //item->setText(0, QString::number(i + 1));
        int px1 = item->text(0).toInt();
        int py1 = item->text(1).toInt();
        int px2 = item->text(2).toInt();
        int py2 = item->text(3).toInt();

        qDebug() << i << " : " << px1 << py1 << px2 << py2;
        px1=px1+pad_left;
        py1=py1+pad_top;
        px2=px2+pad_left;
        py2=py2+pad_top;
        qDebug() << i << " : " << px1 << py1 << px2 << py2 <<"\n";

        item->setText(0, QString::number(px1));
        item->setText(1, QString::number(py1));
        item->setText(2, QString::number(px2));
        item->setText(3, QString::number(py2));

    }


}

void MainWindow::Save_padding_image_and_reload(QPixmap pixmap)
{
    pixmap.save(imagename,"PNG",100);

    ShowImage(imagename);
    dstate=start;



    QString txtfilename = imagename.section('.',0,0) + ".txt";
    qDebug() << "txtfilename " << txtfilename;
    //txtfile->OpenTxtFileLabel(txtfilename.toStdString());
    //LoadLabelTxtFile(txtfilename);

    Delete_Textfile();
    DrawImageLabel_WriteLabelFile_fromWidgetItem();

}



void MainWindow::on_actionConnect_Lines_triggered()
{
    on_bt_connect_lines_clicked();
}

void MainWindow::on_actionDuplicate_Label_txt_triggered()
{
    on_bt_dup_label_clicked();
}

void MainWindow::on_actionMove_line_1_px_to_right_triggered()
{
    on_bt_x_plus_clicked();
}

void MainWindow::on_actionMove_line_1_px_to_left_triggered()
{
    on_bt_x_minus_clicked();
}

void MainWindow::on_actionMove_line_1_px_to_top_triggered()
{
    on_bt_y_minus_clicked();
}

void MainWindow::on_actionMove_line_1_px_to_down_triggered()
{
    on_bt_y_plus_clicked();
}
