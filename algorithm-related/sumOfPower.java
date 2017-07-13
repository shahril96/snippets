
import java.math.BigInteger;
import java.util.Scanner;

public class i
{
    public static void main(String args[])
    {
        Scanner in = new Scanner(System.in);
        int T, N, K;
        
        T = in.nextInt(); // ambik test cases
        
        // create new bigint for large calculation
        BigInteger bi, tmp;
        
        while(T-- > 0)
        {
            bi = new BigInteger("" + in.nextInt()); // end of array
            K = in.nextInt(); // ambik power of
            
            if(K == 1) // (1/2)(n^2 + n)
                bi = bi.pow(2).add(bi).divide(new BigInteger("2"));
                
            else if(K == 2) // (1/6)(2n^3 + 3n^2 + n)
            {
                tmp = new BigInteger("2").multiply(bi.pow(3));
                tmp = tmp.add(new BigInteger("3").multiply(bi.pow(2)));
                bi = tmp.add(bi).divide(new BigInteger("6"));
            }
            else if(K == 3) // (∑ bi^K)^2
                bi = bi.pow(2).add(bi).divide(new BigInteger("2")).pow(2);
            
            else if(K == 4) // (1/30)(6n^5 + 15n^4 + 10n^3 - n)
            {
                tmp = new BigInteger("6").multiply(bi.pow(5));
                tmp = tmp.add(new BigInteger("15").multiply(bi.pow(4)));
                tmp = tmp.add(new BigInteger("10").multiply(bi.pow(3)));
                bi = tmp.subtract(bi).divide(new BigInteger("30"));
            }
            
            System.out.println(bi.remainder(new BigInteger("1000000007")).toString());
        }
    }
}
