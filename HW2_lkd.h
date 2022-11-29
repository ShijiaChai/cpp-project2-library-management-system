#include<cstring>
#include<vector>
#include<algorithm>
#include"Cursor_lkd.h"
using namespace std;
class figure
{
	virtual bool booked()=0;
};
class ACCOUNT;
class BOOKIND;
class DATEYMD
{
	friend void SAVE(vector<BOOKIND>&,vector<ACCOUNT>&);
	friend class TIME;
public:
	DATEYMD(unsigned short year=0,unsigned short month=0,unsigned short day=0):year(year),month(month),day(day)
	{
		return;
	}
	DATEYMD(const DATEYMD &p):year(p.year),month(p.month),day(p.day)
	{
		return;
	}
	~DATEYMD()
	{
		return;
	}
	bool dateisgood()
	{
		if(isleapyear(year)&&month==2)
			return year<2200&&year>1900&&day<30&&day>0;
		else
			return year<2200&&year>1900&&month<13&&month>0&&day<=MONTH[month-1]&&day>0;
	}
	bool operator<(const DATEYMD &p)
	{
		return year==p.year?(month==p.month?(day<p.day):month<p.month):year<p.year;
	}
	int operator-(const DATEYMD &p)
	{
		int ans(0);
		for(unsigned short i=1;i<month;i++)
			if(i==2&&isleapyear(year))
				ans+=29;
			else
				ans+=MONTH[i-1];
		ans+=day-1;
		for(unsigned short i=1;i<p.month;i++)
			if(i==2&&isleapyear(p.year))
				ans-=29;
			else
				ans-=MONTH[i-1];
		ans-=p.day-1;
		if(year<p.year)
			for(unsigned short i=year;i<p.year;i++)
				if(isleapyear(i))
					ans-=366;
				else
					ans-=365;
		else
			for(unsigned short i=p.year;i<year;i++)
				if(isleapyear(i))
					ans+=366;
				else
					ans+=365;
		return ans;
	}
	const DATEYMD& operator=(const DATEYMD &p)
	{
		year=p.year;
		month=p.month;
		day=p.day;
		return *this;
	}
	void Add(int days)
	{
		while(days>0)
		{
			if(month!=2||!isleapyear(year))
			{
				while(days>0&&day<=MONTH[month-1])
				{
					day++;
					days--;
				}
				if(day>MONTH[month-1])
				{
					month++;
					day=1;
				}
				if(month>12)
				{
					year++;
					month=1;
				}
			}
			else
			{
				while(days>0&&day<=29)
				{
					day++;
					days--;
				}
				if(day>29)
				{
					month++;
					day=1;
				}
			}
		}
		return;
	}
	void Print()
	{
		printf("%hu年%hu月%hu日",year,month,day);
		return;
	}
protected:
	unsigned short year,month,day;
	static unsigned short MONTH[12];
	static bool isleapyear(unsigned short year)
	{
		return (year%4==0&&year%100)||year%400==0;
	}
};
unsigned short DATEYMD::MONTH[12]={31,28,31,30,31,30,31,31,30,31,30,31};
class TIME:public DATEYMD,public figure
{
	friend void SAVE(vector<BOOKIND>&,vector<ACCOUNT>&);
	friend class ACCOUNT;
	friend void match(vector<BOOKIND>&,char[],vector<BOOKIND>&);
	friend void Show2(vector<BOOKIND>&,DATEYMD&);
public:
	TIME(unsigned int Stu_id=0):Stu_id(Stu_id)
	{
		return;
	}
	TIME(const TIME &p):DATEYMD(p),Stu_id(p.Stu_id)
	{
		return;
	}
	~TIME()
	{
		return;
	}
	bool BOR(unsigned int id)
	{
		return Stu_id==id;
	}
	bool booked()
	{
		return Stu_id!=0;
	}
	void set(unsigned short _year,unsigned short _month,unsigned short _day,unsigned int _Stu_id)
	{
		year=_year;
		month=_month;
		day=_day;
		Stu_id=_Stu_id;
		return;
	}
	void set(const DATEYMD &p,unsigned int _Stu_id)
	{
		year=p.year;
		month=p.month;
		day=p.day;
		Stu_id=_Stu_id;
		return;
	}
	const TIME& operator=(const TIME &p)
	{
		year=p.year;
		month=p.month;
		day=p.day;
		Stu_id=p.Stu_id;
		return *this;
	}
protected:
	unsigned int Stu_id;
};
class BOOK
{
	friend void match(vector<BOOKIND>&,char[],vector<BOOKIND>&);
	friend void Show1(vector<BOOKIND>&);
	friend void Show2(vector<BOOKIND>&,DATEYMD&);
public:
	BOOK(char *Name,char *Publisher,char *Author,unsigned short Isbn[]):name(new char[strlen(Name)+1]),publisher(new char[strlen(Publisher)+1]),author(new char[strlen(Author)+1])
	{
		strcpy(name,Name);
		strcpy(publisher,Publisher);
		strcpy(author,Author);
		for(short i=0;i<13;i++)
			isbn[i]=Isbn[i];
		return;
	}
	BOOK(const BOOK &p):name(new char[strlen(p.name)+1]),publisher(new char[strlen(p.publisher)+1]),author(new char[strlen(p.author)+1])
	{
		strcpy(name,p.name);
		strcpy(publisher,p.publisher);
		strcpy(author,p.author);
		for(short i=0;i<13;i++)
			isbn[i]=p.isbn[i];
		return;
	}
	~BOOK()
	{
		delete[] name;
		delete[] publisher;
		delete[] author;
		return;
	}
	bool echo(unsigned short *Isbn)
	{
		bool flag(true);
		for(short i=0;i<13;i++)
			if(Isbn[i]!=isbn[i])
			{
				flag=false;
				break;
			}
		return flag;
	}
	bool echo(const BOOK &p)
	{
		bool flag(true);
		for(short i=0;i<13;i++)
			if(p.isbn[i]!=isbn[i])
			{
				flag=false;
				break;
			}
		return flag;
	}
protected:
	char *name,*publisher,*author;
	unsigned short isbn[13]; //新版ISBN为13位，旧版10位ISBN可以对应到唯一的新版13位
};
class BOOKIND:public BOOK,public figure
{
	friend class ACCOUNT;
	friend void SAVE(vector<BOOKIND>&,vector<ACCOUNT>&);
public:
	BOOKIND(char *name,char *publisher,char *author,unsigned short isbn[],unsigned int n):BOOK(name,publisher,author,isbn),n(n),time(new TIME[n])
	{
		return;
	}
	BOOKIND(const BOOKIND &p):BOOK(p),n(p.n),time(new TIME[p.n]),_match(p._match)
	{
		for(unsigned int i=0;i<n;i++)
			if(p.time[i].booked())
				time[i]=p.time[i];
		return;
	}
	~BOOKIND()
	{
		delete[] time;
		return;
	}
	const BOOKIND& operator=(const BOOKIND &p)
	{
		n=p.n;
		TIME *t(new TIME[n]);
		for(unsigned int i=0;i<n;i++)
			t[i]=p.time[i];
		delete[] time;
		time=t;
		char *_name(new char[strlen(p.name)+1]),*_publisher(new char[strlen(p.publisher)+1]),*_author(new char[strlen(p.author)+1]);
		strcpy(_name,p.name);
		strcpy(_publisher,p.publisher);
		strcpy(_author,p.author);
		delete[] name;
		delete[] publisher;
		delete[] author;
		name=_name;
		publisher=_publisher;
		author=_author;
		_match=p._match;
		for(unsigned short i=0;i<13;i++)
			isbn[i]=p.isbn[i];
		return *this;
	}
	bool booked() //借空了为真
	{
		bool flag(true);
		for(unsigned int i=0;i<n;i++)
			if(!time[i].booked())
			{
				flag=false;
				break;
			}
		return flag;
	}
	int nearestday(DATEYMD today)
	{
		DATEYMD Min(3000,0,0);
		for(unsigned int i=0;i<n;i++)
			if(time[i]<Min)
				Min=time[i];
		return Min-today<100&&Min-today>0?Min-today:100;
	}
	unsigned short N()
	{
		unsigned short ans(n);
		for(unsigned int i=0;i<n;i++)
			if(time[i].booked())
				ans--;
		return ans;
	}
	bool operator<(const BOOKIND &p)
	{
		return _match>p._match;
	}
	TIME *time;
	unsigned int n;
	int _match;
};
void match(vector<BOOKIND> &book,char keyword[],vector<BOOKIND> &list)
{
	bool flag;
	unsigned short mapflag[256]={0};
	unsigned int len(strlen(keyword));
	if(len==1)
		for(unsigned int k,j,i=0;i<book.size();i++)
		{
			flag=true;
			for(j=0;j<strlen(book[i].name)&&flag;j++)
			for(k=0;k<len;k++)
				if(book[i].name[j]==keyword[k])
				{
					list.push_back(book[i]);
					flag=false;
					break;
				}
		}
	else
		for(unsigned int k,j,i=0;i<book.size();i++)
		{
			flag=true;
			for(j=0;j+1<strlen(book[i].name)&&flag;j++)
			for(k=0;k+1<len;k++)
				if(book[i].name[j]==keyword[k]&&book[i].name[j+1]==keyword[k+1])
				{
					list.push_back(book[i]);
					flag=false;
					break;
				}
		}
	for(unsigned int i=0;i<len;i++)
		mapflag[keyword[i]<0?127-keyword[i]:keyword[i]]++;
	for(unsigned int j,i=0;i<list.size();i++)
	{
		list[i]._match=-strlen(list[i].name)*8/15;
		flag=false;
		for(j=0;j<strlen(list[i].name);j++)
			if(mapflag[list[i].name[j]<0?127-list[i].name[j]:list[i].name[j]])
			{
				if(flag)
					list[i]._match++;
				list[i]._match+=mapflag[list[i].name[j]<0?127-list[i].name[j]:list[i].name[j]];
				flag=true;
			}
			else
				flag=false;
	}
	sort(list.begin(),list.end());
	return;
}
class ACCOUNT
{
	friend void SAVE(vector<BOOKIND>&,vector<ACCOUNT>&);
public:
	ACCOUNT(unsigned int user,char *pass,unsigned short kind):user(user),password(new char[strlen(pass)+1]),num(0),kind(kind==0?0:1)
	{
		strcpy(password,pass);
		return;
	}
	ACCOUNT(const ACCOUNT &p):user(p.user),password(new char[strlen(p.password)+1]),num(0),kind(p.kind)
	{
		strcpy(password,p.password);
		return;
	}
	~ACCOUNT()
	{
		delete[] password;
		return;
	}
	void booked(vector<BOOKIND> &book)
	{
		for(unsigned int j,i=0;i<book.size();i++)
			for(j=0;j<book[i].n;j++)
				if(book[i].time[j].Stu_id==user)
					num++;
		return;
	}
	unsigned short pass(unsigned int _user,char *_password)
	{
		if(user==_user&&strcmp(password,_password)==0)
			return kind;
		else
			return 32767;
	}
	bool testid(unsigned int id)
	{
		return id==user&&kind==0;
	}
	bool ok()
	{
		return num<5;
	}
	void bor()
	{
		num++;
		return;
	}
	void ret()
	{
		num--;
		return;
	}
	void passwordize(char str[])
	{
		delete[] password;
		password=new char[strlen(str)+1];
		strcpy(password,str);
		return;
	}
	bool echo(unsigned int id)
	{
		return id==user;
	}
	bool recrypt()
	{
		Cursor.Norprint(5,"请输入：",14,0);
		Cursor.Norprint(9,"原密码：",15,0,22);
		Cursor.Norprint(13,"新密码：",15,0,22);
		Cursor.Norprint(17,"确定新密码：",15,0,18);
		char p1[60],p2[60],p3[60];
		Cursor.strscan(9,30,p1,true);
		Cursor.strscan(13,30,p2,true);
		Cursor.strscan(17,30,p3,true);
		if(strcmp(p1,password)==0&&strcmp(p2,p3)==0)
		{
			if(strlen(p2)==0)
				return false;
			passwordize(p2);
			return true;
		}
		return false;
	}
	void own(vector<BOOKIND> &book,DATEYMD &today)
	{
		if(num==0)
		{
			Cursor.Norprint(7,"当前无借书",14,0);
			Cursor.Norprint(16,"按任意键返回到菜单. . .",8,0);
			getch();
			return;
		}
		Cursor.Norprint(3,"正在借阅图书有：",10,0);
		Cursor.Norprint(6,"图书名称        作者     出版社       ISBN码         还书底线        天数",15,0);
		unsigned short top(0);
		for(unsigned int j,i=0;i<book.size();i++)
			for(j=0;j<book[i].n;j++)
				if(book[i].time[j].Stu_id==user)
				{
					Cursor.Lenprint(8+3*top,book[i].name,7,0,14,3);
					Cursor.Lenprint(8+3*top,book[i].author,7,0,8,19);
					Cursor.Lenprint(8+3*top,book[i].publisher,7,0,12,28);
					Cursor.isbnprint(8+3*top,41,book[i].isbn);
					printf("%s","  ");
					book[i].time[j].Print();
					if(today<book[i].time[j])
					{
						Cursor.Norprint(8+3*top,"还有",7,0,71);
						Cursor.Norprint(8+3*top,(unsigned int)(book[i].time[j]-today),15,0,75);
						Cursor.Norprint(8+3*top,"天",7,0,78);
					}
					else
						Cursor.Norprint(8+3*top,"过期速还",12,0,71);
					top++;
				}
		Cursor.Norprint(8+3*top,"按任意键返回到菜单. . .",8,0);
		getch();
		return;
	}
	bool search(vector<BOOKIND> &book,DATEYMD &ddl,DATEYMD &today)
	{
		char keyword[60],c('w');
		Cursor.Norprint(2,"欢迎使用检索方式自助借书，按Esc退出",14,0);
		Cursor.Norprint(4,"关键词：",15,0,29);
		Cursor.strscan(4,37,keyword);
		vector<BOOKIND> list;
		match(book,keyword,list);
		if(list.size()==0)
		{
			Cursor.Wrong("未找到有关匹配图书");
			return false;
		}
		unsigned int x(0),Page(list.size()%7?list.size()/7+1:list.size()/7),page(0);
		Cursor.Norprint(6,"图书名称",15,0,4);
		Cursor.Norprint(6,"作者",15,0,27);
		Cursor.Norprint(6,"出版社",15,0,36);
		Cursor.Norprint(6,"ISBN码",15,0,51);
		Cursor.Norprint(6,"剩余本数",15,0,62);
		Cursor.Norprint(6,"最短天数",15,0,71);
		Cursor.Norprint(22,"Page:    /",15,0,32);
		Cursor.Norprint(22,page+1,10,0,38);
		Cursor.Norprint(22,Page,10,0,43);
		while(c!=27)
		{
			if(c=='w'||c=='W'||c=='s'||c=='S'||c==' '||c==13||c==10||c==8)
				for(unsigned int i=0;page==Page-1?(list.size()%7?i<list.size()%7:i<7):i<7;i++)
					if(i==x)
					{
						Cursor.Norprint(8+2*i,"→",15,0,1);
						Cursor.Lenprint(8+2*i,list[i+page*7].name,11,0,22,4);
						Cursor.Lenprint(8+2*i,list[i+page*7].author,11,0,8,27);
						Cursor.Lenprint(8+2*i,list[i+page*7].publisher,11,0,14,36);
						Cursor.isbnprint(8+2*i,51,list[i+page*7].isbn,11);
						if(list[i+page*7].N())
						{
							Cursor.Norprint(8+2*i,list[i+page*7].N(),11,0,66);
							Cursor.Norprint(8+2*i,"-",11,0,74);
						}
						else
						{
							Cursor.Norprint(8+2*i,list[i+page*7].N(),12,0,66);
							Cursor.Norprint(8+2*i,(unsigned short)list[i+page*7].nearestday(today),11,0,74);
						}
					}
					else
					{
						Cursor.Norprint(8+2*i,"  ",7,0,1);
						Cursor.Lenprint(8+2*i,list[i+page*7].name,7,0,22,4);
						Cursor.Lenprint(8+2*i,list[i+page*7].author,7,0,8,27);
						Cursor.Lenprint(8+2*i,list[i+page*7].publisher,7,0,14,36);
						Cursor.isbnprint(8+2*i,51,list[i+page*7].isbn);
						if(list[i+page*7].N())
						{
							Cursor.Norprint(8+2*i,list[i+page*7].N(),7,0,66);
							Cursor.Norprint(8+2*i,"-",7,0,74);
						}
						else
						{
							Cursor.Norprint(8+2*i,list[i+page*7].N(),4,0,66);
							Cursor.Norprint(8+2*i,(unsigned short)list[i+page*7].nearestday(today),7,0,74);
						}
					}
				c=getch();
				if(c=='w'||c=='W')
					if(x)
						x--;
					else
						if(page>0)
						{
							page--;
							x=6;
							Cursor.cls2();
							Cursor.Norprint(22,"Page:    /",15,0,32);
							Cursor.Norprint(22,page+1,10,0,38);
							Cursor.Norprint(22,Page,10,0,43);
						}
				if(c=='s'||c=='S')
					if(page==Page-1?(list.size()%7?x+1!=list.size()%7:x!=6):x!=6)
						x++;
					else
						if(page!=Page-1)
						{
							page++;
							x=0;
							Cursor.cls2();
							Cursor.Norprint(22,"Page:    /",15,0,32);
							Cursor.Norprint(22,page+1,10,0,38);
							Cursor.Norprint(22,Page,10,0,43);
						}
				if(c==' '||c==13||c==10||c==8)
					if(list[x+page*7].N())
					{
						Cursor.cls();
						Cursor.Norprint(3,"确定要借阅这本书吗？",10,0);
						Cursor.Norprint(5,"可借阅100天，成功后直接到前台领取",10,0);
						Cursor.Norprint(9,"名称：",15,0,30);
						Cursor.Norprint(12,"作者：",15,0,30);
						Cursor.Norprint(15,"出版社：",15,0,28);
						Cursor.Norprint(18,"ISBN：",15,0,30);
						Cursor.Norprint(9,list[x+page*7].name,7,0,36);
						Cursor.Norprint(12,list[x+page*7].author,7,0,36);
						Cursor.Norprint(15,list[x+page*7].publisher,7,0,36);
						Cursor.isbnprint(18,36,list[x+page*7].isbn);
						if(Cursor.confirm(21,9,13))
						{
							if(num>=5)
							{
								Cursor.Wrong("最多保有5本借书，请先还书");
								return false;
							}
							num++;
							for(unsigned int j,i=0;i<book.size();i++)
								if(book[i].echo(list[x+page*7].isbn))
								{
									for(j=0;j<book[i].n;j++)
										if(!book[i].time[j].booked())
										{
											book[i].time[j].set(ddl,user);
											break;
										}
									break;
								}
							return true;
						}
						else
						{
							Cursor.cls();
							Cursor.Norprint(2,"欢迎使用检索方式自助借书，按Esc退出",14,0);
							Cursor.Norprint(4,"关键词：",15,0,29);
							Cursor.Norprint(4,keyword,7,0,37);
							Cursor.Norprint(6,"图书名称",15,0,4);
							Cursor.Norprint(6,"作者",15,0,27);
							Cursor.Norprint(6,"出版社",15,0,36);
							Cursor.Norprint(6,"ISBN码",15,0,51);
							Cursor.Norprint(6,"剩余本数",15,0,62);
							Cursor.Norprint(6,"最短天数",15,0,71);
							Cursor.Norprint(22,"Page:    /",15,0,32);
							Cursor.Norprint(22,page+1,10,0,38);
							Cursor.Norprint(22,Page,10,0,43);
						}
					}
					else
						Cursor.sound('W');
		}
		return false;
	}
protected:
	unsigned int user,num;
	unsigned short kind;// 0是学生，1是管理员
	char *password;
};
const char ENCRYPT[18]={21,101,-9,88,-115,-59,121,-116,-69,46,-67,73,52,-109,89,-75,48,-6};
void strRead(FILE *fin,char *str)
{
	unsigned int top(0);
	char c;
	do
	{
		fread(&c,1,1,fin);
		c^=ENCRYPT[top%18];
		str[top++]=c;
	}while(c!='\0');
	return;
}
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
bool READ(vector<BOOKIND> &book,vector<ACCOUNT> &user)
{
	bool flag(false);
	FILE *fin(fopen("HW2.dat","rb"));
	if(fin!=NULL)
	{
		unsigned int book_n,user_n,n,Stu_id;
		unsigned short isbn[13],top,year,month,day;
		char author[100],name[100],publisher[100];
		fread(&book_n,4,1,fin);
		fread(&user_n,4,1,fin);
		for(unsigned int j,i=0;i<book_n;i++)
		{
			strRead(fin,author);
			strRead(fin,name);
			strRead(fin,publisher);
			fread(isbn,26,1,fin);
			fread(&n,4,1,fin);
			book.push_back(BOOKIND(name,publisher,author,isbn,n));
			for(j=0;j<n;j++)
			{
				fread(&year,2,1,fin);
				fread(&month,2,1,fin);
				fread(&day,2,1,fin);
				fread(&Stu_id,4,1,fin);
				book[i].time[j].set(year,month,day,Stu_id);
			}
		}
		for(unsigned int i=0;i<user_n;i++)
		{
			fread(&Stu_id,4,1,fin);
			strRead(fin,name);
			fread(&top,2,1,fin);
			user.push_back(ACCOUNT(Stu_id,name,top));
		}
		flag=true;
		fclose(fin);
	}
	return flag;
}

