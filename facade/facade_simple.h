#ifndef facade_simple_SIMPLE_H
#define facade_simple_SIMPLE_H


#include "../commands/simple_commands.h"
#include "../load/loader.h"
#include "../managers/draw_manager.h"
#include "../managers/scene_manager.h"
#include "../managers/modify_manager.h"
//#include "../scene/scene.h"

class facade_simple
{
public:
    static std::shared_ptr<facade_simple> instance()
    {
        static std::shared_ptr<facade_simple> _facade_simple(new facade_simple());

        return _facade_simple;
    }

    ~facade_simple() = default;

    void execute(std::function<void()> f)
    {
        f();
    }

    template<typename R, typename ...A>
    void execute_generic(R (*f)(A...))
    {
        //execute_generic(std::function<R(A...)>(f));
        std::function<R(A...)> internal(f);
    }

    template<typename R, typename ...A>
    void execute_any(std::function<R(A...)> f)
    {
        f();
    }

    simple_commands* get_commands()
    {
        return this->commands.get();
    }

private:
    facade_simple()
    {
        this->commands = simple_commands::get_instance();
    }
    facade_simple(const facade_simple &) = delete;
    facade_simple &operator=(const facade_simple &) = delete;

    std::shared_ptr<simple_commands> commands;
};

#endif
