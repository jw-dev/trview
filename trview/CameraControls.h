#pragma once

#include <trview.common/Event.h>
#include "CameraMode.h"

namespace trview
{
    namespace ui
    {
        class Control;
        class Button;
        class Slider;
    }

    struct ITextureStorage;

    // The camera controls control has settings for the operation mode of the camera and
    // other camera related settings.
    class CameraControls
    {
    public:
        CameraControls(ui::Control& parent, const ITextureStorage& texture_storage);

        // Event raised when the camera mode has been selected by the user.
        // camera_mode: The newly selected camera mode.
        Event<CameraMode> on_mode_selected;

        // Event raised when the camera sensitivity has been changed by the user.
        // sensitivity: The new sensitivity value.
        Event<float> on_sensitivity_changed;

        // Event raised when the user clicks the reset button.
        Event<void> on_reset;

        // Set the sensitivity slider to the specified value. This will not raise the on_sensitivity_changed event.
        // value: The sensitivity value.
        void set_sensitivity(float value);

        // Set the current camera mode. This will not raise the on_mode_selected event.
        // mode: The camera mode to change to.
        void set_mode(CameraMode mode);
    private:
        // Set the current camera mode and raise the on_mode_selected event.
        // mode: The new camera mode.
        void change_mode(CameraMode mode);

        ui::Button* _orbit;
        ui::Button* _free;
        ui::Slider* _sensitivity;
    };
}
