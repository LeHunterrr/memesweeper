#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "RectI.h"
#include "SpriteCodex.h"

class MemeField {
public:
	enum GameState {
		IsFucked,
		Going,
		Won
	};
private:
	class Tile {
	public:
		static enum State {
			Hidden,
			Flagged,
			Revealed
		};
	public:
		void SetMeme( bool toSet );
		void Draw( const Vei2& screenPos, Graphics& gfx, GameState isFucked ) const;
		void Reveal();
		void ToggleFlag();
		bool HasMeme() const;
		bool IsRevealed() const;
		bool IsFlagged() const;
	public:
		int numNeighbourMemes = 0;
	private:
		State state = Hidden;
		bool hasMeme = false;
	};
public:
	MemeField( int numMemes );
	void Draw( Graphics& gfx ) const;
	void RevealTile( const Vei2& ScreenPos );
	void ToggleFlag( const Vei2& ScreenPos );
	void CheckForWin();
	RectI GetField() const;
	GameState GetGameState() const;
private:
	void PlaceMeme( const Vei2& pos );
	void DrawField( const RectI& rect, Graphics& gfx ) const;
	void SetNeighbourMemes( const Vei2& pos );
	void SetNeighbourMemes( int index );
	void Recrusion( const Vei2& start );
	const Tile& TileAt( const Vei2& pos ) const;
	Tile& TileAt( const Vei2& pos );
	Vei2 ScreenToGrid( const Vei2& ScreenPos ) const;
private:
	RectI BackgroundField;
	static constexpr int _width = 8;
	static constexpr int _height = 8;
	static constexpr int OffsetX = ( Graphics::ScreenWidth / ( 2 * SpriteCodex::tileSize ) ) - ( _width / 2 );
	static constexpr int OffsetY = ( Graphics::ScreenHeight / ( 2 * SpriteCodex::tileSize ) ) - ( _height / 2 );
	static constexpr int Width = _width + OffsetX;
	static constexpr int Height = _height + OffsetY;
	Tile field[ Width * Height ];
	GameState gamestate = Going;
};