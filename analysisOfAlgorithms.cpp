//NOTE : This file is just supposed to be used for reading and not executed since there are errors in it due to naming
//       We have named several function of the same name since otherwise we would have to name like test1, test2 etc

/*
Here we discuss the Master Method which is used to find the time complexity of the recurrence relations
For that we first need to discuss recurrence relations and how to find the time complexity 
We are already much aware of what a recurrence relation is, therefore we will try to find the time complexity of some recurrence relation

NOTE : All logs(unless mentioned otherwise, are to base 2
*/

#include<bits/stdc++.h>
using namespace std;

//Consider the recurrence function test
void test(int n){
    if(n>0){
        cout<<n<<"\n";
        test(n-1);
    }
}

/*
We can find the time complexity by drawing the recursive tree or we will use the method for which we are studying
The test function takes an integer n, lets suppose it's time complexity is denoted by a function T(n) where T(n) is a function of n which will give time complexity of worst case when the argument is n
Inside the function there are two things happening(we assume the condition always holds true as we calculate the complexity for the worst case)
First of all there is a print statement which will have time complexity of O(1), that is constant space
Next is the test function again, since we earlier assumed that test function's time complexity for argument n was T(n) therefore for n-1 it will be T(n-1)
Now we can simply combine the two as that will be the total time the test function will take
T(n)=1+T(n-1)
This is the recurrence relation
Actually this is partially correct, since we this holds for n>0, for n<=0? is the relation T(n)=0 ? NO
Even if the time taken is 0 we still denote it by constant time and write 1
Therefore T(n) will be 1(or any constant) when n<=0  and 1+T(n-1) when n>0

Solving the Recurrence Relation
Now lets solve this recurrence relation
We need to solve it only for n>0 since for the other case it is already solved
Try solving it on your own, hint : use substitution
T(n) will become equal to 1+1+1+1..(k times) + T(n-k)
T(n)=T(n-k) + k
as we know when n=0 T(n)=1 therfore put n=k
T(n)=T(n-n)+n
T(n)=n+1

This is the same time complexity that we would have gotten using recursive tree as well
*/


//Now we do it for another function

void test(int n){
    if(n>0){
        for(int i=0;i<n;i++) cout<<n<<"\n";
        test(n-1);
    }
}

/*
This time we will be a little quick
The test function, assume time taken to be T(n), then it does a for operation of n times and calls test(n-1) which takes T(n-1)
Therefore T(n)=n+T(n-1)
We can solve this using backward substitution again
T(n)=n+(n-1)+(n-2)+(n-3)+...+(n-k) + T(n-k-1)
T(n)=T(n-k-1)+ (k+1)(2n-k)/2
For n=0 T(n)=1, therefore put k=n-1
T(n)=T(0)+ n(n+1)/2
T(n)=1+n(n+1)/2
*/

//Asymptotic Notation
//The normal usual thing we keep doing, that is reporting time complexity of 2n+2 as O(n), that is called asymptotic time complexity


//Let's solve one more
void test(int n){
    if(n>0){
        for(int i=1;i<n;i=i*2) cout<<n<<"\n";
        test(n-1);
    }
}

/*
T(n)=logn+T(n-1), again use backward substitution
T(n)=T(n-k-1)+log((n!)/(n-k-1)!)
Put k=n-1 to get T(n)=log(n!)+1
Upper Bound of n! is n^n
Therefore T(n)=nlogn+1 or T(n)=nlogn (asymptotic Time Complexity)
(The approximation of T(n!)=T(nlogn) is called Stirling's approximation)
*/

/*
On the basis of the above three results, try to notice something
T(n)=T(n-1)+1 =====> O(n)
T(n)=T(n-1)+n =====> O(n2)
T(n)=T(n-1)+nlogn => O(nlogn)

Therefore 
T(n)=T(n-1)+f(n) ==> O(n*f(n))

Some more results
T(n)=T(n-2)+f(n) ==> O((n/2)*f(n))
More generally 
T(n)=T(n-k)+f(n) ==> O((n/k)*f(n))
*/


//Consider this function
void test(int n){
    if(n>0){
        cout<<n<<"\n";
        test(n-1);
        test(n-1);
    }
}

