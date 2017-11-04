#include "MemeField.h"
#include <random>
#include <assert.h>

void MemeField::Tile::SetMeme( bool toSet ) {
	hasMeme = toSet;
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

const MemeField::Tile & MemeField::TileAt( const Vei2 pos ) const {
	return field[ pos.x + pos.y * Height ];
}

MemeField::Tile & MemeField::TileAt( const Vei2 pos ) {
	return field[ pos.x + pos.y * Height ];
}

void MemeField::PlaceMine( const Vei2 & pos ) {
	field[ pos.x + pos.y * Width ].SetMeme( true );
}
