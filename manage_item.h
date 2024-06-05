#ifndef MANAGE_ITEM_H
#define MANAGE_ITEM_H

#include <QDialog>
#include <QDate>
#include <QJsonDocument>
#include "livre.h"
#include "biblio.h"
#include <QList>
#include <QDialogButtonBox>




namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void set_edit_mode(int edit_mode);

    explicit Dialog(QWidget *parent = nullptr,int edit_mod=0, //edit_mode {0-->bib add/edit,1-->bib_dublicated , 2-->bib_emty, louer_edit ,3 --> louer edit, 4-->add/edit book,5-->addbook_eublicate,6 addbook emty,7-->forced_edit_book}
                    QList<QString> *working_list=nullptr);

    void set_wroking_list(QList<QString> &working_bib_list);

Q_SIGNALS:

    void dialogAccepted();  // Custom signal


private slots:
    void on_buttonBox_accepted();
    void on_button_explorer_clicked();

    void on_edit_name_input_textChanged(const QString &arg1);
public:

private:

   QWidget* _qparent;
   int _edit_mode;



   QList<QString> *_working_list;
    Ui::Dialog *ui;
};

#endif // MANAGE_ITEM_H
