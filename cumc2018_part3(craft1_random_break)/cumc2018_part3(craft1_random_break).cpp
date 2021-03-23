#include <iostream>
#include <random>
#include <chrono>
using namespace std;

int pro_s[3] = { 560, 580, 545 }; //加工时间
int pro = 560;
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
int gotime[8][1000] = { 0 }; //上料时间
int offtime[8][1000] = { 0 }; //下料时间
int sy[1000] = { 0 };//索引


void out(int num) {
    int numm[8] = { 0 };
    cout << "----print----" << endl;
    for (int i = 0; i < num; i++) {
        cout << sy[i] + 1 << " : " << gotime[sy[i]][numm[sy[i]]] << "," << offtime[sy[i]][numm[sy[i]]];
        cout << endl;
        numm[sy[i]]++;
    }
}


//就近原则;
int min_index(int* T) {
    int i = 0, num = 8;
    int min_ind = 0;
    for (; i < num; i++) {
        if (T[i] < T[min_ind]) min_ind = i;
    }
    return min_ind;
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
    int show = 1;
    while (scanf_s("%d", &zuhao)) {
        if (zuhao == -1) break;
        if (zuhao > 3 || zuhao < 1) continue;
        //            scanf("%d", &zuhao);
        zuhao--;
        int S[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; //加工剩余时间
        bool B[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; //是否有料
        int numm[8] = { 0 };
        int time = 0;
        int end_time = 3600 * 8; //28800;// 3600*8;
        int pos = 0, next_pos = 0;//小车起始位置
        int num = 0; //成品数量
        int T[8] = { 0 }; //当前状态到达其他CNC加工台的代价
        int num_error = 0;

        for (int i = 0; i < 8; i++) {
            int temp = i / 2;
            for (int j = 0; j < 8; j++) {
                L[i][j] = d[zuhao][abs(j / 2 - temp)];
            }
        }
        for (int i = 0; i < 8; i++) rep[i] = rep_s[zuhao][i];
        pro = pro_s[zuhao];
        put_down = wash_s[zuhao];
        while (time <= end_time) {
            /**********评估过程***********/
            for (int j = 0; j < 8; j++) {
                if ((S[j] - L[pos][j]) > 0)
                    T[j] = S[j] + rep[j] + B[j] * put_down;
                else
                    T[j] = L[pos][j] + rep[j] + B[j] * put_down;
                //移动T + 上下料T + 清洗T
            }
            /**********选择过程***********/
            next_pos = min_index(T);//选择代价最小的
            //起到了初始化的作用
            pos = next_pos;
            time += T[next_pos];//时间需要延长这个过程的时间
            if (time > end_time) break;
            if (B[next_pos]) {
                offtime[next_pos][numm[next_pos]] = time - rep[next_pos] - B[next_pos] * put_down; //除去上下料时间和清洗时间
                sy[num] = next_pos;
                numm[next_pos] ++;
                num++;
            }
            gotime[next_pos][numm[next_pos]] = time - rep[next_pos] - B[next_pos] * put_down; //除去上下料时间和清洗时间
            B[next_pos] = 1;
            if (randuni() <= 0.01) {
                S[next_pos] = int(pro * randuni());
                double tempp = 0;
                tempp = dis(gen);
                while (tempp > 1200 || tempp < 600) tempp = dis(gen);
                S[next_pos] += int(tempp);
                B[next_pos] = 0;
                num_error++;
            }
            else S[next_pos] = pro - B[next_pos] * put_down;
            for (int i = 0; i < 8; i++) {
                if (i != next_pos) {
                    S[i] -= T[next_pos];
                }
            }
        }
        if (show)
            out(num);
        cout << "-------the total number-------" << endl;
        cout << num << endl;
        cout << "----the total error number----" << endl;
        cout << num_error << endl;
    }
    return 0;
}
