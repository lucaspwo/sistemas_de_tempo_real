#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QTimer>
#include <QDebug>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iomanip>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <regex>
#include <sys/time.h>
#include <signal.h>
#include <sys/resource.h>
#include <sched.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    timerId = startTimer(1);
}

void MainWindow::timerEvent(QTimerEvent *event){
    atualizaPorcentagem();
}

char cpu0[] = "cpu0\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu1[] = "cpu1\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu2[] = "cpu2\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu3[] = "cpu3\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu4[] = "cpu4\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu5[] = "cpu5\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu6[] = "cpu6\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu7[] = "cpu7\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu8[] = "cpu8\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu9[] = "cpu9\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu10[] = "cpu10\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu11[] = "cpu11\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu12[] = "cpu12\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu13[] = "cpu13\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu14[] = "cpu14\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";
char cpu15[] = "cpu15\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)";

char *cpu[16] = {cpu0, cpu1, cpu2, cpu3, cpu4, cpu5, cpu6, cpu7, cpu8, cpu9, cpu10, cpu11, cpu12, cpu13, cpu14, cpu15};

char process[] = "\n([a-zA-Z-+]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([-0-9]+)\\s+([0-9.0-9]+)\\s+([a-zA-Z0-9\\/:\\-_()+)]+.*)";

char row_pid[] = "(?:[a-zA-Z-+\\s]+)([0-9]+)";

long int cpu_total_old[16];
long int cpu_work_old[16];
long int cpu_total_new[16];
long int cpu_work_new[16];
double cpu_percent[16];

int lines;
int list_index = -1;
int pid_vitima;
int prio;
int set_cpu;
bool proc_kill = false;
bool proc_susp = false;
bool proc_resume = false;
bool def_prio = false;
bool def_cpu = false;
std::string s_search;
std::string pid;

cpu_set_t  mask;

using namespace std;

string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void printCpuUsage(int j, smatch m, long int cpu_total[], long int cpu_work[]){
    // cout << "Match: " << m.str(0) << "\n";
    for(int i=1; i < 11; i++){
        cpu_total[j] = cpu_total[j] + stoi(m.str(i));
    }
    // cout << "cpu_total[" << j << "]:\t" << cpu_total[j] << "\n";
    for(int i=1; i < 4; i++){
        cpu_work[j] = cpu_work[j] + stoi(m.str(i));
    }
    // cout << "cpu_work[" << j << "]:\t" << cpu_work[j] << "\n";
}

void eraseVectors(long int cpu_total[], long int cpu_work[]){
    for(int i=0; i < 16; i++){
        cpu_total[i] = 0;
        cpu_work[i] = 0;
    }
}

void printCpuPercent(int j){
    double work_over_period = cpu_work_new[j] - cpu_work_old[j];
    double total_over_period = cpu_total_new[j] - cpu_total_old[j];

    double percent = work_over_period / total_over_period * 100;
    cpu_percent[j] = int(percent);
    cout << fixed;
    cout << setprecision(1);
//    cout << "CPU" << j+1 << ":\t" << percent << "%" << "\n";
}

void refreshCpu(){
    string res;
    res = exec("cat /proc/stat");
    // cout << "res:\n" << res << "\n\n";
    for(int i=0; i < 16; i++){
        regex re_cpu(cpu[i]);
        smatch m;
        regex_search(res, m, re_cpu);
        printCpuUsage(i, m, cpu_total_old, cpu_work_old);
    }
    sleep(1);
    res = exec("cat /proc/stat");
    // cout << "res:\n" << res << "\n\n";
    for(int i=0; i < 16; i++){
        regex re_cpu(cpu[i]);
        smatch m;
        regex_search(res, m, re_cpu);
        printCpuUsage(i, m, cpu_total_new, cpu_work_new);
    }

    for(int i=0; i < 16; i++){
        printCpuPercent(i);
    }
    eraseVectors(cpu_total_new, cpu_work_new);
    eraseVectors(cpu_total_old, cpu_work_old);
}

