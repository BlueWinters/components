
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
	// this is for condition 2
	const float f1_d2 = 0.f, fn_d2 = 0.f;

	// check the points validation
	if (points.size() <= 2 || isSequetial(points) == false)
		return false;

	int N = points.size();
	float* x = new float[N]();
	float* y = new float[N]();
	float* xx = new float[N-1]();
	float* yy = new float[N-1]();
	float* u = new float[N]();
	float* l = new float[N]();
	float* d = new float[N]();

	// convert basic coordinates
	int num_inters = 0;
	x[0] = points[0].first;
	y[0] = points[0].second;
	for (int n = 1; n < N; n++)
	{
		x[n] = float(points[n].first);
		y[n] = float(points[n].second);
		xx[n - 1] = x[n] - x[n - 1];
		yy[n - 1] = y[n] - y[n - 1];
		num_inters += int(xx[n - 1]);
	}
	// include the last point
	num_inters + 1;
	
	// calculate the mu, lambda, d...
	for (int n = 1; n < N-1; n++)
	{
		u[n] = xx[n-1] / (xx[n-1] + xx[n]);
		l[n] = 1.f - u[n];
		d[n] = 6 * (yy[n]/xx[n] - yy[n-1]/xx[n-1]) / (xx[n-1] + xx[n]);
	}
	l[0] = 0;
	d[0] = 2 * f1_d2;
	u[N-1] = 0;
	d[N-1] = 2 * fn_d2;

	// the matrix
	float* matrix = new float[N*N]();
	for (int n = 0; n < N-1; n++)
	{
		matrix[n*N + n] = 2;
		matrix[n*N + n + 1] = l[n];
		matrix[(n+1)*N + n] = u[n+1];
	}
	matrix[N*N - 1] = 2;

	// inverse matrix
	if (inverseSquare(matrix, N) == false)
		return false;

	float* M = new float[N]();
	//cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, 1, N, 1.f,
	//	matrix, N, d, 1, 0.f, M, 1);

	int pre_length = 0;
	int* inter_x = new int[num_inters];
	int* inter_y = new int[num_inters];
	for (int n = 0; n < N - 1; n++)
	{
		int counter = int(x[n+1] - x[n]);
		float tt1 = (M[n+1] - M[n]) / (6 * xx[n]);
		float tt2 = M[n] / 2;
		float tt3 = yy[n] / xx[n] - xx[n] * (M[n + 1] + 2 * M[n]) / 6;
		// interpolation between: x[n]~x[n+1]
		for (int i = 0; i < counter; i++)
		{
			inter_x[pre_length + i] = int(x[n] + i + 0.5);
			float t1 = tt1 * pow(i, 3);
			float t2 = tt2 * pow(i, 2);
			float t3 = tt3 * i;
			float t4 = y[n];
			inter_y[pre_length + i] = int(t1 + t2 + t3 + t4 + 0.5);
		}
		pre_length += counter;
	}
	// the last point
	inter_x[num_inters - 1] = int(x[N - 1] + 0.5f);
	inter_y[num_inters - 1] = int(y[N - 1] + 0.5f);

	// convert to output
	for (int n = 0; n < num_inters; n++)
		inter.push_back(std::make_pair(inter_x[n], inter_y[n]));

	// release all the buffers
	delete[] x;
	delete[] y;
	delete[] xx;
	delete[] yy;
	delete[] inter_x;
	delete[] inter_y;

	delete[] u;
	delete[] l;
	delete[] d;
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

