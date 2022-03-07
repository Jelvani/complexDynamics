#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <array>
#include <vector>
#include <complex>      
#include <cstdint>
#include <omp.h>

//M: width, N: height

#define xMin -1.3
#define xMax 1.3
#define yMin -1.3
#define yMax 1.3
#define ITER 200
#define M 4000
#define PIX_RANGE 255
#define N int((double(yMax-yMin)/(xMax-xMin))*M)

using namespace std;

void writePMG(vector<vector<vector<uint16_t>>>& set){

    ofstream imageFile;
    imageFile.open ("example.pgm");
    imageFile << "P3\n";
    imageFile << M << " " << N << "\n";
    imageFile << PIX_RANGE << "\n";

    for(auto& i:set){
        for(auto& j:i){
            for(auto& z:j){
                imageFile << z << " ";
            }
            imageFile << "   ";
        }
        imageFile << "\n";
    }

    imageFile.close();
}

//takes in x and y pixel cooridnate, outputs equation mappings
void map(int x, int y, double* outX, double* outY){
    *outX = (double(x)/M)*(xMax-xMin)+double(xMin);
    *outY= (double(y)/N)*(yMax-yMin)+double(yMin);
}

int main() {

    

    vector<vector<vector<uint16_t>>> set(N,vector<vector<uint16_t>>(M,vector<uint16_t>(3)));
    cout << M << " X " << N << endl;


    //pow(0.65-0.4198i,1),  pow(z,4);
    //pow(0.3755-0.3i,1)

    complex<double> c = pow(-0.071-0.665i,0.999);

        #pragma omp parallel for
        for(int i = 0; i < N; i++){ 
            for(int j = 0; j < M; j++){
                double x, y;
                map(j,i,&x,&y);
                

                set[i][j][0] = 255;
                set[i][j][1] = 100;
                set[i][j][2] = 0;

                complex<double> z(x,y);
                for(int it = 0; it < ITER; it++){
                    z = pow(z,2) + c;

                    //if escaped to infinity very quickly, we set the pixel to a fixed color
                    if(real(z*conj(z))>(xMin*xMin) && it < 6){
                        set[i][j][0] = 0;
                        set[i][j][1] = 0;
                        set[i][j][2] = 0;
                        break;
                    }
                    //otherwise, we color it accoridng to iteration count
                    if(real(z*conj(z))>(xMin*xMin)){
                        set[i][j][0] = 200;
                        set[i][j][1] = 0;
                        set[i][j][2] = sin(int((double(it)/ITER)*PIX_RANGE/4))*PIX_RANGE/30;
                        break;
                    }

                }
                
            }
        }
    
    writePMG(set);
    return 0;
}