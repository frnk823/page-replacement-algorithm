#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BLOCK_SIZE 3
#define PAGE_SIZE 8
#define PAGE_NUM 20
int page[PAGE_NUM]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
int block[BLOCK_SIZE]={-1,-1,-1};
int t;//��¼��ǰ����ҳ���ַ

void initialize(){//��ʼ����������ݣ�ȫ����Ϊ��
    t=0;
    for(int i=0;i<BLOCK_SIZE;i++) block[i]=-1;
}

int scan_page_position(int a){//������ǰҳ��֮��ҳ��a��������������ֵ�λ��
    for(int i=t+1;i<PAGE_NUM;i++){
        if(page[i]==a) return i;
    }
    return 99;
}

int scan_page_preposition(int a){//������ǰҳ��֮ǰ��ҳ��a�������������ֵ�λ��
    for(int i=t-1;i>=0;i--){
        if(page[i]==a) return i;
    }
    return -99;
}

int scan_block_position(int a){//����ҳ��a�Ƿ����������,������λ��
    for(int i=0;i<BLOCK_SIZE;i++){
        if(block[i]==a) return i;
    }
    return -1;
}

int max(int a[]){//��������a�����Ԫ�صĵ�ַ
    int temp=0;
    for(int i=1;i<BLOCK_SIZE;i++){
        if(a[i]>a[temp]) temp=i;
    }
    return temp;
}

int min(int a[]){//��������a����СԪ�صĵ�ַ
    int temp=0;
    for(int i=1;i<BLOCK_SIZE;i++){
        if(a[i]<a[temp]) temp=i;
    }
    return temp;
}

void OPT(){
    initialize();
    printf("--------------------------OPT--------------------------\n");
    int count=0;//ȱҳ������
    while(t<PAGE_NUM){
        if(scan_block_position(page[t])!=-1){
            printf("ҳ��%d���������,��ǰ�����Ϊ",page[t]);//����������ҵ�ҳ�棬�����û�
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            }
        else{
            if(scan_block_position(-1)!=-1){//�����������пտ飬��ôֱ��װ��ҳ��
                    block[scan_block_position(-1)]=page[t];
                    count++;
                    printf("װ��ҳ��%d,��ǰ�����Ϊ",page[t]);
                    for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                    printf("\n");
            }
        else{
            int position[BLOCK_SIZE];//�û��㷨��Ѱ�����δʹ�õ�ҳ�棬�����û�
            for(int i=0;i<BLOCK_SIZE;i++) position[i]=scan_page_position(block[i]);
            int temp=max(position);

            printf("ҳ��%d����������У���%d����,",page[t],block[temp]);
            block[temp]=page[t];
            printf("��ǰ�����Ϊ");
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            count++;
        }
        }
        t++;
    }
    printf("ȱҳ��Ϊ%.0f%%",(float)count/PAGE_NUM*100);
}

void FIFO(){
    initialize();
    printf("\n--------------------------FIFO--------------------------\n");
    int temp=0;//���������У�˳���û�
    int count=0;//ȱҳ������
    while(t<PAGE_NUM){
            if(scan_block_position(page[t])!=-1){
            printf("ҳ��%d���������,��ǰ�����Ϊ",page[t]);//����������ҵ�ҳ�棬�����û�
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            }
            else{if(block[temp%BLOCK_SIZE]==-1){
                block[temp%BLOCK_SIZE]=page[t];
                count++;
                temp++;
                printf("װ��ҳ��%d,��ǰ�����Ϊ",page[t]);//�����������пտ飬��ôֱ��װ��ҳ��
                for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                printf("\n");
            }
            else{
            printf("ҳ��%d����������У���%d����,",page[t],block[temp%BLOCK_SIZE]);//�û�ҳ�棬������װ���ҳ���û�
            block[temp%BLOCK_SIZE]=page[t];
            temp++;
            printf("��ǰ�����Ϊ");
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            count++;
            }
        }
        t++;
    }
    printf("ȱҳ��Ϊ%.0f%%",(float)count/PAGE_NUM*100);
}

