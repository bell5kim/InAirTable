#include "inairtable.h"
#include "ui_inairtable.h"

#include <iostream>
using namespace std;

#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QTextStream>

QString WX = 0;
QString WY = 0;
int nLine = 0;
QString FNAME = "";

InAirTable::InAirTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InAirTable)
{
    ui->setupUi(this);

    init();
}

InAirTable::~InAirTable()
{
    delete ui;
}


void InAirTable::init() {

     ui->tableProfile->setColumnWidth(0,150);
     ui->tableProfile->setColumnWidth(1,75);
     ui->tableProfile->setColumnWidth(2,35);
     ui->tableProfile->setColumnWidth(3,50);
     ui->tableProfile->setColumnWidth(4,50);
     ui->tableProfile->setColumnWidth(5,50);
     ui->tableProfile->setColumnWidth(6,50);
     ui->tableProfile->setColumnWidth(7,50);

     ui->tableProfile->setColumnCount(8);

     // QHeaderView *header = ui->tableProfile->horizontalHeader();
     // header->setSectionResizeMode(QHeaderView::Stretch);

     QString pwd = getenv("PWD");
     // QString XVMC_WORK = getenv("XVMC_WORK");
     QTextStream(stdout) << "*** DEBUG: PWD = " << pwd << endl;
     // QString XVMC_WORK = getenv("XVMC_WORK");
     QString XVMC_WORK = getenv("PWD");
     QTextStream(stdout) << "*** DEBUG: XVMC_WORK = " << XVMC_WORK << endl;
     QString mName = XVMC_WORK.section('/',-1);
     QTextStream(stdout) << "*** DEBUG: mName= " << mName << endl;
     ui->dataLabel->setText("<p align=center>"+mName+"</p>");
}

