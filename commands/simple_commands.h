#ifndef SIMPLE_COMMANDS_H
#define SIMPLE_COMMANDS_H

#include "../load/abstract_loader.h"
#include "../managers/draw_manager.h"
#include "../managers/modify_manager.h"
#include "../managers/scene_manager.h"
#include "../objects/model.h"
#include "../objects/camera.h"

class simple_commands
{
public:
    static std::shared_ptr<simple_commands> get_instance()
    {
        static std::shared_ptr<simple_commands> _simple_commands(new simple_commands());

        return _simple_commands;
    }


    void move_model_command(const double &dx, const double &dy, const double &dz, const size_t &mnumb);
    void scale_model_command(const double &kx, const double &ky, const double &kz, const size_t &mnumb);
    void turn_model_command(const double &ox, const double &oy, const double &oz, const size_t &mnumb);
    void load_model_command(std::string fname);
    void add_model_command(const std::shared_ptr<object> &model);
    void remove_model_command(const size_t &mnumb);
    void add_camera_command(const double x, const double y, const double z);
    void remove_camera_command(const size_t &mnumb);
    void draw_scene_command(const std::shared_ptr<base_drawer> drawer);
    void modify_model_command(const size_t &numb, const point &move, const point &scale, const point &turn);
    void move_camera_command(const size_t &cam_number, const double &shift_ox, const double &shift_oy);

    size_t get_cams_count();
    size_t get_models_count();

private:
    simple_commands();
    simple_commands(const simple_commands &) = delete;
    simple_commands &operator=(const simple_commands &) = delete;

    scene_manager _scene_manager;
    modify_manager _modify_manager;
    std::shared_ptr<abstract_loader> _load_manager;
    std::shared_ptr<draw_manager> _draw_manager;
};

#endif // SIMPLE_COMMANDS_H
