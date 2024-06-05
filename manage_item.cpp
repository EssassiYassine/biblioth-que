#include "manage_item.h"
#include "ui_manage_item.h"
#include <QDebug>
#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QVBoxLayout>



Dialog::Dialog(QWidget *parent,int edit_mode,QList<QString> *working_bib):
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);

    _qparent = parent;
    _working_list = working_bib;
    _edit_mode=edit_mode;

    ui->label_fill->setVisible(false);

    if(_edit_mode<4){
        ui->edit_auther_edit->setVisible(false);
        ui->label_auther->setVisible(false);
        ui->label_date->setVisible(false);
        ui->dateEdit->setVisible(false);
        ui->label_fill->setVisible(false);
        ui->textEdit->setVisible(false);
       if(edit_mode==1) ui->label_fill->setText("cette bibliothèque deja exsite");
       if(edit_mode==2 ) ui->label_fill->setText("remplir tout !");
       (edit_mode==2 || edit_mode==1)? ui->label_fill->setVisible(true):ui->label_fill->setVisible(false);

        this->setFixedWidth(330);
        if(_edit_mode == -1)
            ui->edit_name_input->setText(_working_list->at(0));
        _working_list->clear();

        }

    else{

        if(_edit_mode==7){
            ui->edit_name_input->setText(_working_list->at(0));
            ui->edit_auther_edit->setText(_working_list->at(1));
            ui->dateEdit->setDate(QDate::fromString(_working_list->at(2),"dd/MM/yyyy"));
            ui->textEdit->setText(_working_list->at(3));
            _working_list->clear();

        }
    }

}





Dialog::~Dialog()
{
    delete ui;
}



void Dialog::set_wroking_list(QList<QString> &working_list){_working_list=&working_list;}
void Dialog::on_buttonBox_accepted()
{


    if(_edit_mode<4){


    _working_list->append(ui->edit_name_input->text());

    }
        else{
        _working_list->append(ui->edit_name_input->text());
        _working_list->append(ui->edit_auther_edit->text());
        _working_list->append(ui->dateEdit->text());
        _working_list->append(ui->textEdit->toPlainText());
    }

    emit dialogAccepted();

        }



void Dialog::on_button_explorer_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("All Files (*.*);;Text Files (*.txt);;Images (*.png *.jpg)"));
    if (!fileName.isEmpty()) {
           QFile file(fileName);

           // Try to open the file in read-only mode
           if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
               QTextStream in(&file);
               QString fileContent = in.readAll();
                ui->textEdit->setText(fileContent);
               file.close();

           } else {
           }
       }




}


void Dialog::on_edit_name_input_textChanged(const QString &arg1)
{



}

void Dialog::set_edit_mode(int edit_mode){_edit_mode=edit_mode;};
