#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

unsigned long long syscall_bitmap[9] = {15, 0, 0, 0, 2, 0, 0, 0, 0};

// struct test_a {
//     int a;
//     int b;
// };

// struct test_b {
//     int c;
//     int d;
// };

// struct test_struct {
//     struct test_a e;
//     struct test_b f;
// };

// void tprintf(struct test_a * test){
//     struct test_b b;
//     memcpy(&b, (char *)test + sizeof(struct test_a), sizeof(struct test_b));
//     printf("test output:%d\n", b.c);
// }

// char * tpointer(){
//     char * tbuffer = NULL;
//     tbuffer = (char *)malloc(sizeof(struct test_a));
//     ((struct test_a *)tbuffer)->a = 1;
//     ((struct test_a *)tbuffer)->b = 2;
//     printf("tbuffer->a:%d, tbuffer->b:%d\n", ((struct test_a *)tbuffer)->a, ((struct test_a *)tbuffer)->b);
//     return tbuffer;
// }

// void tpointer_1(char **tbuffer){
//     *tbuffer = (char *)malloc(sizeof(struct test_a));
// }

#define LLSIZE (sizeof(unsigned long long int) * 8)
#define SET_MASK 0x0000000000000001
#define ISSET_MASK 0xfffffffffffffffe
#define RESET_MASK 0xfffffffffffffffe

// void set_bitmap(unsigned long long int * syscall_bitmap, unsigned int syscall){
//     if (syscall < 0 && syscall > 547){
//         return;
//     }
//     int base = syscall / LLSIZE;    // 获取基址
//     int surplus = syscall % LLSIZE; // 余值

//     unsigned long long int * base_p = syscall_bitmap + base;
//     unsigned long long int base_n = *base_p;
//     *base_p = base_n | ((( base_n >> surplus) | SET_MASK) << surplus);
// }

int is_set(unsigned long long int * syscall_bitmap, unsigned int syscall){
    if (syscall < 0 && syscall > 547){
        return -1;
    }
    int base = syscall / LLSIZE;    // 获取基址
    int surplus = syscall % LLSIZE; // 余值

    unsigned long long int * base_p = syscall_bitmap + base;
    unsigned long long int base_n = *base_p;
    base_n = (base_n >> surplus) | ISSET_MASK;
    return base_n==0xffffffffffffffff?1:-1;
}

// void reset_bitmap(unsigned long long int * syscall_bitmap, unsigned int syscall){
//     if (syscall < 0 && syscall > 547){
//         return;
//     }
//     int base = syscall / LLSIZE;    // 获取基址
//     int surplus = syscall % LLSIZE; // 余值

//     unsigned long long int * base_p = syscall_bitmap + base;
//     unsigned long long int base_n = *base_p;
//     *base_p = base_n | ((( base_n >> surplus) & RESET_MASK) << surplus);
// }

// static unsigned long long int syscall_bitmap[9] = {15, 0, 0, 1, 0, 0, 0, 0, 0};

union semun {          
    int                 val;
    struct semid_ds *   buf;
    unsigned short *    array;
};

// 通过 ftok 获取信号量钥匙号
int CreateKey(const char * pathName)
{
    FILE *fd = NULL;
    ;
 
    if ((fd = fopen( pathName,"r")) == NULL)
    {
        printf("Open file error!\n");
        return -1;
    }
 
    fclose(fd);
    return ftok(pathName, 0);
}
#define SEM_PATHNAME "./system_v_yaoshi.txt"

int main()
{
    // struct test_a a;
    // struct test_b b;

    // a.a = 1;
    // a.b = 2;
    // b.c = 3;
    // b.d = 4;

    // struct test_struct tstruct;
    // memset(&tstruct, 0, sizeof(tstruct));
    // memcpy(&tstruct, &a, sizeof(a));
    // memcpy((char*)&tstruct + sizeof(struct test_a), &b, sizeof(b));
    // tprintf((void *)&tstruct);

    // /* 测试子函数中malloc的内存会不会自动free */
    // struct test_a * tbuffer = NULL;
    // tbuffer = tpointer();
    // if(tbuffer == NULL){
    //     printf("flags2\n");
    // }
    // printf("tbuffer->a:%d, tbuffer->b:%d\n", tbuffer->a, tbuffer->b);
    // free(tbuffer);
    // tbuffer = NULL;

    // /* 测试，，不记得了 */
    // struct test_a * tbuffer = NULL;
    // tpointer_1((char **)&tbuffer);
    // free(tbuffer);
    // tbuffer = NULL;

    // /* 通过 RSC 测试系统调用参数用寄存器传递的对不对 */
    // char a[100] = "huomax is a shuaige!";
    // FILE *fp = NULL;
    // fp = fopen("test.txt", "w");
    // fwrite(a, sizeof(char), strlen(a), fp);
    // fclose(fp);

    /* 测试 char * 表示的地址和 usigned long long int 的转换 */
    // char * a = "huomax is a shuaige!";
    // unsigned long int b = (unsigned long int)a;
    // printf("strlen-long:%ld\n", strlen((char *)b));
    /* 测试位图 */
    // memset(syscall_bitmap, 0, sizeof(unsigned long long int) * 9);
    // set_bitmap(syscall_bitmap, 2);
    // if(is_set(syscall_bitmap, 2) > 0){
    //     printf("OK!\n");
    // }
    // printf("test bitmap_1: %lld\n", *syscall_bitmap);
    // set_bitmap(syscall_bitmap, 257);
    // printf("test bitmap_2: %lld\n", *(syscall_bitmap+1));
    // printf("test bitmap_3: %lld\n", *(syscall_bitmap+2));
    // printf("test bitmap_4: %lld\n", *(syscall_bitmap+3));
    // printf("test bitmap_5: %lld\n", *(syscall_bitmap+4));
    // printf("test bitmap_6: %lld\n", *(syscall_bitmap+5));
    // printf("test bitmap_7: %lld\n", *(syscall_bitmap+6));
    // printf("test bitmap_8: %lld\n", *(syscall_bitmap+7));

    // printf("0:%d, 1:%d, 2:%d, 3:%d, 257:%d\n", is_set(syscall_bitmap, 0), is_set(syscall_bitmap, 1), is_set(syscall_bitmap, 2), is_set(syscall_bitmap, 3), is_set(syscall_bitmap, 257));
    // /* 测试指针长度 */
    // char * test_buffer = "huomax is a very shuaige!";
    // printf("test_buffer length: %ld", sizeof(char *));

    // 测试system v信号量机制使用了哪些系统调用

   int semId;
   union semun arg;
   unsigned short array[4] = {0};
   struct sembuf buffer;
 
    // 解决信号量的创建和初始化不是原子操作的一种方案
    semId = semget(CreateKey(SEM_PATHNAME), 1, 0666);
    semctl(semId, 0, IPC_RMID);
    /* 测试short类型大小 */
    // printf("short type length: %d\n", sizeof(unsigned short));
    // printf("int type length: %d\n", sizeof(unsigned int));
    // printf("long type length: %d\n", sizeof(unsigned long));
    // printf("long long type length: %d\n", sizeof(unsigned long long));
    // printf("is_set:%d\n", is_set(syscall_bitmap, 5));

    return 0;
}

