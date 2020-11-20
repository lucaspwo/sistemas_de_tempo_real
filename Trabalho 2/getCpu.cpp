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

using namespace std;

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

char process[] = "\n([a-zA-Z-+]+)\\s+([0-9]+)\\s+([-0-9]+)\\s+([0-9.0-9]+)\\s+([a-zA-Z0-9\\/:\\-_()+)]+.*)";

long int cpu_total_old[16];
long int cpu_work_old[16];
long int cpu_total_new[16];
long int cpu_work_new[16];
double cpu_percent[16];

int lines;

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

void printCpuPercent(int j){
    double work_over_period = cpu_work_new[j] - cpu_work_old[j];
    double total_over_period = cpu_total_new[j] - cpu_total_old[j];

    double percent = work_over_period / total_over_period * 100;
    cpu_percent[j] = percent;
    cout << fixed;
    cout << setprecision(1);
    cout << "CPU" << j+1 << ":\t" << percent << "%" << "\n";
}

int main(int argc, char *argv[]){
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

    res = exec("ps -eo user,pid,ni,pcpu,comm");
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
    string* s_ni = new string [lines];
    string* s_cpu = new string [lines];
    string* s_comm = new string [lines];
    int k = 0;
    for(sregex_iterator i = sregex_iterator(res.begin(), res.end(), re_proc); i != sregex_iterator(); ++i){
        smatch gm = *i;
        // cout << gm.length() << "\n";
        for(int j=1; j < 6; j++){
            if(j == 1)
                s_user[k] = gm.str(j);
            if(j == 2)
                s_pid[k] = gm.str(j);
            if(j == 3)
                s_ni[k] = gm.str(j);
            if(j == 4)
                s_cpu[k] = gm.str(j);
            if(j == 5)
                s_comm[k] = gm.str(j);
            // cout << "j = " << j << ": " << gm.str(j) << "\n";
        }
        k += 1;
    }
    cout << "\n";
    for(int m = 0; m < lines; m++){
        cout << s_user[m] << "\t" << s_pid[m] << "\t" << s_ni[m] << "\t" << s_cpu[m] << "\t" << s_comm[m] << "\n";
    }
}