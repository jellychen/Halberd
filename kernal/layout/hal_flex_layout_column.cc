#include "hal_flex.h"
using namespace kernal;

bool hal_flex::layout_cloumn_wrap(
    std::shared_ptr<hal_component_layout>&, const hal_rect&) {
    return true;
}
