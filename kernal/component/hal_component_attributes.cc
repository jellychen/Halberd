#include "dom/hal_document.h"
#include "css/hal_css_parser.h"
#include "hal_component_attributes.h"
using namespace kernal;

__hal_attributes_define(hal_component_attributes);
__hal_attributes_map(id, internal_attr_set_id);
__hal_attributes_map(style, internal_attr_set_style);
__hal_attributes_define_end();

bool hal_component_attributes::set_attributes(
    const char* k, const char* val) {
    std::string _attr_k = k;
    return __hal_attributes_dispatch(
        hal_component_attributes).dispath(_attr_k, val, this);
}

bool hal_component_attributes::set_style_attributes(
    const char* k, const char* val) {
    return css_.set_attributes(k, val);
}

void hal_component_attributes::internal_attr_set_style(const char* str) {
    if (nullptr != str) {
        auto component = std::dynamic_pointer_cast<
            hal_component_attributes>(shared_from_this());
        if (component) {
            hal_css_parser parser;
            parser.declaration_list(str, strlen(str), component);
        }
    }
}

void hal_component_attributes::internal_attr_set_id(const char* str) {
    if (!host_document_.expired() && !doc_id_.empty()) {
        host_document_.lock()->id_index_.remove(doc_id_);
    }
    doc_id_ = str;

    auto component = std::dynamic_pointer_cast<hal_component_base>(shared_from_this());
    if (!host_document_.expired() && !doc_id_.empty()) {
        host_document_.lock()->id_index_.add(doc_id_, component);
    }
}

int32_t hal_component_attributes::css_z_index() const {
    return css_.z_index_;
}
