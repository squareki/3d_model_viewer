#include "simple_commands.h"

#include "../objects/composite.h"
#include "../facade/facade_simple.h"

simple_commands::simple_commands()
{
    this->_draw_manager = std::shared_ptr<draw_manager>(new draw_manager);
    std::shared_ptr<base_loader> floader(new file_loader);
    this->_load_manager = std::shared_ptr<abstract_loader>(new model_loader(floader));
}

void simple_commands::move_model_command(const double &dx, const double &dy, const double &dz, const size_t &mnumb)
{
    point move(dx, dy, dz);
    point scale(1, 1, 1);
    point turn(0, 0, 0);

    std::shared_ptr<object> model = this->_scene_manager.get_scene()->get_models().at(mnumb - 1);
    this->_modify_manager.modify_object(model, move, scale, turn);
}

void simple_commands::scale_model_command(const double &kx, const double &ky, const double &kz, const size_t &mnumb)
{
    point move(0, 0, 0);
    point scale(kx, ky, kz);
    point turn(0, 0, 0);

    std::shared_ptr<object> model = this->_scene_manager.get_scene()->get_models().at(mnumb - 1);
    this->_modify_manager.modify_object(model, move, scale, turn);
}

void simple_commands::turn_model_command(const double &ox, const double &oy, const double &oz, const size_t &mnumb)
{
    point move(0, 0, 0);
    point scale(1, 1, 1);
    point turn(ox, oy, oz);

    std::shared_ptr<object> model = this->_scene_manager.get_scene()->get_models().at(mnumb - 1);
    this->_modify_manager.modify_object(model, move, scale, turn);
}

void simple_commands::load_model_command(std::string fname)
{
    std::shared_ptr<model> model = this->_load_manager->load_model(fname);
    this->_scene_manager.get_scene()->add_model(model);
}

void simple_commands::add_model_command(const std::shared_ptr<object> &model)
{
    this->_scene_manager.get_scene()->add_model(model);
}

void simple_commands::remove_model_command(const size_t &mnumb)
{
    this->_scene_manager.get_scene()->remove_model(mnumb);
}

void simple_commands::add_camera_command(const double x, const double y, const double z)
{
    point cam_pos(x, y, z);
    std::shared_ptr<camera> cam(new camera);
    cam->modify(cam_pos, cam_pos, cam_pos);

    this->_scene_manager.get_scene()->add_camera(cam);
    this->_scene_manager.set_cam(this->_scene_manager.get_scene()->get_cams().get_size() - 1);
}

void simple_commands::remove_camera_command(const size_t &mnumb)
{
    this->_scene_manager.get_scene()->remove_camera(mnumb);
}

void simple_commands::draw_scene_command(const std::shared_ptr<base_drawer> _drawer)
{
    _drawer->clear_scene();
    this->_draw_manager->set_drawer(_drawer);
    this->_draw_manager->set_cam(this->_scene_manager.get_cam());
    this->_scene_manager.get_scene()->get_composite()->accept(this->_draw_manager);
}

void simple_commands::modify_model_command(const size_t &mnumb, const point &move, const point &scale, const point &turn)
{
    std::shared_ptr<object> model = this->_scene_manager.get_scene()->get_models().at(mnumb - 1);
    this->_modify_manager.modify_object(model, move, scale, turn);
}

void simple_commands::move_camera_command(const size_t &cam_number, const double &shift_ox, const double &shift_oy)
{
    point shift(shift_ox, shift_oy, 0);

    auto camera = this->_scene_manager.get_scene()->get_cams().at(cam_number - 1);
    this->_modify_manager.modify_object(camera, shift, shift, shift);
}

size_t simple_commands::get_cams_count()
{
    return this->_scene_manager.get_scene()->get_cams().get_size();
}
size_t simple_commands::get_models_count()
{
    return this->_scene_manager.get_scene()->get_models().get_size();
}
