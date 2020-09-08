#include "iostream"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


void mean_filtering(Mat image) {
    Mat clone = image.clone();
    int window_width = 9;
    int window_height = 9;
    int window_size = window_height * window_width;
    int dx = window_width / 2;
    int dy = window_height / 2;
    for (int i = dy; i < image.rows - dy; i++) {
        for (int j = dx; j < image.cols - dx; j++) {
            int sum = 0;
            for (int wi = i - dy; wi <= i + dy; wi++) {
                for (int wj = j - dx; wj <= j + dx; wj++) {
                    int data = (int) clone.at<uchar>(wi, wj);
                    sum += data;
                }
            }
            int val = sum / window_size;
            image.at<uchar>(i, j) = val;
        }
    }
}

void median_filtering(Mat image) {
    Mat clone = image.clone();
    int window_width = 5;
    int window_height = 5;
    int window_size = window_height * window_width;
    int dx = window_width / 2;
    int dy = window_height / 2;
    for (int i = dy; i < image.rows - dy; i++) {
        for (int j = dx; j < image.cols - dx; j++) {
            int myArray[25] = {0};
            int count = 0;
            for (int wi = i - dy; wi <= i + dy; wi++) {
                for (int wj = j - dx; wj <= j + dx; wj++) {
                    int data = (int) clone.at<uchar>(wi, wj);
                    myArray[count] = data;
                    count++;
                }
            }
            sort(myArray, myArray + window_size);
            int val;
            if (window_size % 2 != 0) {
                val = myArray[window_size / 2];
            } else {
                val = myArray[((window_size - 1) / 2 + myArray[window_size / 2]) / 2];
            }
            image.at<uchar>(i, j) = val;
        }
    }
}

void mode_filtering(Mat image) {
    Mat clone = image.clone();
    int window_width = 5;
    int window_height = 5;
    int window_size = window_height * window_width;
    int dx = window_width / 2;
    int dy = window_height / 2;
    for (int i = dy; i < image.rows - dy; i++) {
        for (int j = dx; j < image.cols - dx; j++) {
            int myArray[25] = {0};
            int count = 0;
            for (int wi = i - dy; wi <= i + dy; wi++) {
                for (int wj = j - dx; wj <= j + dx; wj++) {
                    int data = (int) clone.at<uchar>(wi, wj);
                    myArray[count] = data;
                    count++;
                }
            }
            sort(myArray, myArray + window_size);
            int val0 = 0;
            int val1 = myArray[0];
            int n0 = 0;
            int n1 = 1;
            for (int x = 1; x < window_size; x++) {
                if (myArray[x] == val1) {
                    n1++;
                } else if (n1 > n0) {
                    val0 = val1;
                    n0 = n1;
                    n1 = 1;
                } else {
                    val1 = myArray[x];
                    n1 = 1;
                }
            }
            image.at<uchar>(i, j) = val0;
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Image path is required" << endl;
        return 128;
    }
    if (argc < 3) {
        cout << "Filter type is required" << endl;
        cout << "0 - mean" << endl;
        cout << "1 - median" << endl;
        cout << "2 - mode" << endl;
        return 128;
    }
    string path = argv[1];
    Mat image = imread(path, IMREAD_GRAYSCALE);
    imshow("Original", image);
    int filter = atoi(argv[2]);
    switch (filter) {
        case 0:
            mean_filtering(image);
            imshow("Mean Filtering", image);
            break;
        case 1:
            median_filtering(image);
            imshow("Median Filtering", image);
            break;
        case 2:
            mode_filtering(image);
            imshow("Mode Filtering", image);
            break;

    }
    waitKey(0);
    return 0;
}