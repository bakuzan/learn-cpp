#include <iostream>
using namespace std;

template <class T>
class cSum
{
private:
    T value;

public:
    cSum(T first, T second)
    {
        value = first + second;
    }
    T Result()
    {
        return value;
    }
};

int main()
{
    cSum<int> sum(1, 4);
    cout << sum.Result() << endl;
    cSum<float> sumFloat(1.1, 4.4);
    cout << sumFloat.Result() << endl;
    return 0;
}