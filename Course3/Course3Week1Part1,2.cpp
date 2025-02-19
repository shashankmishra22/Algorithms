# include <iostream>
# include <string>
# include <fstream>
# include <vector>
# include <algorithm>
using namespace std;
struct job {
    int len;
    int weight;
};
vector<job> joblist;
void store_file(string);
void print_all(void);
bool my_compare_1(job, job);
bool my_compare_2(job, job);
long complete_time(void);
int main(int argc, char** argv) {
    store_file("/Users/shashankmishra/Desktop/jobs.txt");
    sort(joblist.begin(), joblist.end(), my_compare_1);
    long t = complete_time();
    cout << "(diff version)Complete time: " << t << endl;
    sort(joblist.begin(), joblist.end(), my_compare_2);
    t = complete_time();
    cout << "(ratio version)Complete time: " << t << endl;
    return 0;
}
void store_file(string filename) {
    ifstream infile;
    infile.open(filename, ios::in);
    int sz;
    infile >> sz;
    joblist.resize(sz);
    int tmp_l, tmp_w;
    for (int i = 0; i < sz; ++i) {
        infile >> tmp_w >> tmp_l;
        joblist[i].weight = tmp_w;
        joblist[i].len = tmp_l;
    }
    infile.close();
}
void print_all(void) {
    for (int i = 0; i < joblist.size(); ++i)
        cout << joblist[i].weight << "  " << joblist[i].len << endl;
    cout << endl;
}
bool my_compare_1(job job1, job job2) {
    int diff1 = job1.weight - job1.len;
    int diff2 = job2.weight - job2.len;
    if (diff1 > diff2)
        return true;
    else if (diff1 < diff2)
        return false;
    else
        return (job1.weight > job2.weight);
}
bool my_compare_2(job job1, job job2) {
    double ratio1 = 1.0 * job1.weight / job1.len;
    double ratio2 = 1.0 * job2.weight / job2.len;
    if (ratio1 > ratio2)
        return true;
    else if (ratio1 < ratio2)
        return false;
    else
        return (job1.weight > job2.weight);
}
long complete_time(void) {
    long t = 0;
    int start = 0;
    int finish;
    for (int i = 0; i < joblist.size(); ++i) {
        finish = start + joblist[i].len;
        t += finish * joblist[i].weight;
        start = finish;
    }
    return t;
}
