#include <iostream>
using namespace std;

bool checkDecimalPlaces(double newValue, double oldValue, int noOfUptoDecimalPlaces)
{
	bool doTheValuesMatch = false;
	
	char buffer[64];
	char oldValueCharString[64];
	char newValueCharString[64];
	
	snprintf(buffer, sizeof buffer, "%f", newValue);
	strcpy(newValueCharString, buffer);
	snprintf(buffer, sizeof buffer, "%f", oldValue);
	strcpy(oldValueCharString, buffer);
	
	int decimalIndex = 0;
	while (newValueCharString[decimalIndex] != NULL && newValueCharString[decimalIndex] != '.')	//Find the index of point(decimal).
	{
		decimalIndex++;
	}
	
	int status = strncmp(newValueCharString, oldValueCharString, decimalIndex + noOfUptoDecimalPlaces + 1);
	if (0 == status)
	{
		doTheValuesMatch = true;
	}
	
//	cout << newValueCharString << "\n" << oldValueCharString << "\n";
	
	return doTheValuesMatch;
}

void solveJacobiOrGaussSeidelIterative()
{
	float x, y, z, oldX, oldY, oldZ;
	float xyzCoefficients[12];	//0 = A, 1 = B, C, D, E, F, G, H, J, K, L
	int noOfMaxIterations = 15, currentNoOfIterations = 0;
	float noOfUptoDecimalPlaces = 3;
	bool hasReachedRequiredDecimalPlaces = false;
	
	bool isJacobi = true;	//Jacobi or Gauss Seidel
	bool iterationsOrUptoDecimalPlaces = true;	//
	
	char c;
	
	for (int i = 0; i < 12; i++)	//Get A, B, C, D, E, F, G, H, J, K and L
	{
		c = i + 65;
		cout << "Enter " << c << ":\t";
		cin >> xyzCoefficients[i];
	}
	
	cout << "Should the program run for some number of iterations or for upto some decimal places? [0 / 1]:\t";
	cin >> c;
	if ('0' == c)	//Iterations
	{
		iterationsOrUptoDecimalPlaces = true;
		
		cout << "Enter the number of iterations:\t";
		cin >> noOfMaxIterations;
	}
	else	//Decimal places
	{
		iterationsOrUptoDecimalPlaces = false;

		cout << "Enter the number of decimal places:\t";
		cin >> noOfUptoDecimalPlaces;
	}
	
	cout << "Jacobi or Gauss Seidel? [0 / 1]:\t";
	cin >> c;
	if ('0' == c)
	{
		isJacobi = true;
	}
	else
	{
		isJacobi = false;
	}
	
	while(hasReachedRequiredDecimalPlaces == false && currentNoOfIterations <= noOfMaxIterations)
	{
		float A = xyzCoefficients[0], B = xyzCoefficients[1], C = xyzCoefficients[2], D = xyzCoefficients[3], E = xyzCoefficients[4], F = xyzCoefficients[5], G = xyzCoefficients[6], H = xyzCoefficients[7], I = xyzCoefficients[8], J = xyzCoefficients[9], K = xyzCoefficients[10], L = xyzCoefficients[11];  
		
		if (0 == currentNoOfIterations++)
		{
			x = y = z = 0;
			
			cout << "\t\\intertext{\\textbf{";
			if (isJacobi)
			{
				cout << "Jacobi:} Iteration: " << currentNoOfIterations << "}\n";
			}
			else
			{
				cout << "Gauss Seidel:} Iteration: " << currentNoOfIterations << "}\n";
			}
		}

		if (isJacobi)
		{
			oldX = x, oldY = y, oldZ = z;
			
			x = (D - B * oldY - C * oldZ) / A;
			y = (H - E * oldX - G * oldZ) / F;
			z = (L - I * oldX - J * oldY) / K;

			cout << "\tx &= \\frac{" << D << " - (" << B << ") (" << oldY << ") - (" << C << ") (" << oldZ << ")}{" << A << "} = " << x << " \\\\\n";
			cout << "\ty &= \\frac{" << H << " - (" << E << ") (" << oldX << ") - (" << G << ") (" << oldZ << ")}{" << F << "} = " << y << " \\\\\n";
			cout << "\tz &= \\frac{" << L << " - (" << I << ") (" << oldX << ") - (" << J << ") (" << oldY << ")}{" << K << "} = " << z << " \\\\\n\t\\intertext{Iteration: " << currentNoOfIterations + 1 << "}\n";
		}
		else
		{
			oldX = x, oldY = y, oldZ = z;

			x = (D - B * y - C * z) / A;
			cout << "\tx &= \\frac{" << D << " - (" << B << ") (" << y << ") - (" << C << ") (" << z << ")}{" << A << "} = " << x << " \\\\\n";
			y = (H - E * x - G * z) / F;
			cout << "\ty &= \\frac{" << H << " - (" << E << ") (" << x << ") - (" << G << ") (" << z << ")}{" << F << "} = " << y << " \\\\\n";
			z = (L - I * x - J * y) / K;			
			cout << "\tz &= \\frac{" << L << " - (" << I << ") (" << x << ") - (" << J << ") (" << y << ")}{" << K << "} = " << z << " \\\\\n\t\\intertext{Iteration: " << currentNoOfIterations  + 1 << "}\n";
		}

		if (false == iterationsOrUptoDecimalPlaces)	//Upto some decimal places
		{
			if (currentNoOfIterations >= 2)	//Need at least 2 iterations for comparision.
			{
				bool doesX_match, doesY_match, doesZ_match;
				doesX_match = checkDecimalPlaces(x, oldX, noOfUptoDecimalPlaces);
				doesY_match = checkDecimalPlaces(y, oldY, noOfUptoDecimalPlaces);
				doesZ_match = checkDecimalPlaces(z, oldZ, noOfUptoDecimalPlaces);

				if (doesX_match && doesY_match && doesZ_match)
				{
					hasReachedRequiredDecimalPlaces = true;
				}
			}
		}
		
//		cout << "Iteration no = " << currentNoOfIterations << "\n";
//		cout << "x = " << x << " y = " << y << " z = " << z << "\n";
	}
}

void handle()
{
	bool toContinue = true;
	while(toContinue)
	{
		solveJacobiOrGaussSeidelIterative();
		char c;
		cout << "\nWould you like to add another entry? 'y'/any other:\t";
		cin >> c;
		if ('y' != c)
		{
			toContinue = false;
		}
		else
		{
			cout << "\n";
			cin.clear();	//https://stackoverflow.com/questions/14943789/cin-get-issue-with-empty-line
			cin.sync();
		}
	}	
}

int main(void)
{
	//cout << "\\\\\na";
	handle();
	
	return 0;
}