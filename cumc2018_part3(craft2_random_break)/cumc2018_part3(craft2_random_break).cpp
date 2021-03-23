#include <iostream>
#include <random>
#include <chrono>
using namespace std;

int pro_s[2][3] = {
    400, 280, 455,
    378, 500, 182
}; //加工时间
int pro1 = 400;
int pro2 = 378;
int rep_s[3][8] = {
    28, 31, 28, 31, 28, 31, 28, 31,
    30, 35, 30, 35, 30, 35, 30, 35,
    27, 32, 27, 32, 27, 32, 27, 32
}; //上下料时间
int rep[8] = { 0 };
int wash_s[3] = { 25, 30, 25 };  //清洗时间
int put_down = 25;
int L[8][8] = { 0 };
int d[3][4] = {
    0, 20, 33, 46,
    0, 23, 41, 59,
    0, 18, 32, 46
};
int gotime1[8][1000] = { 0 }; //上料时间
int offtime1[8][1000] = { 0 }; //下料时间
int gotime2[8][1000] = { 0 }; //上料时间
int offtime2[8][1000] = { 0 }; //下料时间
int record[1000][2] = { 0 };
int sy1[1000] = { 0 };//索引
int sy2[1000] = { 0 };
int cnc31[3][8] = {
    2, 4, 6, 8, 0, 0, 0, 0,
    2, 4, 6, 8, 0, 0, 0, 0,
    1, 3, 4, 6, 8, 0, 0, 0
};
int cnc32[3][8] = {
    1, 3, 5, 7, 0, 0, 0, 0,
    1, 3, 5, 7, 0, 0, 0, 0,
    2, 5, 7, 0, 0, 0, 0, 0
};
int num51[3] = { 4, 4, 5 };
int num61[3] = { 4, 4 ,3 };


//就近原则;
int min_index1(int* T, int num10) {
    int i = 0;
    int num = num10;
    int min_ind = 0;
    for (; i < num; i++) {
        if (T[i] < T[min_ind]) min_ind = i;
    }
    return min_ind;
}

//就近原则;
int min_index2(int* T, int num11) {
    int i = 0;
    int num = num11;
    int min_ind = 0;
    for (; i < num; i++) {
        if (T[i] < T[min_ind]) min_ind = i;
    }
    return min_ind;
}


void out(int num1, int num2, int num4) {
    int numm[8] = { 0 };
    int out_temp1[1000][3] = { 0 };
    int out_temp2[1000][3] = { 0 };
    cout << "----print----" << endl;
    for (int i = 0; i < num1; i++) {
        out_temp1[i][0] = sy1[i] + 1;
        out_temp1[i][1] = gotime1[sy1[i]][numm[sy1[i]]];
        out_temp1[i][2] = offtime1[sy1[i]][numm[sy1[i]]];
        numm[sy1[i]]++;
    }
    for (int i = 0; i < num2; i++) {
        out_temp2[i][0] = sy2[i] + 1;
        out_temp2[i][1] = gotime2[sy2[i]][numm[sy2[i]]];
        out_temp2[i][2] = offtime2[sy2[i]][numm[sy2[i]]];
        numm[sy2[i]]++;
    }
    for (int i = 0; i < num4; i++) {
        if (i + 1 < 10)
            cout << "物料序号 " << i + 1 << "  : ";
        else if (i + 1 < 100)
            cout << "物料序号 " << i + 1 << " : ";
        else
            cout << "物料序号 " << i + 1 << ": ";
        cout << out_temp1[record[i][0]][0] << " , " << out_temp1[record[i][0]][1] << "," << out_temp1[record[i][0]][2] << " ; ";
        cout << out_temp2[record[i][1]][0] << " , " << out_temp2[record[i][1]][1] << "," << out_temp2[record[i][1]][2];
        cout << endl;
    }
}


double randuni() {
    return rand() / (RAND_MAX + 1.0);
}


