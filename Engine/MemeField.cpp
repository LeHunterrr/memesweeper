#include "MemeField.h"
#include "SpriteCodex.h"
#include <random>
#include <assert.h>

void MemeField::Tile::SetMeme( bool toSet ) {
	hasMeme = toSet;
}

void MemeField::Tile::Draw( Vei2 screenPos, Graphics & gfx ) {
	assert( screenPos.x >= 0 && screenPos.x < Graphics::ScreenWidth &&
			screenPos.y >= 0 && screenPos.y < Graphics::ScreenHeight );
	SpriteCodex::DrawTile0( screenPos, gfx );
}

bool MemeField::Tile::HasMeme() const {
	return hasMeme;
}

MemeField::MemeField( int numMemes ) {
	assert( numMemes > 0 && numMemes < Width * Height );

	std::random_device rd;
	std::mt19937 RNG( rd() );
	std::uniform_int_distribution<int> xDist( 0, Width - 1 );
	std::uniform_int_distribution<int> yDist( 0, Height - 1 );

	for( int i = 0; i < numMemes; i++ ) {
		Vei2 pos;
		do {
			pos.x = xDist( RNG );
			pos.y = yDist( RNG );
		} while( TileAt(pos).HasMeme() );
		TileAt( pos ).SetMeme( true );
	}
}

void MemeField::Draw( Graphics & gfx ) {
	for( Vei2 pos = { 0,0 }; pos.y < Height; pos.y ++ ) {
		for(pos.x = 0 ; pos.x < Width; pos.x++ ) {
			TileAt( pos ).Draw( pos * SpriteCodex::tileSize, gfx );
		}
	}
}

const MemeField::Tile & MemeField::TileAt( const Vei2 pos ) const {
	return field[ pos.x + pos.y * Height ];
}

MemeField::Tile & MemeField::TileAt( const Vei2 pos ) {
	return field[ pos.x + pos.y * Height ];
}

void MemeField::PlaceMine( const Vei2 & pos ) {
	field[ pos.x + pos.y * Width ].SetMeme( true );
}
