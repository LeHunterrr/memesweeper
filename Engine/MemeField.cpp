#include "MemeField.h"
#include "SpriteCodex.h"
#include <random>
#include <assert.h>

void MemeField::Tile::SetMeme( bool toSet ) {
	hasMeme = toSet;
}

void MemeField::Tile::Draw(const Vei2& screenPos, Graphics & gfx ) const {
	assert( screenPos.x >= 0 && screenPos.x < Graphics::ScreenWidth &&
			screenPos.y >= 0 && screenPos.y < Graphics::ScreenHeight );
	switch( state ) {
		case Revealed:
			if( !HasMeme() ) {
				SpriteCodex::DrawTile0( screenPos, gfx );
			} else {
				SpriteCodex::DrawTileBomb(screenPos, gfx);
			}
			break;
		case Flagged:
			SpriteCodex::DrawTileFlag( screenPos, gfx );
		case Hidden:
			SpriteCodex::DrawTileButton( screenPos, gfx );
			break;
			
	}
	SpriteCodex::DrawTile0( screenPos, gfx );
}

void MemeField::Tile::Reveal() {
	if( state != Flagged ) {
		state = Revealed;
	}
}

void MemeField::Tile::ToggleFlag() {
	if( !IsRevealed() ) {
		if( state == Hidden ) {
			state = Flagged;
		} else {
			state = Hidden;
		}
	}
}


bool MemeField::Tile::HasMeme() const {
	return hasMeme;
}

bool MemeField::Tile::IsRevealed() const {
	return state == Revealed;
}

bool MemeField::Tile::IsFlagged() const {
	return state == Flagged;
}

MemeField::MemeField( int numMemes, bool& fucked ) : isFucked(fucked) {
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
		} while( TileAt( pos ).HasMeme() );
		TileAt( pos ).SetMeme( true );
	}
	BackgroundField = RectI( 0, Width * SpriteCodex::tileSize, 0, Height * SpriteCodex::tileSize );
}

void MemeField::Draw( Graphics & gfx ) const{
	DrawField( BackgroundField, gfx );

	for( Vei2 pos = { 0,0 }; pos.y < Height; pos.y ++ ) {
		for(pos.x = 0 ; pos.x < Width; pos.x++ ) {
			TileAt( pos ).Draw( pos * SpriteCodex::tileSize, gfx );
		}
	}
}

void MemeField::RevealTile( const Vei2 & ScreenPos ) {
	TileAt( ScreenToGrid( ScreenPos ) ).Reveal();
}

void MemeField::ToggleFlag( const Vei2 & ScreenPos ) {
	TileAt( ScreenToGrid( ScreenPos ) ).ToggleFlag();
}

RectI MemeField::GetField() const {
	return BackgroundField;
}

const MemeField::Tile & MemeField::TileAt( const Vei2& pos ) const {
	return field[ pos.x + pos.y * Height ];
}

MemeField::Tile & MemeField::TileAt( const Vei2& pos ) {
	return field[ pos.x + pos.y * Height ];
}

Vei2 MemeField::ScreenToGrid( const Vei2 & ScreenPos ) const {
	return ScreenPos / SpriteCodex::tileSize;
}

void MemeField::DrawField( const RectI & rect, Graphics & gfx ) const {
	gfx.DrawRect( rect, SpriteCodex::baseColor );
}

void MemeField::PlaceMeme( const Vei2 & pos ) {
	field[ pos.x + pos.y * Width ].SetMeme( true );
}
