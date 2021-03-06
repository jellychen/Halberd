#ifndef Halberd_Kernal_Render_Al_Canvas_Hal_Render_Surface_Canvas_H_
#define Halberd_Kernal_Render_Al_Canvas_Hal_Render_Surface_Canvas_H_

#include "base/hal_inct.h"
#include "utils/hal_t_define.h"
#include "hal_render_canvas.h"

namespace kernal {
    class hal_render_context_base;
    class hal_render_surface_canvas : public hal_render_canvas {
    public:
        friend class hal_render_context_base;
        hal_render_surface_canvas(const hal_size& size);
        virtual ~hal_render_surface_canvas();

    public:
        void resize(const hal_size& size);
        void capture_to_file(const char* file);

    public:
        hal_size size() const;

    private:
        SkCanvas* raw_unsafe_canvas();

    private:
        sk_sp<SkSurface> surface_;
    };
}
#endif//Halberd_Kernal_Render_Al_Canvas_Hal_Render_Surface_Canvas_H_