void LRU(){
    initialize();
    printf("\n--------------------------LRU--------------------------\n");
    int count=0;//ȱҳ������
    while(t<PAGE_NUM){
         if(scan_block_position(page[t])!=-1){
             printf("ҳ��%d���������,��ǰ�����Ϊ",page[t]);//����������ҵ�ҳ�棬�����û�
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            }
            else{
                    if(scan_block_position(-1)!=-1){
                        block[scan_block_position(-1)]=page[t];
                        count++;
                        printf("װ��ҳ��%d,��ǰ�����Ϊ",page[t]);//�����������пտ飬��ôֱ��װ��ҳ��
                        for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                        printf("\n");

                    }
                    else{
            int position[BLOCK_SIZE];//�û�ҳ�棬Ѱ��������δʹ�õ�ҳ�棬�����û�
            for(int i=0;i<BLOCK_SIZE;i++) position[i]=scan_page_preposition(block[i]);
            int temp=min(position);

            printf("ҳ��%d����������У���%d����,",page[t],block[temp]);
            block[temp]=page[t];
            printf("��ǰ�����Ϊ");
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            count++;
        }
    }
        t++;
    }
    printf("ȱҳ��Ϊ%.0f%%",(float)count/PAGE_NUM*100);
}

void LFU(){
    initialize();
    printf("\n--------------------------LFU--------------------------\n");
    int count=0;//ȱҳ������
    int usage[PAGE_SIZE];//���ʹ�ô���������
    for(int i=0;i<PAGE_SIZE;i++) usage[i]=0;
    while(t<PAGE_NUM){
        if(scan_block_position(page[t])!=-1) {
            printf("ҳ��%d���������,��ǰ�����Ϊ",page[t]);//����������ҵ�ҳ�棬�����û�
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            usage[scan_block_position(page[t])]++;
        }
        else{
                if(scan_block_position(-1)!=-1){
                    block[scan_block_position(-1)]=page[t];
                    usage[page[t]]++;
                    count++;
                    printf("װ��ҳ��%d,��ǰ�����Ϊ",page[t]);//�����������пտ飬��ôֱ��װ��ҳ��
                    for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                    printf("\n");
                }
        else{
            int num[BLOCK_SIZE];//Ѱ�����ʹ�ô������ٵ�ҳ�棬�����û�
            for(int i=0;i<BLOCK_SIZE;i++) num[i]=usage[block[i]];
            int temp=min(num);

            printf("ҳ��%d����������У���%d����,",page[t],block[temp]);
            block[temp]=page[t];
            usage[page[t]]++;
            printf("��ǰ�����Ϊ");
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            count++;
        }
    }
        t++;
    }
    printf("ȱҳ��Ϊ%.0f%%",(float)count/PAGE_NUM*100);
}

void CLOCK(){
    initialize();
    printf("\n--------------------------CLOCK--------------------------\n");
    int temp=0;//��ǰָ��ָ���ҳ��
    int accessed[BLOCK_SIZE];//����λ
    for(int i=0;i<BLOCK_SIZE;i++) accessed[i]=0;//��ʼ������λ
    int count=0;//ȱҳ������
    while(t<PAGE_NUM){
            if(scan_block_position(page[t])!=-1){
            printf("ҳ��%d���������,��ǰ�����Ϊ",page[t]);//����������ҵ�ҳ�棬�����û�
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            accessed[scan_block_position(page[t])]=1;//����λ��1��ָ�벻�ƶ�
            }
            else{ if(block[temp%BLOCK_SIZE]==-1){//���������пտ飬װ��ҳ��
                    block[temp%BLOCK_SIZE]=page[t];
                    accessed[temp%BLOCK_SIZE]=1;
                    count++;//ȱҳ����+1
                    temp++;//ָ������
                    printf("װ��ҳ��%d,��ǰ�����Ϊ",page[t]);//�����������пտ飬��ôֱ��װ��ҳ��
                    for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                    printf("\n");
            }
            else{
                while(1){//ָ��˳�����ƣ�Ѱ�ҵ�һ������λΪ0��ҳ�棬�����û���ɨ������н�ɨ�����ҳ�����λ��0��
                        if(accessed[temp%BLOCK_SIZE]==0) break;
                        if(accessed[temp%BLOCK_SIZE]==1) {accessed[temp%BLOCK_SIZE]=0;temp++;}
                }
                printf("ҳ��%d����������У���%d����,",page[t],block[temp%BLOCK_SIZE]);
                block[temp%BLOCK_SIZE]=page[t];//�û�ҳ��
                accessed[temp%BLOCK_SIZE]=1;
                temp++;//ָ������
                printf("��ǰ�����Ϊ");//��ӡ��ǰ���������
                for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                printf("\n");
                count++;
            }
            }
        t++;
    }
    printf("ȱҳ��Ϊ%.0f%%",(float)count/PAGE_NUM*100);
}

