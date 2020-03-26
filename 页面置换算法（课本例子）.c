#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BLOCK_SIZE 3
#define PAGE_SIZE 8
#define PAGE_NUM 20
int page[PAGE_NUM]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
int block[BLOCK_SIZE]={-1,-1,-1};
int t;//记录当前查找页面地址

void initialize(){//初始化物理块内容，全部置为空
    t=0;
    for(int i=0;i<BLOCK_SIZE;i++) block[i]=-1;
}

int scan_page_position(int a){//搜索当前页面之后，页面a在序列中最早出现的位置
    for(int i=t+1;i<PAGE_NUM;i++){
        if(page[i]==a) return i;
    }
    return 99;
}

int scan_page_preposition(int a){//搜索当前页面之前，页面a在序列中最后出现的位置
    for(int i=t-1;i>=0;i--){
        if(page[i]==a) return i;
    }
    return -99;
}

int scan_block_position(int a){//搜索页面a是否在物理块中,并返回位置
    for(int i=0;i<BLOCK_SIZE;i++){
        if(block[i]==a) return i;
    }
    return -1;
}

int max(int a[]){//返回数组a中最大元素的地址
    int temp=0;
    for(int i=1;i<BLOCK_SIZE;i++){
        if(a[i]>a[temp]) temp=i;
    }
    return temp;
}

int min(int a[]){//返回数组a中最小元素的地址
    int temp=0;
    for(int i=1;i<BLOCK_SIZE;i++){
        if(a[i]<a[temp]) temp=i;
    }
    return temp;
}

void OPT(){
    initialize();
    printf("--------------------------OPT--------------------------\n");
    int count=0;//缺页计数器
    while(t<PAGE_NUM){
        if(scan_block_position(page[t])!=-1){
            printf("页面%d在物理块中,当前物理块为",page[t]);//在物理块中找到页面，无需置换
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            }
        else{
            if(scan_block_position(-1)!=-1){//如果物理块中有空块，那么直接装入页面
                    block[scan_block_position(-1)]=page[t];
                    count++;
                    printf("装入页面%d,当前物理块为",page[t]);
                    for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                    printf("\n");
            }
        else{
            int position[BLOCK_SIZE];//置换算法，寻找最久未使用的页面，将其置换
            for(int i=0;i<BLOCK_SIZE;i++) position[i]=scan_page_position(block[i]);
            int temp=max(position);

            printf("页面%d不在物理块中，将%d换出,",page[t],block[temp]);
            block[temp]=page[t];
            printf("当前物理块为");
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            count++;
        }
        }
        t++;
    }
    printf("缺页率为%.0f%%",(float)count/PAGE_NUM*100);
}

void FIFO(){
    initialize();
    printf("\n--------------------------FIFO--------------------------\n");
    int temp=0;//数组代替队列，顺序置换
    int count=0;//缺页计数器
    while(t<PAGE_NUM){
            if(scan_block_position(page[t])!=-1){
            printf("页面%d在物理块中,当前物理块为",page[t]);//在物理块中找到页面，无需置换
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            }
            else{if(block[temp%BLOCK_SIZE]==-1){
                block[temp%BLOCK_SIZE]=page[t];
                count++;
                temp++;
                printf("装入页面%d,当前物理块为",page[t]);//如果物理块中有空块，那么直接装入页面
                for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                printf("\n");
            }
            else{
            printf("页面%d不在物理块中，将%d换出,",page[t],block[temp%BLOCK_SIZE]);//置换页面，将最早装入的页面置换
            block[temp%BLOCK_SIZE]=page[t];
            temp++;
            printf("当前物理块为");
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            count++;
            }
        }
        t++;
    }
    printf("缺页率为%.0f%%",(float)count/PAGE_NUM*100);
}

void LRU(){
    initialize();
    printf("\n--------------------------LRU--------------------------\n");
    int count=0;//缺页计数器
    while(t<PAGE_NUM){
         if(scan_block_position(page[t])!=-1){
             printf("页面%d在物理块中,当前物理块为",page[t]);//在物理块中找到页面，无需置换
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            }
            else{
                    if(scan_block_position(-1)!=-1){
                        block[scan_block_position(-1)]=page[t];
                        count++;
                        printf("装入页面%d,当前物理块为",page[t]);//如果物理块中有空块，那么直接装入页面
                        for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                        printf("\n");

                    }
                    else{
            int position[BLOCK_SIZE];//置换页面，寻找最近最久未使用的页面，将其置换
            for(int i=0;i<BLOCK_SIZE;i++) position[i]=scan_page_preposition(block[i]);
            int temp=min(position);

            printf("页面%d不在物理块中，将%d换出,",page[t],block[temp]);
            block[temp]=page[t];
            printf("当前物理块为");
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            count++;
        }
    }
        t++;
    }
    printf("缺页率为%.0f%%",(float)count/PAGE_NUM*100);
}

void LFU(){
    initialize();
    printf("\n--------------------------LFU--------------------------\n");
    int count=0;//缺页计数器
    int usage[PAGE_SIZE];//最近使用次数计数器
    for(int i=0;i<PAGE_SIZE;i++) usage[i]=0;
    while(t<PAGE_NUM){
        if(scan_block_position(page[t])!=-1) {
            printf("页面%d在物理块中,当前物理块为",page[t]);//在物理块中找到页面，无需置换
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            usage[scan_block_position(page[t])]++;
        }
        else{
                if(scan_block_position(-1)!=-1){
                    block[scan_block_position(-1)]=page[t];
                    usage[page[t]]++;
                    count++;
                    printf("装入页面%d,当前物理块为",page[t]);//如果物理块中有空块，那么直接装入页面
                    for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                    printf("\n");
                }
        else{
            int num[BLOCK_SIZE];//寻找最近使用次数最少的页面，将其置换
            for(int i=0;i<BLOCK_SIZE;i++) num[i]=usage[block[i]];
            int temp=min(num);

            printf("页面%d不在物理块中，将%d换出,",page[t],block[temp]);
            block[temp]=page[t];
            usage[page[t]]++;
            printf("当前物理块为");
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            count++;
        }
    }
        t++;
    }
    printf("缺页率为%.0f%%",(float)count/PAGE_NUM*100);
}

