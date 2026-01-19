//Problems based on Maths

//In case Time Complexity is not mentioned , it should be assumed(in most cases) that it is O(N) 
//In case Space Complexity is not mentioned , it should be assumed(in most cases) that it is O(1)(However space may be used to return the ans which is same as the size of ans)

#include<bits/stdc++.h>
using namespace std;


//Q.1) Count the number of digits in an integer
int countDig(int n){
    int count=int(log10(n)+1);
    return count;
}
//Time Complexity is O(1)


//Q.2) Reverse a number
int reverseNumber(int n){
    int lastDig;
    int rev=0;
    while(n>0){
        lastDig=n%10;
        rev=rev*10+lastDig;
        n=n/10;
    }
    return rev;
}
//Time complexity will be O(log10(d)) d is the number of digits


//Q.3) Check whether the given number is a Palindrome or not
bool checkPalindrome(int n){
    int orgNumber=n;
    int lastDig;
    int rev=0;
    while(n>0){
        lastDig=n%10;
        n=n/10;
        rev=rev*10 + lastDig;
    }
    if(rev==orgNumber){
        return true;
    }
    else {
        return false;
    }
}
//Time complexity will be O(log10(d)) d is the number of digits


//Q.4) Check whether the number is armstrong or not
//Armstrong Number : If the sum of cubes of individual digits of a number is equal to the number itself, then that number is Armstrong Number
bool checkArmstrong(int n){
    int orgNumber=n;
    int sum=0;
    int lastDig;
    while(n>0){
        lastDig=n%10;
        n=n/10;
        sum=sum+pow(lastDig,3);
    }
    if(sum==orgNumber){
        return true;
    }
    else{
        return false;
    }
}
//Time complexity will be O(log10(d)) d is the number of digits


//Q.5) Print All The Divisors
vector<int> printAllDivisors_brute(int n){
    vector<int> ans;
    for(int i=1;i<=n;i++){
        if(n%i==0){
            ans.push_back(i);
        }
    }
    return ans;
}

//We can only check until sqrt(n) 
vector<int> printAllDivisors_better(int n){
    vector<int> ans;
    for(int i=1;i<=sqrt(n);i++){
        if(n%i==0){
            ans.push_back(i);
            if(n/i!=i){
                ans.push_back(n/i);
            }
        }
    }
    return ans;
}
//Time complexity will be O(N)+time calculated to sqrt(n) (check for c++ stl on chrome)

//sqrt(n) takes some time to calculate therfore we use the condition i*i)
vector<int> printAllDivisors(int n){
    vector<int> ans;
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            ans.push_back(i);
            if(n/i!=i){
                ans.push_back(n/i);
            }
        }
    }
    return ans;
}
//Time Complexity will be O(sqrt(N))


//Q.6) Checking whether a number is prime or not
bool checkForPrime(int n){
    int count=0;
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            count++;
            if(n/i!=i){
                count++;
            }
        }
    }
    if(count==2){
        return true;
    }
    else {
        return false;
    }
}
//Time Complexity will be around O(sqrt(n)*2*sqrt(n)) (though never equal to it because many times if condition won't be executed)


//Q.7) Find the Greatest Common Divisor
int gcd_brute(int n1,int n2){
    int gcd;
    for(int i=1;i<=min(n1,n2);i++){
        if(n1%i==0 and n2%i==0){
            gcd=i;
        }
    }
    return gcd;
}
//Time complexity will be O(min(n1,n2))


//The euclidean lemma provides a much better approach
int gcd_euclideanLemma(int n1,int n2){
    int a=max(n1,n2);
    int b=min(n1,n2);
    int temp;
    while(a!=0 and b!=0){
        temp=b;
        b=a%b;
        a=temp;
    }
    int gcd=max(a,b);
    return gcd;
}
//Time Complexity will O(log(min(n1,n2)))


//Q.8) Print All Prime Factors of a given number
vector<int> primeFactors_brute(int n){
    vector<int> ans;
    vector<int> div=printAllDivisors_optimal(n);
    for(int i=0;i<div.size();i++){
        if(checkForPrime(div[i])==true) ans.push_back(div[i]);
    }
    return ans;
}
//Time Complexity is the added time for the two function used along with the time taken to run for loop : O(aqrt(n)) + O(sqrt(n)*2*sqrt(n))*O(div.size())

vector<int> primeFactors_better(int n){
    vector<int> ans;
    for(int i=2;i<=n;i++){
        if(n%i==0){
            ans.push_back(i);
            while(n%i==0){
                n=n/i;
            }
        }
    }
    return ans;
}
//One Thing to be noticed here that time Complexity is only reduced for some numbers , eg for numbers that are large and prime like 37(try to run the code , it takes 35 iterations)