void InAirTable::loadData(QString fName) {
     FNAME = fName;
     QFile iFile( FNAME+".tmp" );
     QTextStream(stdout) << "*** DEBUG: fName = " << fName << endl;
     if ( iFile.open( QIODevice::ReadOnly ) ) {
      QTextStream stream( &iFile );
      QString line;
      line = stream.readLine(); // line of text excluding '\n'
      while ( !stream.atEnd() ) {
           line = stream.readLine(); // line of text excluding '\n'
           QString strLine = line.toStdString().c_str();
           strLine = strLine.simplified();
           // QTextStream(stdout) << "*** DEBUG: nLine strLine = " << nLine << " " << strLine << endl;
           if (strLine.length() != 0) nLine++;
      }
     }
     iFile.close();

     // cout << "# nLines = " << nLine << endl;
     ui->tableProfile->setRowCount(nLine);

     if ( iFile.open( QIODevice::ReadOnly) ) {
           QTextStream stream( &iFile );
           QString line;
           line = stream.readLine(); // line of text excluding '\n'
           QString headLine = line.toStdString().c_str();
           headLine = headLine.simplified();
           WX = headLine.section("WX =",1,1);
           WX = WX.section("WY =",0,0);
           WX = WX.simplified();
           WY = headLine.section("WY =",1,1);
           WY = WY.simplified();

           //QTextStream(stdout) << "#file name              fit prof        X       Y"
           //                    << "       Z               WX = " << WX
           //                    << "         WY =" << WY << endl;

           for (int i=0; i < nLine; i++) {
                 line = stream.readLine(); // line of text excluding '\n'
                 QString strLine = line.toStdString().c_str();
                 strLine = strLine.simplified();
                 if (strLine.length() != 0) {
                       QString fileName="";
                       QString fitSW="";
                       QString prof="";
                       QString xValue="", yValue="", zValue="";
                       QString width="", length="";
                       QTextStream(&strLine) >> fileName >> fitSW >> prof >> xValue >>
                                      yValue >> zValue >> width >> length;
                       //QTextStream(stdout) << fileName << "  " << fitSW << "  " << prof << "  " << xValue
                       //               << "  " << yValue << "  " << zValue << "  " << width
                       //               << "  " << length << endl;

                       QTableWidgetItem *newItemFileName = new QTableWidgetItem();
                       newItemFileName->setText(fileName);
                       newItemFileName->setTextAlignment(Qt::AlignRight);
                       //newItemFileName->setTextAlignment(Qt::AlignVCenter);
                       ui->tableProfile->setItem(i,0,newItemFileName);

                       QTableWidgetItem *checkTable = new QTableWidgetItem("Fit");
                       ui->tableProfile->setItem(i,1,checkTable);
                       checkTable->setTextAlignment(Qt::AlignHCenter);
                       //checkTable->setTextAlignment(Qt::AlignVCenter);
                       if(fitSW.contains('1')) {
                           // QTextStream(stdout) << fileName << "  " << fitSW << endl;
                           checkTable->setCheckState(Qt::Checked);
                            // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(true);
                       } else {
                            checkTable->setCheckState(Qt::Unchecked);
                            // QTextStream(stdout) << fileName << "  " << fitSW << endl;
                            // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(false);
                       }
                       QTableWidgetItem *newItemP = new QTableWidgetItem();
                       QTableWidgetItem *newItemX = new QTableWidgetItem();
                       QTableWidgetItem *newItemY = new QTableWidgetItem();
                       QTableWidgetItem *newItemZ = new QTableWidgetItem();
                       QTableWidgetItem *newItemW = new QTableWidgetItem();
                       QTableWidgetItem *newItemL = new QTableWidgetItem();

                       newItemP->setText(prof);
                       newItemP->setTextAlignment(Qt::AlignHCenter);
                       //newItemP->setTextAlignment(Qt::AlignVCenter);
                       ui->tableProfile->setItem(i,2,newItemP);

                       newItemX->setText(xValue);
                       newItemX->setTextAlignment(Qt::AlignRight);
                       //newItemX->setTextAlignment(Qt::AlignVCenter);
                       ui->tableProfile->setItem(i,3,newItemX);

                       newItemY->setText(yValue);
                       newItemY->setTextAlignment(Qt::AlignRight);
                       //newItemY->setTextAlignment(Qt::AlignVCenter);
                       ui->tableProfile->setItem(i,4,newItemY);

                       newItemZ->setText(zValue);
                       newItemZ->setTextAlignment(Qt::AlignRight);
                       //newItemZ->setTextAlignment(Qt::AlignVCenter);
                       ui->tableProfile->setItem(i,5,newItemZ);

                       newItemW->setText(width);
                       newItemW->setTextAlignment(Qt::AlignRight);
                       //newItemW->setTextAlignment(Qt::AlignVCenter);
                       ui->tableProfile->setItem(i,6,newItemW);

                       newItemL->setText(length);
                       //newItemL->setTextAlignment(Qt::AlignVCenter);
                       newItemL->setTextAlignment(Qt::AlignRight);
                       ui->tableProfile->setItem(i,7,newItemL);

                       ui->tableProfile->setRowHeight(i,20);
                }
          }
     }
     // xyToggle();
}

void InAirTable::xyToggle() {
 for (int i=0; i < nLine; i++) {
   if (ui->tableProfile->item(i,2)->text().toLower().contains('x') == 1) {
     // bool sw = radioButtonX->isChecked();
     Qt::CheckState sw = Qt::Checked;
     // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(sw);
     ui->tableProfile->item(i,1)->setCheckState(sw);
     // cout << i << " = " << dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->isChecked() << endl;
   }
   if (ui->tableProfile->item(i,2)->text().toLower().contains('y') == 1) {
     // bool sw = radioButtonY->isChecked();
     //bool sw = true;
     //dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(sw);
     Qt::CheckState sw = Qt::Checked;
     ui->tableProfile->item(i,1)->setCheckState(sw);

     // cout << i << " = "  << dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->isChecked() << endl;
   }
   if (ui->tableProfile->item(i,2)->text().toLower().contains('z') == 1) {
     // bool sw = radioButtonZ->isChecked();
     // bool sw = true;
     // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(sw);
       Qt::CheckState sw = Qt::Checked;
       ui->tableProfile->item(i,1)->setCheckState(sw);
     // cout << i << " = "  << dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->isChecked() << endl;
   }
 }
}

