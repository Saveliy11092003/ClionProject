//
// Created by user on 10.09.22.
//

#ifndef UNTITLED1_VECTOR_H
#define UNTITLED1_VECTOR_H


class Vector {
private:
    double *elem_;
    int size_;
public:
    [[maybe_unused]] Vector(int size);

    [[maybe_unused]] Vector(std::initializer_list )

    int size();

    ~Vector();//диструктор

    const double &operator[](int i) const;

    Vector(const Vector &vec);

    Vector &operator = (const Vector &vec);
};





#endif //UNTITLED1_VECTOR_H
