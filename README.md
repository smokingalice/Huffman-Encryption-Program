# 基于哈夫曼算法的加解密系统
## 一、课题内容和要求
### 题目内容及要求：
（一）课题内容 
哈夫曼算法不仅可以用于数据压缩编解码，同样也可以用于实现简单的加解密功能。设明文由若干英文单词构成，试利用哈夫曼算法实现如下功能要求：
（二）课题要求 
(1) 构建单词字典库（可以下载一些文档，并进行字符串处理，提取其中单词，从而构建字典库）。然后为每个单词配置一个随机数作为权重，利用哈夫曼算法为各单词生成对应的密文，从而构造密码字典；
(2)利用密码字典实现对输入文件的加解密；
(3)界面友好、直观；
(4)按照基本要求实现的加解密系统无法抵抗基于单词频度分析的攻击，试设计能够抵御频度分析攻击的基于哈夫曼算法的加解密方法（提示：可以采用多密码字典混合加解密的方法，加密时随机选择某一个密码字典）；
(5) 当密码字典规模较大时，加解密的性能必然受到影响，试设计好的算法提高加解密的效率。
功能框架图：
# ![image](https://github.com/smokingalice/btimu/assets/112455320/0babab74-735d-4630-a045-e8cce696cc9f)


自我要求：
（1）实现所有要求功能，同时满足提高功能。
（2）尽量降低时间复杂度，对于提高要求尽量选择更为非常规的方法。
（3）代码美观且清晰。

## 二、数据结构说明
```cpp
typedef struct zidian
{
    string word;//单词
    int count;//权值（随机方式）
    int parent;
    int lchild;
    int rchild;
    char* mima;//存放密码（动态分配，毕竟不知道密码到底多长多短）
}zidian;
``` 

该程序我设计了一个结构体，即字典结构体，用于字典的生成和字典的使用。首先是word字符串，用来存储单词，即单词本体。Count用来保存随机数，即随机生成的指定代码。Parent，lchild和rchild则是用来保存其父亲节点和孩子节点，这里我都选用int型，因为字典存储使用数组存储，而用int型存储他们的数组编号，即可连接上父节点和孩子节点。mima则是用于存储对应的哈夫曼编码，而我选择用动态分配的方式，在生成编码时再给予其长度。

## 三、算法设计
1 最长连续公共子序列算法 
该算法主要用于计算与该单词最接近的字典单词是哪一个，应用于字典无法包含所有单词的情况，如部分变形式。该算法采用动态规划的思想，由双循环进入程序，用二维数组表的形式记录最长公共连续子序列的长度后输出，流程图如下：

# ![image](https://github.com/smokingalice/btimu/assets/112455320/b4b14935-943a-4495-85de-977b796288b5)

2 随机数生成算法 
  为了满足字典是随机生成的，我选择用另类的随机数生成法，目的是节约时间复杂度的同时，做到随机数不会重复。由于单词较多，随即次数增多，所以很有可能重复，于是我选用这种使随机数的生成不重复的方法，产生随机数。
  具体方法是，由一个数据与标号相同的顺序数组来寻找随机数，当随机生成一个随机数后，去数组中下标为该数的数据，然后从数组中抹除该数据变成新的数组，然后继续随机处一个下标，打到重复数据随时删除的目的，同时时间复杂度不变，流程图如下：

# ![image](https://github.com/smokingalice/btimu/assets/112455320/d5f42563-69e6-4e4f-a790-1848ba9346c9)

3 哈夫曼树构建与编码获取算法
  该部分分为两个，分别是哈夫曼树的构建以及编码的获取，首先来看哈夫曼树的构建。
哈夫曼树构建我选择用数组进行，一方面贴合我的结构体用int定义的父节点和子节点，一方面减少时间复杂度。首先我们需要一个求最小值函数，即求出该权值数组中权值最小的两个节点，然后合成一个节点加入到数组尾部，以此类推直到生成最后一个根节点。最小两者求解便是采用循环遍历对比法，for循环处理。而第二个部分则是编码的获取，编码获取有基础部分和提高部分，基础部分则是只用到一个字典，即编码获取采用从下至上分别搜索其父亲节点，直到找到根节点后停止，如果自己是父节点的左孩子，则记录为0，右孩子则记录为1。提高部分比基础部分更多的环节是分配字典，使用添加两位的方式分配一个字典，并给密码前两位变成字典编号，如00，01等，用于多字典识别功能。
两个算法的流程图如下：
# ![image](https://github.com/smokingalice/btimu/assets/112455320/dcb8ad2a-5fcd-4b0a-be22-356005ee82b0)


