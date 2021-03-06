#include "hal_render_matrix.h"
using namespace kernal;

hal_render_matrix::hal_render_matrix() {
    raw_matrix_.setIdentity();
}

hal_render_matrix::~hal_render_matrix() {
}

void hal_render_matrix::set_identi() {
    raw_matrix_.setIdentity();
}

void hal_render_matrix::set_rotate(float d) {
    raw_matrix_.setRotate(d);
}

void hal_render_matrix::pre_rotate(float d) {
    raw_matrix_.preRotate(d);
}

void hal_render_matrix::post_rotate(float d) {
    raw_matrix_.postRotate(d);
}

void hal_render_matrix::set_scale(float x, float y) {
    raw_matrix_.setScale(x, y);
}

void hal_render_matrix::pre_scale(float x, float y) {
    raw_matrix_.preScale(x, y);
}

void hal_render_matrix::post_scale(float x, float y) {
    raw_matrix_.postScale(x, y);
}

void hal_render_matrix::set_translate(float x, float y) {
    raw_matrix_.setTranslate(x, y);
}

void hal_render_matrix::pre_translate(float x, float y) {
    raw_matrix_.preTranslate(x, y);
}

void hal_render_matrix::post_translate(float x, float y) {
    raw_matrix_.postTranslate(x, y);
}

void hal_render_matrix::pre_concat(hal_render_matrix& matrix) {
    raw_matrix_.preConcat(matrix.raw_matrix_);
}

void hal_render_matrix::post_concat(hal_render_matrix& matrix) {
    raw_matrix_.postConcat(matrix.raw_matrix_);
}

void hal_render_matrix::set_camera_rotate(float x, float y, float z) {
    Sk3DView _3d_view;
    0 != x? _3d_view.rotateX(x): (void)0;
    0 != y? _3d_view.rotateY(y): (void)0;
    0 != z? _3d_view.rotateZ(z): (void)0;
    _3d_view.getMatrix(&raw_matrix_);
}

void hal_render_matrix::pre_camera_rotate(float x, float y, float z) {
    Sk3DView _3d_view;
    0 != x? _3d_view.rotateX(x): (void)0;
    0 != y? _3d_view.rotateY(y): (void)0;
    0 != z? _3d_view.rotateZ(z): (void)0;

    SkMatrix _3d_martix;
    _3d_view.getMatrix(&_3d_martix);
    raw_matrix_.preConcat(_3d_martix);
}

void hal_render_matrix::post_camera_rotate(float x, float y, float z) {
    Sk3DView _3d_view;
    0 != x? _3d_view.rotateX(x): (void)0;
    0 != y? _3d_view.rotateY(y): (void)0;
    0 != z? _3d_view.rotateZ(z): (void)0;

    SkMatrix _3d_martix;
    _3d_view.getMatrix(&_3d_martix);
    raw_matrix_.postConcat(_3d_martix);
}

void hal_render_matrix::set_camera_translate(float x, float y, float z) {
    Sk3DView _3d_view;
    _3d_view.translate(x, y, z);
    _3d_view.getMatrix(&raw_matrix_);
}

void hal_render_matrix::pre_camera_translate(float x, float y, float z) {
    Sk3DView _3d_view;
    _3d_view.translate(x, y, z);
    SkMatrix _3d_martix;
    _3d_view.getMatrix(&_3d_martix);
    raw_matrix_.preConcat(_3d_martix);
}

void hal_render_matrix::post_camera_translate(float x, float y, float z) {
    Sk3DView _3d_view;
    _3d_view.translate(x, y, z);
    SkMatrix _3d_martix;
    _3d_view.getMatrix(&_3d_martix);
    raw_matrix_.postConcat(_3d_martix);
}

void hal_render_matrix::map_point(hal_point& src, hal_point& dst) {
    SkPoint ret = raw_matrix_.mapXY(src.x_, src.y_);
    dst.x_ = ret.x(); dst.y_ = ret.y();
}

void hal_render_matrix::map_rect(hal_rect& src, hal_rect& dst) {
    SkRect ret_r;
    raw_matrix_.mapRect(&ret_r, __convert_to_t(src));
    dst.x_ = ret_r.x(); dst.y_ = ret_r.y();
    dst.width_ = ret_r.width(); dst.height_ = ret_r.height();
}
