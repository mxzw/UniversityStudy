#include <iostream>
#include <cstring>

using namespace std;
class String;
class String_rep
{
    friend ostream& operator<<(ostream &out, const String &s);
    friend class String;
    public:
    String_rep(const char *str = ""):m_use_count(0)
    {
        m_data = new char[strlen(str)+1];
        strcpy(m_data, str);

    }
    String_rep(const String_rep &rep);
    String_rep& operator=(const String_rep &rep);
    ~String_rep()
    {
        delete []m_data;
        m_data = nullptr;

    }
    public:
    void increment()
    {
        ++m_use_count;

    }
    void decrement()
    {
        if(--m_use_count == 0)
        { 
            delete this; //自杀
        }

    }
    int use_count()const
    {
        return m_use_count;

    }
    private:
    char *m_data;
    int   m_use_count;

};
////////////////////////////////////////////////////////////
class String
{
    friend ostream& operator<<(ostream &out, const String &s);
    public:
    String(const char *str=""):rep(new String_rep(str))
    {
        rep->increment();
    }
    String(const String &s) : rep(s.rep)
    {
        rep->increment();
    }
    String& operator=(const String &s)
    {
        if(this != &s)
        {
            rep->decrement();
            rep = s.rep;
            rep->increment();
        }
        return *this;
    }
    ~String()
    {
        rep->decrement();
    }
    public:
    void to_upper()
    {
        //写时拷贝
        String_rep *new_rep = new String_rep(rep->m_data);
        rep->decrement();
        rep = new_rep;
        rep->increment();

        char *ptmp = rep->m_data;
        while(*ptmp != '\0')
        {
            if(*ptmp>='a' && *ptmp<='z')
                *ptmp -= 32;
            ptmp++;
        }
    }
    private:
    String_rep *rep;
};

ostream& operator<<(ostream &out, const String &s)
{
    out<<s.rep->m_data;
    return out;
}

int main()
{
    String s1("abc");
    String s2 = s1;
    String s3 = s2;

    cout<<"s1 = "<<s1<<endl;
    cout<<"s2 = "<<s2<<endl;

    s1.to_upper();

    cout<<"s1 = "<<s1<<endl;
    cout<<"s2 = "<<s2<<endl;

}
