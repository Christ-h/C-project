#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define N 50//ͳ�����ݳ���ʱ���޸�N��ֵ
typedef struct
{
    char name[10];
    long int num;
    float c;
}stu;//����ṹ��

/*�����˵�*/
void menu()
{
    system("cls");

    printf("\n\n\n\n\t\t\t   ѧ��C���Գɼ�����ϵͳ\n");
    printf("\t\t\t=======================\n");
    printf("\t\t\t  1.�ɼ�¼��\n");
    printf("\t\t\t  2.��ѯ�ɼ�\n");
    printf("\t\t\t  3.�޸ĳɼ�\n");
    printf("\t\t\t  4.��ӳɼ�\n");
    printf("\t\t\t  5.��ʾ�ɼ�\n");
    printf("\t\t\t  6.ͳ�Ƴɼ�\n");
    printf("\t\t\t  7.ɾ���ɼ�\n");
    printf("\t\t\t  0.�˳�ϵͳ\n");
    printf("\t\t\t=======================\n");
    printf("\t\t\t��ѡ����Ӧ�Ĺ���:");

}

/*¼��ɼ�*/
void input()
{
    FILE *fp;
    stu xs; /*����һ���ṹ�������װ���ļ��ж�����������*/
    if((fp=fopen("student.dat","ab"))==NULL) {printf("can't open file!\n");exit(0);}
    printf("\n¼���ʽ: ���� ѧ�� C���Գɼ�  ��������Ϊf����¼�룩\n");
    while(1) //�м����break����ʹѭ���ж�
    {
        scanf("%s",xs.name);
        if(strcmp(xs.name,"f")==0) break;//�ж������Ƿ�Ϊf�����ַ����ж�
        scanf("%d%f",&xs.num,&xs.c);
        fwrite(&xs,sizeof(stu),1,fp); //���ɼ���Ϣд���ļ�
    }
    fclose(fp);
}

//����
void xingming()
{
    FILE *fp;
    stu xs;
    char name[10];
    printf("\n����Ҫ��ѧ��������: ");
    scanf("%s",name);
    if((fp=fopen("student.dat","rb"))==NULL)
        {
            printf("can't open file!\n");
            exit(0);
        }
    while(!feof(fp))
    {
        fread(&xs,sizeof(stu),1,fp);
        if(strcmp(xs.name,name)==0)//��������ѯʱ�ж�����������Ƿ���ڣ���ѭ������������ȡ
        {
            printf("    ѧ������Ϣ����:\n");
            printf("\n%10s    %6s %6s \n","����","ѧ��","C���Գɼ�");
            printf("%10s %10d %6.2f \n",xs.name,xs.num,xs.c);
            break;
        }
    }
    if(feof(fp)) printf("����ʧ��!!!"); /*ѧ��������*/
    fclose(fp);
}

