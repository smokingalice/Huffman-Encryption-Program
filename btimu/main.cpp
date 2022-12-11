#include<stdio.h>
#include<graphics.h>
#include <malloc.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>
#include<fstream>
#include<string>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include<setjmp.h>

using namespace std;
int xx;//用于下问随机字典配置，定义在头部是为了减少重定义
const int hid = 3461;//一共3461个单词（包括逗号句号问号右引号四个符号）
typedef struct zidian
{
    string word;//单词
    int count;//权值（随机方式）
    int parent;
    int lchild;
    int rchild;
    char* mima;//存放密码（动态分配，毕竟不知道密码到底多长多短）
}zidian;

string daxiezhuanxiaoxie(string& s) {
    int len = s.size();
    string s1 = s;
    for (int i = 0; i < len; i++) {
        if (s1[i] >= 'A' && s1[i] <= 'Z') {
            s1[i] += 32;//+32转换为小写          
        }
    }
    return s1;
}
string shouzimuzhuanhuan(string& s) {//首字母转换为大写
    if (s[0] >= 'a' && s[0] <= 'z') {
        s[0] -= 32;//-32转换为大写          
    }
    return s;
}
int douhaojuhaopanduan(string& s, int* n) {//用于判断逗号句号在字符串的哪个位置，并返回位置信息
    int len = s.size();
    string s1 = s;
    string s2;
    if (s == "," || s == "." || s == "?" || s == "'")
        return 1;
    if (s1[len - 1] == ',') {//在末尾
        s2 = s1[len - 1]; *n = len - 1; return 3457;
    }
    if (s1[len - 1] == '.') {
        s2 = s1[len - 1]; *n = len - 1; return 3458;
    }
    if (s1[len - 1] == '?') {
        s2 = s1[len - 1]; *n = len - 1; return 3459;
    }
    if (s1[len - 1] == 39) {
        s2 = s1[len - 1]; *n = len - 1; return 3460;
    }
    if (s1[0] == ',') {//在头部
        s2 = s1[len - 1]; *n = 0; return 3457;
    }
    if (s1[0] == '.') {
        s2 = s1[len - 1]; *n = 0; return 3458;
    }
    if (s1[0] == '?') {
        s2 = s1[len - 1]; *n = 0; return 3459;
    }
    if (s1[0] == 39) {
        s2 = s1[len - 1]; *n = 0; return 3460;
    }
    for (int i = 0; i < len; i++)
    {
        if (s1[i] == ',') {//在中间某个位置，比如I'M
            *n = i; return 3457;
        }
        if (s1[i] == '.') {
            *n = i; return 3458;
        }
        if (s1[i] == '?') {
            *n = i; return 3459;
        }
        if (s1[i] == 39) {
            *n = i; return 3460;
        }
    }
   
    return 1;

}

int LCSbianzhong(string X, string Y) {//用来求最长公共连续子序列，如hing和heingr的最长公共子序列为ing，返回其长度就行，此时返回3，用动态规划方法。

    int c[40][40] = { 0 };//定义矩阵数组
    int maxlen = 0;
    int maxindex = 0;
    for (int i = 1; i <= X.size(); i++) {
        for (int j = 1; j <= Y.size(); j++) {
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;//动态规划，即二维数组存储法
                if (c[i][j] > maxlen)
                {
                    maxlen = c[i][j];
                    maxindex = i + 1 - maxlen;
                }
            }
        }
    }
    return maxlen;
}
void danzhuanshuang(string& s) {//单斜杠转为双斜杠，方便文件直接复制输入读取
    string::size_type pos = 0;
    while ((pos = s.find('\\', pos)) != string::npos) {
        s.insert(pos, "\\");
        pos = pos + 2;
    }
}

int feizifuweizhi(string& s) {//判断字符串非字符位置，主要用于导入字典使用
    int len = s.size(); int k;
    for (int i = 0; i < len; i++) {
        k = i;
        if ((s[i] >= 124 || s[i] <= 64) && (s[i] != 44 && s[i] != 46 && s[i] != 63 && s[i] != 39)) {

            break;
        }
    }
    if (k == 0)return k + 1;
    else return k;
}

void zidiangoujian(zidian* zidian, string filename1)
{
    string filename = "word.txt";//从网上找到的单词表导入单词到字典
    fstream inf(filename);
    string str;
    if (!inf)
    {
        cout << "open error";
        return;
    }
    int i = 0;
    getline(inf, str);
    zidian[i].word = str.substr(0, feizifuweizhi(str));//除去非字典字符
    while (!inf.eof())
    {
        i++;
        getline(inf, str);
        if (inf.fail())break;
        zidian[i].word = str.substr(0, feizifuweizhi(str));
    }

    inf.close();
    ofstream outf(filename1);


    for (int j = 0; j < hid; j++)
    {
        outf << zidian[j].word << ":" << zidian[j].count << endl;
    }
    outf.close();
}//用于处理从网上下载的单词，把他化成我需要的单词列

void quanzhisuijishu(zidian* zidian)//用于产生不重复的随机数
{
    int radnum = 3500;
    int* suijishuzu = new int[3500];
    for (int i = 0; i < 3500; i++)
    {
        suijishuzu[i] = i + 1;
    }
    int ranlen;

    for (int i = 0; i < 3500; i++)
    {


        int x = rand() % (radnum);
        radnum = radnum - 1;
        zidian[i].count = suijishuzu[x];     //把每一次获得的随机数保留到一个数组中
        if (x == radnum)
        {
            suijishuzu[x] = 0;
        }
        else
        {
            suijishuzu[x] = suijishuzu[radnum];
            suijishuzu[radnum] = 0;
        }
    }
    return;

}
void daoruzidian(zidian* zidian, string filename)
{//将生成的字典导入到zidian.txt,方便展示观看以及应用

    fstream inf(filename);
    string str;
    if (!inf)
    {
        cout << "open error";
        return;
    }
    int i = 0;
    inf >> str;
    zidian[i].word = str.substr(0, str.find_first_of(":"));
    zidian[i].count = stoi(str.substr(str.find_first_of(":") + 1, str.length()));
    while (!inf.eof())
    {
        i++;
        inf >> str;
        if (inf.fail())break;
        zidian[i].word = str.substr(0, str.find_first_of(":"));
        zidian[i].count = stoi(str.substr(str.find_first_of(":") + 1, str.length()));
    }
    inf.close();
}

