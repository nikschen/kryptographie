#include <iostream> 



void bbs(int _p, int _q, int _s)
{

    int n = _p * _q;
    int xIOld = _s * _s % n;
    int xI = xIOld * xIOld % n;
    int bI = xI % 2;
    std::cout << "bI=";
    for (int i = 0; i < 255; i++)
    {
        std::cout << bI;
        xI = xIOld * xIOld % n;
        bI = xI % 2;
        xIOld = xI;
    }

}

int main()
{
    int p = 7;
    int q = 19;
    int s = 2;
    bbs(p, q, s);
    return 0;
}