void refreshProcess(Ui::MainWindow ui){
    CPU_ZERO(&mask);
    string res;
    res = exec("ps -eo user,pid,pri,ni,pcpu,comm");
        // cout << res << "\n";
        regex re_proc(process);
        lines = 0;
        for(sregex_iterator i = sregex_iterator(res.begin(), res.end(), re_proc); i != sregex_iterator(); ++i){
            lines += 1;
            smatch gm = *i;
            // cout << gm.length() << "\n";
            // for(int j=1; j < 6; j++){
                // cout << "j = " << j << ": " << gm.str(j) << "\n";
            // }
        }
        // cout << "lines: " << lines << "\n";
        string* s_user = new string [lines];
        string* s_pid = new string [lines];
        string* s_pri = new string [lines];
        string* s_ni = new string [lines];
        string* s_cpu = new string [lines];
        string* s_comm = new string [lines];
        int k = 0;
        for(sregex_iterator i = sregex_iterator(res.begin(), res.end(), re_proc); i != sregex_iterator(); ++i){
            smatch gm = *i;
            // cout << gm.length() << "\n";
            for(int j=1; j < 7; j++){
                if(j == 1)
                    s_user[k] = gm.str(j);
                if(j == 2)
                    s_pid[k] = gm.str(j);
                if(j == 3)
                    s_pri[k] = gm.str(j);
                if(j == 4)
                    s_ni[k] = gm.str(j);
                if(j == 5)
                    s_cpu[k] = gm.str(j);
                if(j == 6)
                    s_comm[k] = gm.str(j);
                // cout << "j = " << j << ": " << gm.str(j) << "\n";
            }
            k += 1;
        }
        QStringListModel *model = new QStringListModel();
        QStringList list;
        if(s_search != ""){
//            cout << "oi!" << "\n";
            for(int i=0; i < lines; i++){
                if(s_comm[i].find(s_search, 0) != std::string::npos){
                    list << QString::fromStdString(s_user[i] + "\t\t" + s_pid[i] + "\t" + s_pri[i] + "\t" + s_ni[i] + "\t" + s_cpu[i] + "\t" + s_comm[i] + "\n");
//                    cout << s_comm[i] << "\n";
                }
            }
        } else {
    //        cout << "\n";
            for(int m = 0; m < lines; m++){
//                cout << s_user[m] << "\t" << s_pid[m] + "\t" << s_pri[m] << "\t" << s_ni[m] << "\t" << s_cpu[m] << "\t" << s_comm[m] << "\n";
                list << QString::fromStdString(s_user[m] + "\t\t" + s_pid[m] + "\t" + s_pri[m] + "\t" + s_ni[m] + "\t" + s_cpu[m] + "\t" + s_comm[m] + "\n");
            }
        }
        if(list_index > -1){
//            qDebug() << "lista: " << list;
            regex re_pid(row_pid);
            smatch m;
            std::string row = list[list_index].toUtf8().constData();
//            cout << "row: " << row;
//            qDebug() << "list[index]: " << list[list_index];

            regex_search(row, m, re_pid);
//            qDebug() << "size: " << m.size();
//            cout << "m1: " << m[1];
            pid_vitima = stoi(m[1]);
            if(proc_kill){
                kill(pid_vitima, SIGKILL);
                pid_vitima = -1;
                proc_kill = false;
                ui.listView->clearSelection();
                s_search = "";
            }
            if(proc_susp){
                char stop[70] = "kill -STOP ";
                char c_pid[10];
                sprintf(c_pid, "%d", pid_vitima);
                strcat(stop, c_pid);
                exec(stop);
                proc_susp = false;
            }
            if(proc_resume){
                char cont[70] = "kill -CONT ";
                char c_pid[10];
                sprintf(c_pid, "%d", pid_vitima);
                strcat(cont, c_pid);
                exec(cont);
                proc_resume = false;
            }
            if(def_prio){
                int ret = setpriority(PRIO_PROCESS, pid_vitima, prio);
//                qDebug() << "ret: " << ret;
                def_prio = false;
            }
            if(def_cpu){
                CPU_SET(set_cpu, &mask);
                int ret = sched_setaffinity(pid_vitima, sizeof(mask), &mask);
//                qDebug() << "ret: " << ret;
                def_cpu = false;
            }
        }
        model->setStringList(list);
        ui.listView->setModel(model);
}

MainWindow::~MainWindow(){
    killTimer(timerId);
    delete ui;
}

void MainWindow::atualizaPorcentagem(){
    refreshCpu();
    refreshProcess(*ui);
    ui->progressBar->setValue(cpu_percent[0]);
    ui->progressBar_2->setValue(cpu_percent[1]);
    ui->progressBar_3->setValue(cpu_percent[2]);
    ui->progressBar_4->setValue(cpu_percent[3]);
    ui->progressBar_5->setValue(cpu_percent[4]);
    ui->progressBar_6->setValue(cpu_percent[5]);
    ui->progressBar_7->setValue(cpu_percent[6]);
    ui->progressBar_8->setValue(cpu_percent[7]);
    ui->progressBar_9->setValue(cpu_percent[8]);
    ui->progressBar_10->setValue(cpu_percent[9]);
    ui->progressBar_11->setValue(cpu_percent[10]);
    ui->progressBar_12->setValue(cpu_percent[11]);
    ui->progressBar_13->setValue(cpu_percent[12]);
    ui->progressBar_14->setValue(cpu_percent[13]);
    ui->progressBar_15->setValue(cpu_percent[14]);
    ui->progressBar_16->setValue(cpu_percent[15]);
}

void MainWindow::pesquisaProcesso(){
    QString text = ui->plainTextEdit->toPlainText();
    s_search = text.toUtf8().constData();
    //    cout << "s_search: " << s_search << "\n";
}

void MainWindow::selecionaProcesso(){
    QModelIndexList id = ui->listView->selectionModel()->selectedIndexes();
    for(int i = 0; i < id.size(); i++){
//        qDebug() << "id.row: " << id[i].row();
        list_index = id[i].row();
    }
    refreshProcess(*ui);
}

void MainWindow::mataProcesso(){
    proc_kill = true;
}

void MainWindow::suspendeProcesso(){
    proc_susp = true;
}

void MainWindow::retomaProcesso(){
    proc_resume = true;
}

void MainWindow::definePrioridade(){
    prio = ui->caixaSpin_2->value();
    def_prio = true;
}

void MainWindow::defineCPU(){
    set_cpu = ui->spinBox->value();
    set_cpu = set_cpu - 1;
    def_cpu = true;
}
