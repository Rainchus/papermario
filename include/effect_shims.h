#ifndef _EFFECT_SHIMS_H_
#define _EFFECT_SHIMS_H_

// void guRotateF(float mf[4][4], float a, float x, float y, float z);
// void guTranslateF(float mf[4][4], float x, float y, float z);
// void guTranslate(Mtx *m, float x, float y, float z);
// void guScaleF(float mf[4][4], float x, float y, float z);
// void guMtxCatF(float m[4][4], float n[4][4], float r[4][4]);
// void guMtxF2L(float mf[4][4], Mtx *m);
// RenderTask* queue_render_task(RenderTask* task);
// EffectInstance* create_effect_instance(EffectBlueprint* effectBp);
// void remove_effect(EffectInstance*);
// void* general_heap_malloc(s32 size);
// void mem_clear(void* data, s32 numBytes);
// s32 rand_int(s32);
// f32 clamp_angle(f32 theta);
// f32 sin_deg(f32 x);
// f32 cos_deg(f32 x);
// f32 atan2(f32 startX, f32 startZ, f32 endX, f32 endZ);
// bool npc_raycast_down_sides(s32, f32*, f32*, f32*, f32*);
// s32 load_effect(s32 effectIndex);
// float sqrtf(float value);
// void mdl_draw_hidden_panel_surface(Gfx**, u16 treeIndex);
// bool is_point_visible(f32, f32, f32, s32, f32*, f32*);
// void guPerspectiveF(f32 mf[4][4], u16* perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale);
// void transform_point(Matrix4f mtx, f32 inX, f32 inY, f32 inZ, f32 inS, f32* outX, f32* outY, f32* outZ, f32* outW);
// void guPositionF(float mf[4][4], float r, float p, float h, float s, float x, float y, float z);
// void guOrthoF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale);
// void guFrustumF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale);
// void draw_prev_frame_buffer_at_screen_pos(s32, s32, s32, s32, f32);
// void draw_box(
//     s32 flags, WindowStyle windowStyle, s32 posX, s32 posY, s32 posZ, s32 width, s32 height, u8 opacity,
//     u8 darkening, f32 scaleX, f32 scaleY, f32 rotX, f32 rotY, f32 rotZ, void (*fpDrawContents)(void*),
//     void* drawContentsArg0, Matrix4f rotScaleMtx, s32 translateX, s32 translateY, f32 (*outMtx)[4]
// );
// void draw_msg(s32, s32, s32, s32, s32, s32);
// s32 get_msg_width(s32, u16);
// void mdl_get_shroud_tint_params(u8* r, u8* g, u8* b, u8* a);
// void sfx_play_sound_at_position(s32 soundID, s32 value2, f32 posX, f32 posY, f32 posZ);

// #define guRotateF shim_guRotateF
// #define guTranslateF shim_guTranslateF
// #define guTranslate shim_guTranslate
// #define guScaleF shim_guScaleF
// #define guMtxCatF shim_guMtxCatF
// #define guMtxF2L shim_guMtxF2L
// #define queue_render_task shim_queue_render_task
// #define create_effect_instance shim_create_effect_instance
// #define remove_effect shim_remove_effect
// #define general_heap_malloc shim_general_heap_malloc
// #define mem_clear shim_mem_clear
// #define rand_int shim_rand_int
// #define clamp_angle shim_clamp_angle
// #define sin_deg shim_sin_deg
// #define cos_deg shim_cos_deg
// #define atan2 shim_atan2
// #define npc_raycast_down_sides shim_npc_raycast_down_sides
// #define load_effect shim_load_effect
// #define sqrtf shim_sqrtf
// #define mdl_draw_hidden_panel_surface shim_mdl_draw_hidden_panel_surface
// #define is_point_visible shim_is_point_visible
// #define guPerspectiveF shim_guPerspectiveF
// #define transform_point shim_transform_point
// #define guPositionF shim_guPositionF
// #define guOrthoF shim_guOrthoF
// #define guFrustumF shim_guFrustumF
// #define draw_prev_frame_buffer_at_screen_pos shim_draw_prev_frame_buffer_at_screen_pos
// #define draw_box shim_draw_box
// #define draw_msg shim_draw_msg
// #define get_msg_width shim_get_msg_width
// #define mdl_get_shroud_tint_params shim_mdl_get_shroud_tint_params
// #define sfx_play_sound_at_position shim_sfx_play_sound_at_position

#endif
