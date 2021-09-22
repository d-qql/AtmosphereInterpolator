//
// Created by d-qql on 22.09.2021.
//

#ifndef VICHMATY1_TRIPLET_HPP
#define VICHMATY1_TRIPLET_HPP

struct Triplet{
    using elm_t = double;
    using idx_t = std::size_t;
    elm_t value;
    idx_t i;
    idx_t j;
    bool operator<(Triplet const &rgh) const{
        return this->i<rgh.i || (this->i == rgh.i && this->j < rgh.j);
    }
};
#endif //VICHMATY1_TRIPLET_HPP
