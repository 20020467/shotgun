#include <iostream>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"

using namespace std;

BaseObject g_background;
BaseObject g_background_menu;
BaseObject g_background_win;
BaseObject g_background_loss;



bool InitData()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		g_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( g_window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			g_screen = SDL_CreateRenderer( g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( g_screen == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( g_screen, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if (TTF_Init() == -1)
                {
                    printf("SDL_TTF failed",TTF_GetError());
                    success = false;
                }

                font_mark = TTF_OpenFont("font//mark.ttf",25);

                if(font_mark == NULL)
                {
                	std::cout<<" load  font mark false";
                    success = false;
                }

                font_time = TTF_OpenFont("font//trebucbi.ttf", 30);
                if(font_time == NULL)
                {
                    success = false;
                }


				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img//vutru.jpg", g_screen);
    bool ret_2 = g_background_menu.LoadImg("img//background_menu.png" , g_screen);
	bool win = g_background_win.LoadImg("img//win.png" , g_screen);
	bool loss = g_background_loss.LoadImg("img//loss.png" , g_screen);

    if (ret == false) return false;
    if(ret_2 == false) return false;
    if (win == false) return false;
    if (loss == false) return false;


    return true;
}

bool LoadMedia()
{
	gBulletMainMusic = Mix_LoadWAV( "music//tieng_lazer.wav");
	if( gBulletMainMusic == NULL) return false;

	gCollisionMusic = Mix_LoadWAV( "music//tieng_min_no.wav");
	if( gCollisionMusic == NULL) return false;

	return true;
}

void close()
{
	Mix_FreeChunk(gBulletMainMusic);
	Mix_FreeChunk(gCollisionMusic);

	gBulletMainMusic = NULL;
	gCollisionMusic = NULL;

    g_background.Free();
	g_background_menu.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();

}



int main(int argc, char* argv[])
{

    srand((int)time(0));

    if (InitData() == false ){
        return -1;
    }
    if (LoadBackground() == false){
        return -1;
    }
    if( LoadMedia() == false)
	{
		return -1;
	}

	bool is_quit = false;
    while(!is_quit)
    {
        while(SDL_PollEvent(&g_event)!= 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

        }
        SDL_SetRenderDrawColor(g_screen,255, 255, 255, 255);
		SDL_RenderClear(g_screen);

		g_background_menu.Render(g_screen, NULL);

		SDL_RenderPresent(g_screen);

		if(g_event.type == SDL_KEYDOWN)
		{
			MainObject p_player;
			p_player.LoadImg("img//goku.png", g_screen);

			ExplosionObject exp_main;
			bool ret = exp_main.LoadImg("img/exp_main.png", g_screen);
			exp_main.SetClip();

			double scrollingOffset = 0;


			TextObject time_game;
			time_game.SetColor(TextObject::WHITE_TEXT);

			TextObject mark_game;
			mark_game.SetColor(TextObject::WHITE_TEXT);
			int mark_value = 0;


			while(!is_quit)
			{
				while(SDL_PollEvent(&g_event)!= 0)
				{
					if(g_event.type == SDL_QUIT)
					{
						is_quit = true;
					}

					p_player.HandelInputAction(g_event, g_screen , gBulletMainMusic);
				}

				SDL_SetRenderDrawColor(g_screen,255, 255, 255, 255);
				SDL_RenderClear(g_screen);

				scrollingOffset-=1;
				if( scrollingOffset < -SCREEN_HEIGHT )
					{
						scrollingOffset = 0;
					}


				g_background.RenderScroll(g_screen, NULL, 0, scrollingOffset );
				g_background.RenderScroll(g_screen, NULL, 0, scrollingOffset + SCREEN_HEIGHT );
				g_background.RenderScroll(g_screen, NULL, 0, scrollingOffset + SCREEN_HEIGHT + SCREEN_HEIGHT);

				p_player.HandelThreatsAction(g_screen , mark_value );

				p_player.HandleBullet(g_screen);
				p_player.HandleThreats(g_screen);

				p_player.Show(g_screen);

				std::vector<ThreatsObject*> threats_list = p_player.get_threats_list();
                for(int i = 0; i<threats_list.size();i++)
                {
                    ThreatsObject* obj_threats = threats_list[i];
                    if(obj_threats != NULL)
                    {
                        SDL_Rect tRect;
                        tRect.y = obj_threats->GetRect().y;
                        if (tRect.y >= SCREEN_HEIGHT)
                        {
                            num_threats_over++;
							if (num_threats_over == 2)
                            {
                            	bool quit_game = false;
                            	while(!quit_game)
								{
									Mix_FreeChunk(gBulletMainMusic);

									SDL_SetRenderDrawColor(g_screen,255, 255, 255, 255);
									SDL_RenderClear(g_screen);


									g_background_loss.Render(g_screen , NULL);
									SDL_RenderPresent(g_screen);

									while(SDL_PollEvent(&g_event)!= 0)
										{

											if(g_event.type == SDL_QUIT || g_event.type == SDL_KEYDOWN)
											{
												is_quit = true;
												quit_game = true;
											}

										}
								}


                            }
                        }


                    }

                }



				std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
				for(int r = 0; r<bullet_arr.size(); r++)
				{
					BulletObject* p_bullet = bullet_arr.at(r);
					if(p_bullet != NULL)
					{
						std::vector<ThreatsObject*> threats_list = p_player.get_threats_list();
						for(int t = 0; t<threats_list.size();t++)
						{
							ThreatsObject* obj_threats = threats_list.at(t);
							if(obj_threats != NULL)
							{
								SDL_Rect tRect;
								tRect.x = obj_threats->GetRect().x;
								tRect.y = obj_threats->GetRect().y;
								tRect.w = 95;
								tRect.h = 80;

								SDL_Rect bRect = p_bullet->GetRect();

								bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

								if (bCol)
								{
									Mix_PlayChannel( -1 , gCollisionMusic , 0);
									mark_value+=5;
									p_player.RemoveBullet(r);
									obj_threats->Free();
									threats_list.erase(threats_list.begin() + t);


									for (int ex = 0; ex < 4; ex++)
									{

									exp_main.ShowExplosion(g_screen, tRect.x+10, tRect.y-20);

									}

								}

								SDL_Rect pRect ;
								SDL_GetMouseState( &pRect.x, &pRect.y );


							}


						}
					}

				}

				std::string str_time = "Time: ";
				int time_val = SDL_GetTicks()/1000;

				int time_limit = 0;
				time_limit +=time_val;



				std::string str_val = std::to_string(time_val);
				str_time += str_val;

				time_game.SetText(str_time);
				time_game.LoadFromRenderText(font_time, g_screen);
				time_game.RenderText(g_screen, 1050,15);


				std::string val_str_mark = std:: to_string(mark_value);
				std::string strMark("Mark: ");
				strMark += val_str_mark;

				mark_game.SetText(strMark);
				mark_game.LoadFromRenderText( font_mark , g_screen);
				mark_game.RenderText(g_screen,50, 15);

				if(time_limit > 100)
				{
					mark_game.Free();
					time_game.Free();
					Mix_FreeChunk(gBulletMainMusic);

					SDL_SetRenderDrawColor(g_screen,255, 255, 255, 255);
					SDL_RenderClear(g_screen);


					g_background_win.Render(g_screen , NULL);
					SDL_RenderPresent(g_screen);

					 while(SDL_PollEvent(&g_event)!= 0)
					{
						if(g_event.type == SDL_QUIT || g_event.type == SDL_KEYDOWN)
						{
							is_quit = true;
						}

					}


				}

				SDL_RenderPresent(g_screen);

			}



		}
    }


    close();

    return 0;
}
