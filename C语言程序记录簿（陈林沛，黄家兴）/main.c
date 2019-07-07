#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define N 50//统计数据超出时，修改N的值
typedef struct
{
    char name[10];
    long int num;
    float c;
}stu;//定义结构体

/*建立菜单*/
void menu()
{
    system("cls");

    printf("\n\n\n\n\t\t\t   学生C语言成绩管理系统\n");
    printf("\t\t\t=======================\n");
    printf("\t\t\t  1.成绩录入\n");
    printf("\t\t\t  2.查询成绩\n");
    printf("\t\t\t  3.修改成绩\n");
    printf("\t\t\t  4.添加成绩\n");
    printf("\t\t\t  5.显示成绩\n");
    printf("\t\t\t  6.统计成绩\n");
    printf("\t\t\t  7.删除成绩\n");
    printf("\t\t\t  0.退出系统\n");
    printf("\t\t\t=======================\n");
    printf("\t\t\t请选择相应的功能:");

}

/*录入成绩*/
void input()
{
    FILE *fp;
    stu xs; /*定义一个结构体变量来装从文件中读出来的数据*/
    if((fp=fopen("student.dat","ab"))==NULL) {printf("can't open file!\n");exit(0);}
    printf("\n录入格式: 姓名 学号 C语言成绩  （当输入为f结束录入）\n");
    while(1) //中间加入break，可使循环中断
    {
        scanf("%s",xs.name);
        if(strcmp(xs.name,"f")==0) break;//判断姓名是否为f，用字符串判断
        scanf("%d%f",&xs.num,&xs.c);
        fwrite(&xs,sizeof(stu),1,fp); //将成绩信息写入文件
    }
    fclose(fp);
}

//姓名
void xingming()
{
    FILE *fp;
    stu xs;
    char name[10];
    printf("\n输入要查学生的姓名: ");
    scanf("%s",name);
    if((fp=fopen("student.dat","rb"))==NULL)
        {
            printf("can't open file!\n");
            exit(0);
        }
    while(!feof(fp))
    {
        fread(&xs,sizeof(stu),1,fp);
        if(strcmp(xs.name,name)==0)//按姓名查询时判断输入的姓名是否存在，会循环从数据中找取
        {
            printf("    学生的信息如下:\n");
            printf("\n%10s    %6s %6s \n","姓名","学号","C语言成绩");
            printf("%10s %10d %6.2f \n",xs.name,xs.num,xs.c);
            break;
        }
    }
    if(feof(fp)) printf("查找失败!!!"); /*学生不存在*/
    fclose(fp);
}

