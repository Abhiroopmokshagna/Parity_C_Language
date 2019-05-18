#include<stdio.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>

struct msgbuf{
	long msgtype;
	int mbits[4][8];
	};

int main(){
	struct msgbuf buf;
	int msqid;
	int i,j;
	key_t key;
	key = ftok("2dshmfile",65);
	msqid = msgget(key,0644);
	msgrcv(msqid,&buf,32*sizeof(int),0,0);
	printf("The recieved message bits are: \n");
	for(j=0;j<4;j++){
		if(j==3)
			printf("The column parity bits are: \n");
		for(i=0;i<8;i++){
			printf("%d ",buf.mbits[j][i]);
		}
		printf("\n");
	}
	int count1 = 0,count2 = 0;
	int k,l;
	for(i=0;i<3;i++){
			for(j=0;j<7;j++){
				count1 = count1+buf.mbits[i][j];
			}
			if(count1%2==buf.mbits[i][7]){
				count1 = 0;continue;}
			else{
				for(k=0;k<7;k++){
					for(l=0;l<3;l++){
						count2 = count2+buf.mbits[l][k];
					}
					if(count2%2==buf.mbits[3][k])
						{count2 = 0;continue;}
					else{
						printf("\n{{{There seems to be an error in row: %d column: %d !}}}",i,k);
						printf("\n{{{flipping the bit at %d:%d}}}",i,k);
						if(buf.mbits[i][k]==1)
							buf.mbits[i][k]=0;
						else
							buf.mbits[i][k]=1;
					}
					count2 = 0;
				}
			}
		count1 = 0;
		}
	printf("\n");
for(j=0;j<4;j++){
                if(j==3)
                        printf("The column parity bits are: \n");
                for(i=0;i<8;i++){
                        printf("%d ",buf.mbits[j][i]);
                }
                printf("\n");
        }

	return 0;
}

