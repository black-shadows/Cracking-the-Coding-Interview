/*
 *Q5.6 Write a program to swap odd and even bits in an integer with as few insttuctions as possible
 *(e.g.,bit 0 and bit 1 are swapped,bit 2 and bit 3 are swapped,etc)
 */

#include <iostream>
#include <string>
using namespace std;

void print_binary(int x)
{
	string s = "";
	for (int i = 0; i < 32 && x != 0; ++i, x >>= 1)
	{
		if (x & 1) s = "1" + s;
		else s = "0" + s;
	}
	cout << s << endl;
}

//下面的代码思路和作用都是一样的，不过按照《Hacker’s delight》这本书里的说法， 第一种方法避免了在一个寄存器中生成两个大常量。
//如果计算机没有与非指令， 将导致第二种方法多使用1个指令。总结之，就是第一种方法更好。

int swap_bits(int x)
{
	return ((x & 0x55555555) << 1) | ((x>>1)&0x55555555);
}

//x & 0xAAAAAAAA得出结果是unsigned，所以最高位为1时，右移1位，最高位是0

int swap_bits1(int x)
{
	return((x&0x55555555)<<1)|((x&0xAAAAAAAA)>>1);
}
int main()
{
	int x = 0xFFFFFFFF;
	x = x & 0xFFFFFFFF;
	cout << (x & 0xFFFFFFFF) << endl;
	print_binary((x|0xFFFFFFFF)>>1);
	print_binary(x);
	print_binary(swap_bits(x));
	print_binary(swap_bits1(x));
	return 0;
}
