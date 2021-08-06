#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

using namespace std;

/*
 * udp：面向数据报，无连接
 * 客户端的实现逻辑:
 *  1. 创建套接字：
 *      a.首先要指定地址域(AF_INET、AF_INET6、AF_UNIX)
 *      b.其次再创建套接字的类型(SOCK_DGRAM、SOCK_STREAM)
 *      c.最后，再指定套接字要使用的协议(0、IPPROTO_TCP:6、IPPROTO_UDP:17)
 *  2.首先要向服务端发送消息：
 *      (服务端是不推荐进行地址绑定的，因为一个端口只能被一个进程所绑定，如果
 *      对在客户端对地址进行了绑定，那么客户端就只能存在一个，不能同时开启多个)
 *      为了让服务端首先能获取到客户端的ip和端口，
 *      我们规定的是客户端首先需要向服务端发送数据 (sendto)'
 *
 *      a.套接字描述符
 *      b.buf:发送的数据
 *      c.发送的长度
 *      d.flags：发送的状态，0为阻塞发送
 *      e.要发送给服务端的地址信息结构
 *          这里我们需要注意的是：服务器的ip和端口是在我们写之前就已经清楚知道
 *          的信息，我们不需要也不能够在不知情的情况下拿到其ip和端口信息。
 *          因此，这里就需要我们自己定义一个地址信息结构(sockaddr_in)
 *          并主动的调用结构体里面的成员进行赋值。
 *
 *          但是这里也出现了相应的问题，我们在初始化sockaddr_in的变量的时候
 *          I.在初始化端口信息的时候,我们输入的端口是一个uint16_t类型的变量，
 *          但是我们还需要将对应的主机字节序转化为网络字节序，
 *          使用htons()函数即可完成上面的工作
 *                  扩展：h：host、to、n：net、s：short(2Byte)
 *                          htonl -->long
 *
 *          II.再初始化ip地址的时候，由于我们输入的是一个字符串，因此我们首先
 *              需要将输入字符串的点分十进制的ip地址转化为uint32_t，
 *              其次，我们还需将其对应的主机字节序转化为网络字节序:
 *              使用 inet_addr() 即可实现上述两个工作
 *                  扩展：如果输入的是 0.0.0.0，则代表的是网卡中的任一地址
 *                        如果输入的是127.0.0.1，则是本地回环网卡的地址
 *          我们还需注意的是，如果客户端没有主动的绑定端口，那么UDP客户端在
 *          调用sendto函数的时候，就会自动绑定一个空闲的端口(OS会自动为其分配)
 *
 *                  那么如果我们需要主动绑定呢？简单，调用bind函数即可。
 *
 *      f.发送给服务器的地址信息结构的长度
 *
 * 3. 接收服务器返回回来的数据(recvfrom)，这里和服务器的recvfrom的逻辑一样
 *          就不再过多描述
 *
 *
 * 这就是客户端实现的一个基本逻辑。
 *      
 *
 */

int main()
{
    //1.创建套接字
    int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd < 0)
    {
        cout << "socket failed" << endl;
        return 0;
    }

    //2.直接发送消息
    while(1)
    {
        char buf[1024] = {0};
        sprintf(buf,"i am client1");

        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(18989);
        addr.sin_addr.s_addr = inet_addr("172.17.0.5");
        ssize_t s_ret = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&addr,sizeof(addr));
        if(s_ret < 0)
        {
            cout << "sento failed" << endl;
            return 0;
        }

        //3.接收消息
        memset(buf,'\0',sizeof(buf));
        
        struct sockaddr_in recv_addr;
        socklen_t socklen = sizeof(recv_addr);

        ssize_t recv_ret = recvfrom(sockfd,buf,sizeof(buf)-1,0,(struct sockaddr *)&recv_addr,&socklen);
        if(recv_ret < 0)
        {
            cout << "recvfrom failed" << endl;
            return 0;
        }
        printf("%s\n",buf);
    }

    return 0;
}
