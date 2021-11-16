#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _facade_simple(nullptr)
{
    ui->setupUi(this);
    this->setup_scene();
    this->_facade_simple = std::shared_ptr<facade_simple>(facade_simple::instance());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check_cam_exist()
{
    auto facade = this->_facade_simple;
    if (!facade->get_commands()->get_cams_count())
    {
        std::string message = "No camera found.";
        throw camera_error(message);
    }
}

void MainWindow::check_models_exist()
{
    auto facade = this->_facade_simple;
    if (!facade->get_commands()->get_models_count())
    {
        std::string message = "No models found.";
        throw model_error(message);
    }
}

void MainWindow::on_move_button_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    } catch (const camera_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной камеры.");
        return;
    } catch (const model_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    auto coms = _facade_simple->get_commands();
    auto f = std::bind(&simple_commands::move_model_command, coms, 10, 10, 10, 1);
    _facade_simple->execute(f);
    update_scene();
}

void MainWindow::on_scale_button_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    } catch (const camera_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной камеры.");
        return;
    } catch (const model_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    auto coms = _facade_simple->get_commands();
    auto f = std::bind(&simple_commands::scale_model_command, coms, 2, 2, 2, 1);
    _facade_simple->execute(f);
    update_scene();
}

void MainWindow::on_turn_button_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    } catch (const camera_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной камеры.");
        return;
    } catch (const model_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    auto coms = _facade_simple->get_commands();
    auto f = std::bind(&simple_commands::turn_model_command, coms, 3, 3, 3, 1);
    _facade_simple->execute(f);
    update_scene();
}

void MainWindow::on_load_button_clicked()
{
    try
    {
        check_cam_exist();
    } catch (const camera_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Прежде чем добавлять модель, добавьте хотя бы одну камеру.");
        return;
    }

    //load_model load_command("D:/Studies/2 year/OOP/Lab3/data/model.csv");
    const std::string name = "D:/Studies/2 year/OOP/Lab3/data/model.csv";

    try
    {
        auto coms = _facade_simple->get_commands();
        auto f = std::bind(&simple_commands::load_model_command, coms, name);
        _facade_simple->execute(f);

    } catch (const file_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Что-то не так пошло при загрузке файла...");
        return;
    }

    update_scene();
}

void MainWindow::setup_scene()
{
    this->_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(_scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->_scene->setSceneRect(0, 0, win_x, win_y);

    std::shared_ptr<abstract_factory> factory(new qt_factory);
    std::shared_ptr<base_drawer> drawer(new qt_drawer(this->_scene));
    this->_drawer = drawer;
}

void MainWindow::update_scene()
{
    auto coms = _facade_simple->get_commands();
    auto f = std::bind(&simple_commands::draw_scene_command, coms, _drawer);
    _facade_simple->execute(f);
}

void MainWindow::on_add_camera_clicked()
{
    auto coms = _facade_simple->get_commands();
    auto f = std::bind(&simple_commands::add_camera_command, coms, win_x / 2, win_y / 2, 0);
    this->_facade_simple->execute(f);
}

void MainWindow::on_right_button_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    } catch (const camera_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной камеры.");
        return;
    } catch (const model_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    auto coms = _facade_simple->get_commands();
    auto f = std::bind(&simple_commands::move_camera_command, coms, 1, 10, 0);
    _facade_simple->execute(f);
    update_scene();
}

void MainWindow::on_up_button_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    } catch (const camera_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной камеры.");
        return;
    } catch (const model_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    auto coms = _facade_simple->get_commands();
    auto f = std::bind(&simple_commands::move_camera_command, coms, 1, 0, 10);
    _facade_simple->execute(f);
    update_scene();
}

void MainWindow::on_down_button_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    } catch (const camera_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной камеры.");
        return;
    } catch (const model_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    auto coms = _facade_simple->get_commands();
    auto f = std::bind(&simple_commands::move_camera_command, coms, 1, 0, -10);
    _facade_simple->execute(f);
    update_scene();
}

void MainWindow::on_left_button_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    } catch (const camera_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной камеры.");
        return;
    } catch (const model_error &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    auto coms = _facade_simple->get_commands();
    auto f = std::bind(&simple_commands::move_camera_command, coms, 1, -10, 0);
    _facade_simple->execute(f);
    update_scene();
}