/*
T(n)=2T(n-1)+1
T(n)=(2^k)*T(n-k) + 2^0+2^1+2^2+...+2^(k-1)
As for n=0 T(n)=1, therefore
T(n)=(2^n)*1+(2^n)-1
T(n)=2^(n+1)-1
Writing in asymptotic form
T(n)=2^n
*/

/*
Now generalising our solution
T(n)=k*T(n-1)+1 ===> T(n)=k^n
T(n)=k*T(n-1)+f(n) ===> T(n)=f(n)*(k^n)
*/


/*
Master's Theorem for Decreasing functions
T(n)=a*T(n-b)+f(n) where a>0 && b>0 and f(n) is of the form O(n^k) where k>=0
Case I : a=1
T(n)=T(n-k)+f(n) ==> O((n/k)*f(n))

Case II : a<1
T(n)=0.7T(n-k)+f(n) ===> O(f(n))

Case III : a>1
T(n)=aT(n-b)+f(n) ==> T(n)=f(n)*(a^(n/b))
*/


//Dividing Functions
void test(int n){
    if(n>1){
        cout<<n<<"\n";
        test(n/2);
    }
}

/*
Time Complexity can be written as 
T(n)=1+T(n/2)
Use backward substitution
T(n)=T(n/2^k)+k
We are given T(1)=1 therefore put n/2^k=1
That is put 2^k=n
k=logn
T(n)=T(1)+logn
T(n)=logn



Consider the function : T(n)=T(n/2)+n for n>1 and 1 when n==1
Keep using backward substitution to get 
T(n)=T(n/2^k)+(n+n/2+n/4+n/8+....+n/2^(k-1))
Substitute k=logn in the above recurrence relation to get T(n)=1+n(2+(1/2^k-1))
Trimming down the complexity becomes T(n)=1+2n ==> O(n)



Consider the example : T(n)=2*T(n/2)+n (when n>1 and 1 when n=1)
Use backward substitution to get T(n)=2^k*(T(n/2^k))+nk
Use k=logn(base 2) to solve it as T(n)=n+nlogn
T(n)=nlogn
*/

/*
Master's Theorem for Dividing Functions
T(n)=a*T(n/b)+f(n), where a>=1 and b>1 and f(n) is of the form fx((n^k)*((logn)^p))
Calculate two things first
One is value of k(power of n in f(n))
Next is log_b(a)(b is base), let log_b(a) be denoted by z
then compare k and z
Case I) z>k
Then O(n^z)

Case II) z==k
    Case a) p>-1 : O(n^k * (logn)^(p+1))
    Case b) p==-1: O(n^k * (log(logn)))
    Case c) p<-1 : O(n^k)

Case III) z<k
    Case a) p>0 : O(n^k * (logn)^p)
    Case b) p<=0 : O(n^k)

*/


//Recurrence Relation for root functions
void test(int n){
    if(n>2){
        cout<<n<<"\n";
        test(sqrt(n));
    }
}

/*
T(n)=T(n^(1/2))+1 when n>2 and =1 when n=2
T(n)=T(n^(1/4))+2
T(n)=T(n^(1/8))+3 and so on..
T(n)=T(T^(1/2^k)) + k
Put k=log(logn) for base condition
T(n)=log(logn)

*/

//// END RESULTS ////
/*
/*
Master's Theorem for Decreasing functions
T(n)=a*T(n-b)+f(n) where a>0 && b>0 and f(n) is of the form O(n^k) where k>=0
Case I : a=1
T(n)=T(n-k)+f(n) ==> O((n/k)*f(n))

Case II : a<1
T(n)=0.7T(n-k)+f(n) ===> O(f(n))

Case III : a>1
T(n)=aT(n-b)+f(n) ==> T(n)=f(n)*(a^(n/b))
*/

/*
Master's Theorem for Dividing Functions
T(n)=a*T(n/b)+f(n), where a>=1 and b>1 and f(n) is of the form fx((n^k)*((logn)^p))
Calculate two things first
One is value of k(power of n in f(n))
Next is log_b(a)(b is base), let log_b(a) be denoted by z
then compare k and z
Case I) z>k
Then O(n^z)

Case II) z==k
    Case a) p>-1 : O(f(n)*logn)
    Case b) p==-1: O(n^k * (log(logn)))
    Case c) p<-1 : O(n^k)

Case III) z<k
    Case a) p>0 : O(f(n))
    Case b) p<=0 : O(n^k)

*/




int main(){
    return 0;
}
