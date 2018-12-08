// See "README.md"

#include "pch.h" //For visual studios
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

int getInput(int lowerLimit, int upperLimit);
bool checkPrime(int number);
void listDivisors(int number, vector<int>& divisors);
void findRest(vector<int>& divisors, int originalNumber);
void listPrimes(int number, vector<int>& primes);


int main()
{
	cout << "####################################\n"
		<< "#     PRIME NUMBER CALCULATOR      #\n"
		<< "#     -----------------------      #\n"
		<< "# 1. Check if Number is Prime      #\n"
		<< "# 2. List Prime Numbers            #\n"
		<< "# 3. Exit                          #\n"
		<< "####################################"
		<< endl;

	int userChoice = getInput(1, 3);

	//USER CHOICE 1 --- CHECK IF NUMBER IS PRIME
	if (userChoice == 1)
	{
		cout << "Type a Number to check if its prime." << endl;
		int userInput = getInput(1, 2000000000);

		// Calculate Result
		bool result = checkPrime(userInput); //check if prime
		vector<int> divisors;
		listDivisors(userInput, divisors); //get divisors

		// Print Results
		if (result == false)
		{
			if (divisors[0] == 1)
			{
				cout << "By defintion, 1 is not a prime number.";
			}
			else
			{
				cout << userInput << " is not a prime number. It is divisible by ";
				for (int i = 0; i < divisors.size(); i++)
				{
					cout << divisors[i] << " ";
				}
			}
			cout << endl;
		}
		else if (result == true)
		{
			cout << userInput << " is a prime number." << endl;
		}

		cout << "\n1. Return to Main Menu " << endl;
		cout << "2. Exit" << endl;

		userChoice == getInput(1, 2);

		if (userChoice == 1)
		{
			system("CLS");
			return main();
		}
		else
			return 0;
	}


	//USER CHOICE 2 --- LIST PRIME NUMBERS
	else if (userChoice == 2)
	{
		cout << "Enter a number to list prime numbers to (Up to 2,000,000,000)." << endl;
		int userInput = getInput(1, 2000000000);

		// Get list of primes
		vector<int> primes;
		listPrimes(userInput, primes);

		//Print list of primes
		for (int i = 0; i < primes.size(); i++)
		{
			cout << primes[i] << " ";
		}
		cout << endl;

		//Return to Menu or exit
		cout << "\n1. Return to Main Menu " << endl;
		cout << "2. Exit" << endl;

		userChoice = getInput(1, 2);

		if (userChoice == 1)
		{
			system("CLS");
			return main();
		}
		else
			return 0;
	}

	//USER CHOICE 3 --- EXIT
	else
	{
		return 0;
	}

	return 0;
}

// Get user input and make sure it is valid
int getInput(int lowerLimit, int upperLimit)
{
	int userInput;
	cin >> userInput;

	//Check if user input is valid
	if (userInput < lowerLimit || userInput > upperLimit)
	{
		do
		{
			cout << "That is not a valid choice. Please a number between " << lowerLimit << " and " << upperLimit << "." << endl;
			cin >> userInput;
		} while (userInput < lowerLimit || userInput > upperLimit);
	}

	return userInput;
}

//check if number is prime
bool checkPrime(int number)
{
	double root = sqrt(number);

	// BASE CASES (1-3)
	if (number == 1)
		return false;
	else if (number == 2)
		return true;
	else if (number == 3)
		return true;
	else
	{
		if (number % 2 == 0) //if odd greater than 2, not prime
			return false;
		else
		{
			for (int i = 3; i <= root; i += 2)
			{
				if (number % i == 0)
					return false;
			}
			return true; // if passes all above requirements, number is prime
		}
	}
}

// list divisors
void listDivisors(int number, vector<int>& divisors)
{
	double root = sqrt(number);

	if (number % 2 == 0)
	{
		for (int i = 2; i <= root; i += 2)
		{
			if (number % i == 0)
			{
				divisors.push_back(i);
			}
		}
		findRest(divisors, number); //find rest of divisors
	}
	else
	{
		for (int i = 3; i <= root; i += 2)
		{
			if (number % i == 0)
			{
				divisors.push_back(i);
			}
			findRest(divisors, number);
		}
	}
}

// Since we are only dividing up to the square root, we will not have the divisors greater than the sqaure root.
// To acquire the rest of the divisors, we simply divide the original number by divisors less than square root.
void findRest(vector<int>& divisors, int originalNumber)
{
	int range = divisors.size() - 1;
	float root = sqrt(originalNumber);
	for (int i = range; i >= 0; i--) //Iterate backwards to maintain increasing divisor order
	{
		if (originalNumber / divisors[i] == root) //skip if divisor is sqrt of original number (ie. 16 -> 4)
		{
			continue;
		}
		divisors.push_back(originalNumber / divisors[i]);
	}
}

// List Prime numbers up to given number
void listPrimes(int number, vector<int>& primes)
{
	//base case, push 2 if given number is >= 2
	if (number >= 2)
		primes.push_back(2);

	bool result;

	// check if odd numbers >= 3 are prime
	for (int i = 3; i <= number; i += 2)
	{
		result = checkPrime(i);
		if (result == true)
			primes.push_back(i); // add to prime list
	}
}