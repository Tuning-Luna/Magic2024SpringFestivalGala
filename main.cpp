#include<iostream>
#include<list>
#include<algorithm>
#include<ctime>
using namespace std;

//展示卡牌信息
void printCards(list<char>& c)
{
	cout << "从上到下卡牌依次为：" << endl;
	for (auto it = c.begin(); it != c.end(); ++it)
		cout << *it << " ";
	cout << endl;
	system("pause");
	system("cls");
}

//展示卡牌信息的重载版本，没有提示和暂停
void printCards(list<char>& c, int)
{
	for (auto it = c.begin(); it != c.end(); ++it)
		cout << *it << " ";
}

//把最上面的卡牌移动到最下面
void moveCards(list<char>& c)
{
	char temp = c.front();
	c.pop_front();
	c.push_back(temp);
}

//折叠撕碎卡牌
void foldCards(list<char>& c)
{
	char c1, c2, c3, c4;
	list<char>::iterator it = c.begin();
	c1 = *it;
	++it;
	c2 = *it;
	++it;
	c3 = *it;
	++it;
	c4 = *it;

	c.push_back(c1);
	c.push_back(c2);
	c.push_back(c3);
	c.push_back(c4);
}

//初始化卡牌
void setCards(list<char>& c)
{
	cout << "请输入插入的牌(每输入一次回车一次或者以空格区分)：" << endl
		<< "最好不要选择重复的，避免偶然性" << endl
		<< "[A 2 3 4 5 6 7 8 9 10 J Q K]" << endl;

	int cnt = 4;//选择四张牌
	while (cnt--)
	{
		char ch{};
		cin >> ch;
		cout << ch << "已记录,请继续输入" << endl;
		c.push_back(ch);
	}
	system("cls");
	printCards(c);

	foldCards(c);
	cout << "折叠卡牌后：" << endl;
	printCards(c);
}

//根据名字长度放置卡片
void moveCardsByName(list<char>& c)
{
	int n = 0;
	cout << "输入名字长度（2-4）：";
	cin >> n;
	cout << "依次把上面的" << n << "张牌放到下面去" << endl;
	while (n--)
	{
		moveCards(c);
	}
	printCards(c);
}

//把牌顶的三张牌放到中间任意位置
void moveCardsMiddleRandom(list<char>& c)
{
	cout << "把牌顶的三张牌放到中间任意位置" << endl;
	int idx = rand() % 4 + 4;//4-7
	list<char>::iterator it = c.begin();
	list<char>::iterator it2 = c.begin();
	advance(it, idx);//移动坐标
	for(int i=0;i<3;++i)
	{
		c.insert(it, *it2);//pos elem
		++it2;
	}
	for (int i = 0; i < 3; ++i)
		c.pop_front();
	printCards(c);
}

//把顶部的牌藏起来
void hideTopCards(list<char>& c, char& a)
{
	cout << "把顶部的牌藏起来：" << c.front() << endl;
	a = c.front();
	c.pop_front();
	printCards(c);
}

//根据区域放牌
void moveCardsByRegion(list<char>& c)
{
	cout << "选择区域：" << endl
		<< "1--南方" << endl
		<< "2--北方" << endl
		<< "3--不知道" << endl;
	int n;
	cin >> n;
	cout << "把" << n << "张牌随机放中间后：" << endl;
	int idx = (rand() % (6 - n)) + n + 1;
	list<char>::iterator it = c.begin();
	list<char>::iterator it2 = c.begin();
	advance(it, idx);
	for (int i = 0; i < n; ++i)
	{
		c.insert(it, *it2);//pos elem
		++it2;
	}
	for (int i = 0; i < n; ++i)
		c.pop_front();
	printCards(c);
}

//根据性别扔牌
void removeCardsBySex(list<char>& c)
{
	cout << "选择性别：" << endl
		<< "1--男生" << endl
		<< "2--女生" << endl;
	int n;
	cin >> n;
	cout << "扔掉上面的" << n << "张牌" << endl;
	while (n--)
		c.pop_front();
	printCards(c);
}

//把顶部的牌移动至底部，执行7次
void moveCards7Times(list<char>& c)
{
	cout << "见 证 奇 迹 的 时 刻" << endl;
	cout << "把顶部的牌移动至底部，执行7次后" << endl;
	int n = 7;
	while (n--)
		moveCards(c);
	printCards(c);
}

//把牌顶的牌移动到末尾，再移除一张牌，直到只剩一张牌
char moveAndRemoveCardsTill1(list<char>& c)
{
	cout << "把牌顶的牌移动到末尾，再移除一张牌，直到只剩一张牌" << endl;
	while (c.size() != 1)
	{
		cout << "好运留下来：" << c.front();
		moveCards(c);
		cout << "     当前的牌：";
		printCards(c, 1);
		cout << endl;
		cout << "烦恼丢出去：" << c.front();
		c.pop_front();
		cout << "     当前的牌：";
		printCards(c, 1);
		cout << endl;
	}
	return c.front();
}

int main()
{
	list<char>cards;
	srand((unsigned int)time(NULL));

	//设置&&初始化
	setCards(cards);

	//名字几个字就往下放几张
	moveCardsByName(cards);

	//把牌顶的三张牌放到中间任意位置
	moveCardsMiddleRandom(cards);

	//把顶部的牌藏起来
	char top;
	hideTopCards(cards, top);

	//根据地域差异把1-3张牌放中间
	moveCardsByRegion(cards);

	//根据性别扔牌
	removeCardsBySex(cards);

	//把顶部的牌移动至底部，执行7次
	moveCards7Times(cards);

	//把牌顶的牌移动到末尾，再移除一张牌，直到只剩一张牌
	char c = moveAndRemoveCardsTill1(cards);

	cout << "剩下的一张牌：" << c << endl;
	cout << "藏起来的牌：" << top << endl;

	if (c == top)
		cout << "魔术成功!" << endl;
	return 0;
}
