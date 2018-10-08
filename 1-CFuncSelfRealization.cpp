#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cassert>

#include <limits.h>

using namespace std;

//1.实现 strcpy
char * MyStrCpy(char* dst, const char * src){
	char * cp = dst;
	while (*cp++ = *src++); /* Copy src over dst */
	return(dst);
}

//2.实现strcat
char * MyStrCat(char * dst, const char * src){

	char *temp = dst;
	while (*dst++);
	dst--;
	while (*dst++ = *src++);
	return temp;
}

//3.strcmp
int MyStrCmp(const char * s1, const char *s2){
	for (; *s1 && *s2 && *s1 == *s2; s1++, s2++);
	return *s1 - *s2;
}

//4.MyString
class MyString{
	MyString(const char * str = nullptr){
		if (str == nullptr){
			pmStr = new char[1];
			assert(pmStr != nullptr);
			pmStr = '\0';
		}
		else{
			pmStr = new char[strlen(str) + 1];
			strcpy(pmStr, str);
		}
	}

	~MyString(){
		if (pmStr != nullptr){
			delete[] pmStr;
			pmStr = NULL;
		}
	}

	MyString(const MyString & another){
		pmStr = new char[strlen(another.pmStr) + 1];
		strcpy(pmStr, another.pmStr);
	}

	const MyString & operator=(const MyString & another){
		if (this == &another)
			return *this;
		delete[] pmStr;
		pmStr = new char[strlen(another.pmStr) + 1];
		strcpy(pmStr, another.pmStr);
		return *this;
	}

private:
	char * pmStr;
};

//5. swap
void SwapA(int &a, int &b){
	if (a == b)
		return;
	a = a + b;
	b = a - b;
	a = a - b;
}

void SwapB(int &a, int &b){
	if (a == b)
		return;
	a ^= b;
	b ^= a;
	a ^= b;
}

//6.atoi
int MyAtoi(const char * str){
	int s = 0;
	bool falg = false;

	while (*str == ' ')
		str++;  //去掉左空格

	if (*str == '-' || *str == '+'){
		if (*str == '-')
			falg = true;
		str++; //提取正负号
	}

	while (*str >= '0'&&*str <= '9')
	{
		s = s * 10 + *str - '0';
		str++;
		if (s < 0)  //什么时候会有这种情况？？？
		{
			s = 2147483647;
			break;
		}
	}

	return s*(falg ? -1 : 1);
}

//7.字符串逆序
char * rev(char *p){
	int len = strlen(p);
	char T;
	for (int i = 0; i < len / 2; i++){
		T = p[i];
		p[i] = p[len - i - 1];
		p[len - i - 1] = T;
	}
	return p;
}

//8.loecase->upcase
char * MyUpper(char * src){
	while (*src){
		if (*src <'a' || *src >'z'){
			src++;
			continue;
		}
		else{
			*src -= 32/*'a' - 'A'*/;  //二者皆可
			src++;
		}
	}
	return src;
}

//9.在【降序排列】的数组中查找某一数值的索引
int findIndex(int * src, int count, int value){
	int left = 0;
	int right = count - 1;
	int mid = 0;
	while (left <= right){
		mid = (left + right) / 2;
		if (src[mid] > value)
			right = mid - 1;
		else if (src[mid] < value)
			left = mid + 1;
		else
			return mid;
	}
	return -1;
}

struct Node{  //所示代码的头尾均不存储数据
	int data;
	struct Node * next;
};

//10.删除链表中值为value的所有节点(这个是)
void deleteValue(Node * head, int value){
	Node *prev = head;
	Node *next = head->next;
	while (next != nullptr){
		if (next->data != value){
			prev = next;
			next = next->next;
		}
		else{
			prev->next = next->next;
			delete next;
			next = prev->next;
		}
	}
}

//11.在链表index的位置插入新的值为 value 的元素
void insertFromList(Node * head, int index, int value){
	Node * next = head->next;
	for (int i = 0; i < index && next != nullptr; ++i, next = next->next);
	Node *newNode;
	newNode->data = value;
	newNode->next = next->next;
	next->next = newNode;
}

//12.将链表逆序
Node* reverseList(Node *head){
	Node * prev = head;
	Node * next = head->next;
	Node * nextnext = nullptr;
	while (next != nullptr){
		nextnext = next->next;
		next->next = prev;
		prev = next;
		next = nextnext;
	}
	head->next = nullptr;
	return prev;
}

