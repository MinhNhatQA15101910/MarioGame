#include "Font.h"

CFont::CFont() {
	CSprites* sprites = CSprites::GetInstance();
	fonts.insert(make_pair('0', sprites->Get(SPRITE_ID_FONT_0)));
	fonts.insert(make_pair('1', sprites->Get(SPRITE_ID_FONT_1)));
	fonts.insert(make_pair('2', sprites->Get(SPRITE_ID_FONT_2)));
	fonts.insert(make_pair('3', sprites->Get(SPRITE_ID_FONT_3)));
	fonts.insert(make_pair('4', sprites->Get(SPRITE_ID_FONT_4)));
	fonts.insert(make_pair('5', sprites->Get(SPRITE_ID_FONT_5)));
	fonts.insert(make_pair('6', sprites->Get(SPRITE_ID_FONT_6)));
	fonts.insert(make_pair('7', sprites->Get(SPRITE_ID_FONT_7)));
	fonts.insert(make_pair('8', sprites->Get(SPRITE_ID_FONT_8)));
	fonts.insert(make_pair('9', sprites->Get(SPRITE_ID_FONT_9)));
	fonts.insert(make_pair('A', sprites->Get(SPRITE_ID_FONT_A)));
	fonts.insert(make_pair('B', sprites->Get(SPRITE_ID_FONT_B)));
	fonts.insert(make_pair('C', sprites->Get(SPRITE_ID_FONT_C)));
	fonts.insert(make_pair('D', sprites->Get(SPRITE_ID_FONT_D)));
	fonts.insert(make_pair('E', sprites->Get(SPRITE_ID_FONT_E)));
	fonts.insert(make_pair('F', sprites->Get(SPRITE_ID_FONT_F)));
	fonts.insert(make_pair('G', sprites->Get(SPRITE_ID_FONT_G)));
	fonts.insert(make_pair('H', sprites->Get(SPRITE_ID_FONT_H)));
	fonts.insert(make_pair('I', sprites->Get(SPRITE_ID_FONT_I)));
	fonts.insert(make_pair('J', sprites->Get(SPRITE_ID_FONT_J)));
	fonts.insert(make_pair('K', sprites->Get(SPRITE_ID_FONT_K)));
	fonts.insert(make_pair('L', sprites->Get(SPRITE_ID_FONT_L)));
	fonts.insert(make_pair('M', sprites->Get(SPRITE_ID_FONT_M)));
	fonts.insert(make_pair('N', sprites->Get(SPRITE_ID_FONT_N)));
	fonts.insert(make_pair('O', sprites->Get(SPRITE_ID_FONT_O)));
	fonts.insert(make_pair('P', sprites->Get(SPRITE_ID_FONT_P)));
	fonts.insert(make_pair('Q', sprites->Get(SPRITE_ID_FONT_Q)));
	fonts.insert(make_pair('R', sprites->Get(SPRITE_ID_FONT_R)));
	fonts.insert(make_pair('S', sprites->Get(SPRITE_ID_FONT_S)));
	fonts.insert(make_pair('T', sprites->Get(SPRITE_ID_FONT_T)));
	fonts.insert(make_pair('U', sprites->Get(SPRITE_ID_FONT_U)));
	fonts.insert(make_pair('V', sprites->Get(SPRITE_ID_FONT_V)));
	fonts.insert(make_pair('W', sprites->Get(SPRITE_ID_FONT_W)));
	fonts.insert(make_pair('X', sprites->Get(SPRITE_ID_FONT_X)));
	fonts.insert(make_pair('Y', sprites->Get(SPRITE_ID_FONT_Y)));
	fonts.insert(make_pair('Z', sprites->Get(SPRITE_ID_FONT_Z)));
}

LPSPRITE CFont::mapping(char c) {
	int ic = (int)c;
	if (!(ic >= 48 && ic <= 57) || (ic >= 64 && ic <= 90)) return NULL;
	return fonts.at(c);
}

std::vector<LPSPRITE> CFont::StringToFont(string str) {
	std::vector<LPSPRITE> sprites;
	LPSPRITE sprite;
	char c;
	for (unsigned int i = 0; i < str.size(); i++) {
		c = (char)str[i];
		sprite = mapping(c);
		if (sprite != NULL) sprites.push_back(sprite);
	}

	return sprites;
}
