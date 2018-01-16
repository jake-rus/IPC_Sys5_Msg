/*
 * proc1.c
 *	Работа с очередью сообщений IPC SysV
 *  Created on: 16 янв. 2018 г.
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
	memset(msg.mtext, 0, 256); // очистка массива
	msg.mtype=5L;// создание сообщения
	strcpy(msg.mtext, "Hello, proc2!\n");
	// создание очереди
	ipckey = ftok("/home/jake/123.txt",'A');
	msgid = msgget(ipckey,IPC_CREAT | 0666);
	// отправка первого сообщения
	msgsnd(msgid,&msg,256,0);

	msgrcv(msgid,&msg,256,-6L,0);
	printf("string input %s\n",msg.mtext);

	return 0;
}