void InAirTable::fsToggle() {
 QString fsLimitText = ui->spinBoxFS->text();
 fsLimitText = fsLimitText.simplified();
 bool ok;
 float fsLimit = fsLimitText.toFloat(&ok);

 for (int i=0; i < nLine; i++) {
   QString xFSText = ui->tableProfile->item(i,6)->text();
   xFSText = xFSText.simplified();
   QString yFSText = ui->tableProfile->item(i,7)->text();
   yFSText = yFSText.simplified();
   float xFS = xFSText.toFloat(&ok)*10;
   float yFS = yFSText.toFloat(&ok)*10;
   //   bool lSw = radioButtonLarger->isChecked();
   // bool lSw = true;
   Qt::CheckState lSw = Qt::Checked;
   //           && dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->isChecked();
   //   bool sSw = radioButtonSmaller->isChecked();
   //bool sSw = true;
   Qt::CheckState sSw = Qt::Checked;
   //           && dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->isChecked();
   // cout << "xFS = " << xFS << "  fsLimit = " << fsLimit << endl;
   if (xFS >= fsLimit || yFS >= fsLimit)
     //dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(lSw);
     ui->tableProfile->item(i,1)->setCheckState(lSw);
   if (xFS < fsLimit && yFS < fsLimit)
     //dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(sSw);
     ui->tableProfile->item(i,1)->setCheckState(sSw);
 }
}

void InAirTable::on_pushButtonXOn_clicked()
{
    for (int i=0; i < nLine; i++) {
      if (ui->tableProfile->item(i,2)->text().toLower().contains('x')) {
        //dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(true);
          // QTextStream(stdout) << "DEBUG: X ON: " << i << endl;
          ui->tableProfile->item(i,1)->setCheckState(Qt::Checked);
      }
    }
}

void InAirTable::on_pushButtonYOn_clicked()
{
    for (int i=0; i < nLine; i++) {
      if (ui->tableProfile->item(i,2)->text().toLower().contains('y')) {
        //dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(true);
          ui->tableProfile->item(i,1)->setCheckState(Qt::Checked);
      }
    }
}

void InAirTable::on_pushButtonZOn_clicked()
{
    for (int i=0; i < nLine; i++) {
      if (ui->tableProfile->item(i,2)->text().toLower().contains('z')) {
        //dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(true);
          ui->tableProfile->item(i,1)->setCheckState(Qt::Checked);
      }
    }
}

void InAirTable::on_pushButtonXOff_clicked()
{
    for (int i=0; i < nLine; i++) {
      if (ui->tableProfile->item(i,2)->text().toLower().contains('x')) {
        // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(false);
          ui->tableProfile->item(i,1)->setCheckState(Qt::Unchecked);
      }
    }
}

void InAirTable::on_pushButtonYOff_clicked()
{
    for (int i=0; i < nLine; i++) {
      if (ui->tableProfile->item(i,2)->text().toLower().contains('y')) {
        // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(false);
          ui->tableProfile->item(i,1)->setCheckState(Qt::Unchecked);
      }
    }
}

void InAirTable::on_pushButtonZOff_clicked()
{
    for (int i=0; i < nLine; i++) {
      if (ui->tableProfile->item(i,2)->text().toLower().contains('z')) {
        // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(false);
          ui->tableProfile->item(i,1)->setCheckState(Qt::Unchecked);
      }
    }
}

