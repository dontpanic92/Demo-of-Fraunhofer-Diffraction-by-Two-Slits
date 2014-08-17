#ifndef __DRAW_H
#define __DRAW_H
#pragma once

class Draw{
public:
	struct Para{
		double theta;
		double phi, alpha;
		double lambda;
		double I;
		int x, y;
		double d;
		double N;
		double multi;
	};
	void init(int x, int y, int total, double dtotal, double d = 0.0015, double multi = 3, double lambda = 632.8);

	Para getNext();

	Draw();
private:
	void calc();

	Para para;
	int x, y, total;
	double dtotal;
	double next_theta;
};
#endif