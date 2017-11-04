#include "MemeField.h"
#include "SpriteCodex.h"
#include <random>
#include <assert.h>
#include <algorithm>

void MemeField::Tile::SetMeme( bool toSet ) {
	hasMeme = toSet;
}

void MemeField::Tile::Draw(const Vei2& screenPos, Graphics & gfx, GameState isFucked ) const {
	assert( screenPos.x >= 0 && screenPos.x < Graphics::ScreenWidth &&
			screenPos.y >= 0 && screenPos.y < Graphics::ScreenHeight );

	if( isFucked != IsFucked ) {
		switch( state ) {
			case Revealed:
				if( HasMeme() ) {
					SpriteCodex::DrawTileBomb( screenPos, gfx );
				} else {
					switch( numNeighbourMemes ) {
						case 0: SpriteCodex::DrawTile0( screenPos, gfx );
							break;
						case 1: SpriteCodex::DrawTile1( screenPos, gfx );
							break;
						case 2: SpriteCodex::DrawTile2( screenPos, gfx );
							break;
						case 3: SpriteCodex::DrawTile3( screenPos, gfx );
							break;
						case 4: SpriteCodex::DrawTile4( screenPos, gfx );
							break;
						case 5: SpriteCodex::DrawTile5( screenPos, gfx );
							break;
						case 6: SpriteCodex::DrawTile6( screenPos, gfx );
							break;
						case 7: SpriteCodex::DrawTile7( screenPos, gfx );
							break;
						case 8: SpriteCodex::DrawTile8( screenPos, gfx );
							break;
					}
				}
				break;
			case Flagged:
				SpriteCodex::DrawTileFlag( screenPos, gfx );
			case Hidden:
				SpriteCodex::DrawTileButton( screenPos, gfx );
				break;
		}
	} else {
		switch( state ) {
			case Revealed:
				if( HasMeme() ) {
					SpriteCodex::DrawTileBombRed( screenPos, gfx );
				} else {
					switch( numNeighbourMemes ) {
						case 0: SpriteCodex::DrawTile0( screenPos, gfx );
							break;
						case 1: SpriteCodex::DrawTile1( screenPos, gfx );
							break;
						case 2: SpriteCodex::DrawTile2( screenPos, gfx );
							break;
						case 3: SpriteCodex::DrawTile3( screenPos, gfx );
							break;
						case 4: SpriteCodex::DrawTile4( screenPos, gfx );
							break;
						case 5: SpriteCodex::DrawTile5( screenPos, gfx );
							break;
						case 6: SpriteCodex::DrawTile6( screenPos, gfx );
							break;
						case 7: SpriteCodex::DrawTile7( screenPos, gfx );
							break;
						case 8: SpriteCodex::DrawTile8( screenPos, gfx );
							break;
					}
				}
				break;
			case Flagged:
				if( HasMeme() ) {
					SpriteCodex::DrawTileFlag( screenPos, gfx );
					SpriteCodex::DrawTileBomb( screenPos, gfx );
				} else {
					SpriteCodex::DrawTileCross( screenPos, gfx );
				}
			case Hidden:
				if( HasMeme() ) {
					SpriteCodex::DrawTileBomb(screenPos, gfx);
				}
				SpriteCodex::DrawTileButton( screenPos, gfx );
				break;
		}
	}
	
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
		} while( TileAt( pos ).HasMeme() );
		TileAt( pos ).SetMeme( true );
	}
	BackgroundField = RectI( 0, Width * SpriteCodex::tileSize, 0, Height * SpriteCodex::tileSize );

	for( int c = 0; c < Width * Height; c++ ) {
		SetNeighbourMemes( c );
	}
}

void MemeField::Draw( Graphics & gfx ) const{
	DrawField( BackgroundField, gfx );

	for( Vei2 pos = { 0,0 }; pos.y < Height; pos.y ++ ) {
		for(pos.x = 0 ; pos.x < Width; pos.x++ ) {
			TileAt( pos ).Draw( pos * SpriteCodex::tileSize, gfx, gamestate );
		}
	}
}

void MemeField::RevealTile( const Vei2 & ScreenPos ) {
	Vei2 pos = ScreenToGrid( ScreenPos );
	TileAt( pos ).Reveal();
	if( TileAt( pos ).HasMeme() ) {
		gamestate = IsFucked;
	} else {
		Recrusion( pos );
	}
}

void MemeField::ToggleFlag( const Vei2 & ScreenPos ) {
	TileAt( ScreenToGrid( ScreenPos ) ).ToggleFlag();
}

RectI MemeField::GetField() const {
	return BackgroundField;
}

bool MemeField::GetGameState() const {
	return gamestate;
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

void MemeField::SetNeighbourMemes( const Vei2 & pos ) {
	int xStart = std::max( 0, pos.x - 1 );
	int yStart = std::max( 0, pos.y - 1 );
	int xEnd = std::min( Width - 1, pos.x + 1 );
	int yEnd = std::min( Height - 1, pos.y + 1 );

	int memesFound = 0;

	for( int y = yStart; y <= yEnd; y++ ) {
		for( int x = xStart; x <= xEnd; x++ ) {
			if( TileAt( { x, y } ).HasMeme() ) {
				memesFound++;
			}
		}
	}
	TileAt( pos ).numNeighbourMemes = memesFound;
}

void MemeField::SetNeighbourMemes( int index ) {
	int x = index % Width;
	index -= index % Width;
	int y = index / Width;
	SetNeighbourMemes( { x, y } );
}

void MemeField::Recrusion( const Vei2 & start ) {
	int xStart = std::max( 0, start.x - 1 );
	int yStart = std::max( 0, start.y - 1 );
	int xEnd = std::min( Width - 1, start.x + 1 );
	int yEnd = std::min( Height - 1, start.y + 1 );

	for( int y = yStart; y <= yEnd; y++ ) {
		for( int x = xStart; x <= xEnd; x++ ) {
			Tile& tile = TileAt( { x, y } );
			if( !tile.IsRevealed() && !tile.IsFlagged() && !tile.HasMeme() ) {
				tile.Reveal();
				Recrusion( { x, y } );
			}
		}
	}
}

void MemeField::PlaceMeme( const Vei2 & pos ) {
	field[ pos.x + pos.y * Width ].SetMeme( true );
}
