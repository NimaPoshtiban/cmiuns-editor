#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString cminus_path;
private slots:
    void on_actionsave_triggered();

    void on_actionexit_triggered();

    void on_actioninfo_triggered();

    void on_actionset_cimus_path_triggered();

    void on_actionrun_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
