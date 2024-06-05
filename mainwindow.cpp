#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "biblio.h"
#include <QList>
#include "manage_item.h"
#include <QDebug>
#include <QTimer>
#include <livre.h>
#include <QMessageBox>
#include <QFileDialog>
#include "manage_item.h"



int S_biblio_index =-1;
int S_livre_index = -1;
int S_biblio_index_new=-1;
int S_livre_index_new =-1;
QList<QString> resut_list;
QList<biblio> bibliolist;
QList<biblio> bibliolist_new;
bool search_methode;
int edit_mode;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}



MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_add_bib_but_clicked()
{
    open_dialog_mode(0);

}





void MainWindow::on_add_book_but_clicked()
{
    if(S_biblio_index!=-1){
    open_dialog_mode(4);
    }
    else{
        QMessageBox::information(this, "Error", "Sélectionner une bibliothèque !");
    }
    ;

}

void MainWindow::refresh_bib(){
    ui->list_bib_display->clear();
    ui->list_book_display->clear();

        for(int i=0;i<bibliolist.size();i++){
        QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->list_bib_display);
        rootItem->setText(0, bibliolist[i].getname());
        rootItem->setText(1, QString::number(i));
        rootItem->setText(2, QString::number(bibliolist[i].getlistlivres().size()));


    }


}

void MainWindow::refresh_book(){
    ui->list_book_display->clear();

    if(S_biblio_index_new!=-1){


        for(int i=0;i<bibliolist[S_biblio_index_new].getlistlivres().size();i++){

            QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->list_book_display);
            rootItem->setText(0,bibliolist[S_biblio_index_new].getlistlivres()[i].getname());
            rootItem->setText(1,bibliolist[S_biblio_index_new].getlistlivres()[i].getauteur());
            rootItem->setText(2,bibliolist[S_biblio_index_new].getlistlivres()[i].getanne());
            rootItem->setText(3,QString::number(i));
            rootItem->setText(4,bibliolist[S_biblio_index_new].getlistlivres()[i].getrenter());
            ui->text_book->setText(bibliolist[S_biblio_index_new].getlistlivres()[i].getcontunnu());

        }
    }

    else{

        ui->list_book_display->clear();

        ui->text_book->setText("");


    }
}

void MainWindow::on_pushButton_clicked()
{

    refresh_bib();
    refresh_book();

}




void MainWindow::on_list_bib_display_itemSelectionChanged()
{
    QList<QTreeWidgetItem *> selectedItems = ui->list_bib_display->selectedItems();


    if (!selectedItems.isEmpty()) {
        QTreeWidgetItem *item = selectedItems.first(); // Get the first selected ite
        QString value2 = item->text(1); // Get the text of the first column
        S_biblio_index = value2.toInt();
        S_biblio_index_new = S_biblio_index;

        qDebug() << "S_biblio_index =" << S_biblio_index;
    } else {
        S_biblio_index = -1;
    }
}




void MainWindow::on_remove_bib_but_clicked()
{

    if(S_biblio_index!=-1){
        bibliolist.removeAt(S_biblio_index);
        S_biblio_index = S_biblio_index-1;
        S_biblio_index_new = S_biblio_index;
        ui->text_book->setText("");
        refresh_bib();
        refresh_book();
    }else{
       QMessageBox::information(this, "Error", "Sélectionner une bibliothèque pour supprimer.");


    }
}


void MainWindow::on_remove_book_but_clicked()
{
    if( S_livre_index !=-1 && S_biblio_index_new !=-1){
        bibliolist[S_livre_index].removelivre(S_livre_index);
        refresh_bib();
        refresh_book();
        ui->text_book->setText("");

    }else{QMessageBox::information(this, "Error", "Sélectionner un livre pour le supprimer.");}
}



void MainWindow::on_edit_book_but_clicked()
{

    if(S_livre_index==-1){
        QMessageBox::information(this, "Error", "Sélectionner un livre !");

    }
    else{
       open_dialog_mode(7);
    }

}


