#include <iostream>
using namespace std;

class Test
{
    public:
        void GetData()
        {
            cout << "Test no const!" << endl;
        }

        void GetData() const
        {
            cout << "Test const!" << endl;
        }
};

int main()
{
    const Test t;
    t.GetData();
    return 0;
}
