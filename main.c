#include "header.h"
int main()
{
	sll *head=0;
	read_database(&head);
	char op;
	while(1)
	{
		printf("\na/A :add new record\nd/D :delete record\ns/s :show list\nm/M :modify record\nv/V :save\ne/E :exit\nt/T :sort the list\nl/L :delete all the records\nr/R :reverse the list\nc/C :Count Students\nEnter Your Choise :\n");
		scanf(" %c",&op);
		op=op&~(1<<5);
		//system("clear");
		switch(op)
		{
			case 'A':stud_add(&head);break;
			case 'D':stud_del(&head);break;
			case 'S':stu_show(head);break;
			case 'M':edit_stud(&head);break;
			case 'V':save(head);break;
			case 'E':exit_(head);
			case 'T':sort_list(head);break;
			case 'L':stud_del_all(&head);break;
			case 'R':stud_rev(&head);break;
			case 'C':printf("\n%d students are there\n",count_students(head));break;
			default :printf("please choose correct option\n");
		}
	}
	return 0;
}
