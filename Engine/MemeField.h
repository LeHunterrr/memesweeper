#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "RectI.h"

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
		void Draw( const Vei2& screenPos, Graphics& gfx ) const;
		bool HasMeme() const;
	private:
		State state = Hidden;
		bool hasMeme = false;
	};
public:
	MemeField( int numMemes );
	void Draw( Graphics& gfx ) const;
	RectI GetField() const;
private:
	RectI BackgroundField;
	static constexpr int Width = 20;
	static constexpr int Height = 20;
	Tile field[ Width * Height ];
	const Tile& TileAt( const Vei2 pos ) const;
	Tile& TileAt( const Vei2 pos );
	void DrawField(const RectI& rect, Graphics& gfx) const;
private:
	void PlaceMine( const Vei2& pos );
};