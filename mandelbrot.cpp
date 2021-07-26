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

#define xMin -2.25
#define xMax 0.75
#define yMin -1.3
#define yMax 1.3
#define ITER 200
#define M 50000
#define PIX_RANGE 255
#define N int((double(yMax-yMin)/(xMax-xMin))*M)

using namespace std;

void writePMG(vector<vector<uint16_t>>& set){

    ofstream imageFile;
    imageFile.open ("example.pgm");
    imageFile << "P2\n";
    imageFile << M << " " << N << "\n";
    imageFile << 255 << "\n";

    for(auto& i:set){
        for(auto& j:i){
            imageFile << j << " ";
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

    

    vector<vector<uint16_t>> set(N,vector<uint16_t>(M));
    cout << M << " X " << N << endl;



        #pragma omp parallel for
        for(int i = 0; i < N; i++){ 
            for(int j = 0; j < M; j++){
                double x, y;
                map(j,i,&x,&y);
                

                set[i][j] = 0;

                complex<double> z(x,y);

                for(int it = 0; it < ITER; it++){
                    complex<double> c(x,y);
                    z = z*z + c;

                    if(real(z*conj(z))>(xMin*xMin)){
                        set[i][j] = PIX_RANGE-int((double(it)/ITER)*PIX_RANGE);
                        break;
                    }

                }
                
            }
        }
    
    writePMG(set);
    return 0;
}