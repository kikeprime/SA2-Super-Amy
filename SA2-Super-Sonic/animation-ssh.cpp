#include "pch.h"

AnimationIndex* SuperShadowNewAnimList;

AnimationInfo SuperShadowAnimationList_r[] = {
	{ 203, 355, 3, 0, 0.0625f, 0.1f },
	{ 170, 355, 3, 1, 0.25f, 0.1f },
	{ 2, 355, 3, 2, 0.25f, 0.1f },
	{ 3, 355, 4, 0, 0.25f, 1 },
	{ 4, 355, 3, 4, 0.03125f, 0.1f },
	{ 5, 355, 3, 5, 0.03125f, 0.1f },
	{ 6, 355, 11, 6, 0.25f, 3.4f },
	{ 171, 355, 11, 7, 0.25f, 1 },
	{ 172, 355, 11, 8, 0.25f, 0.12f },
	{ 173, 355, 11, 9, 0.25f, 0.15f},
	{ 174, 355, 10, 10, 0.5f, 0.2f },
	{ 11, 355, 11, 11, 0.25f, 0.2f },
	{ 12, 355, 10, 12, 0.25f, 0.7f },
	{ 13, 355, 3, 13, 0.25f, 0.4f },
	{ 14, 355, 4, 15, 0.125f, 0.3f },
	{ 15, 355, 3, 15, 0.125f, 0.4f },
	{ 16, 355, 4, 0, 1, 0.2f },
	{ 179, 355, 4, 0, 1, 0.4f },
	{ 18, 355, 9, 0, 0.25f, 0.3f },
	{ 19, 355, 4, 20, 0.125f, 0.2f },
	{ 20, 355, 3, 20, 0.25f, 0.6f },
	{ 21, 355, 6, 21, 1, 0.1f },
	{ 22, 355, 4, 0, 1, 1 },
	{ 23, 355, 3, 23, 0.0625f, 1 },
	{ 24, 355, 4, 25, 0.5f, 0.4f },
	{ 25, 355, 4, 0, 0.0625f, 0.3f },
	{ 26, 355, 4, 1, 0.0625f, 1 },
	{ 175, 355, 4, 0, 1, 0.5f },
	{ 28, 355, 3, 28, 0.0625f, 0.2f },
	{ 29, 355, 3, 29, 0.0625f, 0.2f },
	{ 30, 71, 3, 30, 0.5f, 1 },
	{ 31, 355, 9, 35, 0.125f, 0.2f },
	{ 32, 355, 11, 32, 0.5f, 0.4f },
	{ 33, 355, 6, 33, 0.25f, 0.2f },
	{ 34, 355, 4, 35, 0.5f, 1 },
	{ 35, 355, 3, 35, 0.125f, 0.1f },
	{ 36, 355, 3, 36, 0.03125f, 0.1f },
	{ 37, 355, 3, 37, 0.03125f, 0.1f },
	{ 38, 355, 11, 38, 0.5f, 0.5f },
	{ 39, 355, 4, 6, 0.5f, 0.5f },
	{ 40, 355, 3, 40, 0.5f, 0.6f },
	{ 41, 355, 3, 41, 0.5f, 0.4f },
	{ 42, 355, 3, 42, 0.125f, 0.3f },
	{ 43, 355, 4, 44, 0.5f, 0.2f },
	{ 44, 355, 3, 44, 0.5f, 0.1f },
	{ 45, 355, 3, 45, 0.5f, 0.1f },
	{ 46, 355, 4, 47, 0.5f, 0.1f },
	{ 47, 355, 3, 47, 0.5f, 0.3f },
	{ 48, 355, 4, 35, 1, 0.04f },
	{ 49, 355, 4, 0, 0.5f, 0.3f },
	{ 50, 355, 4, 0, 0.5f, 0.3f },
	{ 51, 355, 4, 15, 0.5f, 0.3f },
	{ 52, 355, 4, 15, 0.5f, 0.3f },
	{ 53, 355, 7, 0, 1, 0.2f },
	{ 180, 355, 6, 54, 1, 0.5f },
	{ 55, 355, 3, 55, 0.125f, 0.3f },
	{ 56, 355, 4, 15, 1, 0.25f },
	{ 57, 355, 4, 58, 0.125f, 0.1f },
	{ 58, 355, 3, 58, 1, 0.1f },
	{ 59, 355, 6, 59, 1, 0.2f },
	{ 60, 355, 6, 60, 0.25f, 1 },
	{ 61, 355, 3, 61, 0.25f, 0.5f },
	{ 62, 355, 6, 62, 0.25f, 0.1f },
	{ 63, 355, 4, 0, 0.25f, 0.3f },
	{ 64, 355, 4, 0, 0.25f, 0.3f },
	{ 65, 355, 4, 66, 0.25f, 1.4f },
	{ 66, 355, 3, 66, 0.25f, 1 },
	{ 67, 355, 4, 68, 0.125f, 0.4f },
	{ 68, 355, 3, 68, 0.125f, 0.4f },
	{ 69, 355, 4, 70, 0.25f, 0.1f },
	{ 70, 355, 3, 70, 1, 0.2f },
	{ 71, 355, 9, 0, 0.125f, 0.2f },
	{ 72, 355, 6, 72, 0.25f, 0.2f },
	{ 73, 355, 4, 0, 0.25f, 0.3f },
	{ 74, 355, 3, 74, 0.25f, 0.4f },
	{ 75, 355, 3, 75, 0.25f, 0.1f },
	{ 76, 355, 6, 76, 0.25f, 0.3f },
	{ 77, 355, 3, 77, 0.25f, 0.8f },
	{ 78, 355, 3, 78, 0.125f, 0.2f },
	{ 79, 355, 4, 0, 0.25f, 0.3f },
	{ 80, 355, 5, 81, 0.25f, 0.5f },
	{ 81, 355, 4, 0, 0.25f, 0.5f },
	{ 82, 355, 9, 0, 0.25f, 0.5f },
	{ 83, 355, 4, 0, 0.0625f, 0.15f },
	{ 84, 355, 4, 0, 0.0625f, 0.15f },
	{ 181, 355, 6, 85, 0.25f, 0.5f },
	{ 86, 355, 3, 86, 1, 0.2f },
	{ 87, 355, 3, 87, 1, 0.5f },
	{ 88, 355, 3, 88, 0.03125f, 0.1f },
	{ 89, 355, 3, 89, 0.03125f, 0.1f },
	{ 90, 355, 7, 0, 0.25f, 0.25f },
	{ 91, 355, 4, 92, 0.25f, 1 },
	{ 92, 355, 4, 93, 0.25f, 1 },
	{ 93, 355, 4, 16, 0.25f, 0.2f },
	{ 94, 355, 9, 0, 0.25f, 0.3f },
	{ 95, 355, 9, 0, 0.25f, 0.3f },
	{ 96, 355, 4, 97, 0.25f, 1 },
	{ 97, 355, 4, 98, 0.25f, 1 },
	{ 98, 355, 4, 99, 0.25f, 0.2f },
	{ 99, 355, 4, 16, 0.25f, 1 },
	{ 66, 355, 3, 100, 1, 3 },
	{ 101, 355, 6, 67, 0.25f, 0.3f },
	{ 102, 355, 6, 67, 0.25f, 0.3f },
	{ 103, 355, 6, 67, 0.25f, 0.3f },
	{ 104, 355, 13, 104, 0.25f, 0.3f },
	{ 105, 355, 13, 105, 0.25f, 0.3f },
	{ 106, 355, 13, 106, 0.25f, 0.3f },
	{ 107, 355, 13, 107, 0.25f, 0.3f },
	{ 108, 355, 13, 108, 0.25f, 0.3f },
	{ 109, 355, 13, 109, 0.25f, 0.3f },
	{ 110, 355, 13, 110, 0.25f, 0.3f },
	{ 111, 355, 13, 111, 0.25f, 0.3f },
	{ 112, 355, 3, 112, 0.25f, 0.3f },
	{ 113, 355, 3, 113, 0.25f, 0.3f },
	{ 114, 355, 9, 15, 0.0625f, 0.2f },
	{ 115, 355, 4, 15, 0.0625f, 0.35f },
	{ 116, 355, 4, 15, 0.0625f, 0.35f },
	{ 246, 355, 4, 15, 0.125f, 1 },
	{ 118, 355, 6, 118, 1, 1 },
	{ 119, 355, 6, 119, 1, 1 },
	{ 120, 355, 3, 120, 1, 0.1f },
	{ 121, 355, 13, 121, 0.25f, 0.3f },
	{ 122, 355, 13, 122, 0.25f, 0.3f },
	{ 123, 355, 13, 123, 0.25f, 0.3f },
	{ 124, 355, 13, 124, 0.25f, 0.3f },
	{ 125, 355, 3, 125, 0.25f, 0.3f },
	{ 126, 355, 3, 126, 0.25f, 0.3f },
	{ 127, 355, 6, 127, 0.25f, 0.4f },
	{ 128, 355, 4, 129, 0.125f, 0.3f },
	{ 129, 355, 3, 129, 0.125f, 0.4f },
	{ 130, 355, 4, 121, 1, 0.3f },
	{ 132, 355, 4, 121, 0.25f, 0.3f },
	{ 131, 355, 4, 122, 0.25f, 0.3f },
	{ 133, 355, 4, 130, 1, 1 },
	{ 134, 355, 4, 130, 1, 1 },
	{ 135, 355, 4, 130, 0.0625f, 1.25f },
	{ 136, 355, 4, 130, 0.0625f, 1 },
	{ 137, 355, 4, 130, 1, 1 },
	{ 138, 355, 4, 130, 0.0625f, 1.25f },
	{ 139, 355, 4, 130, 1, 1 },
	{ 140, 355, 4, 130, 1, 1 },
	{ 141, 355, 4, 130, 0.0625f, 1.25f },
	{ 142, 355, 4, 130, 0.0625f, 1.25f },
	{ 143, 355, 4, 130, 0.0625f, 1 },
	{ 144, 355, 4, 130, 0.0625f, 1 },
	{ 145, 355, 13, 121, 0.25f, 0.3f },
	{ 146, 355, 13, 122, 0.25f, 0.3f },
	{ 147, 355, 13, 123, 0.25f, 0.3f },
	{ 148, 355, 13, 124, 0.25f, 0.3f },
	{ 149, 355, 3, 125, 0.25f, 0.3f },
	{ 150, 355, 3, 126, 0.25f, 0.3f },
	{ 151, 355, 6, 127, 0.25f, 0.4f },
	{ 152, 355, 4, 129, 0.125f, 0.3f },
	{ 153, 355, 3, 129, 0.125f, 0.4f },
	{ 154, 355, 4, 121, 1, 0.3f },
	{ 156, 355, 4, 121, 0.25f, 0.3f },
	{ 155, 355, 4, 122, 0.25f, 0.3f },
	{ 157, 355, 9, 129, 0.0625f, 1 },
	{ 158, 355, 9, 129, 0.0625f, 1 },
	{ 159, 355, 9, 129, 0.0625f, 1 },
	{ 160, 355, 9, 129, 0.0625f, 1 },
	{ 161, 355, 9, 129, 0.0625f, 1 },
	{ 162, 355, 9, 129, 0.0625f, 1 },
	{ 163, 355, 9, 129, 0.0625f, 1 },
	{ 164, 355, 9, 129, 0.0625f, 1 },
	{ 165, 355, 9, 129, 0.0625f, 1 },
	{ 166, 355, 9, 129, 0.0625f, 1 },
	{ 167, 355, 9, 129, 0.0625f, 1 },
	{ 168, 355, 9, 129, 0.0625f, 1 },
	{ 169, 355, 3, 169, 0.0625f, 0.1f },
	{ 170, 355, 3, 170, 0.25f, 0.1f },
	{ 171, 355, 11, 171, 0.25f, 1.4f },
	{ 172, 355, 11, 172, 0.25f, 1.4f },
	{ 173, 355, 11, 173, 0.25f, 1.4f },
	{ 174, 355, 11, 174, 0.25f, 1.4f },
	{ 175, 355, 4, 169, 0.25f, 1.4f },
	{ 176, 355, 3, 176, 0.03125f, 0.1f },
	{ 177, 355, 3, 177, 0.03125f, 0.1f },
	{ 178, 355, 9, 0, 0.03125f, 0.25f },
	{ 179, 355, 4, 169, 0.25f, 1.4f },
	{ 180, 355, 6, 180, 0.25f, 1.4f },
	{ 181, 355, 6, 181, 0.25f, 1.4f },
	{ 182, 355, 6, 182, 1, 1 },
	{ 183, 355, 6, 183, 1, 1 },
	{ 184, 355, 3, 184, 1, 0.1f },
	{ 185, 355, 4, 186, 0.25f, 0.3f },
	{ 186, 355, 3, 186, 0.25f, 0.5f },
	{ 187, 355, 3, 187, 0.25f, 0.8f },
	{ 188, 355, 6, 188, 0.25f, 0.3f },
	{ 189, 355, 4, 189, 0.25f, 0.2f },
	{ 190, 355, 3, 190, 0.25f, 0.3f },
	{ 191, 355, 3, 191, 0.25f, 0.2f },
	{ 192, 355, 11, 192, 0.25f, 0.2f },
	{ 193, 355, 11, 192, 0.25f, 0.2f },
	{ 194, 355, 3, 194, 0.0625f, 0.2f },
	{ 195, 355, 3, 195, 0.0625f, 0.2f },
	{ 196, 355, 3, 196, 0.0625f, 0.2f },
	{ 197, 355, 3, 197, 0.0625f, 0.2f },
	{ 198, 355, 3, 198, 0.125f, 0.2f },
	{ 199, 355, 3, 199, 0.25f, 0.2f },
	{ 200, 355, 3, 200, 0.25f, 0.2f },
	{ 201, 355, 6, 201, 0.125f, 0.2f },
	{ 202, 355, 3, 202, 0.125f, 0.5f },
	{ 205, 355, 6, 0, 1, 0.8f }, //turning to super
	{ 205, 355, 4, 54, 1, 0.5f }, //victory pose
	{ 204, 355, 3, superSonicFlying1, 0.0625f, 0.5f }, //fly 1
	{ 206, 355, 3, superSonicFlying2, 0.0625f, 0.5f }, //fly 2
	{ 207, 355, 4, ssAscending, 0.125f, 0.5f }, //begin ascent
	{ 208, 355, 3, ssAscending, 0.125f, 0.5f }, //ascending
	{ 209, 355, 4, ssDescend, 0.125f, 0.5f }, //begin descent
	{ 210, 355, 3, ssDescend, 0.125f, 0.5f }, //descending
	{ 211, 355, 4, ssDash, 0.0625f, 0.5f }, //begin dash
	{ 212, 355, 3, ssDash, 0.0625f, 0.5f }, //dash
	{ 213, 355, 4, ssDash2, 0.0625f, 0.5f }, //begin dash 2
	{ 214, 355, 3, ssDash2, 0.0625f, 0.5f }, //dash2
	{ 215, 355, 4, 0, 0.25f, 0.4f }, //placeholder? those are originally on shadow anim list, probably unused.
	{ 216, 355, 4, 0, 0.25f, 0.4f },
	{ 217, 355, 4, 0, 0.25f, 0.4f },
	{ 218, 355, 4, 0, 0.25f, 0.4f },
	{ 219, 355, 4, 0, 0.25f, 0.4f },
	{ 220, 355, 4, 0, 0.25f, 0.4f },
	{ 221, 355, 4, 0, 0.25f, 0.4f },
	{ 222, 355, 4, 0, 0.25f, 0.4f },
	{ 223, 355, 4, 0, 0.25f, 0.4f },
	{ 224, 355, 4, 0, 0.25f, 0.4f },
	{ 225, 355, 4, 0, 0.25f, 0.4f },
	{ 226, 355, 4, 0, 0.25f, 0.4f },
	{ 227, 355, 4, 0, 0.25f, 0.4f },
	{ 228, 355, 4, 0, 0.25f, 0.4f },
	{ 229, 355, 4, 0, 0.25f, 0.4f },
	{ 230, 355, 4, 0, 0.25f, 0.4f },
	{ 231, 355, 4, 0, 0.25f, 0.4f },
	{ 232, 355, 4, 0, 0.25f, 0.4f },
	{ 233, 355, 4, 0, 0.25f, 0.4f },
	{ 234, 355, 4, 0, 0.25f, 0.4f },
	{ 235, 355, 4, 0, 0.25f, 0.4f },
	{ 236, 355, 4, 0, 0.25f, 0.4f },
	{ 237, 355, 4, 0, 0.25f, 0.4f },
	{ 238, 355, 4, 0, 0.25f, 0.4f },
	{ 239, 355, 4, 0, 0.25f, 0.4f },
	{ 240, 355, 4, 0, 0.25f, 0.4f },
	{ 241, 355, 4, 0, 0.25f, 0.4f },
	{ 242, 355, 4, 0, 0.25f, 0.4f },
	{ 243, 355, 4, 0, 0.25f, 0.4f },
	{ 244, 355, 4, 0, 0.25f, 0.4f },
	{ 245, 355, 4, 0, 0.25f, 0.4f },
	{ 246, 355, 4, 0, 0.25f, 0.4f },
	{ 247, 355, 4, 0, 0.25f, 0.4f },
	{ 248, 355, 4, 0, 0.25f, 0.4f },
};

void Delete_SSHAnim() {
	AnimationIndex* copy = SuperShadowNewAnimList;
	UnloadAnimation(copy);

	SuperShadowNewAnimList = 0;
	return;
}

void Load_NewSuperShadowAnim() {
	SuperShadowNewAnimList = LoadMTNFile((char*)"ssmotion.prs");
}