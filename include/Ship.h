#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <stdexcept>
#include <iostream>

#include <QDebug>


struct IndexErr : std::runtime_error {
        IndexErr(const std::string& msg): runtime_error("IndexErr:" + msg) {}
};

struct RangeErr : std::runtime_error {
        RangeErr(const std::string& msg): runtime_error("RangeErr: " + msg) {}
};

struct LogicErr : std::runtime_error {
        LogicErr(const std::string& msg): runtime_error("LogicErr: " + msg) {}
};

class CargoBox {
    public:
        int weight;
        int price;

        CargoBox(int w, int p) : weight{w}, price{p} {
            if (w < 0 || p < 0) {
                throw IndexErr("Box's weight and price should be zero or positive numbers");
            }
        }
};

struct Specification {
    int liftingCapactiy;
};

class Ship {
    public:
        Ship(int liftingCapacity = -1) : specs{liftingCapacity} { std::cout << "SHIP done\n"; }

        void updateCap(int newCap) {
            if (newCap <= 0) {
                throw RangeErr("newCap must be non zero");
            }
            this->specs.liftingCapactiy = newCap;
        }

        int getCap() {
            return this->specs.liftingCapactiy;
        }

        bool isOverloaded(int weight) {
            return weight >= this->specs.liftingCapactiy;
        }

    private:
        Specification specs;
};

#endif
