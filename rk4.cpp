#include <fstream>
#include <cmath>
#include <array>

struct State
{
	double x;
	double t;
	State(double xin, double tin) : x(xin), t(tin) {}
};

double dxdt(State s);

double rk4(State s, double(*f)(State s), double step);

int main()
{
	// define parameters
	constexpr double a = 0.0;
	constexpr double b = 10.0;
	constexpr int N = 10;
	constexpr double h = (b - a) / N;

	// declare arrays
	std::array<double, N> tpoints;
	std::array<double, N> xpoints;

	// establish initial values
	tpoints[0] = xpoints[0] = 0.0;
	for (int i = 0; i < N; ++i)
		tpoints[i] = i * h;

	// main loop
	for (int i = 0; i < N - 1; ++i)
	{
		double t = tpoints[i];
		double x = xpoints[i];

		xpoints[i + 1] = x + rk4(State(x, t), dxdt, h);
	}

	// save results
	std::ofstream file("rk4_results.txt");
	for (int i = 0; i < N; ++i)
	{
		file << tpoints[i] << " " << xpoints[i] << std::endl;
	}
}

double dxdt(State s)
{
	double x = s.x;
	double t = s.t;
	return -x * x * x + sin(t);
}

double rk4(State s, double(*f)(State s), double step)
{
	// input state
	double x = s.x;
	double t = s.t;

	// intermediate steps
	double k1 = step * f(s);
	double k2 = step * f(State(x + 0.5 * k1, t + 0.5 * step));
	double k3 = step * f(State(x + 0.5 * k2, t + 0.5 * step));
	double k4 = step * f(State(x + k3, t + step));

	return (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}
