#include <vector>
#include "tcp.hpp"

#include <boost/algorithm/string.hpp>

//ssize_t tcp::Recv(struct DataType* dt)
//{
//    ssize_t ret = recv(sockfd_,dt,sizeof(*dt),0);
//    if(ret < 0)
//    {
//        cout << "recv failed" << endl;
//    }
//    return ret;
//}
//
// 利用boost库中的split函数对字符串进行分割
class StringUtil {    
    public:    
        static void Split(const std::string& input, const std::string& split_char,    
                std::vector<std::string>* output) {    
            boost::split(*output, input, boost::is_any_of(split_char), boost::token_compress_off);    
        }    
};


int Sum(string& data)
{
    //切割或者数据， 按照“+”
    vector<string> output;
    StringUtil::Split(data, "+", &output);

    int total_sum = 0;
    for(size_t i = 0; i < output.size(); i++)
    {
        total_sum += atoi(output[i].c_str());
    }

    return total_sum;
}


void* TcpEntryPthread(void* arg)
{
    pthread_detach(pthread_self());
    tcp *tc = (tcp*) arg; 

    while(1)
    {
        char buf[1024] = {0};

        //struct DataType dt;

        ssize_t ret = tc->Recv(buf,sizeof(buf)-1);
        if(ret < 0)
        {
            cout << "recv failed" << endl;
            continue;
        }
        else if(ret == 0)
        {
            cout << "peer close" << endl;
            break;
        }

        printf("client say: %s\n",buf);
        
        string tmp(buf);
        int total = Sum(tmp);

        memset(buf,'\0',sizeof(buf));
        sprintf(buf,"%d",total);

        ret = tc->Send(buf,strlen(buf));
        if(ret < 0)
        {
            cout << "send failed" << endl;
            continue;
        }
    }

    delete tc;
    return nullptr;
}

int main()
{
    tcp tc;
    int ret = tc.createSockfd();
    if(ret < 0)
        return -1;
    //默认ip 0.0.0.0，默认端口18989
    ret = tc.Bind();
    if(ret < 0)
        return -1;
    //默认已完成连接队列大小为2
    ret = tc.Listen();
    if(ret < 0)
        return -1;

    while(1)
    {
        struct sockaddr_in addr;
        socklen_t socklen = sizeof(addr);
        int new_sockfd = tc.Accept(&addr,&socklen);
        if(new_sockfd < 0)
        {
            cout << "Please again to accept" << endl;
            continue;
        }

        //从这里开始创建工作线程
        //如果只是单纯的将new_sockfd传过去的话，是不行的
        //因为它是一个局部变量，因此，我们需要在堆上开辟出一个空间
        tcp *t = new tcp(new_sockfd);
        if(t == nullptr)
        {
            cout << "new class tcp failed" << endl;
            continue;
        }

        pthread_t tid;
        ret = pthread_create(&tid,NULL,TcpEntryPthread,t);
        if(ret < 0)
        {
            cout << "pthread_create failed" << endl;
            delete t;
            continue;
        }
    }


}
