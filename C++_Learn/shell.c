#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// input 表示切分命令
// output 表示切分结果(字符串数组)
// 返回值表示 output 中包含了几个有效元素
int Split(char input[], char* output[]){
    // 借助 strtok 来实现    
    char* pch;
    pch = strtok(input, " ");
    int i = 0;
    while(pch != NULL){
        printf("%s\n", pch);
        output[i] = pch;
        ++i;
        pch = strtok(NULL, " ");
    }
    return i;
}

int main(){
    while(1){
        // 1. 打印一个提示符
        printf("[minishell]$ ");
        fflush(stdout);
        // 2. 让用户输入一个指令
        
        // 存储用户输入内容
        char command[1024] = {0};
        // 不能读取整行
        //scanf("%s", command);
        // 可以一次读取一行
        gets(command);
        // TODO 测试输入
        // printf("%s\n", command);

        // 3. 解析指令 , 把要执行哪个程序识别出来，
        // 哪些是命令行参数 识别出来
        // 切分结果应该是一个字符串数组

        // 保存切分结果
        char* argv[1024] = {0};

        int n = Split(command, argv);

        // 4. 创建子进程 并且 进行程序替换
    }

    return 0;
}