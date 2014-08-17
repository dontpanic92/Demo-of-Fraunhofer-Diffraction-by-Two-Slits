#include "stdafx.h"
#include "draw.h"
#include <cmath>
#include <stdio.h>
#define PI 3.141592653

Draw::Draw(){
	init(20, 20, 280, 4);
}

void Draw::init(int x, int y, int total, double dtotal, double d, double multi, double lambda){
	this->x = x;
	this->y = y;
	this->total = total;
	this->dtotal = dtotal;

	para.d = d;
	para.N = 2;
	para.multi = multi;
	para.lambda = lambda; //E-9
	para.x = x - 1;
	para.y = y + total;
	next_theta = 0.00001;//- PI / 4.0;
}

Draw::Para Draw::getNext(){
	calc();
	return para;
}

void Draw::calc(){
	//printf("%d %d\n", para.x, para.y);
	para.theta = next_theta;
	para.alpha = PI * para.d / para.multi * sin(para.theta) / para.lambda * 1E9;
	para.phi =  2 * PI * para.d * sin(para.theta) / para.lambda * 1E9;
	para.I = sin(para.alpha) * sin(para.alpha) / para.alpha / para.alpha *
				//sin(para.N * para.phi / 2) * sin(para.N * para.phi / 2) / sin(para.phi / 2) / sin(para.phi / 2);
				4 * cos(para.phi / 2) * cos(para.phi / 2);
	para.x += 1;
	para.y = y + total - para.I / dtotal * total;
	next_theta += 0.000005;
	if(next_theta > PI / 4.0)
		next_theta = - PI / 4.0;
}