/*查询学号*/
void xuehao()
{
    FILE *fp;
    stu xs;
    int num;
    printf("\n输入要查学生的学号: ");scanf("%d",&num);
    if((fp=fopen("student.dat","rb"))==NULL)
    {
        printf("can't open file!\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fread(&xs,sizeof(stu),1,fp);
        if(xs.num==num)//按学号查询时判断输入的学号是否存在，会循环从数据中查找
        {
            printf("    学生的信息如下:\n");
            printf("\n%10s     %6s %6s \n","姓名","学号","C语言成绩");
            printf("%10s %10d %6.2f \n",xs.name,xs.num,xs.c);
            break;
        }
    }
    if(feof(fp)) printf("查找失败!!!");
    fclose(fp);
}

//查询
void search()
{
    char ch1;
    system("cls");
    printf("请输入按何种方式查询：\n");
    printf("1-姓名，2-学号:");
    ch1=getchar();/*用字符接收*/
    switch(ch1)/*判断*/
    {
        case '1':xingming();break;
        case '2':xuehao();break;
    }
    getch();/*让屏幕停留同时按任意键返回*/
}

/*修改:输入学生的姓名,查找该学生，若找到则修改该生的成绩信息，并显示修改前后的结果*/
void modi1()
{
    stu xs;
    FILE *fp;
    char name[10];
    system("cls");
    printf("\n输入要查学生的姓名: ");
    scanf("%s",name);
    if((fp=fopen("student.dat","rb+"))==NULL)
    {
        printf("can't open file!\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fread(&xs,sizeof(stu),1,fp);
        if(strcmp(xs.name,name)==0)//判断输入要修改的姓名是否存在
        {
            printf("   修改前学生的信息如下:\n");
            printf("\n%10s     %6s %6s \n","姓名","学号","C语言成绩");
            printf("%10s %10d %6.2f \n",xs.name,xs.num,xs.c);
            printf("\n请输入该生的C语言成绩:");scanf("%f",&xs.c);
            break;
        }
    }
    if(!feof(fp))
    {
        printf("  \n 修改后的学生的信息如下:\n");
        printf("\n%10s    %6s %6s \n","姓名","学号","C语言成绩");
        printf("%10s %10d %6.2f \n",xs.name,xs.num,xs.c);
        fseek(fp,-sizeof(stu),1);//负号表示后退，1表示文件当前位置
        fwrite(&xs,sizeof(stu),1,fp);//再写入，同时把要修改的那个覆盖
    }
    else
        printf("\n学生不存在，修改失败!!");
        fclose(fp);
        getch();
}

/*修改:输入学生的学号,查找该学生，若找到则修改该生的成绩信息，并显示修改前后的结果*/
void modi2()
{
    stu xs;
    FILE *fp;
    int num;
    system("cls");
    printf("\n输入要查学生的学号: ");
    scanf("%d",&num);
    if((fp=fopen("student.dat","rb+"))==NULL)
    {
        printf("can't open file!\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fread(&xs,sizeof(stu),1,fp);
        if(xs.num==num)/*判断输入要修改的姓名是否存在*/
        {
            printf("   修改前学生的信息如下:\n");
            printf("\n%10s    %6s %6s \n","姓名","学号","C语言成绩");
            printf("%10s %10d %6.2f \n",xs.name,xs.num,xs.c);
            printf("\n请输入该生的C语言成绩:");scanf("%f",&xs.c);
            break;
        }
    }
    if(!feof(fp))
    {
        printf("  \n 修改后的学生的信息如下:\n");
        printf("\n%10s    %6s %6s \n","姓名","学号","C语言成绩");
        printf("%10s %10d %6.2f \n",xs.name,xs.num,xs.c);
        fseek(fp,-sizeof(stu),1);//负号表示后退，1表示文件当前位置
        fwrite(&xs,sizeof(stu),1,fp);//再写入，同时把要修改的那个覆盖掉
    }
    else
    printf("\n学生不存在，修改失败!!");
    fclose(fp);
    getch();
}

/*修改*/
void search1()
{
    char ch1;
    system("cls");
    printf("请输入按何种方式修改：\n");
    printf("1-姓名，2-学号:");
    ch1=getchar();//用字符接收
    switch(ch1)/*判断*/
    {
        case '1':modi1();break;
        case '2':modi2();break;
    }
    getch();//让屏幕停留同时按任意键返回
}

/*插入:输入学生的平时的各项成绩，插入到指定位置；当指定的位置超出范围时，将其插入到全班的最后，并显示插入成功后的结果*/
void insert()
{
    int i=0,j,k,lenth;
    FILE *fp;
    stu s,xs[N];
    system("cls");
    printf("\n请输入插入的学生的姓名:");scanf("%s",&s.name);
    printf("\n学生的学号:");scanf("%d",&s.num);
    printf("\n学生的C成绩:");scanf("%f",&s.c);
    printf("\n插入位置:");scanf("%d",&k);
    // i=0;
    if((fp=fopen("student.dat","rb"))==NULL)
    {
        printf("can't open file!\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fread(&xs[i],sizeof(stu),1,fp);//把数据读入到结构体数组中
        if(feof(fp)) break;
        i++;
    }
    fclose(fp);
    lenth=i;
    if(k<lenth && k>=0)/*k的位置要位于数组范围之内*/
    {//插入
    for(j=lenth-1;j>=k;j--)
        xs[j+1]=xs[j];//一开始j是最大的，往后移一个这样移动避免数据被覆盖
        xs[k]=s;//将输入的学生信息加入这个k位置
        lenth++;
        if((fp=fopen("student.dat","wb"))==NULL)
        {
            printf("不能建立文件!!\n");
            exit(0);
        }
        for(i=0;i<lenth;i++)
        fwrite(&xs[i],sizeof(stu),1,fp);
    }
    else/*不在数组范围之内*/
    {
        if((fp=fopen("student.dat","ab"))==NULL)
            {
                printf("不能建立文件!!\n");
                exit(0);
            }
        fwrite(&s,sizeof(stu),1,fp);
    }
    fclose(fp);
}

/*显示*/
void print()
{
    FILE *fp;
    stu s;
    system("cls");
    if((fp=fopen("student.dat","rb"))==NULL)
    {
        printf("can't open file!\n");
        exit(0);
    }
    printf("\n%10s    %6s %6s  \n","姓名","学号","C语言成绩");
    while(!feof(fp))
    {
        fread(&s,sizeof(stu),1,fp);//从文件中读取成绩信息
        if(feof(fp)) break;//判断是否文件尾
        printf("%10s %10d %6.2f \n",s.name,s.num,s.c );
    }
    fclose(fp);
    getch();
}

/*统计各分数段学生信息*/
void tongji()
{

    int i=0,j=0,k=0,l=0,m=0,n,p,q,r,t,u;
    FILE *fp;
    stu s[N], *p1[N],*p2[N],*p3[N],*p4[N];//用指针数组
    system("cls");
    if((fp=fopen("student.dat","rb"))==NULL)
    {
        printf("cant't open file!\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fread(&s[i++],sizeof(stu),1,fp);//读入数据
        if(feof(fp)) break;
    }
    t=i;i=0;
    for(u=0;u<t;u++)/*以下每个指针数组用于指向各分数段的学生信息*/
    {
        if(s[i].c<60)
        {
            p1[j++]=&s[i++];
            continue;
        }
        if(s[i].c>=60&&s[i].c<80)
        {
            p2[k++]=&s[i++];
            continue;
        }
        if(s[i].c>=80&&s[i].c<90)
        {
            p3[l++]=&s[i++];
            continue;
        }
        if(s[i].c>=90)
        {
            p4[m++]=&s[i++];
            continue;
        }
    }
    printf("60分以下：   姓名      学号   C语言成绩\n");
    for(n=0;n<j-1;n++)
    {
        printf("\t%10s %10d %6.2f\n",p1[n]->name,p1[n]->num,p1[n]->c);
    }
    printf(" 60-79分：   姓名      学号   C语言成绩\n");
    for(p=0;p<k;p++)
    {
        printf("\t%10s %10d %6.2f\n",p2[p]->name,p2[p]->num,p2[p]->c);
    }
    printf(" 80-89分：   姓名      学号   C语言成绩\n");
    for(q=0;q<l;q++)
    {
        printf("\t%10s %10d %6.2f\n",p3[q]->name,p3[q]->num,p3[q]->c);
    }
    printf("90分以上：   姓名      学号   C语言成绩\n");
    for(r=0;r<m;r++)
    {
        printf("\t%10s %10d %6.2f\n",p4[r]->name,p4[r]->num,p4[r]->c);
    }
    fclose(fp);
    getch();
}

/*删除:输入学生姓名，若该学生存在，则删除，并显示删除后余下的学生成绩信息*/
void dele1()
{
    stu xs[N];
    FILE *fp;
    char name[10];
    int i=0,len,k=-1;//k<0是为后面if判断用的
    system("cls");
    printf("\n输入要删除的学生姓名: ");
    scanf("%s",name);
    if((fp=fopen("student.dat","rb+"))==NULL)
    {
        printf("can't open file!\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fread(&xs[i],sizeof(stu),1,fp);
        if(feof(fp)) break;
        if(strcmp(xs[i].name,name)==0) k=i;
        i++;
    }
    fclose(fp);
//以下是删除后重新写文件
    len=i;//结构体数组上限
    if(k>=0)//>0说明找到删除学生位置
    {
        if((fp=fopen("student.dat","wb+"))==NULL)
            {
                printf("can't open file!\n");
                exit(0);
            }
        for(i=0;i<len;i++)
        {
            if(i==k) continue;//从这个位置开始写入
            fwrite(&xs[i],sizeof(stu),1,fp);
        }
        fclose(fp);
    }
    else
    {
        printf("删除失败!!!\n");
        getch();
    } //失败后重新返回菜单
    print();
}

/*删除:输入学生学号，若该学生存在，则删除，并显示删除后余下的学生成绩信息*/
void dele2()
{
    stu xs[N];
    FILE *fp;
    int  num;
    int i=0,len,k=-1;//k<0是为后面if判断用的
    system("cls");
    printf("\n输入要删除的学生学号: ");
    scanf("%d",&num);
    if((fp=fopen("student.dat","rb+"))==NULL)
    {
        printf("can't open file!\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fread(&xs[i],sizeof(stu),1,fp);
        if(feof(fp)) break;
        if(xs[i].num==num) k=i;
        i++;
    }
    fclose(fp);
//以下是删除后重新写文件
    len=i;//结构体数组上限
    if(k>=0)//k>0说明找到删除学生位置
    {
        if((fp=fopen("student.dat","wb+"))==NULL)
        {
            printf("can't open file!\n");
            exit(0);
        }
    for(i=0;i<len;i++)
    {
        if(i==k) continue;//从这个位置开始写入
        fwrite(&xs[i],sizeof(stu),1,fp);
    }
    fclose(fp);
    }
    else
    {
        printf("删除失败!!!\n");
        getch();
    } //失败后重新返回菜单
    print();
}

/*删除*/
void search11()
{
    char ch1;
    system("cls");
    printf("请输入按何种方式删除：\n");
    printf("1-姓名，2-学号:");
    ch1=getchar();/*用字符接收*/
    switch(ch1)/*判断*/
    {
        case '1':dele1();break;
        case '2':dele2();break;
    }
    getch();//让屏幕停留同时按任意键返回
}

/*菜单选择*/
void main()
{
    char ch;
    while(1)
    {
        menu();// 显示菜单
        ch=getch();//选择菜单
        if(ch=='0') break;
        switch(ch)//判断功能项
        {
            case '1':input();break;
            case '2':search();break;
            case '3':search1();break;
            case '4':insert();break;
            case '5':print();break;
            case '6':tongji();break;
            case '7':search11();break;
        }
    }
    printf("\n欢迎使用!!!\n");
}
