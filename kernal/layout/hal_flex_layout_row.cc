#include "hal_flex.h"
#include "component/hal_component.h"
using namespace kernal;

bool hal_flex::layout_row_wrap(const hal_flex_layout_param& param) {
    auto component = host_component_.lock();
    if (!component) return false;

    hal_css_t& css = component->css_;
    int current_line_start =0, current_line_elements_count =0;
    int current_line_flex_total = 0, current_line_flex_total_maybe = 0;
    float current_line_use_width =0, current_line_use_width_maybe = 0;
    float current_line_max_height =0, current_line_max_height_maybe = 0;
    float current_line_flex_min_width =0, current_line_flex_min_width_maybe =0;
    float avaliable_width = param.size_.width_ - css.border_.left_
        - css.border_.right_ - css.padding_.left_ - css.padding_.right_;
    float avaliable_height = param.size_.height_ - css.border_.top_
        - css.border_.bottom_ - css.padding_.top_ - css.padding_.bottom_;

    // note: loop all children
    for (uint32_t index = 0; index < component->children_count();) {
        auto child = std::dynamic_pointer_cast<hal_component_layout>(component->at(index));
        if (!child) {
            ++index; continue;
        }

        hal_css_t& child_css = child->css_;
        // note: not visible
        if (hal_css_display_none == child_css.display_) {
            ++index; continue;
        }

        // note: fixed element
        if (hal_css_postion_fixed == child_css.position_) {
            ++index; continue;
        }

        // note: absolute elment
        if (hal_css_postion_absolute == child_css.position_) {
            hal_flex::layout_absolute(param, child);
            ++index; continue;
        }

        // note: clac width
        current_line_use_width_maybe +=
            child_css.margin_.left_ + child_css.margin_.right_;
        if (_is_css_val_valid(child_css.flex_grow_)) {
            // note: use cache
            hal_flex_layout_size& cache_item = measure_cache_[index];
            if (!(cache_item.measured_ && cache_item.limit_ < 0)) {
                hal_size limit_size = hal_size_make(0, 0);
                cache_item.measure_size_ = child->measure_size(
                    limit_size, hal_layout_no_limited);
                cache_item.measured_ = true; cache_item.limit_ = -1;
            }
            current_line_flex_total_maybe += child_css.flex_grow_;
            current_line_use_width_maybe += cache_item.measure_size_.width_;
            current_line_flex_min_width_maybe += cache_item.measure_size_.width_;
        } else {
            float width = 0;
            if (_is_css_val_valid(child_css.size_.width_)) {
                width = child_css.clamp_width();
            } else {
                // note: use cache
                hal_flex_layout_size& cache_item = measure_cache_[index];
                if (!(cache_item.measured_ && cache_item.limit_ < 0)) {
                    hal_size limit_size = hal_size_make(0, 0);
                    cache_item.measure_size_ = child->measure_size(
                        limit_size, hal_layout_no_limited);
                    cache_item.measured_ = true; cache_item.limit_ = -1;
                }
                width = cache_item.measure_size_.width_;
            }
            current_line_use_width_maybe += width;
        }

        // note: clac height
        float need_height = child_css.margin_.top_ + child_css.margin_.bottom_;
        if (_is_css_val_valid(child_css.size_.height_)) {
            need_height += child_css.clamp_height();
        } else {
            // note: if assgin width
            if (_is_css_val_valid(child_css.size_.width_)) {
                // note: use cache
                float width = child_css.clamp_width();
                hal_flex_layout_size& cache_item = measure_cache_[index];
                if (!(cache_item.measured_ && cache_item.limit_ == width)) {
                    hal_size limit_size = hal_size_make(width, 0);
                    cache_item.measure_size_ = child->measure_size(
                        limit_size, hal_layout_assgin_width);
                    cache_item.measured_ = true; cache_item.limit_ = width;
                }
                need_height += cache_item.measure_size_.height_;
            }
            // note: if no limited
            else {
                // note: use cache
                hal_flex_layout_size& cache_item = measure_cache_[index];
                if (!(cache_item.measured_ && cache_item.limit_ < 0)) {
                    hal_size limit_size = hal_size_make(0, 0);
                    cache_item.measure_size_ = child->measure_size(
                        limit_size, hal_layout_no_limited);
                    cache_item.measured_ = true; cache_item.limit_ = -1;
                }
                need_height += cache_item.measure_size_.height_;
            }
        }

        // note: mark max height
        if (need_height > current_line_max_height_maybe) {
            current_line_max_height_maybe = need_height;
        }

        // note: layout online
        if ((current_line_elements_count > 0
            && current_line_use_width_maybe >= avaliable_width)
                || index == component->children_count() -1) {
            if (index == component->children_count() -1) {
                ++current_line_elements_count; ++index;
                current_line_use_width = current_line_use_width_maybe;
                current_line_max_height = current_line_max_height_maybe;
                current_line_flex_total = current_line_flex_total_maybe;
                current_line_flex_min_width = current_line_flex_min_width_maybe;
            }

            // note: start and divide
            float left_start = 0, item_interval = 0;
            if (hal_css_flex_start == css.flex_justify_content) {

            } else if (hal_css_flex_end == css.flex_justify_content) {

            } else if (hal_css_center == css.flex_justify_content) {

            } else if (hal_css_space_between == css.flex_justify_content) {

            } else if (hal_css_space_around == css.flex_justify_content) {

            }

            // note: layout line
            uint32_t last_index = current_line_start + current_line_elements_count;
            for (uint32_t item = current_line_start; item < last_index; ++item) {
                auto child = std::dynamic_pointer_cast<hal_component_layout>(component->at(item));
                if (!child) continue;

                hal_css_t& child_css = child->css_;
                if (hal_css_display_none == child_css.display_) {
                    continue;
                } else if (hal_css_postion_fixed == child_css.position_) {
                    continue;
                } else if (hal_css_postion_absolute == child_css.position_) {
                    continue;
                }


            }

            // note: new line
            current_line_start = index;
            current_line_elements_count = 0;
            current_line_use_width_maybe = 0;
            current_line_max_height_maybe = 0;
            current_line_flex_total_maybe = 0;
            current_line_flex_min_width_maybe = 0;
        } else {
            ++current_line_elements_count; ++index;
            current_line_use_width = current_line_use_width_maybe;
            current_line_max_height = current_line_max_height_maybe;
            current_line_flex_total = current_line_flex_total_maybe;
            current_line_flex_min_width = current_line_flex_min_width_maybe;
        }
    }
    return true;
}
