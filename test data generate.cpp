#include<iostream>
#include<cstdio>
using namespace std;
const char ENCRYPT[18]={21,101,-9,88,-115,-59,121,-116,-69,46,-67,73,52,-109,89,-75,48,-6};
void strWrite(FILE *fout,char *str)
{
	unsigned int n(strlen(str)+1);
	for(unsigned int i=0;i<n;i++)
		str[i]^=ENCRYPT[i%18];
	fwrite(str,n,1,fout);
	for(unsigned int i=0;i<n;i++)
		str[i]^=ENCRYPT[i%18];
	return;
}
int main()
{
	FILE *fin(fopen("list.txt","r"));
	if(fin==NULL)
		return 0;
	FILE *fout(fopen("HW2.dat","wb"));
	unsigned int book_n,user_n,user,n;
	char author[100],name[100],publisher[100],c;
	unsigned short isbn[13],year,month,day,top;
	fscanf(fin,"%u%u",&book_n,&user_n);
	fwrite(&book_n,4,1,fout);
	fwrite(&user_n,4,1,fout);
	for(unsigned int j,i=0;i<book_n;i++)
	{
		top=0;
		fscanf(fin,"%s",author);
		fscanf(fin,"%s",name);
		fscanf(fin,"%s",publisher);
		do
		{
			fscanf(fin,"%c",&c);
			if(c>='0'&&c<='9')
				isbn[top++]=c-'0';
		}while(top!=13);
		fscanf(fin,"%u",&n);
		strWrite(fout,author);
		strWrite(fout,name);
		strWrite(fout,publisher);
		fwrite(isbn,26,1,fout);
		fwrite(&n,4,1,fout);
		for(j=0;j<n;j++)
		{
			fscanf(fin,"%hu%hu%hu%u",&year,&month,&day,&user);
			cout<<user<<endl;
			fwrite(&year,2,1,fout);
			fwrite(&month,2,1,fout);
			fwrite(&day,2,1,fout);
			fwrite(&user,4,1,fout);
		}
	}
	for(unsigned int i=0;i<user_n;i++)
	{
		fscanf(fin,"%u",&user);
		fscanf(fin,"%s",name);;
		fscanf(fin,"%hu",&day);
		fwrite(&user,4,1,fout);
		strWrite(fout,name);
		fwrite(&day,2,1,fout);
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