/*��ѯѧ��*/
void xuehao()
{
    FILE *fp;
    stu xs;
    int num;
    printf("\n����Ҫ��ѧ����ѧ��: ");scanf("%d",&num);
    if((fp=fopen("student.dat","rb"))==NULL)
    {
        printf("can't open file!\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fread(&xs,sizeof(stu),1,fp);
        if(xs.num==num)//��ѧ�Ų�ѯʱ�ж������ѧ���Ƿ���ڣ���ѭ���������в���
        {
            printf("    ѧ������Ϣ����:\n");
            printf("\n%10s     %6s %6s \n","����","ѧ��","C���Գɼ�");
            printf("%10s %10d %6.2f \n",xs.name,xs.num,xs.c);
            break;
        }
    }
    if(feof(fp)) printf("����ʧ��!!!");
    fclose(fp);
}

//��ѯ
void search()
{
    char ch1;
    system("cls");
    printf("�����밴���ַ�ʽ��ѯ��\n");
    printf("1-������2-ѧ��:");
    ch1=getchar();/*���ַ�����*/
    switch(ch1)/*�ж�*/
    {
        case '1':xingming();break;
        case '2':xuehao();break;
    }
    getch();/*����Ļͣ��ͬʱ�����������*/
}

/*�޸�:����ѧ��������,���Ҹ�ѧ�������ҵ����޸ĸ����ĳɼ���Ϣ������ʾ�޸�ǰ��Ľ��*/
void modi1()
{
    stu xs;
    FILE *fp;
    char name[10];
    system("cls");
    printf("\n����Ҫ��ѧ��������: ");
    scanf("%s",name);
    if((fp=fopen("student.dat","rb+"))==NULL)
    {
        printf("can't open file!\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fread(&xs,sizeof(stu),1,fp);
        if(strcmp(xs.name,name)==0)//�ж�����Ҫ�޸ĵ������Ƿ����
        {
            printf("   �޸�ǰѧ������Ϣ����:\n");
            printf("\n%10s     %6s %6s \n","����","ѧ��","C���Գɼ�");
            printf("%10s %10d %6.2f \n",xs.name,xs.num,xs.c);
            printf("\n�����������C���Գɼ�:");scanf("%f",&xs.c);
            break;
        }
    }
    if(!feof(fp))
    {
        printf("  \n �޸ĺ��ѧ������Ϣ����:\n");
        printf("\n%10s    %6s %6s \n","����","ѧ��","C���Գɼ�");
        printf("%10s %10d %6.2f \n",xs.name,xs.num,xs.c);
        fseek(fp,-sizeof(stu),1);//���ű�ʾ���ˣ�1��ʾ�ļ���ǰλ��
        fwrite(&xs,sizeof(stu),1,fp);//��д�룬ͬʱ��Ҫ�޸ĵ��Ǹ�����
    }
    else
        printf("\nѧ�������ڣ��޸�ʧ��!!");
        fclose(fp);
        getch();
}

/*�޸�:����ѧ����ѧ��,���Ҹ�ѧ�������ҵ����޸ĸ����ĳɼ���Ϣ������ʾ�޸�ǰ��Ľ��*/
void modi2()
{
    stu xs;
    FILE *fp;
    int num;
    system("cls");
    printf("\n����Ҫ��ѧ����ѧ��: ");
    scanf("%d",&num);
    if((fp=fopen("student.dat","rb+"))==NULL)
    {
        printf("can't open file!\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fread(&xs,sizeof(stu),1,fp);
        if(xs.num==num)/*�ж�����Ҫ�޸ĵ������Ƿ����*/
        {
            printf("   �޸�ǰѧ������Ϣ����:\n");
            printf("\n%10s    %6s %6s \n","����","ѧ��","C���Գɼ�");
            printf("%10s %10d %6.2f \n",xs.name,xs.num,xs.c);
            printf("\n�����������C���Գɼ�:");scanf("%f",&xs.c);
            break;
        }
    }
    if(!feof(fp))
    {
        printf("  \n �޸ĺ��ѧ������Ϣ����:\n");
        printf("\n%10s    %6s %6s \n","����","ѧ��","C���Գɼ�");
        printf("%10s %10d %6.2f \n",xs.name,xs.num,xs.c);
        fseek(fp,-sizeof(stu),1);//���ű�ʾ���ˣ�1��ʾ�ļ���ǰλ��
        fwrite(&xs,sizeof(stu),1,fp);//��д�룬ͬʱ��Ҫ�޸ĵ��Ǹ����ǵ�
    }
    else
    printf("\nѧ�������ڣ��޸�ʧ��!!");
    fclose(fp);
    getch();
}

/*�޸�*/
void search1()
{
    char ch1;
    system("cls");
    printf("�����밴���ַ�ʽ�޸ģ�\n");
    printf("1-������2-ѧ��:");
    ch1=getchar();//���ַ�����
    switch(ch1)/*�ж�*/
    {
        case '1':modi1();break;
        case '2':modi2();break;
    }
    getch();//����Ļͣ��ͬʱ�����������
}

/*����:����ѧ����ƽʱ�ĸ���ɼ������뵽ָ��λ�ã���ָ����λ�ó�����Χʱ��������뵽ȫ�����󣬲���ʾ����ɹ���Ľ��*/
void insert()
{
    int i=0,j,k,lenth;
    FILE *fp;
    stu s,xs[N];
    system("cls");
    printf("\n����������ѧ��������:");scanf("%s",&s.name);
    printf("\nѧ����ѧ��:");scanf("%d",&s.num);
    printf("\nѧ����C�ɼ�:");scanf("%f",&s.c);
    printf("\n����λ��:");scanf("%d",&k);
    // i=0;
    if((fp=fopen("student.dat","rb"))==NULL)
    {
        printf("can't open file!\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fread(&xs[i],sizeof(stu),1,fp);//�����ݶ��뵽�ṹ��������
        if(feof(fp)) break;
        i++;
    }
    fclose(fp);
    lenth=i;
    if(k<lenth && k>=0)/*k��λ��Ҫλ�����鷶Χ֮��*/
    {//����
    for(j=lenth-1;j>=k;j--)
        xs[j+1]=xs[j];//һ��ʼj�����ģ�������һ�������ƶ��������ݱ�����
        xs[k]=s;//�������ѧ����Ϣ�������kλ��
        lenth++;
        if((fp=fopen("student.dat","wb"))==NULL)
        {
            printf("���ܽ����ļ�!!\n");
            exit(0);
        }
        for(i=0;i<lenth;i++)
        fwrite(&xs[i],sizeof(stu),1,fp);
    }
    else/*�������鷶Χ֮��*/
    {
        if((fp=fopen("student.dat","ab"))==NULL)
            {
                printf("���ܽ����ļ�!!\n");
                exit(0);
            }
        fwrite(&s,sizeof(stu),1,fp);
    }
    fclose(fp);
}

/*��ʾ*/
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
    printf("\n%10s    %6s %6s  \n","����","ѧ��","C���Գɼ�");
    while(!feof(fp))
    {
        fread(&s,sizeof(stu),1,fp);//���ļ��ж�ȡ�ɼ���Ϣ
        if(feof(fp)) break;//�ж��Ƿ��ļ�β
        printf("%10s %10d %6.2f \n",s.name,s.num,s.c );
    }
    fclose(fp);
    getch();
}

/*ͳ�Ƹ�������ѧ����Ϣ*/
void tongji()
{

    int i=0,j=0,k=0,l=0,m=0,n,p,q,r,t,u;
    FILE *fp;
    stu s[N], *p1[N],*p2[N],*p3[N],*p4[N];//��ָ������
    system("cls");
    if((fp=fopen("student.dat","rb"))==NULL)
    {
        printf("cant't open file!\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fread(&s[i++],sizeof(stu),1,fp);//��������
        if(feof(fp)) break;
    }
    t=i;i=0;
    for(u=0;u<t;u++)/*����ÿ��ָ����������ָ��������ε�ѧ����Ϣ*/
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
    printf("60�����£�   ����      ѧ��   C���Գɼ�\n");
    for(n=0;n<j-1;n++)
    {
        printf("\t%10s %10d %6.2f\n",p1[n]->name,p1[n]->num,p1[n]->c);
    }
    printf(" 60-79�֣�   ����      ѧ��   C���Գɼ�\n");
    for(p=0;p<k;p++)
    {
        printf("\t%10s %10d %6.2f\n",p2[p]->name,p2[p]->num,p2[p]->c);
    }
    printf(" 80-89�֣�   ����      ѧ��   C���Գɼ�\n");
    for(q=0;q<l;q++)
    {
        printf("\t%10s %10d %6.2f\n",p3[q]->name,p3[q]->num,p3[q]->c);
    }
    printf("90�����ϣ�   ����      ѧ��   C���Գɼ�\n");
    for(r=0;r<m;r++)
    {
        printf("\t%10s %10d %6.2f\n",p4[r]->name,p4[r]->num,p4[r]->c);
    }
    fclose(fp);
    getch();
}

/*ɾ��:����ѧ������������ѧ�����ڣ���ɾ��������ʾɾ�������µ�ѧ���ɼ���Ϣ*/
void dele1()
{
    stu xs[N];
    FILE *fp;
    char name[10];
    int i=0,len,k=-1;//k<0��Ϊ����if�ж��õ�
    system("cls");
    printf("\n����Ҫɾ����ѧ������: ");
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
//������ɾ��������д�ļ�
    len=i;//�ṹ����������
    if(k>=0)//>0˵���ҵ�ɾ��ѧ��λ��
    {
        if((fp=fopen("student.dat","wb+"))==NULL)
            {
                printf("can't open file!\n");
                exit(0);
            }
        for(i=0;i<len;i++)
        {
            if(i==k) continue;//�����λ�ÿ�ʼд��
            fwrite(&xs[i],sizeof(stu),1,fp);
        }
        fclose(fp);
    }
    else
    {
        printf("ɾ��ʧ��!!!\n");
        getch();
    } //ʧ�ܺ����·��ز˵�
    print();
}

/*ɾ��:����ѧ��ѧ�ţ�����ѧ�����ڣ���ɾ��������ʾɾ�������µ�ѧ���ɼ���Ϣ*/
void dele2()
{
    stu xs[N];
    FILE *fp;
    int  num;
    int i=0,len,k=-1;//k<0��Ϊ����if�ж��õ�
    system("cls");
    printf("\n����Ҫɾ����ѧ��ѧ��: ");
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
//������ɾ��������д�ļ�
    len=i;//�ṹ����������
    if(k>=0)//k>0˵���ҵ�ɾ��ѧ��λ��
    {
        if((fp=fopen("student.dat","wb+"))==NULL)
        {
            printf("can't open file!\n");
            exit(0);
        }
    for(i=0;i<len;i++)
    {
        if(i==k) continue;//�����λ�ÿ�ʼд��
        fwrite(&xs[i],sizeof(stu),1,fp);
    }
    fclose(fp);
    }
    else
    {
        printf("ɾ��ʧ��!!!\n");
        getch();
    } //ʧ�ܺ����·��ز˵�
    print();
}

/*ɾ��*/
void search11()
{
    char ch1;
    system("cls");
    printf("�����밴���ַ�ʽɾ����\n");
    printf("1-������2-ѧ��:");
    ch1=getchar();/*���ַ�����*/
    switch(ch1)/*�ж�*/
    {
        case '1':dele1();break;
        case '2':dele2();break;
    }
    getch();//����Ļͣ��ͬʱ�����������
}

/*�˵�ѡ��*/
void main()
{
    char ch;
    while(1)
    {
        menu();// ��ʾ�˵�
        ch=getch();//ѡ��˵�
        if(ch=='0') break;
        switch(ch)//�жϹ�����
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
    printf("\n��ӭʹ��!!!\n");
}