void quanzhixiaozhe(zidian* zdt, int end, int* s1, int* s2) //找出剩下的节点中小的节点
{
    int min1, min2;//min1<min2
    int i = 0;
    while (zdt[i].parent != 0 && i <= end) {
        i++;
    }
    min1 = zdt[i].count;
    *s1 = i;
    i++;
    while (zdt[i].parent != 0 && i <= end) {
        i++;
    }
    if (zdt[i].count < min1) {
        min2 = min1;
        *s2 = *s1;
        min1 = zdt[i].count;
        *s1 = i;
    }
    else {
        min2 = zdt[i].count;
        *s2 = i;
    }
    //对余下的结点进行遍历
    for (int j = i + 1; j <= end; j++) {
        if (zdt[j].parent != 0) continue;
        if (zdt[j].count < min1) {
            min2 = min1;
            min1 = zdt[j].count;
            *s2 = *s1;
            *s1 = j;
        }
        //如果 min1<=zdt[i].count<=min2,则 将zdt[j].count的值赋给min2
        else if (zdt[j].count >= min1 && zdt[j].count < min2) {
            min2 = zdt[j].count;
            *s2 = j;
        }

    }
}
void gouzaohafuman(zidian* zdt)
{
    //构造哈夫曼树
    int m = 2 * hid - 1;
    for (int i = hid; i < m; i++) {
        int s1 = 0, s2 = 0;
        quanzhixiaozhe(zdt, i - 1, &s1, &s2);//找出剩余节点中权值小的
        zdt[s1].parent = i; zdt[s2].parent = i;
        zdt[i].lchild = s1;//将s1和s2分别作为结点i的左右孩子 
        zdt[i].rchild = s2;
        zdt[i].count = zdt[s1].count + zdt[s2].count;//结点i的权值为左右孩子之和,即合树的过程
    }
}



