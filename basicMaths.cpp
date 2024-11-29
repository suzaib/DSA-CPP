#include<bits/stdc++.h>
using namespace std;

void countDig(int n){
    int count=int(log10(n)+1);
    cout<<count<<"\n";
}

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

//Printing all the divisors (brute force)
void printAllDivisors1(int n){
    for(int i=1;i<=n;i++){
        if(n%i==0){
            cout<<i<<"\n";
        }
    }
}

//Printing all the divisors (better method)
void printAllDivisors2(int n){
    for(int i=1;i<=sqrt(n);i++){
        if(n%i==0){
            cout<<i<<"\n";
            if(n/i!=i){
                cout<<(n/i)<<"\n";
            }
        }
        
    }
}

//Printing all the divisors in sorted order
//We will use a list/array/vector to store the divisors and then we will sort them
void printAllDivisors3(int n){
    vector<int> v;
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            v.push_back(i);
            if(n/i!=i){
                v.push_back(n/i);
            }
        }
    }
    sort(v.begin(),v.end());
    for(auto it:v){
        cout<<it<<"\n";
    }
}

//Checking for primes
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

int greatestCommonDivisor(int n1,int n2){
    int gcd;
    for(int i=1;i<=min(n1,n2);i++){
        if(n1%i==0 and n2%i==0){
            gcd=i;
        }
    }
    return gcd;
}

int gcdByEuclideanLemma(int n1,int n2){
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

int main(){
    int n1,n2;
    cin>>n1>>n2;
    //Enter your function here
    return 0;
}
