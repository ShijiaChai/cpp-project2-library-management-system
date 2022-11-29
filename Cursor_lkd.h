#include<Windows.h>
#include<conio.h>
#include<ctime>
#include<cstring>
class
{
public:
	static void cls(unsigned char S=0)
	{
		gotoxy(0,0);
		setcolor(7,S);
		printf("%s","                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ");
		gotoxy(0,0);
		return;
	}
	static void cls2()
	{
		gotoxy(0,7);
		setcolor();
		printf("%s","                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ");
		gotoxy(0,0);
		return;
	}
	static void cls3()
	{
		gotoxy(0,5);
		setcolor();
		printf("%s","                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ");
		gotoxy(0,0);
		return;
	}
	static void end()
	{
		cls();
		Norprint(9,"刘奎达设计",15,0);
		Norprint(10,"感谢使用，谢谢",15,0);
		Sleep(1600);
		unsigned char X,Y,S;
		for(unsigned short  j,i=0;i<400;i++)
		{
			for(j=0;i<150?j<i/50:j<i/10;j++)
			{
				do
				{
					X=rand()%80;
					Y=rand()%25;
				}while(X==79&&Y==24);
				S=rand()%15+1;
				gotoxy(X,Y);
				setcolor(7,S);
				printf("%c",' ');
			}
			Sleep(7);
		}
		for(unsigned short  i=0;i<rand()%8+8;i++)
		{
			S=rand()%15+1;
			cls(S);
			Sleep(rand()%250+85);
		}
		cls();
		clock_t cl(clock());
		char str[16]="将在5.2秒后退出";
		while(clock()-cl<=5200)
		{
			str[4]=(5200+cl-clock())/1000%10+48;
			str[6]=(5200+cl-clock())/100%10+48;
			Norprint(10,str,15,0);
		}
		return;
	}
	static void setcolor(unsigned char foreground=7,unsigned char background=0)
	{
		HANDLE hOut(GetStdHandle(STD_OUTPUT_HANDLE));
		SetConsoleTextAttribute(hOut,foreground+background*16);
		return;
	}
	static void sound(char c)
	{
		switch(c)
		{
		case 'R':
			Beep(323,250);
			Beep(384,350);
			break;
		case 'W':
			Beep(575,280);
			Beep(512,250);
			break;
		case ' ':
			Beep(323,350);
			break;
		}
		return;
	}
	static bool confirm(unsigned char y,unsigned char foreground,unsigned char background)
	{
		char c(0);
		bool ans(true);
		while(c!=13&&c!=32)
		{
			if(ans)
			{
				gotoxy(23,y);
				setcolor(background,0);
				printf("%c",'<');
				setcolor(0,background);
				printf("%s","确认");
				setcolor(background,0);
				printf("%c",'>');
				gotoxy(50,y);
				setcolor(foreground,0);
				printf("%s"," 取消 ");
			}
			else
			{
				gotoxy(23,y);
				setcolor(foreground,0);
				printf("%s"," 确认 ");
				gotoxy(50,y);
				setcolor(background,0);
				printf("%c",'<');
				setcolor(0,background);
				printf("%s","取消");
				setcolor(background,0);
				printf("%c",'>');
			}
			c=getch();
			if(c=='a'||c=='A')
				ans=true;
			if(c=='d'||c=='D')
				ans=false;
			if(c==8)
				ans=!ans;
		}
		return ans;
	}
	static void Norprint(unsigned char y,char *s,unsigned char foreground,unsigned char background,unsigned char x=0)
	{
		if(x==0)
			gotoxy((80-strlen(s))/2,y);
		else
			gotoxy(x,y);
		setcolor(foreground,background);
		printf("%s",s);
		welldone();
		return;
	}
	static void Norprint(unsigned char y,unsigned short s,unsigned char foreground,unsigned char background,unsigned char x=0)
	{
		if(x==0)
			gotoxy((80-6)/2,y);
		else
			gotoxy(x,y);
		setcolor(foreground,background);
		printf("%hu",s);
		welldone();
		return;
	}
	static void Norprint(unsigned char y,unsigned int s,unsigned char foreground,unsigned char background,unsigned char x=0)
	{
		if(x==0)
			gotoxy((80-6)/2,y);
		else
			gotoxy(x,y);
		setcolor(foreground,background);
		printf("%u",s);
		welldone();
		return;
	}
	static void Norprint(unsigned char y,double s,unsigned char foreground,unsigned char background,unsigned char x=0)
	{
		if(x==0)
			gotoxy((80-6)/2,y);
		else
			gotoxy(x,y);
		setcolor(foreground,background);
		printf("%.3lf",s);
		welldone();
		return;
	}
	static void Chosenprint(unsigned char y,char L,char *s,char R,unsigned char foreground,unsigned char background)
	{
		gotoxy((80-strlen(s))/2-1,y);
		setcolor(background,0);
		printf("%c",L);
		setcolor(foreground,background);
		printf("%s",s);
		setcolor(background,0);
		printf("%c",R);
		welldone();
		return;
	}
	static unsigned char Chose(unsigned char n,char L,char *s[],char R,unsigned char pos[],unsigned char foreground,unsigned char background,bool Esc=false)
	{
		char c(0);
		unsigned char ans(0);
		while(c!=13&&c!=8&&c!=32)
		{
			for(unsigned char i=0;i<n;i++)
				if(i==ans)
					if(background>8)
						Chosenprint(pos[i],L,s[i],R,0,background);
					else
						Chosenprint(pos[i],L,s[i],R,15,background);
				else
					Chosenprint(pos[i],' ',s[i],' ',foreground,0);
			c=getch();
			if(c=='w'||c=='W')
				if(ans)
					ans--;
				else if(Esc)
					return 99;
			if(c=='s'||c=='S')
				if(ans!=n-1)
					ans++;
				else if(Esc)
					return 100;
			if(c==27&&Esc)
			{
				ans=127;
				break;
			}
		}
		sound(' ');
		return ans;
	}
	static void scan(unsigned char y,unsigned char len,char *s,bool secrecy=false)
	{//8_Backspace 13_Enter 32_space
		gotoxy((80-len)/2,y);
		setcolor();
		char c(0),i(0);
		while(c!=13)
		{
			if(i==len)
				cursor_reveal(false);
			else
				cursor_reveal(true);
			c=getch();
			if(c==8)
			{
				if(i)
				{
					gotoxy((80-len)/2+i-1,y);
					printf("%c",' ');
					gotoxy((80-len)/2+i-1,y);
					i--;
				}
				continue;
			}
			if(c==13)
			{
				s[i++]='\0';
				break;
			}
			if(i!=len)
			{
				s[i++]=c;
				if(secrecy)
					printf("%c",'*');
				else
					printf("%c",c);
			}
		}
		/*for(char i=0;i<len;i++)
		{
			
			s[i]=Waitscanchar();
			if(s[i]==8)
			{
				if(i==0)
				{
					i--;
					continue;
				}
				X=(80-len)/2+i-1;
				Y=y;
				gotoxy();
				printf("%c",' ');
				X=(80-len)/2+i-1;
				Y=y;
				gotoxy();
				i-=2;
				continue;
			}
			if(s[i]==13)
			{
				s[i]='\0';
				break;
			}
			if(secrecy)
				printf("%c",'*');
			else
				printf("%c",s[i]);
		}*/
		s[len]='\0';
		welldone();
		return;
	}
	static void isbnscan(unsigned char y,unsigned char x,unsigned short isbn[])
	{
		gotoxy(x,y);
		setcolor();
		char c(0),i(0);
		cursor_reveal(true);
		while((c!=13&&c!=10)||i!=13)
		{
			c=getch();
			if(c==8)
			{
				if(i)
				{
					gotoxy(x+i-1,y);
					printf("%c",' ');
					gotoxy(x+i---1,y);
				}
				continue;
			}
			if(c>='0'&&c<='9'&&i<13)
			{	
				isbn[i++]=c-'0';
				printf("%c",c);
			}
		}
		cursor_reveal(false);
		return;
	}
	static unsigned int numberscan(unsigned char y,unsigned char x,bool secrecy=false)
	{
		gotoxy(x,y);
		setcolor();
		char c(0),i(0);
		unsigned long long ans(0);
		cursor_reveal(true);
		while(c!=13&&c!=10)
		{
			c=getch();
			if(c==8)
			{
				if(i)
				{
					gotoxy(x+i-1,y);
					printf("%c",' ');
					gotoxy(x+i---1,y);
					ans/=10;
				}
				continue;
			}
			if(c>='0'&&c<='9')
			{
				
				ans*=10;
				ans+=c-'0';
				if(ans>4294967295u)
				{
					ans/=10;
					continue;
				}
				if(secrecy)
					printf("%c",'*');
				else
					printf("%c",c);
				i++;
			}
		}
		cursor_reveal(false);
		return (unsigned int)ans;
	}
	static void strscan(unsigned char y,unsigned x,char *str,bool secrecy=false)
	{
		gotoxy(x,y);
		setcolor();
		char c(0),i(0);
		cursor_reveal(true);
		while(c!=13&&c!=10)
		{
			c=getch();
			if(c==8)
			{
				if(i)
				{
					gotoxy(x+i-1,y);
					printf("%c",' ');
					gotoxy(x+i---1,y);
				}
				continue;
			}
			if(c!=13&&c!=10&&i<40)
			{
				if(i<50)
					str[i++]=c;
				if(secrecy)
					printf("%c",'*');
				else
					printf("%c",c);
			}
		}
		str[i]='\0';
		cursor_reveal(false);
		return;
	}
	static void background()
	{
		for(short i=0;i<80;i++)
		{
			setcolor(i%8+7,0);
			gotoxy(i,0);
			printf("%c",3);
			setcolor((i+24)%8+7,0);
			gotoxy(i,24);
			printf("%c",3);
		}
		for(short i=0;i<24;i++)
		{
			setcolor(i%8+7,0);
			gotoxy(0,i);
			printf("%c",3);
			setcolor((79+i)%8+7,0);
			gotoxy(79,i);
			printf("%c",3);
		}
		Norprint(4,"图书管理系统",13,0);
		Norprint(8,"轻松管理",10,0);
		Norprint(10,"简单借阅",10,0);
		char str[5]={1,' ',' ',' ','\0'};
		Norprint(13,str,14,0);
		Norprint(16,"  任意键点击进入登录. . .",8,0);
		Norprint(19,"  Designed. by.",14,0);
		Norprint(20,"  Queta. Liu. ",14,0);
		Norprint(21,"chaishijia设计",14,0);
		clock_t cl(clock());
		bool flag(true);
		while(!kbhit())
			if(clock()-cl>341)
				if(flag)
				{
					str[0]=1;
					str[3]=' ';
					Norprint(13,str,14,0);
					flag=false;
					cl=clock();
				}
				else
				{
					str[0]=' ';
					str[3]=1;
					Norprint(13,str,14,0);
					flag=true;
					cl=clock();
				}
		sound(' ');
		for(short i=0;i<80;i++)
		{
			setcolor(7,rand()%8+7);
			gotoxy(79-i,0);
			printf("%c",' ');
			setcolor(7,rand()%8+7);
			gotoxy(i,24);
			printf("%c",' ');
			Sleep(1);
		}
		for(short i=0;i<24;i++)
		{
			setcolor(7,rand()%8+7);
			gotoxy(79,24-i);
			printf("%c",' ');
			setcolor(7,rand()%8+7);
			gotoxy(0,i);
			printf("%c",' ');
			Sleep(1);
		}
		setcolor(7,13);
		for(short i=0;i<80;i++)
		{
			gotoxy(i,0);
			printf("%c",' ');
			gotoxy(i,24);
			printf("%c",' ');
		}
		for(short i=0;i<24;i++)
		{
			gotoxy(79,i);
			printf("%c",' ');
			gotoxy(0,i);
			printf("%c",' ');
		}
		Sleep(350);
		setcolor(7,14);
		for(short i=0;i<80;i++)
		{
			gotoxy(i,0);
			printf("%c",' ');
			gotoxy(i,24);
			printf("%c",' ');
		}
		for(short i=0;i<24;i++)
		{
			gotoxy(79,i);
			printf("%c",' ');
			gotoxy(0,i);
			printf("%c",' ');
		}
		Sleep(300);
		setcolor(7,10);
		for(short i=0;i<80;i++)
		{
			gotoxy(i,0);
			printf("%c",' ');
			gotoxy(i,24);
			printf("%c",' ');
		}
		for(short i=0;i<24;i++)
		{
			gotoxy(79,i);
			printf("%c",' ');
			gotoxy(0,i);
			printf("%c",' ');
		}
		Sleep(250);
		cls();
		Norprint(4,"欢迎您登录",10,0);
		Norprint(6,"请您输入",13,0);
		Norprint(11,"帐号：",15,0,31);
		Norprint(15,"密码：",15,0,31);
		setcolor(7,11);
		for(short i=0;i<80;i++)
		{
			gotoxy(i,0);
			printf("%c",' ');
			gotoxy(i,24);
			printf("%c",' ');
		}
		for(short i=0;i<24;i++)
		{
			gotoxy(79,i);
			printf("%c",' ');
			gotoxy(0,i);
			printf("%c",' ');
		}
		return;
	}
	static void backgroun()
	{
		cls();
		Norprint(4,"欢迎您登录",10,0);
		Norprint(6,"请您输入",13,0);
		Norprint(11,"帐号：",15,0,31);
		Norprint(15,"密码：",15,0,31);
		setcolor(7,11);
		for(short i=0;i<80;i++)
		{
			gotoxy(i,0);
			printf("%c",' ');
			gotoxy(i,24);
			printf("%c",' ');
		}
		for(short i=0;i<24;i++)
		{
			gotoxy(79,i);
			printf("%c",' ');
			gotoxy(0,i);
			printf("%c",' ');
		}
		return;
	}
	static void Wrong(char *str)
	{
		cls();
		Norprint(9,"操作失败",12,0);
		Norprint(11,"×",12,0);
		Norprint(14,str,12,0);
		sound('W');
		Sleep(2100);
		return;
	}
	static void Rright()
	{
		cls();
		Norprint(9,"操作成功",10,0);
		Norprint(11,"√",10,0);
		sound('R');
		Sleep(1500);
		return;
	}
	static unsigned char Teabackground()
	{
		cls();
		setcolor(0,9);
		for(short i=0;i<80;i++)
		{
			gotoxy(i,0);
			printf("%c",' ');
			gotoxy(i,24);
			printf("%c",' ');
		}
		for(short i=0;i<24;i++)
		{
			gotoxy(79,i);
			printf("%c",' ');
			gotoxy(0,i);
			printf("%c",' ');
		}
		Norprint(4,"欢迎，尊敬的图书管理员",14,0);
		Norprint(6,"请您选择：",14,0);
		char *s[7]={"     手 动 借 书     ","     手 动 还 书     ","     增 添 图 书     ","     查 看 图 书     ","     启 封 帐 号     ","     修 改 密 码     ","     退 出 系 统     "};
		unsigned char pos[7]={9,11,13,15,17,19,21};
		return Chose(7,4,s,4,pos,13,11);
	}
	static unsigned char Stubackground()
	{
		cls();
		setcolor(0,14);
		for(short i=0;i<80;i++)
		{
			gotoxy(i,0);
			printf("%c",' ');
			gotoxy(i,24);
			printf("%c",' ');
		}
		for(short i=0;i<24;i++)
		{
			gotoxy(79,i);
			printf("%c",' ');
			gotoxy(0,i);
			printf("%c",' ');
		}
		Norprint(4,"欢迎，同学你好",13,0);
		Norprint(6,"请选择：",13,0);
		char *s[4]={"      查 看 借 阅 图 书      ","      自 助 搜 索 借 书      ","      修 改 个 人 密 码      ","      退   出   登   陆      "};
		unsigned char pos[4]={10,13,16,19};
		return Chose(4,'<',s,'>',pos,9,11);
	}
	static void Lenprint(unsigned char y,char *s,unsigned char foreground,unsigned char background,unsigned int len,unsigned char x)
	{
		gotoxy(x,y);
		setcolor(foreground,background);
		if(strlen(s)>len)
		{
			for(unsigned int i=0;i+2<len;i++)
				printf("%c",s[i]);
			printf("%s","…");
		}
		else
			printf("%s",s);
		welldone();
		return;
	}
	static void isbnprint(unsigned char y,unsigned char x,unsigned short isbn[],unsigned char foreground=7,unsigned background=0)
	{
		gotoxy(x,y);
		setcolor(foreground,background);
		for(unsigned short i=0;i<13;i++)
			printf("%hu",isbn[i]);
		return;
	}
private:
	static void welldone()
	{
		setcolor(7,0);
		gotoxy(0,0);
		cursor_reveal(false);
		return;
	}
	static void cursor_reveal(bool flag)
	{
		HANDLE hOut(GetStdHandle(STD_OUTPUT_HANDLE));
		CONSOLE_CURSOR_INFO cci;
		GetConsoleCursorInfo(hOut,&cci);
		cci.bVisible=flag;
		SetConsoleCursorInfo(hOut,&cci);
		return;
	}
	static void gotoxy(unsigned short x,unsigned short y)
	{
		HANDLE hOut(GetStdHandle(STD_OUTPUT_HANDLE));
		COORD pos;
		pos.X=x;
		pos.Y=y;
		SetConsoleCursorPosition(hOut,pos);
		return;
	}
}Cursor;
