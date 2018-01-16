/*
 * proc2.c
 *	Работа с очередью сообщений IPC SysV
 *  Created on: 16.01.2018
 *      Author: jake
 */

#include <sys/types.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int main(void)
{
	key_t ipckey;
	int msgid;
	struct {
		long mtype;
		char mtext[256];
	} msg;
	memset(msg.mtext, 0, 256); /* Clear out the space */;

	ipckey = ftok("/home/jake/123.txt",'A');//генерация ключа
	msgid = msgget(ipckey,0); //присоединение к очереди

	msgrcv(msgid,&msg,256,-5L,0);//получение сообщения
	
	msg.mtype=6L;//создание ответного сообщения
	strcat(msg.mtext, "Hello, proc1!\n");

	msgsnd(msgid,&msg,256,0);//отправка ответного сообщения

	return 0;
}
