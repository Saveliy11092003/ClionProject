#include <iostream>

int main(){
    int startLine = 4;
    int X = 20;
    int Y=20;
    int Z = 20;
    for (int i = 0; i < X; i++, startLine++) {
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < Z; k++) {
                std::cout << i * Y * Z + j * Z + k << std::endl;
            }
        }
    }
}