#include "linkc_network_protocol.h"

char	buf[1024];
int	type = 0;	// check后的返回值
int	flag = 0;	// 是否还有数据没有读取完
int	size = 0;	// 接收到数据的长度

int Recv(int sockfd, void *buffer, size_t len, int flag)
{
	if(flag == 1)
	{
		type = ckeck_message(buf,size);
		if(type == MESSAGE_INCOMPLETE){
			while(1){
				size += recv(sockfd,buf+size,STD_PACKAGE_SIZE,0);
				type = ckeck_message(buf,size);
				if(type < 0)
					return -1;
				else if(type == LINKC_SUCCESS)
					break;
				else if(type == 1);
			}
		}
		if(type == LINKC_SUCCESS){
			flag = 0;	// 设置成没有数据
			unpack_message(buf, size, buffer);
			return type;
		}
		else if(type == NOT_MESSAGE)
			fprintf(stderr,"[Warning]\tNOT DATA!\n");
		else if(type == EXCEED_THE_LIMIT)
			fprintf(stderr,"[Warning]\tData's Lenth beyond the LIMIT!\n");
		else if(type == DIFF_VERSION)
			fprintf(stderr,"[Warning]\tVersion of the protocol is NOT THE SAME!\n");
		return -1;		// 返回出错
	}
//	recv(sockfd,)
	return size;
}