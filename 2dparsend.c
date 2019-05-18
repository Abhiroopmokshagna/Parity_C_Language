#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<time.h>

struct msgbuf{
long msgtype;
int mbits[4][8];
};

int main(){
	struct msgbuf buf;
	int msqid;
	int len;
	char ch[3];
	key_t key;
	key = ftok("2dshmfile",65);
	msqid = msgget(key,0644|IPC_CREAT);
	buf.msgtype = 1;
	printf("Enter a string of 3 characters: ");
	scanf("%s",&ch);
	for(int j=0;j<3;j++){
	int asc = ch[j];
	printf("\n%d \n",asc);
	int i;
	int temp = 1;
	int count = 0;
	for(i=0;i<7;i++){
			if(asc&temp){
				buf.mbits[j][i]=1;
				count=count+1;
			}
			else
				buf.mbits[j][i]=0;
			temp = temp<<1;
		}

//setting parity bit......
//	printf("\n%d",count);
	if(count%2==0)
		buf.mbits[j][7] = 0;
	else
		buf.mbits[j][7] = 1;
//printing actual binary of character......

	for(i=0;i<8;i++){
		printf("%d ",buf.mbits[j][i]);
	}
count = 0;
}
int colcount = 0;
	for(int k=0;k<8;k++){
		for(int s=0;s<3;s++){
			colcount = colcount+buf.mbits[s][k];
		       }
		buf.mbits[3][k]=colcount%2;
		colcount = 0;
		}
//printing the coloumn parity bits.......
	printf("\ncolumn parity bits:\n");
for(int k=0;k<8;k++){
	printf("%d ",buf.mbits[3][k]);
}
//flipping (or leaving) a random bit.....
srand(time(0));
int randomize = rand()%2;
int fliprow = rand()%3;
int flipcol = rand()%7;
if(randomize ==1){
if(buf.mbits[fliprow][flipcol])
buf.mbits[fliprow][flipcol]=0;
else
buf.mbits[fliprow][flipcol]=1;
}
//sending message..........
	msgsnd(msqid,&buf,32*sizeof(int),0);
	printf("\ncharacters sent to reciever....\n");
	return 0;
}

