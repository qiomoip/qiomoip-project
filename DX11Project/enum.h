#pragma once

enum ENTITY_TYPE
{
	ET_NONE = -1,
	ET_BOX,
	ET_TERRAIN,
	ET_SKULL,
	ET_WAVES,
	ET_PLAYER,
	ET_ZOMBIE,
	ET_MAX,
};


enum TECH_TYPE
{
	DST_NONE = -1,
	DST_DEFAULT,
	DST_MAX,
};

enum PASS_TYPE
{
	//TechKey_Pass
	DEFAULT_COLOR,
	DEFAULT_LIGHT,
	DPT_MAX,
};

//버텍스 구조 서술은 메쉬에서 갖고 있겠ㄷ지
enum INPUTLAYOUT_TYPE
{
	//inputlayout_type_shaderType_TechType_PassType
	IT_DEFAULT_DEFAULT_COLOR,
	IT_DEFAULT_DEFAULT_LIGHT,
	IT_MAX,
};

enum RENDER_TYPE
{
	RT_NONE = -1,
	RT_ENTITY,
	RT_ALPHA1,
	RT_MAX,
};

enum MESH_TYPE
{
	MT_NONE = -1,
	MT_STATIC,
	MT_MAX
};

enum GEOMETRY_TYPE
{
	GT_NONE = -1,
	GT_STATIC,
	GT_BOX,
	GT_MAX,
	GT_TERRAIN,
};

enum CAMERA_TYPE
{
	CAM_PERSPECTIVE,
	CAM_ORTHOGONAL,
	CAM_MAX,
};

enum KEY
{
	KEY_VKRIGHT,
	KEY_VKLEFT,
	KEY_VKUP,
	KEY_VKDOWN,
	KEY_W,
	KEY_S,
	KEY_D,
	KEY_A,
	KEY_Z,
	KEY_C,
	KEY_VKINSERT,
	KEY_VKDEL,
	KEY_VKHOME,
	KEY_VKEND,
	KEY_VKPGUP,
	KEY_VKPGDN,
	KEY_VKSPACE,
};

enum AXIS_TYPE
{
	AT_X,
	AT_Y,
	AT_Z,
	AT_MAX
};