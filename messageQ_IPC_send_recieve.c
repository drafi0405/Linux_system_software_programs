#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/msg.h>
typedef struct message{
    long msg_type;
    char msg_text[100];
}message;
void sendmsg(int msgid){
    message smsg;
    smsg.msg_type=1;
    strcpy(smsg.msg_text,"hello world!");
    if(msgsnd(msgid,&smsg,sizeof(smsg.msg_text),0)==-1){
        perror("sending msg failed\n");
        exit(1);
    }
    printf("message send %s by child processor %d\n",smsg.msg_text,getpid());
}
void recievemsg(int msgid){
    message rmsg;
    if(msgrcv(msgid, &rmsg, sizeof(rmsg.msg_text),1,0)==-1){
        perror("recieve message failed\n");
        exit(1);
    }
    printf("recieved message %s by parent processor %d\n",rmsg.msg_text,getpid());
}
int main()
{
    key_t key = ftok("profile",65);
    int msgid = msgget(key, 0666|IPC_CREAT);
    if(fork()==0){
        sendmsg(msgid);
    }else{
        sleep(1);
        recievemsg(msgid);
        msgctl(msgid,IPC_RMID,NULL);
    }
    return 0;
}