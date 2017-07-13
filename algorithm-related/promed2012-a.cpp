#include <iostream>
#include <cctype>

using namespace std;

int validate_input(char input[])
{
    char bool_zul[30] = {0}, *ptr = input;

    while(*ptr)
    {
    	int index = *ptr - 'A';

        // 1. check jika setiap characters dlm string 'input' mengandungi bukan uppercase character (A-Z)
        // 2. check jika character dh wujud dalam array -> O(1) performance
        if(!isupper(*ptr++) || bool_zul[index] == 1)
        {
            return 0;
        }
        else bool_zul[index] = 1;
    }

    int len = (int)(ptr - input);

    return len > 2 && len < 27;
}

int main()
{
    int n;
    char input[1000];
    cin >> n;
    cin.ignore();

    for(int i = 1; i <= n; i++)
    {
        cin.getline(input, 1000);
        cout << "Case #" << i << ": " << (validate_input(input) ? "VALID" : "INVALID") << endl;
    }
}