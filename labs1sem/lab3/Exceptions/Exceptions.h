//
// Created by user on 29.12.22.
//

#ifndef LAB3_EXCEPTIONS_H
#define LAB3_EXCEPTIONS_H

#include <iostream>

namespace Exceptions {

    class AbstrExcp {
    public:
        virtual int errorCode() const = 0;
        virtual ~AbstrExcp() {};
    };

    class CanNotOpenFile : public AbstrExcp {
    public:
        CanNotOpenFile();
        int errorCode() const override;
    };

    class InapropriateFile : public AbstrExcp {
    public:
        InapropriateFile();
        int errorCode() const override;
    };

    class OutOfRange : public AbstrExcp {
    public:
        OutOfRange();
        int errorCode() const override;
    };

    class InapropriateConv : public AbstrExcp {
    public:
        InapropriateConv();
        int errorCode() const override;
    };

    class WrongParameters : public AbstrExcp {
    public:
        WrongParameters();
        int errorCode() const override;
    };

    class WrongComandLineParameters : public AbstrExcp {
    public:
        WrongComandLineParameters();
        int errorCode() const override;
    };
};


#endif //LAB3_EXCEPTIONS_H
