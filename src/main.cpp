#include <iostream>
#include <vector>
using namespace std;
using ull = unsigned long long int; 


vector<unsigned int> m;  


unsigned int modPow(ull x, ull y, ull m) {
	if (y == 0) {
		return 1;
	}
	// fast exponentiation
	int p = modPow(x, y / 2, m) % m;
	p = (p * p) % m;
	return (y % 2 == 0) ? p : (x * p) % m;
}

int modInv(ull a, ull m) {
	// don't have to check gcd because we know m is prime
	// int d = gcd(a, m);
	return modPow(a, m-2, m);
}

ull gcd(ull a, ull b) {
	// easy recursive gcd algorithm
	return a == 0 ? b : gcd(b % a, a); 
}

void sieve(unsigned int n) {
	vector<bool> is_prime(n+1, true);
	// zero is not prime
	is_prime[0] = false;
	// one is not prime
	is_prime[1] = false;
	// implementation of sieve or erastosthenes to generate primes
	for (int i = 2; i < n; i++) {
		if (is_prime[i] && (long long) i * i <= n) {
			for (int j = i * i; j <= n; j += i) {
				is_prime[j] = false;
			}
		}
	}
	for (int i = 2; i < n; i++) {
		if (is_prime[i]) m.push_back(i);
	}
}

vector<unsigned int> forwardConvert(ull x) {
	vector<unsigned int> ret; 
	// just take the remainder mod each of our mi
	for (size_t i = 0; i < m.size(); i++) 
		ret.push_back(x % m[i]); 	
	return ret;
}

ull backwardConvert(vector<unsigned int> r) {
	// M is product of all coprime integers used for representation
    ull	M = 1;
	for (auto mi : m) M *= mi;
	// each M_i is M divided by one of the integers used for  representation
	vector<unsigned int> M_vec;
	for (auto mi : m) M_vec.push_back(M / mi);
	// compute inverse of each M_i
	vector<int> M_inv;
	for (size_t i = 0; i < m.size(); i++) {
		M_inv.push_back(modInv(M_vec[i], m[i]));
	}
	ull ret = 0;
	for (size_t i = 0; i < m.size(); i++) {
		ret += r[i] * abs(M_inv[i]) * M_vec[i];
	}

	return ret % M; 
}

vector<unsigned int> add(vector<unsigned int> a, vector<unsigned int> b) {
	vector<unsigned int> c;
	for (size_t i = 0; i < m.size(); i++) {
		c.push_back((a[i] + b[i]) % m[i]);
	}
	return c;
}

vector<unsigned int> times(vector<unsigned int> a, vector<unsigned int> b) {
	vector<unsigned int> c;
	for (size_t i = 0; i < m.size(); i++) {
		c.push_back((a[i] * b[i]) % m[i]);
	}
	return c;
}




int main() {
	cout << "Enter limit for prime generation" << endl;
	unsigned int n;
	cin >> n;
	sieve(n);
	cout << "Enter two numbers" << endl;
	ull a, b;
	cin >> a >> b;
	cout << endl << "Enter an operation: " << endl;
	char op;
	cin >> op;
	switch(op) {
		case '+':
			cout << backwardConvert(add(forwardConvert(a), forwardConvert(b))) << endl;
			break;
		case '*':
			cout << backwardConvert(times(forwardConvert(a), forwardConvert(b))) << endl;
			break;
		default:
			cout << "Operation invalid" << endl;
	}
	
}
