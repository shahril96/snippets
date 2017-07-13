#include <iostream> // cout, cin
#include <cmath> // sqrt, pow
#include <random> // random_device, mt19937, uniform_real_distribution
#include <iomanip> // setprecision
#include <ctime> // time
#include <cstdint> // uint64_t

uint64_t s[2] = {(uint64_t)time(NULL) % 100, (uint64_t)time(NULL) % 10000};

int xorshift128(int start, int end) {
	uint64_t s1 = s[0];
	const uint64_t s0 = s[1];
	s[0] = s0;
	s1 ^= s1 << 23; // a
	s[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5); // b, c
	return start + (s[1] + s0) % (end  - start);
}

class PiApprox {

private:

    // max x,y (radius of circle)
    int size;

    // maximum random number to generate
    int maxrand;

    inline bool inCircle(int x, int y) {

        // calculate real y by using circle eq.
        double ycalc = sqrt(pow(size,2) - pow(x,2));

        // check if in circle
        return static_cast<double>(y) <= ycalc;
    }

public:

    PiApprox() {
        setSize(0);
    }

    void setSize(int N) {

        // set max x,y (radius of circle)
        size = N;

        // make sure doesnt fill all boxes
        // just random eq, improve this if u want
        maxrand = pow(N,2) - N*2;
    }

    double calc() {

        // count inside circle
        int incirle = 0;

        // collecting data from random number
        for(int i = 0; i < maxrand; i++) {

            // generate two random x,y location
            int x = xorshift128(0, size);
        	int y = xorshift128(0, size);

            if(inCircle(x,y) == true) {
                incirle++;
            }
        }

        // probability = incircle / maxrand
        // pi/4 = probability
        // pi = probability * 4
        return static_cast<double>(incirle) / static_cast<double>(maxrand) * 4.0;
    }
};

int main(int argc, char const *argv[]) {

    PiApprox pi;

    for(int i = 1; i <= 5; i++) {

        int num = pow(8, i);
        pi.setSize(num);

        std::cout << "\n Number of random distribution : " << num << std::endl;
        std::cout << " Pi Approximation : " << std::setprecision(9) << pi.calc() << std::endl;
    }

    std::cout << std::endl;

    return 0;
}
