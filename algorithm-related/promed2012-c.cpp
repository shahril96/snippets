#include <iostream>
#include <cmath>

#define MAXF 999999.0
#define EPSILON 0.0000000001

using namespace std;

int main()
{
    int n;
    cin >> n;
    cin.ignore();

    for(int i = 1; i <= n; i++)
    {
        int customer[2], x, y, nearestx, nearesty;
        float min_dist = MAXF;
        cin >> customer[0] >> customer[1];

        for(x = y = 0; x != 10001 && y != 10001; cin >> x >> y)
        {
            float calc_dist = hypotf(x - customer[0], y - customer[1]);

            if(calc_dist < min_dist)
            {
                nearestx = x, nearesty = y;
                min_dist = calc_dist;
            }
            else if(fabs(calc_dist - min_dist) < EPSILON) // floating number comparison kena pakai epsilon
            {
                if(y > nearesty || (y == nearesty && x > nearestx))
                {
                    nearestx = x, nearesty = y;
                }
            }
        }

        cout << "Case " << i << ": " << nearestx << " " << nearesty << endl;
    }
}
