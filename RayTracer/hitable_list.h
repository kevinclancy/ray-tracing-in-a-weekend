#pragma once

#include "hitable.h"
#include <memory>
#include <vector>

class hitable_list : public hitable {
public:
    hitable_list() {}
    hitable_list(const hitable_list& l) = delete;
    hitable_list(std::vector<std::shared_ptr<hitable>> l) : list{ l }  { }
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

    std::vector<std::shared_ptr<hitable>> list;
};
