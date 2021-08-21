//下面的程序，与 Unix 的 cp 命令类似，需要两个文件名作为参数，将第一个文件的内容复制到第二个文件。

//该程序涉及到main()函数传参的问题，请查看：C语言mian()函数详解


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    FILE *fin, *fout;
    char c;

    if (argc!=3){
        printf("Usage: %s filein fileout\n", argv[0]);
        exit(0);
    }
    if ((fin=fopen(argv[1],"r"))==NULL){
        perror("fopen filein");
        exit(0);
    } 
    if ((fout=fopen(argv[2],"w"))==NULL){
        perror("fopen fileout");
        exit(0);
    }

    while ((c=getc(fin))!=EOF)
        putc(c,fout);

    fclose(fin);
    fclose(fout);
    return 0;
}
