
#include <iostream>
#include <vector>
#include <utility>
#include <mkl_lapacke.h>



void matrixToString(float* matrix, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf(" %4.3f", matrix[i*m + j]);
		}
		printf("\n");
	}
	printf("\n");
}

bool inverseSquare(float* matrix, int n)
{
	int lda = n;
	int info = 0;
	int* ipiv = new int[n];
	
	// TODO: LU factorization
	if (LAPACKE_sgetrf(LAPACK_COL_MAJOR, n, n, matrix, lda, ipiv) != 0)
		return false;
	// TODO: inverse of an LU-factored general matrix
	if (LAPACKE_sgetri(LAPACK_COL_MAJOR, n, matrix, lda, ipiv) != 0)
		return false;
	
	delete[] ipiv;
	return true;
}

bool isSequetial(std::vector<std::pair<float, float>>& x)
{
	int n = 0;
	while (n < x.size() - 1 && x[n].first < x[n + 1].first)
		n++;
	return (n == x.size());
}

bool spline(std::vector<std::pair<float, float>>& points, std::vector<std::pair<float, float>>& inter)
{
	if (points.size() <= 2 || isSequetial(points) == false)
		return false;

	int N = points.size();
	float* h = new float[N-1]();
	float* u = new float[N-1]();
	float* l = new float[N-1]();
	
	h[0] = points[1].first - points[0].first;
	for (int n = 1; n < N-1; n++)
	{
		h[n] = points[n].first - points[n-1].second;
		u[n] = h[n-1] / (h[n-1] + h[n]);
		l[n] = 1 - u[n];
	}

	float* matrix = new float[N*N]();
	for (int n = 0; n < N; n++)
	{
		// TODO:
		matrix[n*N + n] = 2;
		matrix[n*N + n + 1] = l[n];
	}
}




int main()
{
	float a[] =
	{
		+3,+4, -3,
		-1,-2, +2,
		-1,-1, +1,
	};
	
	inverseSquare(a, 3);
	matrixToString(a, 3, 3);
}

