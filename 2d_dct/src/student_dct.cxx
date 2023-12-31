#include "main.h"


using namespace cv;


Mat LUT_w;
Mat LUT_h;


// Helper function
float sf(int in){
	if (in == 0)
		return 0.70710678118; // = 1 / sqrt(2)
	return 1.;
}

// Initialize LUT
void initDCT(int WIDTH, int HEIGHT)
{
	// TODO
}

// Baseline: O(N^4)
Mat student_dct(Mat input)
{
	const int HEIGHT = input.rows;
	const int WIDTH  = input.cols;

	float scale = 2./sqrt(HEIGHT*WIDTH);

	Mat result = Mat(HEIGHT, WIDTH, CV_32FC1);

	// Note: Using pointers is faster than Mat.at<float>(x,y)
	// Try to use pointers for your LUT as well
	float* result_ptr = result.ptr<float>();
	float* input_ptr  = input.ptr<float>();

	for(int x = 0; x < HEIGHT; x++)
	{
		for(int y = 0; y < WIDTH; y++)
		{
			float value = 0.f;

			for(int i = 0; i < HEIGHT; i++)
			{
				for(int j = 0; j < WIDTH; j++)
				{
					value += input_ptr[i * WIDTH + j]
						// TODO
						// --- Replace cos calculation by LUT ---
						* cos(M_PI/((float)HEIGHT)*(i+1./2.)*(float)x)
						* cos(M_PI/((float)WIDTH)*(j+1./2.)*(float)y);
				}
			}
			// TODO
			// --- Incorporate the scale in the LUT coefficients ---
			// --- and remove the line below ---
			value = scale * sf(x) * sf(y) * value;

			result_ptr[x * WIDTH + y] = value;
		}
	}

	return result;
}


// *****************
//   Hint
// *****************
//
// DCT as matrix multiplication

/*
Mat student_dct(Mat input)
{
	// -- Works only for WIDTH == HEIGHT
	assert(input.rows == input.cols);
	
	// -- Matrix multiply with OpenCV
	Mat output = LUT_w * input * LUT_w.t();

	// TODO
	// Replace the line above by your own matrix multiplication code
	// You can use a temp matrix to store the intermediate result

	return output;
}
*/