void InAirTable::on_pushButtonSmallOn_clicked()
{
    QString fsLimitText = ui->spinBoxFS->text();
    fsLimitText = fsLimitText.simplified();
    bool ok;
    float fsLimit = fsLimitText.toFloat(&ok);

    for (int i=0; i < nLine; i++) {
      QString xFSText = ui->tableProfile->item(i,6)->text();
      xFSText = xFSText.simplified();
      QString yFSText = ui->tableProfile->item(i,7)->text();
      yFSText = yFSText.simplified();
      float xFS = xFSText.toFloat(&ok)*10;
      float yFS = yFSText.toFloat(&ok)*10;
      // bool sSw = true;
      Qt::CheckState sSw = Qt::Checked;
      if (xFS < fsLimit && yFS < fsLimit)
        // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(sSw);
        ui->tableProfile->item(i,1)->setCheckState(sSw);
    }
}

void InAirTable::on_pushButtonSmallOff_clicked()
{
    QString fsLimitText = ui->spinBoxFS->text();
    fsLimitText = fsLimitText.simplified();
    bool ok;
    float fsLimit = fsLimitText.toFloat(&ok);

    for (int i=0; i < nLine; i++) {
      QString xFSText = ui->tableProfile->item(i,6)->text();
      xFSText = xFSText.simplified();
      QString yFSText = ui->tableProfile->item(i,7)->text();
      yFSText = yFSText.simplified();
      float xFS = xFSText.toFloat(&ok)*10;
      float yFS = yFSText.toFloat(&ok)*10;
      // bool sSw = false;
      Qt::CheckState sSw = Qt::Checked;
      if (xFS < fsLimit && yFS < fsLimit)
        //dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(sSw);
        ui->tableProfile->item(i,1)->setCheckState(sSw);
    }
}

void InAirTable::on_pushButtonLargeOn_clicked()
{
    QString fsLimitText = ui->spinBoxFS->text();
    fsLimitText = fsLimitText.simplified();
    bool ok;
    float fsLimit = fsLimitText.toFloat(&ok);

    for (int i=0; i < nLine; i++) {
      QString xFSText = ui->tableProfile->item(i,6)->text();
      xFSText = xFSText.simplified();
      QString yFSText = ui->tableProfile->item(i,7)->text();
      yFSText = yFSText.simplified();
      float xFS = xFSText.toFloat(&ok)*10;
      float yFS = yFSText.toFloat(&ok)*10;
      // QTextStream (stdout) << xFS << " x " << yFS << " " << fsLimit << endl;
      //bool lSw = true;
      Qt::CheckState lSw = Qt::Checked;
      if (xFS >= fsLimit || yFS >= fsLimit)
        //dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(lSw);
        ui->tableProfile->item(i,1)->setCheckState(lSw);
    }
}

void InAirTable::toggleAll() {
 // bool allSw = radioButtonAll->isChecked();
 // bool allSw = true;
 Qt::CheckState allSw = Qt::Checked;
 for (int i=0; i < nLine; i++) {
   // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(allSw);
     ui->tableProfile->item(i,1)->setCheckState(allSw);
 }
}


void InAirTable::on_pushButtonLargeOff_clicked()
{
    QString fsLimitText = ui->spinBoxFS->text();
    fsLimitText = fsLimitText.simplified();
    bool ok;
    float fsLimit = fsLimitText.toFloat(&ok);

    for (int i=0; i < nLine; i++) {
      QString xFSText = ui->tableProfile->item(i,6)->text();
      xFSText = xFSText.simplified();
      QString yFSText = ui->tableProfile->item(i,7)->text();
      yFSText = yFSText.simplified();
      float xFS = xFSText.toFloat(&ok)*10;
      float yFS = yFSText.toFloat(&ok)*10;
      //bool lSw = false;
      Qt::CheckState lSw = Qt::Unchecked;
      if (xFS >= fsLimit || yFS >= fsLimit)
        //dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(lSw);
        ui->tableProfile->item(i,1)->setCheckState(lSw);
    }
}

void InAirTable::on_pushButtonAllOn_clicked()
{
    //bool allSw = true;
    Qt::CheckState allSw = Qt::Checked;
    for (int i=0; i < nLine; i++) {
      // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(allSw);
        ui->tableProfile->item(i,1)->setCheckState(allSw);
    }
}

