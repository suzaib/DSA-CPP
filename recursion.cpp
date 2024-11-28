//Recursion happens when a function calls itself

#include<bits/stdc++.h>
using namespace std;

//Create a function that prints 1
void print1(){
    cout<<1<<"\n";
}

//Creating a function that executes infinitely and prints 1
//Such a function causes a segmentation error and this condition is also called stack overflow
void print1Inf(){
    cout<<1<<"\n";

    //Here we call the function inside itself, A very basic example of recursion
    print1Inf();
}

//To prevent such infinite recursion we must give a terminating condition (base condition)

//With a base condition
void printCount(int count=1){
    cout<<count<<"\n";
    count++;
    if(count==10){
        return;
    }
    else {
        printCount(count);
    }
}


//Now we will do some questions on recursions

//Print Name n times
//This has time complexity O(n) and stack space (space complexity) is also O(n) as n functions are waiting in the stack to be executed
void printName(int i=0,int n=5){
    if(i>n){
        return;
    }
    cout<<"Raj\n";
    printName(i+1,n);
}

//Print linearly from 1 to n
void printFirstN(int i=1,int n=5){
    if(i>n){
        return;
    }
    cout<<i<<"\n";
    printFirstN(i+1,n);
}

//Print linearly from n to 1
void printFirstN_Reverse(int i=1,int n=5){
    if(i>n){
        return;
    }
    printFirstN_Reverse(i+1,n);
    cout<<i<<"\n";
}

//Calculate the sum of first n natural numbers
//My method
int sumToN(int n){
    if(n==0){
        return 0;
    }
    return n+sumToN(n-1);
}
//method 2
void sumToN_striverMethod(int n,int sum){
    if(n<1){
        cout<<sum<<"\n";
        return;
    }
    sumToN_striverMethod(n-1,sum+n);
}

//Calculate factorial of n
//My method
int factorial(int n){
    if(n==1){
        return 1;
    }
    return n*factorial(n-1);
}
//method 2
void factorial_striverMethod(int n,int fac){
    if(n==1){
        cout<<fac<<"\n";
        return;
    }
    factorial_striverMethod(n-1,fac*n);
};

//Reverse an array 
//My Method
void revArray(int currArr[],int n){
    if(n==-1){
        return;
    }
    cout<<currArr[n]<<"\n";
    revArray(currArr,n-1);
}
//Striver's Method
void revArray_striver(int arr[],int i,int n){
    if(i>=n/2){
        return;
    }
    swap(arr[i],arr[n-i-1]);
    revArray_striver(arr,i+1,n);
}


//Test for palindrome
//My Method
bool palindromeTest(string str,int n,int i){
    if(i>=n/2){
        return true;
    }
    if(str[i]!=str[n-i-1]){
        return false;
    }
    return palindromeTest(str,n,i+1);
}


//Functions with multiple recursions calls
//A thing to be noted in multiple recursion calls is that for eg: return = recursion1 + recursion2 , then only after
//recursion1 is fully completed , recursion2 takes place
//Print the nth fibonacci's term
//This is a problem where the recursion will be called twice since f(n)=f(n-1) + f(n-2)

int fibonacciTerm(int n){
    if(n<=1){
        return n;
    }
    return (fibonacciTerm(n-1) + fibonacciTerm(n-2));
}

int main(){
    return 0;
}
