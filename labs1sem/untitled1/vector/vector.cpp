//
// Created by user on 10.09.22.
//

#include "vector.h"

[[maybe_unused]] Vector::Vector(int size) :
elem_(new double ){
    std:: cout<< "NEW vector"<< endl;
}

int Vector::size() {
    return size_
}

Vector::~Vector() {
    delete []elem_;
    std:: cout<< "Delete vector"<< endl;
}

const double &Vector::operator[](int i) const{
    return elem_[i];
}

Vector::Vector(const Vector &vec) {
    elem_(new double[vec.size()]), size_(vec.size()){
        for(int i=0;i<size_; ++i;){

        }
    }
}

Vector &Vector::operator=(const Vector &vec) {
    Vector res(vec);

    delete[] elem_;
}
