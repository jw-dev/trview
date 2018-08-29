/// @file ItemsWindow.h
/// @brief Used to show and filter the items in the level.

#pragma once

#include <trview.common/MessageHandler.h>
#include <trview.graphics/Device.h>
#include <trview.input/Mouse.h>
#include <trview.common/TokenStore.h>
#include <trview.ui/Listbox.h>
#include "WindowResizer.h"
#include "Item.h"

namespace trview
{
    namespace graphics
    {
        struct IShaderStorage;
        class FontFactory;
    }

    namespace ui
    {
        namespace render
        {
            class Renderer;
        }
    }

    /// Used to show and filter the items in the level.
    class ItemsWindow final : public MessageHandler
    {
    public:
        /// Create an items window as a child of the specified window.
        /// @param device The graphics device
        /// @param shader_storage The shader storage instance to use.
        /// @param font_factory The font factory to use.
        /// @param parent The parent window.
        explicit ItemsWindow(const graphics::Device& device, const graphics::IShaderStorage& shader_storage, const graphics::FontFactory& font_factory, HWND parent);

        /// Destructor for items window
        virtual ~ItemsWindow() = default;

        /// Handles a window message.
        /// @param window The window that received the message.
        /// @param message The message that was received.
        /// @param wParam The WPARAM for the message.
        /// @param lParam The LPARAM for the message.
        virtual void process_message(HWND window, UINT message, WPARAM wParam, LPARAM lParam) override;

        /// Render the window and contents.
        /// @param device The device to render with.
        /// @param vsync Whether to use vsync when rendering.
        void render(const graphics::Device& device, bool vsync);

        /// Set the items to display in the window.
        /// @param items The items to show.
        void set_items(const std::vector<Item>& items);

        /// Event raised when an item is selected in the list.
        Event<Item> on_item_selected;

        /// Event raised when the items window is closed.
        Event<> on_window_closed;

        /// Set the current room. This will be used when the track room setting is on.
        /// @param room The current room number.
        void set_current_room(uint32_t room);
    private:
        void generate_ui();
        void populate_items(const std::vector<Item>& items);

        WindowResizer _window_resizer;
        std::unique_ptr<graphics::DeviceWindow> _device_window;
        std::unique_ptr<ui::Window> _ui;
        ui::Listbox* _items_list;
        std::unique_ptr<ui::render::Renderer> _ui_renderer;
        input::Mouse _mouse;
        TokenStore _token_store;

        std::vector<Item> _all_items;
        bool _track_room{ false };
        uint32_t _current_room{ 0u };
    };
}
