#pragma once
#include "Vei2.h"
#include "Graphics.h"

class MemeField {
private:
	class Tile {
	public:
		enum State {
			Hidden,
			Flagged,
			Revealed
		};
	public:
		void SetMeme( bool toSet );
		void Draw( Vei2 screenPos, Graphics& gfx );
		bool HasMeme() const;
	private:
		State state = Hidden;
		bool hasMeme = false;
	};
public:
	MemeField( int numMemes );
	void Draw( Graphics& gfx );
private:
	static constexpr int Width = 20;
	static constexpr int Height = 20;
	Tile field[ Width * Height ];
	const Tile& TileAt( const Vei2 pos ) const;
	Tile& TileAt( const Vei2 pos );
private:
	void PlaceMine( const Vei2& pos );
};