//We need to optimise it more 
vector<int> primeFactors_optimal(int n){
    vector<int> ans;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            ans.push_back(i);
            while(n%i==0){
                n=n/i;
            }
        }
    }
    if(n!=1) ans.push_back(n);
    return ans;
}
//Time complexity will be O(sqrt(n)*logN) (for worst case)


//Q.9) Power Exponentiation
int power_brute(int n,int m){
    int ans=1;
    for(int i=0;i<m;i++){
        ans=ans*n;
    }
    return ans;
}

double power(double n, int m) {
    double ans = 1.0; 
    int abs_m = abs(m);

    while (abs_m>0) {
        if (abs_m%2==0){
            n=n*n; 
            abs_m=abs_m/2; 
        }
        else{
            ans=ans*n; 
            abs_m=abs_m-1; 
        }
    }

    if (m<0) ans=1.0/ans; 
    return ans;
}
//Time Complexity will be O(log2(N)) 


//Q.10) Print All Primes till N
vector<int> primesTillN_brute(int n){
    vector<int> ans;
    for(int i=2;i<=n;i++){
        if(checkForPrime(i)==true) ans.push_back(i);
    }
    return ans;
}
//Time Complexity will be O(N*sqrt(N))

//Using sieve of eratosthenes
//For this we first create a function to get the sieve of prime numbers, ie; an array uptil n(specified) in which (except 0 and 1) all other indexes are marked with 1(if the index is prime) and 0 (if the index is not prime)
vector<int> getSieve(int n){
    vector<int> sieve(n+1,1);
    for(int i=2;i*i<=n;i++){
        if(sieve[i]==1){
            for(int j=i*i;j<=n;j=j+i){
                sieve[j]=0;
            }
        }
    }
    return sieve;
}
vector<int> primesTillN_optimal(int n){
    vector<int> sieve=getSieve(n);
    vector<int> ans;
    for(int i=2;i<sieve.size();i++){
        if(sieve[i]==1) ans.push_back(i);
    }
    return ans;
}
//Time Complexity is : O(N)(for marking the primes array as 1) + O(NLog(LogN))(derived from complex mathematical calculations) + O(sieve.size())



//Q.11) Primes Between L and R (Both inclusive)
int primesBetLAndR(int l,int r){
    vector<int> sieve=getSieve(r);
    int count=0;
    for(int i=2;i<sieve.size();i++){
        count=count+sieve[i];
        sieve[i]=count;
    }
    int ans=sieve[r]-sieve[l-1];
    return ans;
}


//Q.12) Find the smallest Prime Factor of a number
//We will again generate a sieve for it , one that's different from the previous one, A sieve containing the smallest Prime Factor of its indices
vector<int> getSieveOfSPF(int n){
    vector<int> sieve;
    for(int i=0;i<=n;i++){
        sieve.push_back(i);
    }
    for(int i=2;i<=n;i++){
        if(sieve[i]==i){
            for(int j=i*i;j<=n;j=j+i){
                sieve[j]=i;
            }
        }
    }
    return sieve;
}


//Q.13) Prime Factorisation of a number n
vector<int> primeFactorisation_brute(int n){
    vector<int> ans;
    for(int i=2;i*i<=n;i++){
        while(n%i==0){
            n=n/i;
            ans.push_back(i);
        }
    }
    if(n>1) ans.push_back(n);
    return ans;
}
//Time complexity is again a bit difficult to compute

//We Can optimise it if we can find the smallest prime factor, we can use the function we made earlier
vector<int> primeFactorisation_optimal(int n){
    vector<int> ans;
    vector<int> sieve=getSieveOfSPF(n);
    int i;
    while(n>1){
        i=sieve[n];
        n=n/i;
        ans.push_back(i);
    }
    return ans;
}


//Q.14) Sum 1 to n Divisors
//For eg for n=4 generate the sum for all divisors beginning from 1 then 2 then 3 then 4.
//Ans =>15
//Brute Force is to use the logic of print all divisors functions.Time Complexity will be N*N

//Better Method uses the i*i<=n techinique to reduce time complexity to N*sqrt(N)

//Optimal Approach:
//List down the factors for all numbers until n, like:
/*
1=>1
2=>1+2
3=>1+3
4=>1+2+4
As you saw 2 appeared only 4/2=2 times, hence each number in this appears only n/i times therefore it contributes (n/i)*i to the sum. Use this logic
*/

int sum1ToNDivisors_optimal(int n){
    int sum=0;
    for(int i=1;i<=n;i++){
        sum+=((n/i)*i);
    }
    return sum;
}
//Time Complexity will be N

int main(){
    return 0;
}