void MainWindow::on_list_book_display_itemSelectionChanged()
{

    QList<QTreeWidgetItem *> selectedItems = ui->list_book_display->selectedItems();
    if (!selectedItems.isEmpty()) {
        QTreeWidgetItem *item = selectedItems.first(); // Get the first selected item
        QString name = item->text(0); // Get the text of the first column
        QString auther = item->text(1); // Get the text of the first column
        QString anner = item->text(2); // Get the text of the first column
        QString id = item->text(3); // Get the text of the first column.
        ui->text_book->setText(bibliolist[S_biblio_index_new].getlistlivres()[id.toInt()].getcontunnu());
        S_livre_index = id.toInt();
        S_livre_index_new = S_livre_index;
    } else {
        S_livre_index = -1;
    }

}


void MainWindow::on_list_bib_display_itemDoubleClicked(QTreeWidgetItem *item, int column)
{

    //S_biblio_index= S_biblio_index=QString::number((item->text(1)))

}

void MainWindow::onDialogAccepted()
{
    bool dublicate= false;

    if(!resut_list.isEmpty()){
        if(!resut_list.at(0).length() && edit_mode !=3){
            if(edit_mode==3) bibliolist[S_biblio_index_new].getlistlivres()[S_livre_index_new].set_renter("");
            else if(edit_mode <3) open_dialog_mode(edit_mode);
            else if (edit_mode>3 && edit_mode <7) open_dialog_mode(6);
            else open_dialog_mode(7);
        }else{

           if(resut_list.size()==1){

              bool dublicate = false;
               if(edit_mode != 3){
                   for(int i=0;i<bibliolist.size();i++){
                       if(bibliolist[i].getname()==resut_list[0]) {
                           open_dialog_mode(1);
                            dublicate = true;
                           break;
                       }
                   }
                  if(!dublicate) {
                      if(edit_mode == -1){
                          bibliolist[S_biblio_index_new].changebibname(resut_list[0]);

                      }else{
                          biblio newbib;
                          newbib.changebibname(resut_list[0]);
                          bibliolist.append(newbib);
                          qDebug() <<"biblist size :  "<<bibliolist.size();
                      }


                  }
               }else{
               livre new_livre;
               new_livre.set_id(QString::number((bibliolist[S_biblio_index_new].getlistlivres().size())));

                 livre new_book = bibliolist[S_biblio_index_new].getlistlivres()[S_livre_index_new];
                    new_book.set_renter(resut_list[0]);
                    new_book.set_id(QString::number((bibliolist[S_biblio_index_new].getlistlivres().size())));

               bibliolist[S_biblio_index_new].replacelivre(new_book,S_livre_index_new);
               }


           }
           else{
           if(!resut_list[1].size()) open_dialog_mode(6);
           else{
               livre new_livre;
               new_livre.setname(resut_list[0]);
               new_livre.setauteur(resut_list[1]);
               if(!bibliolist.isEmpty() && !bibliolist[S_biblio_index_new].getlistlivres().isEmpty()){
               for(int i=0;i<bibliolist.size();i++){
                   if(bibliolist[S_biblio_index_new].getlistlivres()[i]==new_livre) {
                    dublicate =true;
                    break;
           }


           }
           }
               if(dublicate && edit_mode ==7){
               open_dialog_mode(7);
               } else if (dublicate){
                   open_dialog_mode(5);
               }

               else{
                   new_livre.setanne(resut_list[2]);
                   new_livre.setcontenu(resut_list[3]);
                   if(edit_mode == 7){
                     bibliolist[S_biblio_index_new].replacelivre(new_livre,S_livre_index_new);
                   }else{
                   bibliolist[S_biblio_index_new].addlivre(new_livre);
                   }




               }


           }
           }
        }

    }

    refresh_bib();
    refresh_book();
}


void MainWindow::set_livre_items(int bib_index){

};


void MainWindow::on_button_rent_clicked()
{

    if(S_livre_index!=-1){

        open_dialog_mode(3);


    }
    else{

    QMessageBox::information(this, "Error", "Sélectionner un livre !");

    }



}





void MainWindow::on_search_bib_input_textChanged(const QString &arg1)
{
   ui->list_bib_display->clear();
    for(int i=0;i<bibliolist.size();i++){
        if(bibliolist[i].getname().contains(arg1)){
            QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->list_bib_display);
            rootItem->setText(0, bibliolist[i].getname());
            rootItem->setText(1, QString::number(i));
            rootItem->setText(2, QString::number(bibliolist[i].getlistlivres().size()));

        }
    }

}