//13.判断X年X月X日是这年的第几天
int getDay(int year, int month, int day){
	int monthDay[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (year % 4 == 0 && year % 400 == 0 || year % 400 == 0)
		monthDay[2]++;
	int DAYS = 0;
	for (int i = 1; i < month; i++)
		DAYS += monthDay[i];
	DAYS += day;
	return DAYS;
}

//14.斐波拉契数列
int getFibonacci1(int N){
	if (N == 1 || N == 2)
		return 1;
	if (N == 3)
		return 2;
	if (N == 4)
		return 3;

	int A = 2;
	int B = 3;
	int C = 5;

	for (int i = 0; i < N - 4; ++i){
		C = A + B;
		A = B;
		B = C;
	}

	return C;
}

//15.递归求斐波拉契那波
int getFibonacii2(int N){
	if (N == 1 || N == 2)
		return 1;
	return getFibonacii2(N - 1) + getFibonacii2(N - 2);
}

//16.不考虑内存重叠的strncpy
char *strncpy(char *dest, const char *src, size_t len)
{
	assert(dest != NULL && src != NULL);
	char *res = dest;
	int offset = 0;
	if (strlen(src) < len)//src长度小于len
	{
		offset = len - strlen(src);
		len = strlen(src);
	}

	while (len--)
	{
		*dest++ = *src++;
	}
	while (offset--)
	{
		*dest++ = '\0';
	}
	return res;
}

//17.考虑内存重叠的strncpy
char *MyStrncpy(char *dst, const char *src, size_t len)
{
	assert(dst != NULL && src != NULL);
	char *res = dst;
	int offset = 0;
	char *tmp;
	if (strlen(src) < len)//src长度小于len
	{
		offset = len - strlen(src);
		len = strlen(src);
	}

	if (dst >= src && dst <= src + len - 1)//重叠,从后向前复制
	{
		dst = dst + len - 1;
		src = src + len - 1;
		tmp = dst;
		while (len--)
			*dst-- = *src--;
	}
	else
	{
		while (len--)
			*dst++ = *src++;
		tmp = dst;
	}
	while (offset--)
	{
		*tmp++ = '\0';
	}
	return res;
}

//18.itoa

//19.如何判断链表有环
bool isLoop(const Node * head){
	Node * next = head->next;
	Node * nextnext = head->next;
	while (next != nullptr && nextnext != nullptr){
		next = next->next;
		nextnext = next->next->next;
		if (next == nextnext)
			return true;
	}
	return false;
}

//20.统计一个字符串每种字母出现的次数，要求复杂度为 O(n)
void countLetter(const char * src){
	int count[256] = {};
	for (; *src != '\0'; ++src){
		const char &c = *src;
		if ((c <'A' || c>'Z') && (c<'a' || c>'z'))
			continue;
		++count[c];
	}
}

//21.选择排序
//22.冒泡排序
//23.找到数组中第二大的数字
int findSecond(const int * arr, int N){
	int maxv = arr[0];
	int secv = arr[0];
	for (int i = 0; i < N; i++){
		if (maxv < arr[i]){
			secv = maxv;
			maxv = arr[i];
		}
	}
	return secv;
}



int main1(void)
{
	char a[100] = "neverland_ly"; cout << a << endl;
	char b[100] = "neverland_ly"; cout << b << endl;

	//1. strcpy
	strcpy(a, "cleverland"); cout << a << endl;
	MyStrCpy(b, "cleverland"); cout << b << endl;

	//2.strccat
	strcat(a, "strcat"); cout << a << endl;
	MyStrCat(b, "strcat"); cout << b << endl;

	//3.strcmp
	cout << strcmp("abc", "abc") << endl;
	cout << MyStrCmp("abc", "abc") << endl;

	//4.MyString

	//5.swap
	int x = 1; int y = 2;
	SwapA(x, y); cout << x << y << endl;
	SwapB(x, y); cout << x << y << endl;

	//6. atoi
	cout << atoi("123abc") << endl;
	cout << MyAtoi("123abc") << endl;

	//7.翻转字符串
	char z[100] = "123456789";
	cout << rev(z) << endl;

	//8.转为大写字母
	char u[10] = "aBcDeF"; cout << u << endl;
	MyUpper(u); cout << u << endl;

	//9.查找指定字符的索引
	int m[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	cout << findIndex(m, 9, 5) << endl;

	//10.删除链表某个节点
	//11.删除指定元素的节点
	//12.链表翻转

	//13.年月日是第几天
	cout << getDay(2018, 1, 1) << endl;

	//14.返回斐波那契数列
	cout << getFibonacci1(6) << endl;

	//15.
	//16.
	//17.

	//18.



	cout << "hello world" << endl;

	return 0;
}

int main(void){
	int i = 2;
	int num = 0;
	num = (++i) + (++i) + (++i) + (++i);

	cout << num << endl;

	cout << "hello world" << endl;
}
