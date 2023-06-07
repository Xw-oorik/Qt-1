#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_yd_clicked();

    void on_yd1_clicked();

    void on_yd2_clicked();

    void on_rebuild_clicked();

    void on_module_clicked();

    void on_msgbox_clicked();

    void on_mulu_clicked();

    void on_font_clicked();

    void on_colorbt_clicked();

    void on_chat_clicked();

    void on_download_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