void MainWindow::on_search_book_input_textChanged(const QString &arg1)
{

    ui->list_book_display->clear();
    QList<livre> serach_list = bibliolist[S_biblio_index_new].getlistlivres();
     for(int i=0;i<bibliolist[S_biblio_index_new].getlistlivres().size();i++){
        QString search_string ;

         search_string = !search_methode?serach_list[i].getauteur():serach_list[i].getname();


         if(search_string.contains(arg1)){
             QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->list_book_display);
             rootItem->setText(0,bibliolist[S_biblio_index_new].getlistlivres()[i].getname());
             rootItem->setText(1,bibliolist[S_biblio_index_new].getlistlivres()[i].getauteur());
             rootItem->setText(2,bibliolist[S_biblio_index_new].getlistlivres()[i].getanne());
             rootItem->setText(3,QString::number(i));}
     }

}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    search_methode=arg1;
    if(arg1)  ui->label_search->setText("la méthode de la recherche : titre");
    else    ui->label_search->setText("la méthode de la recherche : auteur");


    ui->list_book_display->clear();


    if(S_biblio_index_new !=-1 && S_livre_index_new !=-1){

        QList<livre> serach_list = bibliolist[S_biblio_index_new].getlistlivres();
         for(int i=0;i<bibliolist[S_biblio_index_new].getlistlivres().size();i++){
            QString search_string ;

             search_string = !search_methode?serach_list[i].getauteur():serach_list[i].getname();


             if(search_string.contains(ui->search_book_input->text())){
                 QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->list_book_display);
                 rootItem->setText(0,bibliolist[S_biblio_index_new].getlistlivres()[i].getname());
                 rootItem->setText(1,bibliolist[S_biblio_index_new].getlistlivres()[i].getauteur());
                 rootItem->setText(2,bibliolist[S_biblio_index_new].getlistlivres()[i].getanne());
                 rootItem->setText(3,QString::number(i));}
         }


    }



}


void MainWindow::on_button_save_clicked()
{



    if( S_livre_index !=-1){
    QString fileName = QFileDialog::getSaveFileName(nullptr,
                                                     "Save File",
                                                     "",
                                                     "Text Files (*.txt);;All Files (*)");

     // Check if the user has selected a file name
     if (!fileName.isEmpty()) {
         // Create a QFile object
         QFile file(fileName);

         // Try to open the file
         if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
             // Create a QTextStream to write to the file
             QTextStream out(&file);

             QString filetext = "l'auteur de ce livre est : ";
                     filetext.append(bibliolist[S_biblio_index_new].getlistlivres()[S_livre_index_new].getauteur());
                     filetext.append("\n");
                     filetext.append(bibliolist[S_biblio_index_new].getlistlivres()[S_livre_index_new].getcontunnu());
             out << filetext;

             // Close the file
             file.close();

             QMessageBox::information(nullptr, "Success", "File saved successfully!");
         } else {
             QMessageBox::warning(nullptr, "Error", "Failed to save the file.");
         }
     } else {
         QMessageBox::information(nullptr, "Cancelled", "File save operation was cancelled.");
     }}
    else     QMessageBox::information(this, "Error", "Sélectionner un livre !");


}

void MainWindow::open_dialog_mode(int mode){
    resut_list.clear();
    edit_mode =mode;

    if(edit_mode == 7){
        resut_list.append(bibliolist[S_biblio_index_new].getlistlivres()[S_livre_index_new].getname());
        resut_list.append(bibliolist[S_biblio_index_new].getlistlivres()[S_livre_index_new].getauteur());
        resut_list.append(bibliolist[S_biblio_index_new].getlistlivres()[S_livre_index_new].getanne());
        resut_list.append(bibliolist[S_biblio_index_new].getlistlivres()[S_livre_index_new].getcontunnu());

    }else if (edit_mode == -1){
        resut_list.append(bibliolist[S_biblio_index_new].getname());
    }
    Dialog edit_item(this,mode,&resut_list);
    edit_item.setModal(true);
    _mydialog = &edit_item;
    connect(_mydialog, &Dialog::dialogAccepted, this, &MainWindow::onDialogAccepted);

    _mydialog->exec();




}

void MainWindow::on_pushButton_2_clicked()
{
    if(S_biblio_index!=-1){
        open_dialog_mode(-1);
    }else{
        QMessageBox::information(this, "Error", "Sélectionner une bibliothèque !");

    }
}