int main()
{
    unsigned seed;
    seed = unsigned(chrono::system_clock::now().time_since_epoch().count());
    default_random_engine gen(seed);
    normal_distribution<double> dis(900, 1);
    srand(seed);
    int zuhao = 0;
    while (scanf_s("%d", &zuhao)) {
        if (zuhao == -1) break;
        if (zuhao > 3 || zuhao < 1) continue;
        zuhao--;
        int flag_12 = 0;
        int num1 = 0;
        int num2 = 0; //成品数量
        int num4 = 0;
        int num5 = 4;
        int num6 = 4;
        int time = 0;
        int cnc1[8] = { 0 };
        int cnc2[8] = { 0 };
        int numm[8] = { 0 };
        int T1[8] = { 0 }; //当前状态到达其他CNC加工台的代价
        int T2[8] = { 0 };
        int S[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; //加工剩余时间
        int B[8][2] = { 0 }; //是否有料
        int end_time = 28800; //28800;// 3600*8;
        int pos = 0, next_pos = 0, next_xuhao = 0;//小车起始位置
        int num_error1 = 0;
        int num_error2 = 0;
        for (int i = 0; i < 8; i++) {
            int temp = i / 2;
            for (int j = 0; j < 8; j++) {
                L[i][j] = d[zuhao][abs(j / 2 - temp)];
            }
        }
        for (int i = 0; i < 8; i++) rep[i] = rep_s[zuhao][i];
        num5 = num51[zuhao];
        num6 = num61[zuhao];
        for (int i = 0; i < 8; i++) cnc1[i] = cnc31[zuhao][i];
        for (int i = 0; i < 8; i++) cnc2[i] = cnc32[zuhao][i];
        pro1 = pro_s[0][zuhao];
        pro2 = pro_s[1][zuhao];
        //    cout << pro1 << pro2;
        put_down = wash_s[zuhao];
        while (time <= end_time) {
            if (flag_12 == 0) {
                /**********评估过程***********/
                for (int i = 0; i < num5; i++) {
                    int j = cnc1[i] - 1;
                    if ((S[j] - L[pos][j]) > 0)
                        T1[i] = S[j] + rep[j];
                    else
                        T1[i] = L[pos][j] + rep[j];
                    //移动T + 上下料T
                }
                /**********选择过程***********/
                next_xuhao = min_index1(T1, num5);
                next_pos = cnc1[next_xuhao] - 1;//选择代价最小的
                //起到了初始化的作用
                pos = next_pos;
                time += T1[next_xuhao];//时间需要延长这个过程的时间
                if (B[next_pos][0]) {
                    flag_12 = 1;
                    offtime1[next_pos][numm[next_pos]] = time - rep[next_pos]; //除去上下料时间
                    sy1[num1] = next_pos;
                    numm[next_pos] ++;
                    num1++;
                }
                gotime1[next_pos][numm[next_pos]] = time - rep[next_pos]; //除去上下料时间
                B[next_pos][0] = 1;
                if (randuni() <= 0.01) {
                    S[next_pos] = int(pro1 * randuni());
                    double tempp = 0;
                    tempp = dis(gen);
                    while (tempp > 1200 || tempp < 600) tempp = dis(gen);
                    S[next_pos] += int(tempp);
                    B[next_pos][0] = 0;
                    num_error1++;
                }
                else S[next_pos] = pro1;
                for (int i = 0; i < 8; i++) {
                    if (i != next_pos) {
                        S[i] -= T1[next_xuhao];
                    }
                }
            }
            else {
                flag_12 = 0;
                /**********评估过程***********/
                for (int i = 0; i < num6; i++) {
                    int j = cnc2[i] - 1;
                    if ((S[j] - L[pos][j]) > 0)
                        T2[i] = S[j] + rep[j] + B[j][0] * put_down;
                    else
                        T2[i] = L[pos][j] + rep[j] + B[j][0] * put_down;
                    //移动T + 上下料T + 清洗T
                }
                /**********选择过程***********/
                next_xuhao = min_index2(T2, num6);
                next_pos = cnc2[next_xuhao] - 1;//选择代价最小的
                //起到了初始化的作用
                pos = next_pos;
                time += T2[next_xuhao];//时间需要延长这个过程的时间

                if (time > end_time) break;

                if (B[next_pos][0]) {
                    offtime2[next_pos][numm[next_pos]] = time - rep[next_pos] - B[next_pos][0] * put_down; //除去上下料时间和清洗时间
                    sy2[num2] = next_pos;
                    numm[next_pos] ++;
                    record[num4][0] = B[next_pos][1];
                    record[num4][1] = num2;
                    num4++;
                    num2++;
                }
                gotime2[next_pos][numm[next_pos]] = time - rep[next_pos] - B[next_pos][0] * put_down; //除去上下料时间和清洗时间
                B[next_pos][0] = 1;
                B[next_pos][1] = num1 - 1;
                if (randuni() <= 0.01) {
                    S[next_pos] = int(pro2 * randuni());
                    double tempp = 0;
                    tempp = dis(gen);
                    while (tempp > 1200 || tempp < 600) tempp = dis(gen);
                    S[next_pos] += int(tempp);
                    B[next_pos][0] = 0;
                    num_error2++;
                }
                else S[next_pos] = pro2 - B[next_pos][0] * put_down;
                for (int i = 0; i < 8; i++) {
                    if (i != next_pos) {
                        S[i] -= T2[next_xuhao];
                    }
                }
            }
        }
        out(num1, num2, num4);
        cout << "---------the total number---------" << endl;
        cout << num2 << endl;
        cout << "----the total error1&2 number----" << endl;
        cout << num_error1 << " " << num_error2 << endl;
    }
    return 0;
}