4 翻译与解译算法：
翻译算法的目的为根据文章中的单词找出其密码，这里我选择的是单循环的形式，即遍历字典，寻找与该单词相近的单词，但注意，其中会出现标点符号识别问题，所以我加入了标点符号识别判断的函数，用于辨别标点符号与单词重合的情况。提高部分则是采用随机数赋予字典的形式，随即赋予其字典代号，其于类似于基础。这部分相对简介，即for循环完成，程序框图省略。
解译算法则是以该密码从头开始，从树的根结点开始，从上往下搜锁，直到找不到子节点为止，而多字典的翻译则需要添加一个识别头两位并找出是哪一个字典的功能，程序框图如下：
# ![image](https://github.com/smokingalice/btimu/assets/112455320/15253932-2c53-4797-a356-ba63cf438260)


## 四、详细设计 
核心算法实现的源程序（函数实现形式），源程序要按照写程序的规则来编写。要结构清晰，重点函数的重点变量，重点功能部分要加上清晰的程序注释。
由于代码过多，只挑选重要算法用于展示，大小写转换，空格标点处理等细节算法不展示。
1 随机数生成算法
```cpp
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
```
2 最长公共连续子序列算法：
```cpp
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
```
3哈夫曼树的构建算法：
```cpp
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
```
4加密算法：代码过长，选取核心部分。
```cpp
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
                int ks; cd = 0;
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
     }
```
5解密算法：
```cpp
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
```
6多字典加密解密算法：基础部分与上类似，这里只展示增加部分：
```cpp
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
```
7主界面部分（界面设计细节部分过多这里不展示，详情请参阅源代码）：
```cpp
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
```
五、测试数据及其结果分析
文章翻译的加密与解密选用两篇，用于单字典加密解密，同时进行多字典加密解密测试。 程序主界面如下

# ![image](https://github.com/smokingalice/btimu/assets/112455320/2318d921-f48d-4412-9461-c396e6d70672)

（1）第一篇文章，原文如下：
When students come into the period of high school, it means they are starting to become mature, and they have to the consciousness of being independent, at the same time, most parents haven’t realized that their kids have grown up, but they still treat them like small babies. Then the parents’ overprotection and the children’s desire to be independent conflict, so the students become rebels, in the hope that their parents would realize they are no more their babies. Everyone will come to adolescence, most students choose to go against what their parents tell them to do, announcing that they won’t be manipulated by anyone, they live for themselves. Less students choose to talk to their parents directly. This is how the generation gap comes, parents should realize their babies will grow up sooner
or later, learning to let go gradually. The children should talk to their parents calmly.
单字典加密结果：
# ![image](https://github.com/smokingalice/btimu/assets/112455320/44f1378e-dcf7-48e2-a1ee-e5cd8067367e)

多字典加密如下：
# ![image](https://github.com/smokingalice/btimu/assets/112455320/0420f181-e5c0-44c6-83b4-d539103231cf)


可以看出，多字典加密比单子点加密明显多出很多，这便是加入了字典识别符的原因，所以多字典加密密码变长。
解密结果如下：
# ![image](https://github.com/smokingalice/btimu/assets/112455320/296ca4af-f432-417f-9b5a-100d876abea1)


我们可以看出，翻译结果中大小写符合规则，且单词拼写无误，符号正确，而部分文章中单词的变形式能够完整输出其原单词，文章解密完全正确，程序执行成功。

（2）第二篇文章，原文如下：
Some of us are having problems with our parents , as they often look into our school bags or read our diaries . I fully understand why we are not comfortable about it , but there’s no need to feel too sad. Our parents are checking our bags or diaries to make sure we are not getting into any trouble . They have probably heard some horrible stories about other kids and thought we might do the same . Or perhaps they just want to connect with us but are doing it all wrong . My suggestion is Tell them we want them to trust us as much as we’d like to trust them .If you don’t think you can talk to them , write them a letter and leave it lying around they are bound to read it .
单字典加密结果：
# ![image](https://github.com/smokingalice/btimu/assets/112455320/320a2970-8dee-4dba-b5b2-1e0c1c53fed5)

多字典加密如下：
# ![image](https://github.com/smokingalice/btimu/assets/112455320/f5239cb1-ff2c-474b-adb7-5f7e085ae756)

可以看出，多字典加密比单子点加密明显多出很多，这便是加入了字典识别符的原因，所以多字典加密密码变长。
解码结果如下：
# ![image](https://github.com/smokingalice/btimu/assets/112455320/0ee282c4-3ab7-4740-9cf0-777a21e70370)

图24 文章二单解码结果图
（3）代码健壮性检验
测试加密文件密码确实部分的情况，看是否会程序崩溃，测试如下，虽然解码错误，但是没有出先程序bug，健壮性验证成功。

# ![image](https://github.com/smokingalice/btimu/assets/112455320/1a8e69bc-8638-4cd3-8ee8-39887ae85ec0)

### 至此，测试完成，加密解谜功能皆能正常运行且解密无误，程序健壮性测试也成功。

