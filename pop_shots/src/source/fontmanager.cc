/******************************************************************************
 *                                                                            *
 *  POP SHOTS.                                                                *
 *                                                                            *
 *  Technological School Electronic Systems                                   *
 *  Technical University of Sofia                                             *
 *                                                                            *
 *  Copyright (C) 2009-2010 Viktor Kirilov ( n1ntendo@abv.bg )                *
 *                                                                            *
 ******************************************************************************/

#include "../include/fontmanager.h"

FontManager::FontManager() {
	TTF_Init();
}

FontManager::~FontManager() {
	for ( map<string , vector<TTF_Font*> >::iterator it = fonts.begin(); it != fonts.end(); it++ ) {
		for ( vector<TTF_Font*>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++ ) {
			TTF_CloseFont(*it2);
		}
	}
	
	TTF_Quit();
}

TTF_Font* FontManager::getFont(string fontName, int size) {
	map<string , vector<TTF_Font*> >::iterator it = fonts.find(fontName);
	
	if ( it != fonts.end() ) {
		for ( vector<TTF_Font*>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++ ) {
			if ( size+1 == TTF_FontHeight(*it2) ) {
				return *it2;
			}
		}
		
		TTF_Font* temp = TTF_OpenFont(fontName.c_str(), size);
		
		for ( vector<TTF_Font*>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++ ) {
			if ( TTF_FontHeight(temp) == TTF_FontHeight(*it2) ) {
				TTF_CloseFont(temp);
				return *it2;
			}
		}
		
		it->second.push_back( temp );
		
		return temp;
	} else {
		vector<TTF_Font*> vect;
		vect.push_back( TTF_OpenFont(fontName.c_str(), size) );
		if ( vect.back() != NULL ) {
			fonts.insert( pair<string, vector<TTF_Font*> > ( fontName, vect ) );
			return vect.back();
		}
	}
	
	return NULL;
}
