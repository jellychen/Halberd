#ifndef Halberd_Kernal_Component_Hal_Component_Render_H_
#define Halberd_Kernal_Component_Hal_Component_Render_H_

#include "base/hal_inct.h"
#include "hal_component_layout.h"
#include "render_recoder/hal_render_recoder_inct.h"

namespace kernal {
    class hal_component_render : public hal_component_layout {
    public:
        using hal_component_layout::hal_component_layout;

    public:
        // note: render recoder
        std::shared_ptr<hal_render_command_buffer> render_command_buffer();

    public:
        // note: called
        void render(std::shared_ptr<hal_render_command_context>&);

    protected:
        // note: render function
        virtual void paint(std::shared_ptr<hal_render_command_context>&);

        // note: when need rerender call this function
        virtual void invalidate_render();

    protected:
        bool is_need_render = true;
    };
}
#endif//Halberd_Kernal_Component_Hal_Component_Render_H_
