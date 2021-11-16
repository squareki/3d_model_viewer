#ifndef REFORM_MANAGER_H
#define REFORM_MANAGER_H

#include "../objects/component.h"
#include "base_manager.h"

class modify_manager : public base_manager
{
public:
    modify_manager() = default;
    ~modify_manager() = default;

    void modify_object(std::shared_ptr<object> _object, const point &move, const point &scale, const point &turn);

    void move_object(std::shared_ptr<object> _object, const double &dx, const double &dy, const double &dz);
    void scale_object(std::shared_ptr<object> _object, const double &kx, const double &ky, const double &kz);
    void turn_object(std::shared_ptr<object> _object, const double &ox, const double &oy, const double &oz);
};

#endif
