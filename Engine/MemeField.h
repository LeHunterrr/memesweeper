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
		void Reveal();
		void ToggleFlag();
		bool HasMeme() const;
		bool IsRevealed() const;
		bool IsFlagged() const;
	private:
		State state = Hidden;
		bool hasMeme = false;
	};
public:
	MemeField( int numMemes );
	void Draw( Graphics& gfx ) const;
	void RevealTile( const Vei2& ScreenPos );
	void ToggleFlag( const Vei2& ScreenPos );
	RectI GetField() const;
private:
	void PlaceMine( const Vei2& pos );
	void DrawField( const RectI& rect, Graphics& gfx ) const;
	const Tile& TileAt( const Vei2& pos ) const;
	Tile& TileAt( const Vei2& pos );
private:
	RectI BackgroundField;
	static constexpr int Width = 20;
	static constexpr int Height = 20;
	Tile field[ Width * Height ];
};