void InAirTable::on_pushButtonAllOff_clicked()
{
    // bool allSw = false;
    Qt::CheckState allSw = Qt::Unchecked;
    for (int i=0; i < nLine; i++) {
      // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(allSw);
        ui->tableProfile->item(i,1)->setCheckState(allSw);
    }
}

void InAirTable::on_pushButtonZ100On_clicked()
{
    for (int i=0; i < nLine; i++) {
      if (ui->tableProfile->item(i,0)->text().contains(".100")) {
        // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(true);
          ui->tableProfile->item(i,1)->setCheckState(Qt::Checked);
      }
    }
}

void InAirTable::on_pushButtonZ100Off_clicked()
{
    for (int i=0; i < nLine; i++) {
      if (ui->tableProfile->item(i,0)->text().contains(".100")) {
        // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(false);
          ui->tableProfile->item(i,1)->setCheckState(Qt::Unchecked);
      }
    }
}

void InAirTable::on_pushButtonRectOn_clicked()
{
    QTextStream(stdout)<< "DEBUG RecOn:" << endl;
    bool ok;
    for (int i=0; i < nLine; i++) {
      QString xFSText = ui->tableProfile->item(i,6)->text();
      xFSText = xFSText.simplified();
      QString yFSText = ui->tableProfile->item(i,7)->text();
      yFSText = yFSText.simplified();
      float xFS = xFSText.toFloat(&ok)*10;
      float yFS = yFSText.toFloat(&ok)*10;
      // bool lSw = true;
      Qt::CheckState lSw = Qt::Checked;
      if (xFS != yFS)
        //dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(lSw);
       ui->tableProfile->item(i,1)->setCheckState(lSw);
    }
}

void InAirTable::on_pushButtonRectOff_clicked()
{
    bool ok;
    for (int i=0; i < nLine; i++) {
      QString xFSText = ui->tableProfile->item(i,6)->text();
      xFSText = xFSText.simplified();
      QString yFSText = ui->tableProfile->item(i,7)->text();
      yFSText = yFSText.simplified();
      float xFS = xFSText.toFloat(&ok)*10;
      float yFS = yFSText.toFloat(&ok)*10;
      // QTextStream(stdout)<< "DEBUG RecOn: xFS and yFS = " << xFS << " x " << yFS << endl;
      // bool lSw = false;
      Qt::CheckState lSw = Qt::Unchecked;
      if (xFS != yFS)
        // dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->setChecked(lSw);
        ui->tableProfile->item(i,1)->setCheckState(lSw);
    }
}

void InAirTable::on_pushButtonDone_clicked()
{
    QFile oFile( FNAME );
    oFile.remove();
    oFile.open( QIODevice::ReadWrite );
    QTextStream oStream( &oFile );

    QString tmpStr;
    oStream << "#file name              fit prof        X       Y"
        << "       Z               WX = " << WX
        << "         WY = " << WY << endl;
   for (int i=0; i < nLine; i++) {
       Qt::CheckState sw = Qt::Unchecked;
       if (ui->tableProfile->item(i,1)->checkState() == Qt::Checked)
           sw = Qt::PartiallyChecked;

    oStream << ui->tableProfile->item(i,0)->text() << "\t"
  //        << dynamic_cast<QCheckTableItem*>(ui->tableProfile->item(i,1))->isChecked() << "\t"
  //          << ui->tableProfile->item(i,1)->checkState() << "\t"
          << sw << "\t"
          << ui->tableProfile->item(i,2)->text() << "\t"
          << ui->tableProfile->item(i,3)->text() << "\t"
          << ui->tableProfile->item(i,4)->text() << "\t"
          << ui->tableProfile->item(i,5)->text() << "\t"
          << ui->tableProfile->item(i,6)->text() << "\t"
          << ui->tableProfile->item(i,7)->text() << endl;
   }
   oFile.close();
   close();
}

