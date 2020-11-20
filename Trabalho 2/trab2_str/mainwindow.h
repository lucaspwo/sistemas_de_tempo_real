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

public slots:
    void atualizaPorcentagem();
    void pesquisaProcesso();
    void selecionaProcesso();
    void mataProcesso();
    void suspendeProcesso();
    void retomaProcesso();
    void definePrioridade();
    void defineCPU();

private:
    Ui::MainWindow *ui;
    int timerId;

protected:
    void timerEvent(QTimerEvent *event);
};
#endif // MAINWINDOW_H
