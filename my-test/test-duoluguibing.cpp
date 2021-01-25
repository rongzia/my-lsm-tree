//
// Created by rrzhang on 19-3-1.
//

#include <iostream>

using namespace std;

#define LEN 10            //最大归并段长
#define MINKEY -1     //默认全为正数
#define MAXKEY 100    //最大值,当一个段全部输出后的赋值

struct Array {
    int arr[LEN];
    int num;
    int pos;
} *A;

int k, count;
int *LoserTree, *External;

void Adjust(int s) {
    int t = (s + k) / 2;//ls[t]是b[s]的双亲结点的下标
    int temp;
    while (t > 0) {
        if (External[s] > External[LoserTree[t]]) {
            temp = s;
            s = LoserTree[t];
            LoserTree[t] = temp;
        }
        t = t / 2;
    }
    LoserTree[0] = s;
}

void CreateLoserTree() {
    External[k] = MINKEY;
    int i;
    for (i = 0; i < k; i++)LoserTree[i] = k;//设置ls中败者的初值，简化了败者树的建立过程，这样就可以直接通过(调整过程)来建立败者树。
    for (i = k - 1; i >= 0; i--)Adjust(i);
    for(i = 0; i<5; i++){
        cout<<LoserTree[i]<<" ";
    }
}

void K_Merge() {
    int i, p;
    //初始化External数组，用以接下来创建LoserTree
    for (i = 0; i < k; i++) {
        p = A[i].pos;
        External[i] = A[i].arr[p];
        //cout<<External[i]<<",";
        A[i].pos++;
    }
    //创建LoserTree
    CreateLoserTree();
    int NO = 0;
    //输出最小值，并替代调整
    while (NO < count) {
        p = LoserTree[0];
        cout << External[p] << ",";
        NO++;
        if (A[p].pos >= A[p].num)External[p] = MAXKEY;
        else {
            External[p] = A[p].arr[A[p].pos];
            A[p].pos++;
        }
        Adjust(p);
    }
    cout << endl;
}

int main() {
    //freopen("in.txt","r",stdin);

    int i, j;
    count = 0;
    cin >> k;
    A = (Array *) malloc(sizeof(Array) * k);
    for (i = 0; i < k; i++) {
        cin >> A[i].num;
        count = count + A[i].num;
        for (j = 0; j < A[i].num; j++) {
            cin >> A[i].arr[j];
        }
        A[i].pos = 0;
    }
    LoserTree = (int *) malloc(sizeof(int) * k);
    External = (int *) malloc(sizeof(int) * (k + 1));

    K_Merge();
    system("pause");
    return 0;
}