#include "CameraControls.h"

#include <trview.ui/GroupBox.h>
#include <trview.ui/Checkbox.h>
#include <trview.ui/Button.h>
#include <trview.ui/Slider.h>
#include <trview.ui/Label.h>

namespace trview
{
    CameraControls::CameraControls(ui::Control& parent)
    {
        using namespace ui;

        auto camera_window = std::make_unique<GroupBox>(Point(), Size(150, 152), Colour::Transparent, Colour::Grey, L"Camera");

        auto reset_camera = std::make_unique<Button>(Point(12, 20), Size(16, 16));
        reset_camera->on_click += on_reset;

        auto reset_camera_label = std::make_unique<Label>(Point(30, 20), Size(40, 16), Colour::Transparent, L"Reset", 8, graphics::TextAlignment::Left, graphics::ParagraphAlignment::Centre);

        auto orbit_camera = std::make_unique<Checkbox>(Point(86, 20), Size(16, 16), Colour::Transparent, L"Orbit");
        _token_store += orbit_camera->on_state_changed += [&](auto) { change_mode(CameraMode::Orbit); };

        auto free_camera = std::make_unique<Checkbox>(Point(12, 42), Size(16, 16), Colour::Transparent, L"Free");
        _token_store += free_camera->on_state_changed += [&](auto) { change_mode(CameraMode::Free); };

        auto axis_camera = std::make_unique<Checkbox>(Point(86, 42), Size(16, 16), Colour::Transparent, L"Axis");
        _token_store += axis_camera->on_state_changed += [&](auto) { change_mode(CameraMode::Axis); };

        // Camera section for the menu bar.
        auto camera_sensitivity_box = std::make_unique<GroupBox>(Point(12, 64), Size(130, 40), Colour::Transparent, Colour::Grey, L"Sensitivity");
        auto camera_sensitivity = std::make_unique<ui::Slider>(Point(6, 12), Size(118, 16));
        
        auto movement_speed_box = std::make_unique<GroupBox>(Point(12, 104), Size(130, 40), Colour::Transparent, Colour::Grey, L"Movement Speed");
        auto movement_speed = std::make_unique<ui::Slider>(Point(6, 12), Size(118, 16));

        camera_sensitivity->on_value_changed += on_sensitivity_changed;
        movement_speed->on_value_changed += on_movement_speed_changed;

        _sensitivity = camera_sensitivity_box->add_child(std::move(camera_sensitivity));
        _movement_speed = movement_speed_box->add_child(std::move(movement_speed));

        camera_window->add_child(std::move(reset_camera));
        camera_window->add_child(std::move(reset_camera_label));
        _orbit = camera_window->add_child(std::move(orbit_camera));
        _free = camera_window->add_child(std::move(free_camera));
        _axis = camera_window->add_child(std::move(axis_camera));
        camera_window->add_child(std::move(camera_sensitivity_box));
        camera_window->add_child(std::move(movement_speed_box));

        parent.add_child(std::move(camera_window));
    }

    // Set the current camera mode and raise the on_mode_selected event.
    // mode: The new camera mode.
    void CameraControls::change_mode(CameraMode mode)
    {
        set_mode(mode);
        on_mode_selected(mode);
    }

    // Set the sensitivity slider to the specified value. This will not raise the on_sensitivity_changed event.
    // value: The sensitivity value.
    void CameraControls::set_sensitivity(float value)
    {
        _sensitivity->set_value(value);
    }

    // Set the movement speed slider to specified value.
    // value: The movement speed.
    void CameraControls::set_movement_speed(float value)
    {
        _movement_speed->set_value(value);
    }

    // Set the current camera mode. This will not raise the on_mode_selected event.
    // mode: The camera mode to change to.
    void CameraControls::set_mode(CameraMode mode)
    {
        _orbit->set_state(mode == CameraMode::Orbit);
        _free->set_state(mode == CameraMode::Free);
        _axis->set_state(mode == CameraMode::Axis);
    }
}