void SAVE(vector<BOOKIND> &book,vector<ACCOUNT> &user)
{
	FILE *fout(fopen("HW2.dat","wb"));
	if(fout!=NULL)
	{
		unsigned int book_n(book.size()),user_n(user.size());
		fwrite(&book_n,4,1,fout);
		fwrite(&user_n,4,1,fout);
		for(unsigned int j,i=0;i<book_n;i++)
		{
			strWrite(fout,book[i].author);
			strWrite(fout,book[i].name);
			strWrite(fout,book[i].publisher);
			fwrite(book[i].isbn,26,1,fout);
			fwrite(&book[i].n,4,1,fout);
			for(j=0;j<book[i].n;j++)
			{
				fwrite(&book[i].time[j].year,2,1,fout);
				fwrite(&book[i].time[j].month,2,1,fout);
				fwrite(&book[i].time[j].day,2,1,fout);
				fwrite(&book[i].time[j].Stu_id,4,1,fout);
			}
		}
		for(unsigned int i=0;i<user_n;i++)
		{
			fwrite(&user[i].user,4,1,fout);
			strWrite(fout,user[i].password);
			fwrite(&user[i].kind,2,1,fout);
		}
		fclose(fout);
	}
	return;
}
void Show1(vector<BOOKIND> &book)
{
	Cursor.cls();
	unsigned int Page(book.size()%7?book.size()/7+1:book.size()/7),page(0);
	Cursor.Norprint(2,"按Esc键退出",14,0);
	Cursor.Norprint(4,"图书名称",15,0,2);
	Cursor.Norprint(4,"作者",15,0,31);
	Cursor.Norprint(4,"出版社",15,0,42);
	Cursor.Norprint(4,"ISBN码",15,0,59);
	Cursor.Norprint(4,"本数",15,0,74);
	do
	{
		Cursor.cls3();
		Cursor.Norprint(20,"Page:    /",15,0,32);
		Cursor.Norprint(20,page+1,11,0,38);
		Cursor.Norprint(20,Page,11,0,43);
		Cursor.Norprint(22,"按任意键翻页. . . ",8,0);
		for(unsigned int i=0;page==Page-1?(book.size()%7?i<book.size()%7:i<7):i<7;i++)
		{
			Cursor.Lenprint(6+2*i,book[i+page*7].name,7,0,28,2);
			Cursor.Lenprint(6+2*i,book[i+page*7].author,7,0,10,31);
			Cursor.Lenprint(6+2*i,book[i+page*7].publisher,7,0,16,42);
			Cursor.isbnprint(6+2*i,59,book[i+page*7].isbn);
			Cursor.Norprint(6+2*i,book[i+page*7].n,7,0,75);		
		}
		page++;
	}while(getch()!=27&&page<Page);
	return;
}
void Show2(vector<BOOKIND> &list,DATEYMD &today)
{
	Cursor.cls();
	vector<BOOKIND> book;
	for(unsigned int j,i=0;i<list.size();i++)
	for(j=0;j<list[i].n;j++)
		if(list[i].time[j].booked())
		{
			book.push_back(BOOKIND(list[i].name,list[i].publisher,list[i].author,list[i].isbn,1));
			book[book.size()-1].time[0]=list[i].time[j];
		}
	unsigned int Page(book.size()%7?book.size()/7+1:book.size()/7),page(0);
	Cursor.Norprint(2,"按Esc键退出",14,0);
	Cursor.Norprint(4,"图书名称",15,0,1);
	Cursor.Norprint(4,"作者",15,0,26);
	Cursor.Norprint(4,"出版社",15,0,35);
	Cursor.Norprint(4,"ISBN码",15,0,50);
	Cursor.Norprint(4,"学生学号",15,0,65);
	Cursor.Norprint(4,"天数",15,0,76);
	do
	{
		Cursor.cls3();
		Cursor.Norprint(20,"Page:    /",15,0,32);
		Cursor.Norprint(20,page+1,11,0,38);
		Cursor.Norprint(20,Page,11,0,43);
		Cursor.Norprint(22,"按任意键翻页. . . ",8,0);
		for(unsigned int i=0;page==Page-1?(book.size()%7?i<book.size()%7:i<7):i<7;i++)
		{
			Cursor.Lenprint(6+2*i,book[i+page*7].name,7,0,24,1);
			Cursor.Lenprint(6+2*i,book[i+page*7].author,7,0,8,26);
			Cursor.Lenprint(6+2*i,book[i+page*7].publisher,7,0,14,35);
			Cursor.isbnprint(6+2*i,50,book[i+page*7].isbn);
			Cursor.Norprint(6+2*i,book[i+page*7].time[0].Stu_id,7,0,65);
			if(today<book[i+page*7].time[0])
				Cursor.Norprint(6+2*i,(unsigned short)(book[i+page*7].time[0]-today),7,0,76);
			else
				Cursor.Norprint(6+2*i,"过期",4,0,76);
		}
		page++;
	}while(getch()!=27&&page<Page);
	return;
}