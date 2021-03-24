#include <iostream>
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


//就近原则;
int min_index1(int* T, int num5) {
    int i = 0;
    int num = num5;
    int min_ind = 0;
    for (; i < num; i++) {
        if (T[i] < T[min_ind]) min_ind = i;
    }
    return min_ind;
}

//就近原则;
int min_index2(int* T, int num6) {
    int i = 0;
    int num = num6;
    int min_ind = 0;
    for (; i < num; i++) {
        if (T[i] < T[min_ind]) min_ind = i;
    }
    return min_ind;
}


int main()
{
    int zuhao = 0;
    while (scanf_s("%d", &zuhao)) {
        if (zuhao == -1) break;
        if (zuhao > 3 || zuhao < 1) continue;
        zuhao--;
        int num1 = 0;
        int num2 = 0; //成品数量
        int num5 = 0;
        int num6 = 0;
        int num7[300][9] = { 0 };
        int num8 = 0;
        for (int i1 = 0; i1 < 2; i1++)
            for (int i2 = 0; i2 < 2; i2++)
                for (int i3 = 0; i3 < 2; i3++)
                    for (int i4 = 0; i4 < 2; i4++)
                        for (int i5 = 0; i5 < 2; i5++)
                            for (int i6 = 0; i6 < 2; i6++)
                                for (int i7 = 0; i7 < 2; i7++)
                                    for (int i8 = 0; i8 < 2; i8++) {
                                        int S[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; //加工剩余时间
                                        int B[8][2] = { 0 }; //是否有料
                                        int cnc11[8] = { 0 };
                                        int cnc21[8] = { 0 };
                                        int flag_12 = 0;
                                        int T1[8] = { 0 }; //当前状态到达其他CNC加工台的代价
                                        int T2[8] = { 0 };
                                        num5 = 0;
                                        num6 = 0;
                                        num2 = 0;
                                        num1 = 0;
                                        if (i1 == 0) {
                                            cnc11[num5] = 1;
                                            num5++;
                                        }
                                        else {
                                            cnc21[num6] = 1;
                                            num6++;
                                        }
                                        if (i2 == 0) {
                                            cnc11[num5] = 2;
                                            num5++;
                                        }
                                        else {
                                            cnc21[num6] = 2;
                                            num6++;
                                        }
                                        if (i3 == 0) {
                                            cnc11[num5] = 3;
                                            num5++;
                                        }
                                        else {
                                            cnc21[num6] = 3;
                                            num6++;
                                        }
                                        if (i4 == 0) {
                                            cnc11[num5] = 4;
                                            num5++;
                                        }
                                        else {
                                            cnc21[num6] = 4;
                                            num6++;
                                        }
                                        if (i5 == 0) {
                                            cnc11[num5] = 5;
                                            num5++;
                                        }
                                        else {
                                            cnc21[num6] = 5;
                                            num6++;
                                        }
                                        if (i6 == 0) {
                                            cnc11[num5] = 6;
                                            num5++;
                                        }
                                        else {
                                            cnc21[num6] = 6;
                                            num6++;
                                        }
                                        if (i7 == 0) {
                                            cnc11[num5] = 7;
                                            num5++;
                                        }
                                        else {
                                            cnc21[num6] = 7;
                                            num6++;
                                        }
                                        if (i8 == 0) {
                                            cnc11[num5] = 8;
                                            num5++;
                                        }
                                        else {
                                            cnc21[num6] = 8;
                                            num6++;
                                        }
                                        if (num6 == 0 || num5 == 0) {
                                            num2 = 0;
                                            cout << num8 << ":" << num2;
                                            num7[num8][0] = num2;
                                            num7[num8][1] = i1;
                                            num7[num8][2] = i2;
                                            num7[num8][3] = i3;
                                            num7[num8][4] = i4;
                                            num7[num8][5] = i5;
                                            num7[num8][6] = i6;
                                            num7[num8][7] = i7;
                                            num7[num8][8] = i8;
                                            cout << ";" << i1 << i2 << i3 << i4 << i5 << i6 << i7 << i8 << endl;
                                            num8++;
                                            continue;
                                        }
                                        int time = 0;
                                        int end_time = 28800; //28800;// 3600*8;
                                        int pos = 0, next_pos = 0, next_xuhao = 0;//小车起始位置
                                        for (int i = 0; i < 8; i++) {
                                            int temp = i / 2;
                                            for (int j = 0; j < 8; j++) {
                                                L[i][j] = d[zuhao][abs(j / 2 - temp)];
                                            }
                                        }
                                        for (int i = 0; i < 8; i++) rep[i] = rep_s[zuhao][i];
                                        pro1 = pro_s[0][zuhao];
                                        pro2 = pro_s[1][zuhao];
                                        put_down = wash_s[zuhao];
                                        while (time <= end_time) {
                                            if (flag_12 == 0) {
                                                /**********评估过程***********/
                                                for (int i = 0; i < num5; i++) {
                                                    int j = cnc11[i] - 1;
                                                    if ((S[j] - L[pos][j]) > 0)
                                                        T1[i] = S[j] + rep[j];
                                                    else
                                                        T1[i] = L[pos][j] + rep[j];
                                                    //移动T + 上下料T
                                                }
                                                /**********选择过程***********/
                                                next_xuhao = min_index1(T1, num5);
                                                next_pos = cnc11[next_xuhao] - 1;//选择代价最小的
                                                //起到了初始化的作用
                                                pos = next_pos;
                                                time += T1[next_xuhao];//时间需要延长这个过程的时间
                                                if (B[next_pos][0]) {
                                                    flag_12 = 1;
                                                    num1++;
                                                }
                                                B[next_pos][0] = 1;
                                                S[next_pos] = pro1;
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
                                                    int j = cnc21[i] - 1;
                                                    if ((S[j] - L[pos][j]) > 0)
                                                        T2[i] = S[j] + rep[j] + B[j][0] * put_down;
                                                    else
                                                        T2[i] = L[pos][j] + rep[j] + B[j][0] * put_down;
                                                    //移动T + 上下料T + 清洗T
                                                }
                                                /**********选择过程***********/
                                                next_xuhao = min_index2(T2, num6);
                                                next_pos = cnc21[next_xuhao] - 1;//选择代价最小的
                                                //起到了初始化的作用
                                                pos = next_pos;
                                                time += T2[next_xuhao];//时间需要延长这个过程的时间

                                                if (time > end_time) break;

                                                if (B[next_pos][0]) {
                                                    num2++;
                                                }
                                                B[next_pos][0] = 1;
                                                S[next_pos] = pro2 - B[next_pos][0] * put_down;
                                                for (int i = 0; i < 8; i++) {
                                                    if (i != next_pos) {
                                                        S[i] -= T2[next_xuhao];
                                                    }
                                                }
                                            }
                                        }
                                        cout << num8 << ":" << num2;
                                        num7[num8][0] = num2;
                                        num7[num8][1] = i1;
                                        num7[num8][2] = i2;
                                        num7[num8][3] = i3;
                                        num7[num8][4] = i4;
                                        num7[num8][5] = i5;
                                        num7[num8][6] = i6;
                                        num7[num8][7] = i7;
                                        num7[num8][8] = i8;
                                        cout << ";" << i1 << i2 << i3 << i4 << i5 << i6 << i7 << i8 << endl;
                                        num8++;
                                    }
        int temp = 0;
        int max_num = 0;
        max_num = num7[0][0];
        for (int i = 0; i < 300; i++) {
            temp = num7[i][0];
            if (temp >= max_num) {
                max_num = temp;
            }
        }
        cout << "-------max--------" << endl;
        for (int i = 0; i < 300; i++) {
            temp = num7[i][0];
            if (temp == max_num) {
                cout << i << endl;
                for (int j = 0; j < 9; j++) {
                    if (j == 0) cout << num7[i][j] << ";";
                    else if (j > 0 && j < 8) cout << j << " ";
                    else cout << j << endl;
                }
                for (int j = 0; j < 9; j++) {
                    if (j == 0) cout << num7[i][j] << ";";
                    else if (j > 0 && j < 8) cout << num7[i][j] << " ";
                    else cout << num7[i][j] << endl;
                }
            }
        }
    }
    return 0;
}