void dedaobianma(zidian* num) {
    //得到哈夫曼编码 
    int xunhuan, c, f;

    char* cd = new char[hid];
    cd[hid - 1] = '\0';
    for (int i = 0; i < hid; i++) { //从头开始遍历   
        xunhuan = hid - 1;
        c = i; f = num[i].parent;
        while (f != 0) {
            xunhuan--;
            if (num[f].lchild == c) cd[xunhuan] = '0';
            else cd[xunhuan] = '1';//从树尾往上搜索，直到搜索到

            c = f; f = num[f].parent;
        }
        num[i].mima = new char[hid - xunhuan];
        strcpy_s(num[i].mima, hid - xunhuan, &cd[xunhuan]);

    }
    delete cd;
}
void dedaobianma2(zidian* num, int n) {
    //得到哈夫曼编码 
    int xunhuan, c, f;

    char* cd = new char[hid];
    cd[hid - 1] = '\0';
    for (int i = 0; i < hid; i++) {
        xunhuan = hid - 1;
        c = i; f = num[i].parent;
        while (f != 0) {
            xunhuan--;
            if (num[f].lchild == c) cd[xunhuan] = '0';
            else cd[xunhuan] = '1';//从树尾往上搜索，直到搜索到

            c = f; f = num[f].parent;
        }
        if (n == 1)//赋予哈夫曼编码前两位，用于多字典解密
        {
            cd[xunhuan - 1] = '0';
            cd[xunhuan - 2] = '0';
        }
        if (n == 2)
        {
            cd[xunhuan - 1] = '1';
            cd[xunhuan - 2] = '0';
        }
        if (n == 3)
        {
            cd[xunhuan - 1] = '0';
            cd[xunhuan - 2] = '1';
        }
        if (n == 4)
        {
            cd[xunhuan - 1] = '1';
            cd[xunhuan - 2] = '1';
        }


        num[i].mima = new char[hid - xunhuan + 2];
        strcpy_s(num[i].mima, hid - xunhuan + 2, &cd[xunhuan - 2]);

    }
    delete cd;
}
void fanyiwenjian(zidian* zidian1)
//将文章翻译为哈夫曼码，其中包括符号和单词连在一起时的处理方式。如i'm等，但不支持一个连续字符单词有多个符号，
//且符号只支持逗号，句号，问好和单引号即 , . ? '
//
{
    string filename;
    cin >> filename;
    danzhuanshuang(filename);

    fstream inf(filename);
    ofstream outf("jiamiwenjian.txt");
    string str;
    if (!inf)
    {
        cout << "文件名输入错误或输入的不是文件名" << endl;
        return;
    }
    cout << "加密结果如下" << endl;
    int panduan = 0;
    int i = 0;
    inf >> str;
    int n1;
    panduan = douhaojuhaopanduan(str, &n1);//判断标点
    int jj = 1;
    int cd = 0;
    if (panduan == 1)//判断字符是否含有标点
    {

        for (int i = 0; i < hid; i++)
        {
            if (daxiezhuanxiaoxie(str) == daxiezhuanxiaoxie(zidian1[i].word))//全部转换为小写后对比，下文同理
            {
                cout << zidian1[i].mima;
                outf << zidian1[i].mima;
                jj = 2;
                break;
            }

        }
        if (jj == 1)//用于判断能否从字典中找到单词，下文同理
        {
            int ks=0;
            cd = 0;
            for (int i = 0; i < hid; i++)
            {

                int d = LCSbianzhong(daxiezhuanxiaoxie(str), daxiezhuanxiaoxie(zidian1[i].word));
                if (cd < d)
                    cd = d, ks = i;

            }
            cout << zidian1[ks].mima;
            outf << zidian1[ks].mima;
        }
    }
    else
    {
        if (n1 == str.size() - 1) {//进入有标点的情况，分类为三种，标点在前，在后以及在中间
            string str1 = str.substr(0, str.size() - 1);
            for (int i = 0; i < hid; i++)
            {
                if (daxiezhuanxiaoxie(str1) == daxiezhuanxiaoxie(zidian1[i].word))
                {
                    cout << zidian1[i].mima;
                    outf << zidian1[i].mima;
                    jj = 2;
                    break;
                }

            }
            if (jj == 1)
            {
                int ks=0;
                cd = 0;
                for (int i = 0; i < hid; i++)
                {
                    int d = LCSbianzhong(daxiezhuanxiaoxie(str), daxiezhuanxiaoxie(zidian1[i].word));
                    if (cd < d)
                        cd = d, ks = i;

                }
                cout << zidian1[ks].mima;
                outf << zidian1[ks].mima;
            }

            cout << zidian1[panduan].mima;
            outf << zidian1[panduan].mima;

        }
        else if (n1 == 0) {


            cout << zidian1[panduan].mima;
            outf << zidian1[panduan].mima;
            string str1 = str.substr(1, str.size() - 1);
            for (int i = 0; i < hid; i++)
            {
                if (daxiezhuanxiaoxie(str1) == daxiezhuanxiaoxie(zidian1[i].word))
                {
                    cout << zidian1[i].mima;
                    outf << zidian1[i].mima;
                    jj = 2;
                    break;
                }

            }
            if (jj == 1)
            {
                int ks=0; cd = 0;
                for (int i = 0; i < hid; i++)
                {
                    int d = LCSbianzhong(daxiezhuanxiaoxie(str), daxiezhuanxiaoxie(zidian1[i].word));
                    if (cd < d)
                        cd = d, ks = i;

                }
                cout << zidian1[ks].mima;
                outf << zidian1[ks].mima;
            }


        }
        else
        {
            string str1 = str.substr(0, n1);
            for (int i = 0; i < hid; i++)
            {
                if (daxiezhuanxiaoxie(str1) == daxiezhuanxiaoxie(zidian1[i].word))
                {
                    cout << zidian1[i].mima;
                    outf << zidian1[i].mima;
                    jj = 2;
                    break;
                }

            }
            if (jj == 1)
            {
                int ks=0; cd = 0;
                for (int i = 0; i < hid; i++)
                {
                    int d = LCSbianzhong(daxiezhuanxiaoxie(str1), daxiezhuanxiaoxie(zidian1[i].word));
                    if (cd < d)
                        cd = d, ks = i;

                }
                cout << zidian1[ks].mima;
                outf << zidian1[ks].mima;
            }


            cout << zidian1[panduan].mima;
            outf << zidian1[panduan].mima;
            string str2 = str.substr(n1 + 1, str.size() - 1 - n1);
            for (int i = 0; i < hid; i++)
            {
                if (daxiezhuanxiaoxie(str2) == daxiezhuanxiaoxie(zidian1[i].word))
                {
                    cout << zidian1[i].mima;
                    outf << zidian1[i].mima;
                    jj = 2;
                    break;
                }

            }
            if (jj == 1)
            {
                int ks=0; cd = 0;
                for (int i = 0; i < hid; i++)
                {
                    int d = LCSbianzhong(daxiezhuanxiaoxie(str2), daxiezhuanxiaoxie(zidian1[i].word));
                    if (cd < d)
                        cd = d, ks = i;

                }
                cout << zidian1[ks].mima;
                outf << zidian1[ks].mima;
            }



        }
    }
    while (!inf.eof())//循环读取文件单词即可，内容和第一次读取时一致
    {
        i++;
        inf >> str;
        panduan = douhaojuhaopanduan(str, &n1);
        int jj = 1;
        int cd = 0;
        if (panduan == 1)
        {

            for (int i = 0; i < hid; i++)
            {
                if (daxiezhuanxiaoxie(str) == daxiezhuanxiaoxie(zidian1[i].word))
                {
                    cout << zidian1[i].mima;
                    outf << zidian1[i].mima;
                    jj = 2;
                    break;
                }

            }
            if (jj == 1)
            {
                int ks=0; cd = 0;
                for (int i = 0; i < hid; i++)
                {

                    int d = LCSbianzhong(daxiezhuanxiaoxie(str), daxiezhuanxiaoxie(zidian1[i].word));
                    if (cd < d)
                        cd = d, ks = i;

                }
                cout << zidian1[ks].mima;
                outf << zidian1[ks].mima;
            }
        }
        else
        {
            if (n1 == str.size() - 1) {
                string str1 = str.substr(0, str.size() - 1);
                for (int i = 0; i < hid; i++)
                {
                    if (daxiezhuanxiaoxie(str1) == daxiezhuanxiaoxie(zidian1[i].word))
                    {
                        cout << zidian1[i].mima;
                        outf << zidian1[i].mima;
                        jj = 2;
                        break;
                    }

                }
                if (jj == 1)
                {
                    int ks=0; cd = 0;
                    for (int i = 0; i < hid; i++)
                    {
                        int d = LCSbianzhong(daxiezhuanxiaoxie(str), daxiezhuanxiaoxie(zidian1[i].word));
                        if (cd < d)
                            cd = d, ks = i;

                    }
                    cout << zidian1[ks].mima;
                    outf << zidian1[ks].mima;
                }

                cout << zidian1[panduan].mima;
                outf << zidian1[panduan].mima;

            }
            else if (n1 == 0)
            {


                cout << zidian1[panduan].mima;
                outf << zidian1[panduan].mima;
                string str1 = str.substr(1, str.size() - 1);
                for (int i = 0; i < hid; i++)
                {
                    if (daxiezhuanxiaoxie(str1) == daxiezhuanxiaoxie(zidian1[i].word))
                    {
                        cout << zidian1[i].mima;
                        outf << zidian1[i].mima;
                        jj = 2;
                        break;
                    }

                }
                if (jj == 1)
                {
                    int ks=0; cd = 0;
                    for (int i = 0; i < hid; i++)
                    {
                        int d = LCSbianzhong(daxiezhuanxiaoxie(str), daxiezhuanxiaoxie(zidian1[i].word));
                        if (cd < d)
                            cd = d, ks = i;

                    }
                    cout << zidian1[ks].mima;
                    outf << zidian1[ks].mima;
                }


            }
            else
            {
                string str1 = str.substr(0, n1);
                for (int i = 0; i < hid; i++)
                {
                    if (daxiezhuanxiaoxie(str1) == daxiezhuanxiaoxie(zidian1[i].word))
                    {
                        cout << zidian1[i].mima;
                        outf << zidian1[i].mima;
                        jj = 2;
                        break;
                    }

                }
                if (jj == 1)
                {
                    int ks=0; cd = 0;
                    for (int i = 0; i < hid; i++)
                    {
                        int d = LCSbianzhong(daxiezhuanxiaoxie(str1), daxiezhuanxiaoxie(zidian1[i].word));
                        if (cd < d)
                            cd = d, ks = i;

                    }
                    cout << zidian1[ks].mima;
                    outf << zidian1[ks].mima;
                }


                cout << zidian1[panduan].mima;
                outf << zidian1[panduan].mima;
                string str2 = str.substr(n1 + 1, str.size() - 1 - n1);
                for (int i = 0; i < hid; i++)
                {
                    if (daxiezhuanxiaoxie(str2) == daxiezhuanxiaoxie(zidian1[i].word))
                    {
                        cout << zidian1[i].mima;
                        outf << zidian1[i].mima;
                        jj = 2;
                        break;
                    }

                }
                if (jj == 1)
                {
                    int ks=0; cd = 0;
                    for (int i = 0; i < hid; i++)
                    {
                        int d1 = LCSbianzhong(daxiezhuanxiaoxie(str2), daxiezhuanxiaoxie(zidian1[i].word));
                        if (cd < d1)
                            cd = d1, ks = i;

                    }
                    cout << zidian1[ks].mima;
                    outf << zidian1[ks].mima;
                }

            }
        }
    }
    cout << endl << "加密结果已自动生成文件jiamijieguo.txt,在该程序的文件夹中自行查找" << endl;//输出
    inf.close();
    outf.close();
}
void fanyiwenjian2(zidian* zidian1, zidian* zidian2, zidian* zidian3, zidian* zidian4)
//将文章翻译为哈夫曼码，其中包括符号和单词连在一起时的处理方式。如i'm等，但不支持一个连续字符单词有多个符号，
//且符号只支持逗号，句号，问好和单引号即 , . ? '
 //该函数实现多字典的识别，本质为每个单词随机赋予一个1到4任意值，然后将其00，01，10，11分别加入单词前两位，
 //体现随机性和不确定性，完成提高目标
 //其于基础部分与fanyiwenjian函数类似，这里不多做注释
{
    string filename;
    cin >> filename;
    danzhuanshuang(filename);
    fstream inf(filename);
    ofstream outf("jiamiwenjian.txt");

    string str;
    if (!inf)
    {
        cout << "文件名输入错误或输入的不是文件名" << endl;
        return;
    }
    cout << "加密结果如下" << endl;
    int panduan = 0;
    int i = 0;
    int n1;
    inf >> str;
    panduan = douhaojuhaopanduan(str, &n1);
    int jj = 1;
    int cd = 0;
    if (panduan == 1)
    {

        for (int i = 0; i < hid; i++)
        {
            if (daxiezhuanxiaoxie(str) == daxiezhuanxiaoxie(zidian1[i].word))
            {
                xx = 1 + rand() % (4);//体现赋予随机数的部分，
                if (xx == 1)//将输入的密码变化成前两位为00，01，10，11的密码，下文同样如此
                {
                    cout << zidian1[i].mima;
                    outf << zidian1[i].mima;
                }
                if (xx == 2)
                {
                    cout << zidian2[i].mima;
                    outf << zidian2[i].mima;
                }
                if (xx == 3)
                {
                    cout << zidian3[i].mima;
                    outf << zidian3[i].mima;
                }
                if (xx == 4)
                {
                    cout << zidian4[i].mima;
                    outf << zidian4[i].mima;
                }
                jj = 2;
                break;
            }

        }
        if (jj == 1)
        {
            int ks=0; cd = 0;
            for (int i = 0; i < hid; i++)
            {

                int d = LCSbianzhong(daxiezhuanxiaoxie(str), daxiezhuanxiaoxie(zidian1[i].word));
                if (cd < d)
                    cd = d, ks = i;

            }
            xx = 1 + rand() % (4);
            if (xx == 1)
            {
                cout << zidian1[ks].mima;
                outf << zidian1[ks].mima;
            }
            if (xx == 2)
            {
                cout << zidian2[ks].mima;
                outf << zidian2[ks].mima;
            }
            if (xx == 3)
            {
                cout << zidian3[ks].mima;
                outf << zidian3[ks].mima;
            }
            if (xx == 4)
            {
                cout << zidian4[ks].mima;
                outf << zidian4[ks].mima;
            }
        }
    }
    else
    {
        if (n1 == str.size() - 1) {
            string str1 = str.substr(0, str.size() - 1);
            for (int i = 0; i < hid; i++)
            {
                if (daxiezhuanxiaoxie(str1) == daxiezhuanxiaoxie(zidian1[i].word))
                {
                    xx = 1 + rand() % (4);
                    if (xx == 1)
                    {
                        cout << zidian1[i].mima;
                        outf << zidian1[i].mima;
                    }
                    if (xx == 2)
                    {
                        cout << zidian2[i].mima;
                        outf << zidian2[i].mima;
                    }
                    if (xx == 3)
                    {
                        cout << zidian3[i].mima;
                        outf << zidian3[i].mima;
                    }
                    if (xx == 4)
                    {
                        cout << zidian4[i].mima;
                        outf << zidian4[i].mima;
                    }
                    jj = 2;
                    break;
                }

            }
            if (jj == 1)
            {
                int ks=0; cd = 0;
                for (int i = 0; i < hid; i++)
                {
                    int d = LCSbianzhong(daxiezhuanxiaoxie(str), daxiezhuanxiaoxie(zidian1[i].word));
                    if (cd < d)
                        cd = d, ks = i;

                }
                xx = 1 + rand() % (4);
                if (xx == 1)
                {
                    cout << zidian1[ks].mima;
                    outf << zidian1[ks].mima;
                }
                if (xx == 2)
                {
                    cout << zidian2[ks].mima;
                    outf << zidian2[ks].mima;
                }
                if (xx == 3)
                {
                    cout << zidian3[ks].mima;
                    outf << zidian3[ks].mima;
                }
                if (xx == 4)
                {
                    cout << zidian4[ks].mima;
                    outf << zidian4[ks].mima;
                }
            }

            xx = 1 + rand() % (4);
            if (xx == 1)
            {
                cout << zidian1[panduan].mima;
                outf << zidian1[panduan].mima;
            }
            if (xx == 2)
            {
                cout << zidian2[panduan].mima;
                outf << zidian2[panduan].mima;
            }
            if (xx == 3)
            {
                cout << zidian3[panduan].mima;
                outf << zidian3[panduan].mima;
            }
            if (xx == 4)
            {
                cout << zidian4[panduan].mima;
                outf << zidian4[panduan].mima;
            }

        }
        else if (n1 == 0)
        {


            xx = 1 + rand() % (4);
            if (xx == 1)
            {
                cout << zidian1[panduan].mima;
                outf << zidian1[panduan].mima;
            }
            if (xx == 2)
            {
                cout << zidian2[panduan].mima;
                outf << zidian2[panduan].mima;
            }
            if (xx == 3)
            {
                cout << zidian3[panduan].mima;
                outf << zidian3[panduan].mima;
            }
            if (xx == 4)
            {
                cout << zidian4[panduan].mima;
                outf << zidian4[panduan].mima;
            }
            string str1 = str.substr(1, str.size() - 1);
            for (int i = 0; i < hid; i++)
            {
                if (daxiezhuanxiaoxie(str1) == daxiezhuanxiaoxie(zidian1[i].word))
                {
                    xx = 1 + rand() % (4);
                    if (xx == 1)
                    {
                        cout << zidian1[i].mima;
                        outf << zidian1[i].mima;
                    }
                    if (xx == 2)
                    {
                        cout << zidian2[i].mima;
                        outf << zidian2[i].mima;
                    }
                    if (xx == 3)
                    {
                        cout << zidian3[i].mima;
                        outf << zidian3[i].mima;
                    }
                    if (xx == 4)
                    {
                        cout << zidian4[i].mima;
                        outf << zidian4[i].mima;
                    }
                    jj = 2;
                    break;
                }

            }
            if (jj == 1)
            {
                int ks=0; cd = 0;
                for (int i = 0; i < hid; i++)
                {
                    int d = LCSbianzhong(daxiezhuanxiaoxie(str), daxiezhuanxiaoxie(zidian1[i].word));
                    if (cd < d)
                        cd = d, ks = i;

                }
                xx = 1 + rand() % (4);
                if (xx == 1)
                {
                    cout << zidian1[ks].mima;
                    outf << zidian1[ks].mima;
                }
                if (xx == 2)
                {
                    cout << zidian2[ks].mima;
                    outf << zidian2[ks].mima;
                }
                if (xx == 3)
                {
                    cout << zidian3[ks].mima;
                    outf << zidian3[ks].mima;
                }
                if (xx == 4)
                {
                    cout << zidian4[ks].mima;
                    outf << zidian4[ks].mima;
                }
            }


        }
        else
        {
            string str1 = str.substr(0, n1);
            for (int i = 0; i < hid; i++)
            {
                if (daxiezhuanxiaoxie(str1) == daxiezhuanxiaoxie(zidian1[i].word))
                {
                    xx = 1 + rand() % (4);
                    if (xx == 1)
                    {
                        cout << zidian1[i].mima;
                        outf << zidian1[i].mima;
                    }
                    if (xx == 2)
                    {
                        cout << zidian2[i].mima;
                        outf << zidian2[i].mima;
                    }
                    if (xx == 3)
                    {
                        cout << zidian3[i].mima;
                        outf << zidian3[i].mima;
                    }
                    if (xx == 4)
                    {
                        cout << zidian4[i].mima;
                        outf << zidian4[i].mima;
                    }
                    jj = 2;
                    break;
                }

            }
            if (jj == 1)
            {
                int ks=0; cd = 0;
                for (int i = 0; i < hid; i++)
                {
                    int d = LCSbianzhong(daxiezhuanxiaoxie(str1), daxiezhuanxiaoxie(zidian1[i].word));
                    if (cd < d)
                        cd = d, ks = i;

                }
                xx = 1 + rand() % (4);
                if (xx == 1)
                {
                    cout << zidian1[ks].mima;
                    outf << zidian1[ks].mima;
                }
                if (xx == 2)
                {
                    cout << zidian2[ks].mima;
                    outf << zidian2[ks].mima;
                }
                if (xx == 3)
                {
                    cout << zidian3[ks].mima;
                    outf << zidian3[ks].mima;
                }
                if (xx == 4)
                {
                    cout << zidian4[ks].mima;
                    outf << zidian4[ks].mima;
                }
            }


            xx = 1 + rand() % (4);
            if (xx == 1)
            {
                cout << zidian1[panduan].mima;
                outf << zidian1[panduan].mima;
            }
            if (xx == 2)
            {
                cout << zidian2[panduan].mima;
                outf << zidian2[panduan].mima;
            }
            if (xx == 3)
            {
                cout << zidian3[panduan].mima;
                outf << zidian3[panduan].mima;
            }
            if (xx == 4)
            {
                cout << zidian4[panduan].mima;
                outf << zidian4[panduan].mima;
            }
            string str2 = str.substr(n1 + 1, str.size() - 1 - n1);
            for (int i = 0; i < hid; i++)
            {
                if (daxiezhuanxiaoxie(str2) == daxiezhuanxiaoxie(zidian1[i].word))
                {
                    xx = 1 + rand() % (4);
                    if (xx == 1)
                    {
                        cout << zidian1[i].mima;
                        outf << zidian1[i].mima;
                    }
                    if (xx == 2)
                    {
                        cout << zidian2[i].mima;
                        outf << zidian2[i].mima;
                    }
                    if (xx == 3)
                    {
                        cout << zidian3[i].mima;
                        outf << zidian3[i].mima;
                    }
                    if (xx == 4)
                    {
                        cout << zidian4[i].mima;
                        outf << zidian4[i].mima;
                    }
                    jj = 2;
                    break;
                }

            }
            if (jj == 1)
            {
                int ks=0; cd = 0;
                for (int i = 0; i < hid; i++)
                {
                    int d1 = LCSbianzhong(daxiezhuanxiaoxie(str2), daxiezhuanxiaoxie(zidian1[i].word));
                    if (cd < d1)
                        cd = d1, ks = i;

                }
                xx = 1 + rand() % (4);
                if (xx == 1)
                {
                    cout << zidian1[ks].mima;
                    outf << zidian1[ks].mima;
                }
                if (xx == 2)
                {
                    cout << zidian2[ks].mima;
                    outf << zidian2[ks].mima;
                }
                if (xx == 3)
                {
                    cout << zidian3[ks].mima;
                    outf << zidian3[ks].mima;
                }
                if (xx == 4)
                {
                    cout << zidian4[ks].mima;
                    outf << zidian4[ks].mima;
                }
            }

        }
    }
    while (!inf.eof())
    {
        i++;
        inf >> str;
        panduan = douhaojuhaopanduan(str, &n1);
        int jj = 1;
        int cd = 0;
        if (panduan == 1)
        {

            for (int i = 0; i < hid; i++)
            {
                if (daxiezhuanxiaoxie(str) == daxiezhuanxiaoxie(zidian1[i].word))
                {
                    xx = 1 + rand() % (4);
                    if (xx == 1)
                    {
                        cout << zidian1[i].mima;
                        outf << zidian1[i].mima;
                    }
                    if (xx == 2)
                    {
                        cout << zidian2[i].mima;
                        outf << zidian2[i].mima;
                    }
                    if (xx == 3)
                    {
                        cout << zidian3[i].mima;
                        outf << zidian3[i].mima;
                    }
                    if (xx == 4)
                    {
                        cout << zidian4[i].mima;
                        outf << zidian4[i].mima;
                    }
                    jj = 2;
                    break;
                }

            }
            if (jj == 1)
            {
                int ks=0; cd = 0;
                for (int i = 0; i < hid; i++)
                {

                    int d = LCSbianzhong(daxiezhuanxiaoxie(str), daxiezhuanxiaoxie(zidian1[i].word));
                    if (cd < d)
                        cd = d, ks = i;

                }
                xx = 1 + rand() % (4);
                if (xx == 1)
                {
                    cout << zidian1[ks].mima;
                    outf << zidian1[ks].mima;
                }
                if (xx == 2)
                {
                    cout << zidian2[ks].mima;
                    outf << zidian2[ks].mima;
                }
                if (xx == 3)
                {
                    cout << zidian3[ks].mima;
                    outf << zidian3[ks].mima;
                }
                if (xx == 4)
                {
                    cout << zidian4[ks].mima;
                    outf << zidian4[ks].mima;
                }
            }
        }
        else
        {
            if (n1 == str.size() - 1) {
                string str1 = str.substr(0, str.size() - 1);
                for (int i = 0; i < hid; i++)
                {
                    if (daxiezhuanxiaoxie(str1) == daxiezhuanxiaoxie(zidian1[i].word))
                    {
                        xx = 1 + rand() % (4);
                        if (xx == 1)
                        {
                            cout << zidian1[i].mima;
                            outf << zidian1[i].mima;
                        }
                        if (xx == 2)
                        {
                            cout << zidian2[i].mima;
                            outf << zidian2[i].mima;
                        }
                        if (xx == 3)
                        {
                            cout << zidian3[i].mima;
                            outf << zidian3[i].mima;
                        }
                        if (xx == 4)
                        {
                            cout << zidian4[i].mima;
                            outf << zidian4[i].mima;
                        }
                        jj = 2;
                        break;
                    }

                }
                if (jj == 1)
                {
                    int ks=0; cd = 0;
                    for (int i = 0; i < hid; i++)
                    {
                        int d = LCSbianzhong(daxiezhuanxiaoxie(str), daxiezhuanxiaoxie(zidian1[i].word));
                        if (cd < d)
                            cd = d, ks = i;

                    }
                    xx = 1 + rand() % (4);
                    if (xx == 1)
                    {
                        cout << zidian1[ks].mima;
                        outf << zidian1[ks].mima;
                    }
                    if (xx == 2)
                    {
                        cout << zidian2[ks].mima;
                        outf << zidian2[ks].mima;
                    }
                    if (xx == 3)
                    {
                        cout << zidian3[ks].mima;
                        outf << zidian3[ks].mima;
                    }
                    if (xx == 4)
                    {
                        cout << zidian4[ks].mima;
                        outf << zidian4[ks].mima;
                    }
                }

                xx = 1 + rand() % (4);
                if (xx == 1)
                {
                    cout << zidian1[panduan].mima;
                    outf << zidian1[panduan].mima;
                }
                if (xx == 2)
                {
                    cout << zidian2[panduan].mima;
                    outf << zidian2[panduan].mima;
                }
                if (xx == 3)
                {
                    cout << zidian3[panduan].mima;
                    outf << zidian3[panduan].mima;
                }
                if (xx == 4)
                {
                    cout << zidian4[panduan].mima;
                    outf << zidian4[panduan].mima;
                }

            }
            else if (n1 == 0)
            {


                xx = 1 + rand() % (4);
                if (xx == 1)
                {
                    cout << zidian1[panduan].mima;
                    outf << zidian1[panduan].mima;
                }
                if (xx == 2)
                {
                    cout << zidian2[panduan].mima;
                    outf << zidian2[panduan].mima;
                }
                if (xx == 3)
                {
                    cout << zidian3[panduan].mima;
                    outf << zidian3[panduan].mima;
                }
                if (xx == 4)
                {
                    cout << zidian4[panduan].mima;
                    outf << zidian4[panduan].mima;
                }
                string str1 = str.substr(1, str.size() - 1);
                for (int i = 0; i < hid; i++)
                {
                    if (daxiezhuanxiaoxie(str1) == daxiezhuanxiaoxie(zidian1[i].word))
                    {
                        xx = 1 + rand() % (4);
                        if (xx == 1)
                        {
                            cout << zidian1[i].mima;
                            outf << zidian1[i].mima;
                        }
                        if (xx == 2)
                        {
                            cout << zidian2[i].mima;
                            outf << zidian2[i].mima;
                        }
                        if (xx == 3)
                        {
                            cout << zidian3[i].mima;
                            outf << zidian3[i].mima;
                        }
                        if (xx == 4)
                        {
                            cout << zidian4[i].mima;
                            outf << zidian4[i].mima;
                        }
                        jj = 2;
                        break;
                    }

                }
                if (jj == 1)
                {
                    int ks=0; cd = 0;
                    for (int i = 0; i < hid; i++)
                    {
                        int d = LCSbianzhong(daxiezhuanxiaoxie(str), daxiezhuanxiaoxie(zidian1[i].word));
                        if (cd < d)
                            cd = d, ks = i;

                    }
                    xx = 1 + rand() % (4);
                    if (xx == 1)
                    {
                        cout << zidian1[ks].mima;
                        outf << zidian1[ks].mima;
                    }
                    if (xx == 2)
                    {
                        cout << zidian2[ks].mima;
                        outf << zidian2[ks].mima;
                    }
                    if (xx == 3)
                    {
                        cout << zidian3[ks].mima;
                        outf << zidian3[ks].mima;
                    }
                    if (xx == 4)
                    {
                        cout << zidian4[ks].mima;
                        outf << zidian4[ks].mima;
                    }
                }


            }
            else
            {
                string str1 = str.substr(0, n1);
                for (int i = 0; i < hid; i++)
                {
                    if (daxiezhuanxiaoxie(str1) == daxiezhuanxiaoxie(zidian1[i].word))
                    {
                        xx = 1 + rand() % (4);
                        if (xx == 1)
                        {
                            cout << zidian1[i].mima;
                            outf << zidian1[i].mima;
                        }
                        if (xx == 2)
                        {
                            cout << zidian2[i].mima;
                            outf << zidian2[i].mima;
                        }
                        if (xx == 3)
                        {
                            cout << zidian3[i].mima;
                            outf << zidian3[i].mima;
                        }
                        if (xx == 4)
                        {
                            cout << zidian4[i].mima;
                            outf << zidian4[i].mima;
                        }
                        jj = 2;
                        break;
                    }

                }
                if (jj == 1)
                {
                    int ks=0; cd = 0;
                    for (int i = 0; i < hid; i++)
                    {
                        int d = LCSbianzhong(daxiezhuanxiaoxie(str1), daxiezhuanxiaoxie(zidian1[i].word));
                        if (cd < d)
                            cd = d, ks = i;

                    }
                    xx = 1 + rand() % (4);
                    if (xx == 1)
                    {
                        cout << zidian1[ks].mima;
                        outf << zidian1[ks].mima;
                    }
                    if (xx == 2)
                    {
                        cout << zidian2[ks].mima;
                        outf << zidian2[ks].mima;
                    }
                    if (xx == 3)
                    {
                        cout << zidian3[ks].mima;
                        outf << zidian3[ks].mima;
                    }
                    if (xx == 4)
                    {
                        cout << zidian4[ks].mima;
                        outf << zidian4[ks].mima;
                    }
                }


                xx = 1 + rand() % (4);
                if (xx == 1)
                {
                    cout << zidian1[panduan].mima;
                    outf << zidian1[panduan].mima;
                }
                if (xx == 2)
                {
                    cout << zidian2[panduan].mima;
                    outf << zidian2[panduan].mima;
                }
                if (xx == 3)
                {
                    cout << zidian3[panduan].mima;
                    outf << zidian3[panduan].mima;
                }
                if (xx == 4)
                {
                    cout << zidian4[panduan].mima;
                    outf << zidian4[panduan].mima;
                }
                string str2 = str.substr(n1 + 1, str.size() - 1 - n1);
                for (int i = 0; i < hid; i++)
                {
                    if (daxiezhuanxiaoxie(str2) == daxiezhuanxiaoxie(zidian1[i].word))
                    {
                        xx = 1 + rand() % (4);
                        if (xx == 1)
                        {
                            cout << zidian1[i].mima;
                            outf << zidian1[i].mima;
                        }
                        if (xx == 2)
                        {
                            cout << zidian2[i].mima;
                            outf << zidian2[i].mima;
                        }
                        if (xx == 3)
                        {
                            cout << zidian3[i].mima;
                            outf << zidian3[i].mima;
                        }
                        if (xx == 4)
                        {
                            cout << zidian4[i].mima;
                            outf << zidian4[i].mima;
                        }
                        jj = 2;
                        break;
                    }

                }
                if (jj == 1)
                {
                    int ks=0; cd = 0;
                    for (int i = 0; i < hid; i++)
                    {
                        int d1 = LCSbianzhong(daxiezhuanxiaoxie(str2), daxiezhuanxiaoxie(zidian1[i].word));
                        if (cd < d1)
                            cd = d1, ks = i;

                    }
                    xx = 1 + rand() % (4);
                    if (xx == 1)
                    {
                        cout << zidian1[ks].mima;
                        outf << zidian1[ks].mima;
                    }
                    if (xx == 2)
                    {
                        cout << zidian2[ks].mima;
                        outf << zidian2[ks].mima;
                    }
                    if (xx == 3)
                    {
                        cout << zidian3[ks].mima;
                        outf << zidian3[ks].mima;
                    }
                    if (xx == 4)
                    {
                        cout << zidian4[ks].mima;
                        outf << zidian4[ks].mima;
                    }
                }

            }
        }
    }
    cout << endl << "加密结果已自动生成文件jiamijieguo.txt,在该程序的文件夹中自行查找" << endl;
    inf.close();
    outf.close();
}
void jieyiwenjian(zidian* zidian1)//从哈夫曼树树顶搜索往下的搜索方法
{
    string filename;
    cin >> filename;
    danzhuanshuang(filename);

    fstream inf1(filename);
    string str1;
    if (!inf1)
    {
        cout << "文件名输入错误或输入的不是文件名";
        return;
    }
    cout << "解密结果如下" << endl;
    char ch;
    int k = 0; int j = hid * 2 - 1 - 1;
    int ks; int js = 2;
    while (inf1.get(ch))//从哈夫曼树的顶部开始往下搜索
    {
        if (ch != '1' && ch != '0')//判断是否输入的是加密文件
        {
            cout << "该文件不是加密文件，请重新选择" << endl;
            return;
        }
        ks = 1;
        while (ks)//从上往下遍历树
        {
            if (ch == '0')//0则为左孩子
            {
                j = zidian1[j].lchild;
            }
            if (ch == '1')//1则为右孩子
            {
                j = zidian1[j].rchild;
            }
            if (zidian1[j].lchild == 0 && zidian1[j].rchild == 0)
            {//孩子节点为空则找到该单词，否则继续寻找
                if (js == 2)
                {
                    cout << shouzimuzhuanhuan(zidian1[j].word) << " ";
                }
                else cout << zidian1[j].word << " ";
                if (j == 3458 || j == 3459)
                    js = 2;
                else js = 1;
                ks = 0; j = hid * 2 - 1 - 1;
            }
            else
                inf1.get(ch);

        }




    }
    inf1.close();
}
void jieyiwenjian2(zidian* zidian1, zidian* zidian2, zidian* zidian3, zidian* zidian4)
//从哈夫曼树树顶搜索往下的搜索方法，同样与jieyiwejian类似，但是区别在于在识别之前要先识别前两位找出
//字典是哪一本，所以多设计一个判断即可，其余部分不多做注释
{
    string filename;
    cin >> filename;
    danzhuanshuang(filename);
    fstream inf1(filename);
    string str1;

    if (!inf1)
    {
        cout << "文件名输入错误或输入的不是文件名";
        return;
    }
    cout << "解密结果如下" << endl;
    char ch;
    int k = 0; int j = hid * 2 - 1 - 1;
    int ks; int js = 2;
    char s1, s2;

    while (inf1.get(ch)) {
        if (ch != '1' && ch != '0')
        {
            cout << "该文件不是加密文件，请重新选择" << endl;
            return;
        }
        if (ch == '0') {//此判断用于判断第1位字符
            inf1.get(ch);
            if (ch == '0') {
                // 此判断用于判断前第2位字符
                ks = 1;
                inf1.get(ch);
                while (ks)
                {
                    if (ch == '0')
                    {
                        j = zidian1[j].lchild;
                    }
                    if (ch == '1')
                    {
                        j = zidian1[j].rchild;
                    }
                    if (zidian1[j].lchild == 0 && zidian1[j].rchild == 0)
                    {
                        if (js == 2)
                        {
                            cout << shouzimuzhuanhuan(zidian1[j].word) << " ";
                        }
                        else cout << zidian1[j].word << " ";
                        if (j == 3458 || j == 3459)
                            js = 2;
                        else js = 1;
                        ks = 0; j = hid * 2 - 1 - 1;
                    }
                    else
                        inf1.get(ch);

                }
                continue;
            }
            if (ch == '1') {//此判断用于判断第2位字符
                ks = 1;
                inf1.get(ch);
                while (ks)
                {
                    if (ch == '0')
                    {
                        j = zidian2[j].lchild;
                    }
                    if (ch == '1')
                    {
                        j = zidian2[j].rchild;
                    }
                    if (zidian2[j].lchild == 0 && zidian2[j].rchild == 0)
                    {
                        if (js == 2)
                        {
                            cout << shouzimuzhuanhuan(zidian2[j].word) << " ";
                        }
                        else cout << zidian2[j].word << " ";
                        if (j == 3458 || j == 3459)
                            js = 2;
                        else js = 1;
                        ks = 0; j = hid * 2 - 1 - 1;
                    }
                    else
                        inf1.get(ch);

                }
                continue;
            }
        }

        if (ch == '1') {//此判断用于判断第1位字符
            inf1.get(ch);
            if (ch == '0') {//此判断用于判断第2位字符
                ks = 1;
                inf1.get(ch);
                while (ks)
                {
                    if (ch == '0')
                    {
                        j = zidian3[j].lchild;
                    }
                    if (ch == '1')
                    {
                        j = zidian3[j].rchild;
                    }
                    if (zidian3[j].lchild == 0 && zidian3[j].rchild == 0)
                    {
                        if (js == 2)
                        {
                            cout << shouzimuzhuanhuan(zidian3[j].word) << " ";
                        }
                        else cout << zidian3[j].word << " ";
                        if (j == 3458 || j == 3459)
                            js = 2;
                        else js = 1;
                        ks = 0; j = hid * 2 - 1 - 1;
                    }
                    else
                        inf1.get(ch);

                }
                continue;
            }
            if (ch == '1') {//此判断用于判断第2位字符
                ks = 1;
                inf1.get(ch);
                while (ks)
                {
                    if (ch == '0')
                    {
                        j = zidian4[j].lchild;
                    }
                    if (ch == '1')
                    {
                        j = zidian4[j].rchild;
                    }
                    if (zidian4[j].lchild == 0 && zidian4[j].rchild == 0)
                    {
                        if (js == 2)
                        {
                            cout << shouzimuzhuanhuan(zidian4[j].word) << " ";
                        }
                        else cout << zidian4[j].word << " ";
                        if (j == 3458 || j == 3459)
                            js = 2;
                        else js = 1;
                        ks = 0; j = hid * 2 - 1 - 1;
                    }
                    else
                        inf1.get(ch);

                }
                continue;
            }


        }


    }
    inf1.close();
}
void jiemian1()
{//界面1界面设计，即基础功能界面
    zidian* zidian1 = new zidian[3461 * 2 - 1];
    for (int i = 0; i < (hid * 2 - 1); i++) {
        zidian1[i].parent = 0;
        zidian1[i].lchild = 0;
        zidian1[i].rchild = 0;
    }//设置并导入字典
    daoruzidian(zidian1, "zidian.txt");

    gouzaohafuman(zidian1);
    dedaobianma(zidian1);//构造哈夫曼树
    while (1)
    {
        cout << "   -------------------------------------------------------" << endl << endl << endl;
        cout << "                     单字典加密" << endl;
        cout << "                   输入1：加密程序" << endl;
        cout << "                   输入2：解密程序" << endl;
        cout << "                   输入3：返回" << endl;
        cout << "   -------------------------------------------------------" << endl;
        char sd;
        cin >> sd;

        switch (sd)
        {
        case '1':
            cout << "加密程序开始，请输入需要加密的文件名" << endl;

            fanyiwenjian(zidian1);//翻译文件
            cout << endl;

            break;
        case '2':

            cout << "解密程序开始，请输入需要加密的文件名" << endl;

            jieyiwenjian(zidian1);//解译文件
            cout << endl;

            break;

        case '3':
            return;
        default: cout << "请输入1，2，3" << endl;//退出返回主界面
        }

    }

}
void jiemian2()
{//提高功能界面
    zidian* zidian11 = new zidian[3461 * 2 - 1];
    zidian* zidian12 = new zidian[3461 * 2 - 1];
    zidian* zidian13 = new zidian[3461 * 2 - 1];
    zidian* zidian14 = new zidian[3461 * 2 - 1];
    for (int i = 0; i < (hid * 2 - 1); i++) {
        zidian11[i].parent = 0;
        zidian11[i].lchild = 0;
        zidian11[i].rchild = 0;
        zidian12[i].parent = 0;
        zidian12[i].lchild = 0;
        zidian12[i].rchild = 0;
        zidian13[i].parent = 0;
        zidian13[i].lchild = 0;
        zidian13[i].rchild = 0;
        zidian14[i].parent = 0;
        zidian14[i].lchild = 0;
        zidian14[i].rchild = 0;
    }
    //设置并导入私奔需要用到的字典
    daoruzidian(zidian11, "zidian1.txt");
    daoruzidian(zidian12, "zidian2.txt");
    daoruzidian(zidian13, "zidian3.txt");
    daoruzidian(zidian14, "zidian4.txt");

    gouzaohafuman(zidian11);
    gouzaohafuman(zidian12);
    gouzaohafuman(zidian13);
    gouzaohafuman(zidian14);
    dedaobianma2(zidian11, 1);
    dedaobianma2(zidian12, 2);
    dedaobianma2(zidian13, 3);
    dedaobianma2(zidian14, 4);//构造哈夫曼树


    while (1)
    {
        cout << "   -------------------------------------------------------" << endl << endl << endl;
        cout << "                 多字典多重加密（提高内容）" << endl;
        cout << "                   输入1：加密程序" << endl;
        cout << "                   输入2：解密程序" << endl;
        cout << "                   输入3：返回" << endl;
        cout << "   -------------------------------------------------------" << endl;
        char sd;
        cin >> sd;

        switch (sd)
        {
        case '1':
            cout << "加密程序开始，请输入需要加密的文件名" << endl;

            fanyiwenjian2(zidian11, zidian12, zidian13, zidian14);
            cout << endl;//翻译文件

            break;
        case '2':

            cout << "解密程序开始，请输入需要加密的文件名" << endl;

            jieyiwenjian2(zidian11, zidian12, zidian13, zidian14);
            cout << endl;//解译文件

            break;

        case '3':
            return;
        default: cout << "请输入1，2，3" << endl;//推出返回主界面
        }

    }


}
void grah()
{
    initgraph(800, 700);
    loadimage(NULL, L"121.jpg");
    IMAGE img_bk;
    loadimage(&img_bk, L"122.jpg");
    putimage(80, 60, 295, 100, &img_bk, 10, 10);
    loadimage(&img_bk, L"123.jpg");
    putimage(80, 180, 295, 100, &img_bk, 10, 10);
    loadimage(&img_bk, L"124.jpg");
    putimage(80, 300, 295, 100, &img_bk, 5, 5);
    MOUSEMSG mnm;
    //主界面生成
    HWND hwnd = GetHWnd();
    while (1)
    {

        mnm = GetMouseMsg();//识别鼠标信息
        if (mnm.uMsg == WM_LBUTTONDOWN)
        {
            if (mnm.x <= 380 && mnm.x >= 80 && mnm.y <= 160 && mnm.y >= 60)
            {
                closegraph();
                jiemian1();
                closegraph();
                grah();//按钮1：进入基础部分
            }
            if (mnm.x <= 380 && mnm.x >= 80 && mnm.y <= 280 && mnm.y >= 180)
            {
                closegraph();
                jiemian2();
                grah();//按钮2：进入提高部分

            }
            if (mnm.x <= 380 && mnm.x >= 80 && mnm.y <= 400 && mnm.y >= 300)
            {
                zidian* zidianchushihua = new zidian[3500];
                zidian* zidianchushihua1 = new zidian[3500];
                zidian* zidianchushihua2 = new zidian[3500];
                zidian* zidianchushihua3 = new zidian[3500];
                zidian* zidianchushihua4 = new zidian[3500];
                quanzhisuijishu(zidianchushihua);
                quanzhisuijishu(zidianchushihua1);
                quanzhisuijishu(zidianchushihua2);
                quanzhisuijishu(zidianchushihua3);
                quanzhisuijishu(zidianchushihua4);
                zidiangoujian(zidianchushihua, "zidian.txt");
                zidiangoujian(zidianchushihua1, "zidian1.txt");
                zidiangoujian(zidianchushihua2, "zidian2.txt");
                zidiangoujian(zidianchushihua3, "zidian3.txt");
                zidiangoujian(zidianchushihua4, "zidian4.txt");
                MessageBox(hwnd, L"构建/重建成功", L"提示", MB_OK);//按钮3：重新构造字典
            }
        }
    }
}
void main()
{
    srand((unsigned int)time(NULL));
    grah();//调用页面函数即可

    return;

}
