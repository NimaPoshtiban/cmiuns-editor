#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextBlock>
#include <QMessageBox>
#include <QProcess>
#include <QStringList>
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->cminus_path = "cimuns.exe";
#ifdef Q_OS_LINUX
    this->cminus_path = "cminus";
#endif
#ifdef Q_OS_DARWIN
    this->cminus_path = "cimuns";
#endif
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionsave_triggered()
{
    QTextDocument *doc = ui->textEdit->document();
    QTextBlock tb = doc->findBlockByLineNumber(0);
    QString s = tb.text();

    QString path = QFileDialog::getSaveFileName(this,tr("Save File"),s+".cm");
    QFile file{path};
    // QFile file;
    if(file.open(QIODevice::WriteOnly)){
        QTextStream stream{&file};
        stream << ui->textEdit->toPlainText();
        stream.flush();
        qInfo( "File Written");
    }
    file.close();
    // file.setFileName(path.)
}


void MainWindow::on_actionexit_triggered()
{
    this->close();
}


void MainWindow::on_actioninfo_triggered()
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    msg.setWindowTitle("info");
    msg.setText(QString("Created By Nima Poshtiban\nCminus editor"));
    msg.exec();
}


void MainWindow::on_actionset_cimus_path_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Save File"),"");
    this->cminus_path = path;
}


void MainWindow::on_actionrun_triggered()
{
    QFile file{"tmp.cm"};
    if(file.open(QIODevice::WriteOnly)){
        QTextStream stream{&file};
        stream << this->ui->textEdit->toPlainText();
        stream.flush();
    }
    file.close();
    auto out = exec(QString(this->cminus_path + " --interpret tmp.cm").toLocal8Bit().data());

    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    msg.setText(QString::fromLocal8Bit(out));
    msg.exec();
}



