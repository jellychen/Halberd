#ifndef Halberd_Kernal_Component_Hal_Component_Layout_H_
#define Halberd_Kernal_Component_Hal_Component_Layout_H_

#include "base/hal_inct.h"
#include "layout/hal_flex.h"
#include "hal_component_define.h"
#include "hal_component_attributes.h"

namespace kernal {
    class hal_component_layout : public hal_component_attributes {
    public:
        using hal_component_attributes::hal_component_attributes;

    public:
        virtual bool init_construct();

    public:
        // note: layout measure
        virtual hal_size measure_size(hal_size&, hal_layout_type);

        // note: layout children
        virtual void layout_children(const hal_rect&, const hal_rect&);

    public:
        // note: relative parent
        hal_rect rect() const;

        // note: relative document
        hal_rect document_relative_rect() const;

    protected:
        // note: when need relayout call this function
        void invalidate_layout();

        // note: when layout position
        void internal_set_layouted();

    protected:
        // note: layouter
        hal_flex flex_layout_;

        // note: is sync area index
        bool is_sync_area_index_ = false;
    };
}
#endif//Halberd_Kernal_Component_Hal_Component_Layout_H_
