#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int rev;
typedef struct st
{
	int rn;
	char name[20];
	float marks;
	struct st *next;
}sll;
void stud_add(sll **);
void stud_del(sll **);
void stu_show(sll *);
void edit_stud(sll **);
void save(sll *);
void exit_(sll *);
void sort_list(sll *);
void stud_del_all(sll **);
void stud_rev(sll **);
void read_database(sll **);
int count_students(sll *);

void stud_add(sll **ptr)
{
	if(rev)
		stud_rev(&(*ptr));
	sll *new=malloc(sizeof(sll));
	new->next=0;
	printf("Enter Name and Marks\n");
	scanf("%s%f",new->name,&new->marks);
	if(*ptr==0)
	{
		new->rn=1;
		*ptr=new;
		return;
	}
	sll *prev,*last=*ptr;
	int c=1;
	while((c==last->rn))
	{
		c++;
		if(last->next==0)
			break;
		prev=last;
		last=last->next;
	}
	new->rn=c;
	if(c==1)
	{
		new->next=*ptr;
		*ptr=new;
	}
	else
	{
		if((last->next==0) && (last->rn<c))
			last->next=new;
		else
		{
			new->next=prev->next;
			prev->next=new;
		}
	}
	
}
void stud_del(sll **ptr)
{
	char op;
	char s[15];
	int num,i=0,f=1;
	sll *del,*prev,*temp;
l:	printf("Choose option\n");
	printf("R/r : enter roll no to delete\nN/n :Enter name to delete\n");
	scanf(" %c",&op);
	if(op=='R'||op=='r')
	{
k:		printf("Enter roll number to delete\n");
		scanf("%d",&num);
	}
	else if(op=='N'||op=='n')
	{
		printf("Enter name to delete : ");
		scanf("%s",s);
		sll *dup=*ptr;
		printf("\n");
		while(dup)
		{
			if((strcmp(s,dup->name))==0)
			{
				++i;
				if(i>1)
					printf("%d %s %f\n",dup->rn,dup->name,dup->marks);
				if(i==1)
				{
					del=dup;
					num=dup->rn;
				}
			}
			dup=dup->next;
		}
		if(i==0)
		{
			printf("No matching names\n");
			return;
		}

		if(i>1)
		{
			printf("%d %s %f\n",del->rn,del->name,del->marks);
			printf("These all are similar named so ");
			goto k;
		}

	}
	else
	{
		printf("Choosen option is wrong, Re ");
		goto l;
	}
	del=*ptr;
	while(del)
	{
		if(del->rn==num)
		{
			f=0;
			if(*ptr==del)
				*ptr=del->next;
			else
				prev->next=del->next;
			free(del);
			printf("successfully deleted\n");
			break;
		}
		prev=del;
		del=del->next;
	}
	if(f)
		printf("no record found\n");

}
void stu_show(sll *ptr)
{
	if(ptr==0)
		printf("No students records found\n");
	while(ptr)
	{
		printf("%d %s %g\n",ptr->rn,ptr->name,ptr->marks);
		ptr=ptr->next;
	}
}
void edit_stud(sll **ptr)
{
	char op,s[20];
	int num,i=0;
	float m;
	sll *mod=0,*p;

	printf("Enter which record to search for modification\n");
	printf("R/r :to search a rollno\n");
	printf("N/n :to search Name\n");
	printf("P/p :percentage based\n");

	scanf(" %c",&op);
	op=op&~(1<<5);

	switch(op)
	{
		case 'R':
			printf("Enter student roll number to modify\n");
			scanf("%d",&num);

			p=*ptr;
			while(p)
			{
				if(p->rn==num)
				{
					mod=p;
					break;
				}
				p=p->next;
			}
			break;

		case 'N':
			printf("Enter name to search\n");
			scanf("%s",s);

			p=*ptr;
			while(p)
			{
				if(strcmp(p->name,s)==0)
				{
					printf("%d %s %f\n",p->rn,p->name,p->marks);
					mod=p;
					i++;
				}
				p=p->next;
			}
			if(i>1)
			{
				printf("Enter roll number : ");
				scanf("%d",&num);

				p=*ptr;
				mod=0;

				while(p)
				{
					if(p->rn==num)
					{
						mod=p;
						break;
					}
					p=p->next;
				}
			}
			break;

		case 'P':
			printf("Enter marks to search\n");
			scanf("%f",&m);

			p=*ptr;
			while(p)
			{
				if(p->marks==m)
				{
					printf("%d %s %f\n",p->rn,p->name,p->marks);
					mod=p;
					i++;
				}
				p=p->next;
			}

			if(i>1)
			{
				printf("Enter roll number : ");
				scanf("%d",&num);

				p=*ptr;
				mod=0;

				while(p)
				{
					if(p->rn==num)
					{
						mod=p;
						break;
					}
					p=p->next;
				}
			}
			break;

		default:
			printf("Entered wrong option\n");
			return;
	}

	if(mod==0)
	{
		printf("No records found as ur requirement\n");
		return;
	}

	printf("Enter new name : ");
	scanf("%s",mod->name);

	printf("Enter new marks : ");
	scanf("%f",&mod->marks);

	printf("Successfully modified\n");
}
void save(sll *ptr)
{
	FILE *fp=fopen("data","w");
		while(ptr)
		{
			fprintf(fp,"%d %s %f\n",ptr->rn,ptr->name,ptr->marks);
			ptr=ptr->next;
		}
		printf("\ndata saved successfully\n");
}
void exit_(sll *ptr)
{
	char op;
	printf("Enter\nS/s :Save and exit\nE/e :exit without saving\n");
	scanf(" %c",&op);
	op=op&~(1<<5);
	switch(op)
	{
		case 'S':{
				FILE *fp=fopen("data","w");
				while(ptr)
				{
					fprintf(fp,"%d %s %f\n",ptr->rn,ptr->name,ptr->marks);
					ptr=ptr->next;
				}
				printf("\ndata saved successfully\n");
				exit(0);
			 }break;
		case 'E' :exit(0);
	}
}
void sort_list(sll *ptr)
{
	sll *p=ptr,*p1,t;
	char op,c=count_students(ptr);
	printf("Enter\nR/R :sort with Roll number\nN/n :sort with name\nP/p :sort with percentage\n");
	scanf(" %c",&op);
	op=op&~(1<<5);
	for(int i=0;i<c-1;i++)
	{
		p1=p->next;
		for(int j=i+1;j<c;j++)
		{
			if( ((op=='N')&&(strcmp(p->name,p1->name))>0) || ((op=='P')&&(p->marks>p1->marks)) || ((op=='R')&&(p->rn>p1->rn)) )
			{
				t.rn=p->rn;
				strcpy(t.name,p->name);
				t.marks=p->marks;
				p->rn=p1->rn;
				strcpy(p->name,p1->name);
				p->marks=p1->marks;
				p1->rn=t.rn;
				strcpy(p1->name,t.name);
				p1->marks=t.marks;
			}
			p1=p1->next;
		}
		p=p->next;
	}
}
void stud_del_all(sll **ptr)
{
	sll *del=*ptr;
	while(del)
	{
		*ptr=(*ptr)->next;
		free(del);
		del=*ptr;
	}
	printf("All nodes are deleted\n");
}
void stud_rev(sll **ptr)
{
	rev=!rev;
	int i=0,c=count_students(*ptr);
	sll **arr=malloc(sizeof(sll *)*c);
	sll *p=*ptr;
	while(p)
	{
		arr[i++]=p;
		p=p->next;
	}
	for(i=c-1;i>0;i--)
		arr[i]->next=arr[i-1];
	arr[0]->next=0;
	*ptr=arr[c-1];
	printf("Completely Reversed the List\n");
}
void read_database(sll **ptr)
{
	FILE *fp=fopen("data","r");
	if(fp==NULL)
		return;
	while(1)
	{
		sll *new=malloc(sizeof(sll));
		new->next=0;
		if((fscanf(fp,"%d%s%f",&new->rn,new->name,&new->marks))==EOF)
			break;
		if(*ptr==0)
			*ptr=new;
		else
		{
			sll *last=*ptr;
			while(last->next)
				last=last->next;
			last->next=new;
		}
	}
	fclose(fp);

}
int count_students(sll *ptr)
{
	int c=0;
	for(;ptr;ptr=ptr->next,c++);
	return c;
}


