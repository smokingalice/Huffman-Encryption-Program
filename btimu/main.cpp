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
int xx;//������������ֵ����ã�������ͷ����Ϊ�˼����ض���
const int hid = 3461;//һ��3461�����ʣ��������ž���ʺ��������ĸ����ţ�
typedef struct zidian
{
    string word;//����
    int count;//Ȩֵ�������ʽ��
    int parent;
    int lchild;
    int rchild;
    char* mima;//������루��̬���䣬�Ͼ���֪�����뵽�׶೤��̣�
}zidian;

string daxiezhuanxiaoxie(string& s) {
    int len = s.size();
    string s1 = s;
    for (int i = 0; i < len; i++) {
        if (s1[i] >= 'A' && s1[i] <= 'Z') {
            s1[i] += 32;//+32ת��ΪСд          
        }
    }
    return s1;
}
string shouzimuzhuanhuan(string& s) {//����ĸת��Ϊ��д
    if (s[0] >= 'a' && s[0] <= 'z') {
        s[0] -= 32;//-32ת��Ϊ��д          
    }
    return s;
}
int douhaojuhaopanduan(string& s, int* n) {//�����ж϶��ž�����ַ������ĸ�λ�ã�������λ����Ϣ
    int len = s.size();
    string s1 = s;
    string s2;
    if (s == "," || s == "." || s == "?" || s == "'")
        return 1;
    if (s1[len - 1] == ',') {//��ĩβ
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
    if (s1[0] == ',') {//��ͷ��
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
        if (s1[i] == ',') {//���м�ĳ��λ�ã�����I'M
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

int LCSbianzhong(string X, string Y) {//��������������������У���hing��heingr�������������Ϊing�������䳤�Ⱦ��У���ʱ����3���ö�̬�滮������

    int c[40][40] = { 0 };//�����������
    int maxlen = 0;
    int maxindex = 0;
    for (int i = 1; i <= X.size(); i++) {
        for (int j = 1; j <= Y.size(); j++) {
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;//��̬�滮������ά����洢��
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
void danzhuanshuang(string& s) {//��б��תΪ˫б�ܣ������ļ�ֱ�Ӹ��������ȡ
    string::size_type pos = 0;
    while ((pos = s.find('\\', pos)) != string::npos) {
        s.insert(pos, "\\");
        pos = pos + 2;
    }
}

int feizifuweizhi(string& s) {//�ж��ַ������ַ�λ�ã���Ҫ���ڵ����ֵ�ʹ��
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
    string filename = "word.txt";//�������ҵ��ĵ��ʱ��뵥�ʵ��ֵ�
    fstream inf(filename);
    string str;
    if (!inf)
    {
        cout << "open error";
        return;
    }
    int i = 0;
    getline(inf, str);
    zidian[i].word = str.substr(0, feizifuweizhi(str));//��ȥ���ֵ��ַ�
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
}//���ڴ�����������صĵ��ʣ�������������Ҫ�ĵ�����

void quanzhisuijishu(zidian* zidian)//���ڲ������ظ��������
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
        zidian[i].count = suijishuzu[x];     //��ÿһ�λ�õ������������һ��������
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
{//�����ɵ��ֵ䵼�뵽zidian.txt,����չʾ�ۿ��Լ�Ӧ��

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

void quanzhixiaozhe(zidian* zdt, int end, int* s1, int* s2) //�ҳ�ʣ�µĽڵ���С�Ľڵ�
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
    //�����µĽ����б���
    for (int j = i + 1; j <= end; j++) {
        if (zdt[j].parent != 0) continue;
        if (zdt[j].count < min1) {
            min2 = min1;
            min1 = zdt[j].count;
            *s2 = *s1;
            *s1 = j;
        }
        //��� min1<=zdt[i].count<=min2,�� ��zdt[j].count��ֵ����min2
        else if (zdt[j].count >= min1 && zdt[j].count < min2) {
            min2 = zdt[j].count;
            *s2 = j;
        }

    }
}
void gouzaohafuman(zidian* zdt)
{
    //�����������
    int m = 2 * hid - 1;
    for (int i = hid; i < m; i++) {
        int s1 = 0, s2 = 0;
        quanzhixiaozhe(zdt, i - 1, &s1, &s2);//�ҳ�ʣ��ڵ���ȨֵС��
        zdt[s1].parent = i; zdt[s2].parent = i;
        zdt[i].lchild = s1;//��s1��s2�ֱ���Ϊ���i�����Һ��� 
        zdt[i].rchild = s2;
        zdt[i].count = zdt[s1].count + zdt[s2].count;//���i��ȨֵΪ���Һ���֮��,�������Ĺ���
    }
}



void dedaobianma(zidian* num) {
    //�õ����������� 
    int xunhuan, c, f;

    char* cd = new char[hid];
    cd[hid - 1] = '\0';
    for (int i = 0; i < hid; i++) { //��ͷ��ʼ����   
        xunhuan = hid - 1;
        c = i; f = num[i].parent;
        while (f != 0) {
            xunhuan--;
            if (num[f].lchild == c) cd[xunhuan] = '0';
            else cd[xunhuan] = '1';//����β����������ֱ��������

            c = f; f = num[f].parent;
        }
        num[i].mima = new char[hid - xunhuan];
        strcpy_s(num[i].mima, hid - xunhuan, &cd[xunhuan]);

    }
    delete cd;
}
void dedaobianma2(zidian* num, int n) {
    //�õ����������� 
    int xunhuan, c, f;

    char* cd = new char[hid];
    cd[hid - 1] = '\0';
    for (int i = 0; i < hid; i++) {
        xunhuan = hid - 1;
        c = i; f = num[i].parent;
        while (f != 0) {
            xunhuan--;
            if (num[f].lchild == c) cd[xunhuan] = '0';
            else cd[xunhuan] = '1';//����β����������ֱ��������

            c = f; f = num[f].parent;
        }
        if (n == 1)//�������������ǰ��λ�����ڶ��ֵ����
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
//�����·���Ϊ�������룬���а������ź͵�������һ��ʱ�Ĵ���ʽ����i'm�ȣ�����֧��һ�������ַ������ж�����ţ�
//�ҷ���ֻ֧�ֶ��ţ���ţ��ʺú͵����ż� , . ? '
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
        cout << "�ļ���������������Ĳ����ļ���" << endl;
        return;
    }
    cout << "���ܽ������" << endl;
    int panduan = 0;
    int i = 0;
    inf >> str;
    int n1;
    panduan = douhaojuhaopanduan(str, &n1);//�жϱ��
    int jj = 1;
    int cd = 0;
    if (panduan == 1)//�ж��ַ��Ƿ��б��
    {

        for (int i = 0; i < hid; i++)
        {
            if (daxiezhuanxiaoxie(str) == daxiezhuanxiaoxie(zidian1[i].word))//ȫ��ת��ΪСд��Աȣ�����ͬ��
            {
                cout << zidian1[i].mima;
                outf << zidian1[i].mima;
                jj = 2;
                break;
            }

        }
        if (jj == 1)//�����ж��ܷ���ֵ����ҵ����ʣ�����ͬ��
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
        if (n1 == str.size() - 1) {//�����б������������Ϊ���֣������ǰ���ں��Լ����м�
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
    while (!inf.eof())//ѭ����ȡ�ļ����ʼ��ɣ����ݺ͵�һ�ζ�ȡʱһ��
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
    cout << endl << "���ܽ�����Զ������ļ�jiamijieguo.txt,�ڸó�����ļ��������в���" << endl;//���
    inf.close();
    outf.close();
}
void fanyiwenjian2(zidian* zidian1, zidian* zidian2, zidian* zidian3, zidian* zidian4)
//�����·���Ϊ�������룬���а������ź͵�������һ��ʱ�Ĵ���ʽ����i'm�ȣ�����֧��һ�������ַ������ж�����ţ�
//�ҷ���ֻ֧�ֶ��ţ���ţ��ʺú͵����ż� , . ? '
 //�ú���ʵ�ֶ��ֵ��ʶ�𣬱���Ϊÿ�������������һ��1��4����ֵ��Ȼ����00��01��10��11�ֱ���뵥��ǰ��λ��
 //��������ԺͲ�ȷ���ԣ�������Ŀ��
 //���ڻ���������fanyiwenjian�������ƣ����ﲻ����ע��
{
    string filename;
    cin >> filename;
    danzhuanshuang(filename);
    fstream inf(filename);
    ofstream outf("jiamiwenjian.txt");

    string str;
    if (!inf)
    {
        cout << "�ļ���������������Ĳ����ļ���" << endl;
        return;
    }
    cout << "���ܽ������" << endl;
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
                xx = 1 + rand() % (4);//���ָ���������Ĳ��֣�
                if (xx == 1)//�����������仯��ǰ��λΪ00��01��10��11�����룬����ͬ�����
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
    cout << endl << "���ܽ�����Զ������ļ�jiamijieguo.txt,�ڸó�����ļ��������в���" << endl;
    inf.close();
    outf.close();
}
void jieyiwenjian(zidian* zidian1)//�ӹ������������������µ���������
{
    string filename;
    cin >> filename;
    danzhuanshuang(filename);

    fstream inf1(filename);
    string str1;
    if (!inf1)
    {
        cout << "�ļ���������������Ĳ����ļ���";
        return;
    }
    cout << "���ܽ������" << endl;
    char ch;
    int k = 0; int j = hid * 2 - 1 - 1;
    int ks; int js = 2;
    while (inf1.get(ch))//�ӹ��������Ķ�����ʼ��������
    {
        if (ch != '1' && ch != '0')//�ж��Ƿ�������Ǽ����ļ�
        {
            cout << "���ļ����Ǽ����ļ���������ѡ��" << endl;
            return;
        }
        ks = 1;
        while (ks)//�������±�����
        {
            if (ch == '0')//0��Ϊ����
            {
                j = zidian1[j].lchild;
            }
            if (ch == '1')//1��Ϊ�Һ���
            {
                j = zidian1[j].rchild;
            }
            if (zidian1[j].lchild == 0 && zidian1[j].rchild == 0)
            {//���ӽڵ�Ϊ�����ҵ��õ��ʣ��������Ѱ��
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
//�ӹ������������������µ�����������ͬ����jieyiwejian���ƣ���������������ʶ��֮ǰҪ��ʶ��ǰ��λ�ҳ�
//�ֵ�����һ�������Զ����һ���жϼ��ɣ����ಿ�ֲ�����ע��
{
    string filename;
    cin >> filename;
    danzhuanshuang(filename);
    fstream inf1(filename);
    string str1;

    if (!inf1)
    {
        cout << "�ļ���������������Ĳ����ļ���";
        return;
    }
    cout << "���ܽ������" << endl;
    char ch;
    int k = 0; int j = hid * 2 - 1 - 1;
    int ks; int js = 2;
    char s1, s2;

    while (inf1.get(ch)) {
        if (ch != '1' && ch != '0')
        {
            cout << "���ļ����Ǽ����ļ���������ѡ��" << endl;
            return;
        }
        if (ch == '0') {//���ж������жϵ�1λ�ַ�
            inf1.get(ch);
            if (ch == '0') {
                // ���ж������ж�ǰ��2λ�ַ�
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
            if (ch == '1') {//���ж������жϵ�2λ�ַ�
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

        if (ch == '1') {//���ж������жϵ�1λ�ַ�
            inf1.get(ch);
            if (ch == '0') {//���ж������жϵ�2λ�ַ�
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
            if (ch == '1') {//���ж������жϵ�2λ�ַ�
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
{//����1������ƣ����������ܽ���
    zidian* zidian1 = new zidian[3461 * 2 - 1];
    for (int i = 0; i < (hid * 2 - 1); i++) {
        zidian1[i].parent = 0;
        zidian1[i].lchild = 0;
        zidian1[i].rchild = 0;
    }//���ò������ֵ�
    daoruzidian(zidian1, "zidian.txt");

    gouzaohafuman(zidian1);
    dedaobianma(zidian1);//�����������
    while (1)
    {
        cout << "   -------------------------------------------------------" << endl << endl << endl;
        cout << "                     ���ֵ����" << endl;
        cout << "                   ����1�����ܳ���" << endl;
        cout << "                   ����2�����ܳ���" << endl;
        cout << "                   ����3������" << endl;
        cout << "   -------------------------------------------------------" << endl;
        char sd;
        cin >> sd;

        switch (sd)
        {
        case '1':
            cout << "���ܳ���ʼ����������Ҫ���ܵ��ļ���" << endl;

            fanyiwenjian(zidian1);//�����ļ�
            cout << endl;

            break;
        case '2':

            cout << "���ܳ���ʼ����������Ҫ���ܵ��ļ���" << endl;

            jieyiwenjian(zidian1);//�����ļ�
            cout << endl;

            break;

        case '3':
            return;
        default: cout << "������1��2��3" << endl;//�˳�����������
        }

    }

}
void jiemian2()
{//��߹��ܽ���
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
    //���ò�����˽����Ҫ�õ����ֵ�
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
    dedaobianma2(zidian14, 4);//�����������


    while (1)
    {
        cout << "   -------------------------------------------------------" << endl << endl << endl;
        cout << "                 ���ֵ���ؼ��ܣ�������ݣ�" << endl;
        cout << "                   ����1�����ܳ���" << endl;
        cout << "                   ����2�����ܳ���" << endl;
        cout << "                   ����3������" << endl;
        cout << "   -------------------------------------------------------" << endl;
        char sd;
        cin >> sd;

        switch (sd)
        {
        case '1':
            cout << "���ܳ���ʼ����������Ҫ���ܵ��ļ���" << endl;

            fanyiwenjian2(zidian11, zidian12, zidian13, zidian14);
            cout << endl;//�����ļ�

            break;
        case '2':

            cout << "���ܳ���ʼ����������Ҫ���ܵ��ļ���" << endl;

            jieyiwenjian2(zidian11, zidian12, zidian13, zidian14);
            cout << endl;//�����ļ�

            break;

        case '3':
            return;
        default: cout << "������1��2��3" << endl;//�Ƴ�����������
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
    //����������
    HWND hwnd = GetHWnd();
    while (1)
    {

        mnm = GetMouseMsg();//ʶ�������Ϣ
        if (mnm.uMsg == WM_LBUTTONDOWN)
        {
            if (mnm.x <= 380 && mnm.x >= 80 && mnm.y <= 160 && mnm.y >= 60)
            {
                closegraph();
                jiemian1();
                closegraph();
                grah();//��ť1�������������
            }
            if (mnm.x <= 380 && mnm.x >= 80 && mnm.y <= 280 && mnm.y >= 180)
            {
                closegraph();
                jiemian2();
                grah();//��ť2��������߲���

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
                MessageBox(hwnd, L"����/�ؽ��ɹ�", L"��ʾ", MB_OK);//��ť3�����¹����ֵ�
            }
        }
    }
}
void main()
{
    srand((unsigned int)time(NULL));
    grah();//����ҳ�溯������

    return;

}
