#ifndef PILOTWINGS64_UV_MODEL_H
#define PILOTWINGS64_UV_MODEL_H

#include <uv_common.h>
#include <uv_matrix.h>

#define MODEL_PROPID_END            0
#define MODEL_PROPID_UNK1           1 // type:f32
#define MODEL_PROPID_LOD_COUNT      2 // type:s32
#define MODEL_PROPID_UNK3           3 // type:s32
#define MODEL_PROPID_PART_COUNT     4 // type:s32
#define MODEL_PROPID_UNK5           5 // type:u8

#define MODEL_PROP_END              MODEL_PROPID_END
#define MODEL_PROP_UNK1(x)          MODEL_PROPID_UNK1, (x)
#define MODEL_PROP_LOD_COUNT(x)     MODEL_PROPID_LOD_COUNT, (x)
#define MODEL_PROP_UNK3(x)          MODEL_PROPID_UNK3, (x)
#define MODEL_PROP_PART_COUNT(x)    MODEL_PROPID_PART_COUNT, (x)  
#define MODEL_PROP_UNK5(x)          MODEL_PROPID_UNK5, (x)

s32 uvModelGet(s32 fxId, s32 modelId); // TODO should move to fx / rename to uvFxModel
void uvModelGetProps(s32 modelId, ...);
void uvModelGetPosm(s32 modelId, s32 part, Mtx4F*);

#endif // PILOTWINGS64_UV_MODEL_H

