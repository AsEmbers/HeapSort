#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//定义动态数组数据结构
typedef int ElemType;
typedef struct{
    ElemType *elem;
    int len;
}SequenceTable;

//初始化随机数组
void init_rand_seq_table(SequenceTable &seq_table,int len)
{
    seq_table.len=len;
    seq_table.elem=(ElemType*)malloc(sizeof(ElemType)*seq_table.len);
    srand(time(NULL));
    for(int i=0;i<seq_table.len;i++)
    {
        seq_table.elem[i]=rand()%100;
    }
}

//初始化数组
void init_seq_table(SequenceTable &seq_table,int len)
{
    seq_table.len=len;
    seq_table.elem=(ElemType*)malloc(sizeof(ElemType)*seq_table.len);
    ElemType element;
    for(int i=0;i<seq_table.len;i++)
    {
        scanf("%d",&element);
        seq_table.elem[i]=element;
    }
}

//打印数组
void print_seq_table(SequenceTable seq_table)
{
    for(int i=0;i<seq_table.len;i++)
    {
        printf("%3d",seq_table.elem[i]);
    }
    printf("\n");
}

//交换元素
void swap(ElemType &a,ElemType &b)
{
    ElemType temp=a;
    a=b;
    b=temp;
}

//调整子树
void adjust_down(ElemType *arr,int i,int len)
{
    /**
     * 采用循环原因：每次调整一棵子树为大根堆之后，当调整的子树为中间层子树时，
     * 调整完当前子树后，还需重新检查之前已经调整过的子树被交换新的父结点之后是否还符合大根堆特点，
     * 即父结点恒大于子结点
     */
    int dad = i;
    int son = 2 * dad + 1; //左孩子下标
    while(son<len)
    {
        if(son+1<len && arr[son]<arr[son+1])//看下有没有右孩子，比较左右孩子选大的
        {
            son++;
        }
        if(arr[son]>arr[dad])//比较孩子和父亲，如果孩子大于父亲，那么进行交换
        {
            swap(arr[son], arr[dad]);
            dad=son;//孩子重新作为父亲，判断下一颗子树是否符合大根堆
            son=2*dad+1;
        }
        else
        {
            break;
        }
    }
}

//堆排序
void heap_sort(ElemType *arr,int len)
{
    //调整每一颗子树以及整棵树为大根堆
    int i;
    for(i=len/2-1;i>=0;i--)
    {
        adjust_down(arr,i,len);
    }
    swap(arr[0],arr[len-1]);
    for(i=len-1;i>1;i--)
    {
        adjust_down(arr,0,i);//剩下的元素继续调整为大根堆
        swap(arr[0],arr[i-1]);//继续将调整好的最大根交换到剩余元素的最后一位
    }
}

int main() {
    SequenceTable seq_table;
    int len=10;
    init_rand_seq_table(seq_table,len);
//    ElemType arr[10]={12,63,58,95,41,35,65,0,38,44};
//    memcpy(seq_table.elem,arr,sizeof(arr));//使用前提：动态数组的内存空间已经初始化，即已获得一片连续的内存空间
    print_seq_table(seq_table);
    heap_sort(seq_table.elem,10);
    print_seq_table(seq_table);
    return 0;
}
