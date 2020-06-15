/**
 *Ï£¶ûÅÅĞòËã·¨
 * */
void shellSort(int *a,int length)
{
	int i,j;
	int dt=length;
	do
	{
		dt=dt/3+1;
		for(i=0+dt;i<length;i++)
		{
			if(a[i]<a[i-dt])
			{
				int temp=a[i];
				for(j=i-dt;(temp<a[j])&&(j>=0);j=j-dt)
				{
					a[j+dt]=a[j];
				}
				a[j+dt]=temp;
			}
		}
	}while(dt>1);
}

void arrayTraversal(int *a,int length)
{
	int i;
	for(i=0;i<length;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}

void main()
{
	int a[7]={5,4,3,2,1,7,6};
	shellSort(a,7);
	arrayTraversal(a,7);

	int b[5]={5,3,4,6,2};
	shellSort(b,5);
	arrayTraversal(b,5);
}

