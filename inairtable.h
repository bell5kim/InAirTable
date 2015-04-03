#ifndef INAIRTABLE_H
#define INAIRTABLE_H

#include <QDialog>

namespace Ui {
class InAirTable;
}

class InAirTable : public QDialog
{
    Q_OBJECT

public:
    explicit InAirTable(QWidget *parent = 0);
    ~InAirTable();

    void init();
    void loadData(QString fName);
    void writeData();
    void xyToggle();
    //void xProfileOn();
    //void yProfileOn();
    //void zProfileOn();
    //void xProfileOff();
    //void yProfileOff();
    //void zProfileOff();
    void fsToggle();
    //void smallerOn();
    //void smallerOff();
    //void largerOn();
    //void largerOff();
    void toggleAll();
    //void allOn();
    //void allOff();
    //void z100On();
    //void z100Off();
    // void rectgleOn();
    // void rectgleOff();



private slots:
    void on_pushButtonZOn_clicked();

    void on_pushButtonXOn_clicked();

    void on_pushButtonYOn_clicked();

    void on_pushButtonXOff_clicked();

    void on_pushButtonYOff_clicked();

    void on_pushButtonZOff_clicked();

    void on_pushButtonSmallOn_clicked();

    void on_pushButtonSmallOff_clicked();

    void on_pushButtonLargeOn_clicked();

    void on_pushButtonLargeOff_clicked();

    void on_pushButtonAllOn_clicked();

    void on_pushButtonAllOff_clicked();

    void on_pushButtonZ100On_clicked();

    void on_pushButtonZ100Off_clicked();

    void on_pushButtonRectOn_clicked();

    void on_pushButtonRectOff_clicked();

    void on_pushButtonDone_clicked();

private:
    Ui::InAirTable *ui;
};

#endif // INAIRTABLE_H