void CLOCK(){
    initialize();
    printf("\n--------------------------CLOCK--------------------------\n");
    int temp=0;//当前指针指向的页面
    int accessed[BLOCK_SIZE];//访问位
    for(int i=0;i<BLOCK_SIZE;i++) accessed[i]=0;//初始化访问位
    int count=0;//缺页计数器
    while(t<PAGE_NUM){
            if(scan_block_position(page[t])!=-1){
            printf("页面%d在物理块中,当前物理块为",page[t]);//在物理块中找到页面，无需置换
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            accessed[scan_block_position(page[t])]=1;//访问位置1，指针不移动
            }
            else{ if(block[temp%BLOCK_SIZE]==-1){//如果物理块有空块，装入页面
                    block[temp%BLOCK_SIZE]=page[t];
                    accessed[temp%BLOCK_SIZE]=1;
                    count++;//缺页次数+1
                    temp++;//指针下移
                    printf("装入页面%d,当前物理块为",page[t]);//如果物理块中有空块，那么直接装入页面
                    for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                    printf("\n");
            }
            else{
                while(1){//指针顺序下移，寻找第一个访问位为0的页面，将其置换。扫描过程中将扫描过的页面访问位置0。
                        if(accessed[temp%BLOCK_SIZE]==0) break;
                        if(accessed[temp%BLOCK_SIZE]==1) {accessed[temp%BLOCK_SIZE]=0;temp++;}
                }
                printf("页面%d不在物理块中，将%d换出,",page[t],block[temp%BLOCK_SIZE]);
                block[temp%BLOCK_SIZE]=page[t];//置换页面
                accessed[temp%BLOCK_SIZE]=1;
                temp++;//指针下移
                printf("当前物理块为");//打印当前物理块内容
                for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                printf("\n");
                count++;
            }
            }
        t++;
    }
    printf("缺页率为%.0f%%",(float)count/PAGE_NUM*100);
}

void CLOCK_advanced(){
    initialize();
    printf("\n----------------------CLOCK_advanced----------------------\n");
    int temp=0;
    int accessed[BLOCK_SIZE];//访问位
    for(int i=0;i<BLOCK_SIZE;i++) accessed[i]=0;//初始化访问位
    int modified[BLOCK_SIZE];//修改位
    for(int i=0;i<BLOCK_SIZE;i++) modified[i]=0;//初始化修改位
    int count=0;//缺页计数器
    int flag;//标记是第几轮扫描
    while(t<PAGE_NUM){
        //为了实现修改位的模拟，在每次请求页面之前都随机将某个物理块中的修改位置1
            int random_Num=rand()%3;
            if(block[random_Num]!=-1) modified[random_Num]=1;//如果随机出的物理块号中内容不为空，将其修改位置1
            //模拟系统修改结束
            flag=1;//从第一轮扫描开始
            if(scan_block_position(page[t])!=-1){
            printf("页面%d在物理块中,当前物理块为",page[t]);//在物理块中找到页面，无需置换
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            accessed[scan_block_position(page[t])]=1;
            }
            else{ if(block[temp%BLOCK_SIZE]==-1){//如果有空闲的物理块，装入页面
                    block[temp%BLOCK_SIZE]=page[t];
                    accessed[temp%BLOCK_SIZE]=1;
                    count++;
                    temp++;
                    printf("装入页面%d,当前物理块为",page[t]);//如果物理块中有空块，那么直接装入页面
                    for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                    printf("\n");
            }
            else{//置换页面
                while(flag!=0){
                    if(flag==1){//第一轮扫描，找1类页面
                        for(int i=0;i<BLOCK_SIZE;i++){
                        if(accessed[temp%BLOCK_SIZE]==0&&modified[temp%BLOCK_SIZE]==0) {flag=0;break;}//如果找到1类页面，退出循环，进行替换
                        temp++;//指针下移
                        }
                        if(flag!=0)flag=2;//如果没找到，开始第二轮扫描
                        }
                    if(flag==2){//第二轮扫描，找2类页面
                        for(int i=0;i<BLOCK_SIZE;i++){
                        if(accessed[temp%BLOCK_SIZE]==0&&modified[temp%BLOCK_SIZE]==1) {flag=0;break;}//如果找到2类页面，退出循环，进行替换
                        accessed[temp%BLOCK_SIZE]=0;//第二轮扫描将经过的页面访问位置0
                        temp++;//指针下移
                        }
                        if(flag!=0)flag=1;//如果没找到，重新开始第一轮扫描
                    }

                }
                printf("页面%d不在物理块中，将%d换出,",page[t],block[temp%BLOCK_SIZE]);
                block[temp%BLOCK_SIZE]=page[t];
                accessed[temp%BLOCK_SIZE]=1;
                temp++;
                printf("当前物理块为");
                for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                printf("\n");
                count++;
            }
            }
        t++;
    }
    printf("缺页率为%.0f%%",(float)count/PAGE_NUM*100);
}

int main(){
    srand((int)time(0));//为了保证真随机数，随机生成种子
    printf("----------------------20151681310036 冯懿----------------------\n");
    printf("----------------------页面置换算法模拟----------------------\n\n");
    OPT();
    FIFO();
    LRU();
    LFU();
    CLOCK();
    CLOCK_advanced();
}