void CLOCK_advanced(){
    initialize();
    printf("\n----------------------CLOCK_advanced----------------------\n");
    int temp=0;
    int accessed[BLOCK_SIZE];//����λ
    for(int i=0;i<BLOCK_SIZE;i++) accessed[i]=0;//��ʼ������λ
    int modified[BLOCK_SIZE];//�޸�λ
    for(int i=0;i<BLOCK_SIZE;i++) modified[i]=0;//��ʼ���޸�λ
    int count=0;//ȱҳ������
    int flag;//����ǵڼ���ɨ��
    while(t<PAGE_NUM){
        //Ϊ��ʵ���޸�λ��ģ�⣬��ÿ������ҳ��֮ǰ�������ĳ��������е��޸�λ��1
            int random_Num=rand()%3;
            if(block[random_Num]!=-1) modified[random_Num]=1;//���������������������ݲ�Ϊ�գ������޸�λ��1
            //ģ��ϵͳ�޸Ľ���
            flag=1;//�ӵ�һ��ɨ�迪ʼ
            if(scan_block_position(page[t])!=-1){
            printf("ҳ��%d���������,��ǰ�����Ϊ",page[t]);//����������ҵ�ҳ�棬�����û�
            for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
            printf("\n");
            accessed[scan_block_position(page[t])]=1;
            }
            else{ if(block[temp%BLOCK_SIZE]==-1){//����п��е�����飬װ��ҳ��
                    block[temp%BLOCK_SIZE]=page[t];
                    accessed[temp%BLOCK_SIZE]=1;
                    count++;
                    temp++;
                    printf("װ��ҳ��%d,��ǰ�����Ϊ",page[t]);//�����������пտ飬��ôֱ��װ��ҳ��
                    for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                    printf("\n");
            }
            else{//�û�ҳ��
                while(flag!=0){
                    if(flag==1){//��һ��ɨ�裬��1��ҳ��
                        for(int i=0;i<BLOCK_SIZE;i++){
                        if(accessed[temp%BLOCK_SIZE]==0&&modified[temp%BLOCK_SIZE]==0) {flag=0;break;}//����ҵ�1��ҳ�棬�˳�ѭ���������滻
                        temp++;//ָ������
                        }
                        if(flag!=0)flag=2;//���û�ҵ�����ʼ�ڶ���ɨ��
                        }
                    if(flag==2){//�ڶ���ɨ�裬��2��ҳ��
                        for(int i=0;i<BLOCK_SIZE;i++){
                        if(accessed[temp%BLOCK_SIZE]==0&&modified[temp%BLOCK_SIZE]==1) {flag=0;break;}//����ҵ�2��ҳ�棬�˳�ѭ���������滻
                        accessed[temp%BLOCK_SIZE]=0;//�ڶ���ɨ�轫������ҳ�����λ��0
                        temp++;//ָ������
                        }
                        if(flag!=0)flag=1;//���û�ҵ������¿�ʼ��һ��ɨ��
                    }

                }
                printf("ҳ��%d����������У���%d����,",page[t],block[temp%BLOCK_SIZE]);
                block[temp%BLOCK_SIZE]=page[t];
                accessed[temp%BLOCK_SIZE]=1;
                temp++;
                printf("��ǰ�����Ϊ");
                for(int i=0;i<BLOCK_SIZE;i++) printf("%d ",block[i]);
                printf("\n");
                count++;
            }
            }
        t++;
    }
    printf("ȱҳ��Ϊ%.0f%%",(float)count/PAGE_NUM*100);
}

int main(){
    srand((int)time(0));//Ϊ�˱�֤��������������������
    printf("----------------------20151681310036 ��ܲ----------------------\n");
    printf("----------------------ҳ���û��㷨ģ��----------------------\n\n");
    OPT();
    FIFO();
    LRU();
    LFU();
    CLOCK();
    CLOCK_advanced();
}
