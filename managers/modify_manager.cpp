#include "modify_manager.h"

void modify_manager::modify_object(std::shared_ptr<object> _object, const point &move, const point &scale, const point &turn)
{
    _object->modify(move, scale, turn);
}

void modify_manager::move_object(std::shared_ptr<object> _object, const double &dx, const double &dy, const double &dz)
{
    point move(dx, dy, dz);
    point scale(1, 1, 1);
    point turn(0, 0, 0);

    _object->modify(move, scale, turn);
}

void modify_manager::scale_object(std::shared_ptr<object> _object, const double &kx, const double &ky, const double &kz)
{
    point move(0, 0, 0);
    point scale(kx, ky, kz);
    point turn(0, 0, 0);

    _object->modify(move, scale, turn);
}

void modify_manager::turn_object(std::shared_ptr<object> _object, const double &ox, const double &oy, const double &oz)
{
    point move(0, 0, 0);
    point scale(1, 1, 1);
    point turn(ox, oy, oz);

    _object->modify(move, scale, turn);
}

