/*
 *  linux/kernel/who.c
 *
 *  (C) 2015 Zhiming Liu
 */

#define __LIBRARY__
#include <unistd.h>
#include <errno.h>
#include <asm/segment.h>
#include <linux/kernel.h>

#define BUFFERLENGTH 32
#define LENGTH 23

_syscall1(int, iam, const char*, name);		/* iam()在用户空间的接口函数 */
_syscall2(int, whoami,char*,name,unsigned int,size);	/* whoami()在用户空间的接口函数 */

char buffer[BUFFERLENGTH];

/*
* int iam(const char * name);
* 完成的功能是将字符串参数name的内容拷贝到内核中保存下来。
* 要求name的长度不能超过23个字符。返回值是拷贝的字符数。
* 如果name的字符个数超过了23，则返回“-1”，并置errno为EINVAL。
*/
int sys_iam(const char *name)
{
	int counts;
	int item;
	counts = 0;
	while((counts < BUFFERLENGTH) && (get_fs_byte(name + counts) != '\0'))
	{
		counts++;
	}

	if(item > LENGTH)
	{
		return -EINVAL;
	}

	item = 0;
	while(item <= counts)
	{
		buffer[item] = get_fs_byte(name + item);
		item++;
	}
	return counts;
}


/*
* int whoami(char* name, unsigned int size);
* 它将内核中由iam()保存的名字拷贝到name指向的用户地址空间中，
* 同时确保不会对name越界访存（name的大小由size说明）。
* 返回值是拷贝的字符数。
* 如果size小于需要的空间，则返回“-1”，并置errno为EINVAL。
*/
int sys_whoami(char *name, unsigned int size)
{
	int counts;
	int item;
	counts = 0;
	while((counts < BUFFERLENGTH) && (buffer[counts] != '\0'))
	{
		counts++;
	}
	if (counts > size)
	{
		return -EINVAL;
	}
	else
	{
		item = 0;
		while(item <= counts)
		{
			put_fs_byte(buffer[item], (name + item));
			item++;
		}
	}
	return counts;
}
