#ifndef LBUTTON_H_
#define LBUTTON_H_

class LButton
{
public:
	LButton();
	~LButton();

	void setPosition( int &x, int &y );
	void handleEvent( SDL_Event* g_event );

	void render();

private:

	SDL_Point mPosition;




};


#endif // LBUTTON_H_