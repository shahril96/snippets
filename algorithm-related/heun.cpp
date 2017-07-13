#include <iostream>

using namespace std;

// cara nk buat function biasa
// return = output calculation tu
double f(double x, double y)
{
	return 2 * x * y;
}

int main()
{
	double i, deltax, x, y, output;
	
	cout << "Enter i : ";
	cin >> i;
	
	cout << "Enter delta x (step of x) : ";
	cin >> deltax;
	
	cout << "Enter initial x : ";
	cin >> x;
	
	cout << "Enter initial y : ";
	cin >> y;
	
	for(int ii = 0; ii <= i ; ii++)
	{
		// first step, find f(xi, yi)
		double step1 = f(x, y);
		
		// second step, find yi+1 = yi + deltax . f(xi, yi)
		double step2 = y + (deltax * step1);

		// third step, find f(xi+1, yi+1)
		// xi+1 = xi + deltax
		double xplus1 = x + deltax;
		double step3 = f(step2, xplus1);
		
		cout << "\n Step i = " << ii << ":-\n\n xi+1 -> " << xplus1 << "\n f(xi, yi) -> " << step1
		     << "\n yi+1 = yi + deltax . f(xi, yi) -> " << step2 << "\n f(xi+1, yi+1) -> " << step3 << endl << endl;
		
		// corrected yi+1 value
		output = y + (deltax * (step1 + step3)) / 2;
		
		// ganti xi+1 & yi+1 with current x & y
		// guna untuk next iteration
		x = xplus1;
		y = output;
	}
	
	cout << "Jawapan : " << output << endl;
}
