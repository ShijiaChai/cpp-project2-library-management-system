#include<iostream>
#include"HW2_lkd.h"
#include<ctime>
using namespace std;
int main()
{
	time_t tt=time(NULL);
	tm* t=localtime(&tt);
	srand(unsigned(time(NULL)));
	DATEYMD today(t->tm_year+1900,t->tm_mon+1,t->tm_mday),ddl(today);
	ddl.Add(100);
	Cursor.background();
	vector<BOOKIND> book;
	vector<ACCOUNT> user;
	if(READ(book,user))
		for(unsigned int i=0;i<user.size();i++)
			user[i].booked(book);
	else
		user.push_back(ACCOUNT(10000,"12345678",1));
	unsigned int id,ind;
	unsigned short kind(32767);
	char pass[50];
	while(kind==32767)
	{
		id=Cursor.numberscan(11,37);
		Cursor.strscan(15,37,pass,true);
		for(unsigned int i=0;i<user.size();i++)
			if(kind=user[i].pass(id,pass),kind!=32767)
			{
				ind=i;
				break;
			}
		if(kind==32767)
		{
			Cursor.Wrong("用户名不存在或密码不正确");
			Cursor.backgroun();
		}
	}
	if(kind)
	{
		unsigned int kind,id,idf,idt;
		unsigned short isbn[13];
		char password[60],name[60],publisher[60];
		bool flag,flag2,flag3;
		while(kind=Cursor.Teabackground(),kind!=6)
		{
			Cursor.cls();
			switch(kind)
			{
			case 0://借
				Cursor.Norprint(4,"请您输入：",12,0);
				Cursor.Norprint(11,"学生学号：",13,0,29);
				Cursor.Norprint(15,"13位ISBN：",13,0,29);
				id=Cursor.numberscan(11,39);
				Cursor.isbnscan(15,39,isbn);
				flag=true;
				for(unsigned int k,j,i=0;i<user.size();i++)
					if(user[i].testid(id))
					{
						flag=false;
						flag2=true;
						for(j=0;j<book.size();j++)
							if(book[j].echo(isbn))
							{
								flag2=false;
								if(!user[i].ok())
								{
									Cursor.Wrong("学生借书超过5本");
									break;
								}
								if(book[j].booked())
								{
									Cursor.Wrong("该图书已借空");
									break;
								}
								user[i].bor();
								for(k=0;k<book[j].n;k++)
									if(!book[j].time[k].booked())
									{
										book[j].time[k].set(ddl,id);
										break;
									}
								SAVE(book,user);
								Cursor.Rright();
								break;
							}
						if(flag2)
							Cursor.Wrong("未找到图书信息，ISBN输入有误");
						break;
					}
				if(flag)
					Cursor.Wrong("账户未开通（管理员帐号不能借书）");
				break;
			case 1://还
				Cursor.Norprint(4,"请您输入：",12,0);
				Cursor.Norprint(11,"学生学号：",15,0,29);
				Cursor.Norprint(15,"13位ISBN：",15,0,29);
				id=Cursor.numberscan(11,39);
				Cursor.isbnscan(15,39,isbn);
				flag=true;
				for(unsigned int k,j,i=0;i<user.size();i++)
					if(user[i].testid(id))
					{
						flag=false;
						flag2=true;
						for(j=0;j<book.size();j++)
							if(book[j].echo(isbn))
							{
								flag2=false;
								flag3=true;
								for(k=0;k<book[j].n;k++)
									if(book[j].time[k].BOR(id))
									{
										flag3=false;
										book[j].time[k].set(0,0,0,0);
										user[i].ret();
										SAVE(book,user);
										Cursor.Rright();
										break;
									}
								if(flag3)
									Cursor.Wrong("该同学未借阅过此书，请检查输入");
								break;
							}
							if(flag2)
							Cursor.Wrong("未找到图书信息，ISBN输入有误");
						break;
					}
				if(flag)
					Cursor.Wrong("账户未开通（管理员帐号不能借书）");
				break;
			case 2://加
				Cursor.Norprint(5,"请您输入：",9,0);
				Cursor.Norprint(9,"图书名称：",15,0,26);
				Cursor.Norprint(12," 出版社 ：",15,0,26);
				Cursor.Norprint(15,"图书作者：",15,0,26);
				Cursor.Norprint(18,"13位ISBN：",15,0,26);
				Cursor.Norprint(21,"图书个数：",15,0,26);
				Cursor.strscan(9,36,name);
				Cursor.strscan(12,36,publisher);
				Cursor.strscan(15,36,password);
				Cursor.isbnscan(18,36,isbn);
				id=Cursor.numberscan(21,36);
				flag=true;
				for(unsigned int i=0;i<book.size();i++)
					if(book[i].echo(isbn))
					{
						flag=false;
						break;
					}
				if(id==0)
				{
					Cursor.Wrong("本数不可为零");
					break;
				}
				if(flag)
				{
					book.push_back(BOOKIND(name,publisher,password,isbn,id));
					SAVE(book,user);
					Cursor.Rright();
				}
				else
					Cursor.Wrong("图书ISBN码冲突，请检查输入");
				break;
			case 3://看
				{
					char *s[2]={"   查看图书总量   ","   查看被借图书   "};
					unsigned char pos[2]={9,16};
					if(Cursor.Chose(2,'[',s,']',pos,14,11))
						Show2(book,today);
					else
						Show1(book);
				}
				break;
			case 4://人
				Cursor.Norprint(4,"请输入始末学号，并设置统一初始密码",10,0);
				Cursor.Norprint(6,"始末学号相同则会重设密码，否则已开通帐号密码不变",10,0);
				Cursor.Norprint(10,"起始学号：",15,0,29);
				Cursor.Norprint(13,"终止学号：",15,0,29);
				Cursor.Norprint(16,"设定密码：",15,0,29);
				Cursor.Norprint(19,"（0为学生，否则为管理员）账号类型：",15,0,4);
				idf=Cursor.numberscan(10,39);
				idt=Cursor.numberscan(13,39);
				Cursor.strscan(16,39,password);
				id=Cursor.numberscan(19,39);
				if(idf==0)
				{
					Cursor.Wrong("非法学号0");
					break;
				}
				if(idf==idt)
				{
					flag=true;
					for(unsigned int i=0;i<user.size();i++)
						if(user[i].echo(idf))
						{
							user[i].passwordize(password);
							flag=false;
							SAVE(book,user);
							Cursor.Rright();
							break;
						}
					if(flag)
						Cursor.Wrong("未开通帐号不能重置密码");
					break;
				}
				else
				{
					if(idf>idt)
					{
						Cursor.Wrong("起始学号不得小于中止学号");
						break;
					}
					for(unsigned int j,i=idf;i<=idt;i++)
					{
						flag=true;
						for(j=0;j<user.size();j++)
							if(user[j].echo(i))
							{
								flag=false;
								break;
							}
						if(flag)
							user.push_back(ACCOUNT(i,password,(unsigned short)id));
					}
					SAVE(book,user);
					Cursor.Rright();
				}
				break;
			case 5://password
				if(user[ind].recrypt())
				{
					SAVE(book,user);
					Cursor.Rright();
				}
				else
					Cursor.Wrong("密码不正确 或 新密码两次输入不一致");
				break;
			}
		}
	}
	else
	{
		unsigned short kind;
		while(kind=Cursor.Stubackground(),kind!=3)
		{
			Cursor.cls();
			switch(kind)
			{
			case 0:
				user[ind].own(book,today);
				break;
			case 1:
				if(user[ind].search(book,ddl,today))
				{
					SAVE(book,user);
					Cursor.Rright();
				}
				break;
			case 2:
				if(user[ind].recrypt())
				{
					SAVE(book,user);
					Cursor.Rright();
				}
				else
					Cursor.Wrong("密码不正确 或 新密码两次输入不一致");
				break;
			}
		}
	}
	Cursor.end();
	return 0;
}
