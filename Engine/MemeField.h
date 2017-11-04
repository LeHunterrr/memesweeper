#pragma once
#include "Vei2.h"

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
		bool HasMeme() const;
	private:
		State state = Hidden;
		bool hasMeme = false;
	};
public:
	MemeField( int numMemes );
private:
	static constexpr int Width = 20;
	static constexpr int Height = 20;
	Tile field[ Width * Height ];
	const Tile& TileAt( const Vei2 pos ) const;
	Tile& TileAt( const Vei2 pos );
private:
	void PlaceMine( const Vei2& pos );
};