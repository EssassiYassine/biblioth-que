#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QObject>
#include "manage_item.h"
#include <QTimer>
#include "manage_item.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refresh_bib();
    void refresh_book();



private slots:
    void onDialogAccepted();
    void on_add_bib_but_clicked();
    void on_add_book_but_clicked();

    void on_pushButton_clicked();
    void on_list_bib_display_itemSelectionChanged();

    void on_remove_bib_but_clicked();

    void on_edit_book_but_clicked();

    void on_list_book_display_itemSelectionChanged();
    void on_list_bib_display_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void set_livre_items(int bib_index);
    void on_remove_book_but_clicked();

    void on_button_rent_clicked();


    void on_search_bib_input_textChanged(const QString &arg1);

    void on_search_book_input_textChanged(const QString &arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_button_save_clicked();

    void on_pushButton_2_clicked();

private:
    void open_dialog_mode(int mode);
    Ui::MainWindow *ui;
    Dialog *_mydialog;


};
#endif // MAINWINDOW_H
