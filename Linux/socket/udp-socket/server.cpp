#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

using namespace std;

/*
 * udp：面向数据报，无连接
 * 服务端的实现逻辑:
 * 1. 创建套接字：socket 
 *      a.首先要指定地址域(AF_INET、AF_INET6、AF_UNIX)
 *      b.其次再创建套接字的类型(SOCK_DGRAM、SOCK_STREAM)
 *      c.最后，再指定套接字要使用的协议(0、IPPROTO_TCP:6、TPPROTO_UDP:17)
 * 2.然后要绑定相应的地址信息：bind
 *      a.套接字描述符
 *      b.地址信息结构(通用的数据结构)：在传入的时候对其传入的具体类型进行
 *      相应的强转
 *      c.地址信息结构的长度(本质上就是对网络能解析多少字节做出限制，防止越界的行为产生)。
 *      这里的越界行为：举个例子来说，假设如果没有这个长度的限制:
 *      那么如果传入的是sockaddr_in结构体(ipv4)，
 *      当对其进行初始化的时候，若是给其中的地址域信息(__SOCKADDR_COMMON)
 *      传入AF_UNIX，那么当bind函数拿到我们所传入的结构体，再对其地址域进行
 *      解析的时候，发现是本地域套接字，由于没有长度的限制，则它会向下读110Byte
 *      但是我们所定义的sockaddr_in是一个ipv4的结构体，它的大小就只有16Byte，
 *      因此，再向下读的时候就会发生越界访问的问题，综上所述，我们需要这个长度
 *      来对传入的结构体应该访问的长度做一个限制。
 *
 *      tips:__SOCKADDR_COMMON是一个sa_family_t类型，它占用两个Byte
 *
 * 3. 由于服务端在回复消息之前，需要知道客户端的ip和地址，因此，我们在这里规定
 *    客户端首先需要向服务器发生一条消息，然后，服务端再做相应的回复。
 *    因此，接下来我们需要做的就是对网络数据的接收。(recvfrom)
 *      a.套接字描述符
 *      b.buf:接收到的数据
 *      c.buf的最大接收能力
 *      d.flags:定义接收时的状态，0为阻塞接收
 *      e.接收的客户端的结构体属性，其中包括客户端的ip和端口信息，它的值是由
 *          recvfrom这个函数赋的值,它会被用来作为后面回复消息的依据
 *      f.所接受的结构体的长度，是一个输入输出型参数
 *          输入：在接收之前准备的对端地址信息的长度
 *          输出：实际接收回来的地址信息长度
 *
 * 4.处理数据：
 *      a.获取ip地址：我们可以直接从上面的结构体中获取到相应的ip地址信息
 *          但是我们需要首先将网络字节序转为主机字节序，其次再将uint32_t的
 *          ip地址转为我们所需要的点分十进制的字符串。
 *              使用：inet_ntoa()
 *      b.获取端口：同理，我们需要将网络字节序转为主机字节序，然后再进行使用
 *              可以使用：ntohs()函数(short)、ntohl()函数(long)
 *
 * 5. 接下来我们就需要对接收到的数据进行处理了,将处理完的数据根据在前面接收到
 *    的客户端的ip和端口信息，再将处理完的结果返回给目标客户端，形成一个闭环
 *    ，因此，再处理完数据之后，我们要将数据发送到目标客户端。(sendto)
 *      a.套接字描述符
 *      b.buf:要发送的数据，这里需要注意的是，如果要使用上面的创建的buf，则
 *          在使用之前一定要记得初始化。
 *      c.发送数据的长度
 *      d.flags:发送数据的状态，0：阻塞发送
 *      e.dest_addr:目标主机的地址信息结构(记得在传的时候要进行相应的强转
 *          因为，这里参数给的是通用的地址信息结构)
 *      f.目标主机的地址信息结构的长度
 *
 *  至此，一个大抵的服务端的逻辑流程已经梳理完毕。
 *
 */

int main()
{
    //1.创建ipv4的套接字
    int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd < 0)
    {
        cout << "socket create failed" << endl;
        return 0;
    }
    
    //创建ipv4的结构体，这也是服务端的ip和端口号
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(18989);
    //这里需要注意的是inet_addr包含在#include <arpa/inet.h>
    addr.sin_addr.s_addr = inet_addr("172.17.0.5");

    //2.绑定地址信息结构(sockaddr)
    int ret = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        cout << "bind failed" << endl;
        return 0;
    }
    
    //3.接收和发送来自客户端的消息
    while(1)
    {
        char buf[1024] = {0};
        struct sockaddr_in recv_addr;
        socklen_t recvlen = sizeof(recv_addr);
        ssize_t recv_size = recvfrom(sockfd,buf,sizeof(buf)-1,0,(struct sockaddr *)&recv_addr,&recvlen);
        if(recv_size < 0)
        {
            cout << "recvfrom failed" << endl;
            return 0;
        }
        //走到这表示接收到消息了
        printf("i am server,i recv : %s,i recv sucess %s:%d\n",buf,inet_ntoa(recv_addr.sin_addr),ntohs(recv_addr.sin_port));

        //然后开始处理和发送数据
        memset(buf,'\0',sizeof(buf));
        sprintf(buf,"hello client, i am server, %s:%d\n",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));

        ssize_t s_ret = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&recv_addr,sizeof(recv_addr));
        if(s_ret < 0)
        {
            cout << "sendto failed" << endl;
            return 0;
        }
            
    }

    close(sockfd);
    return 0;
}
