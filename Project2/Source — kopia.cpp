#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

enum KEYS{LEFT,RIGHT}; //nazywamy keysy bo bedzie ciezko zapamietac z tablicy co jest czym

int main(void)
{

	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	int szerokosc = 1920;
	int wysokosc = 1080;

	int kamera_x = 0;

	bool done = false;
	bool przerys = true;

	int pos_x = 10;
	int pos_y = (wysokosc*3)/4;

	int FPS = 60;
	int ostatni_ruch = 0;

	int grunt1_x = 0;
	int grunt1_y = pos_y + 80;


	bool keys[4] = { false,false,false,false };//bo ich nie trzymasz


 //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	ALLEGRO_DISPLAY *okno = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bohater = NULL;
	ALLEGRO_BITMAP *grunt1 = NULL;
	ALLEGRO_BITMAP *wrog1 = NULL;
	ALLEGRO_BITMAP *wrog2 = NULL;
	ALLEGRO_BITMAP *tlo_gl = NULL;
	ALLEGRO_BITMAP *tlo2 = NULL;
	ALLEGRO_FONT *font18 = al_load_ttf_font("verdana.ttf", 18, 0);


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	if (!al_init())
		return -1;

	okno = al_create_display(szerokosc, wysokosc);

	if (!okno)
		return -1;


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	bohater = al_load_bitmap("player model.png");
	grunt1 = al_load_bitmap("grunt1.png");
	wrog1 = al_load_bitmap("wrog.png");
	wrog2 = al_load_bitmap("wrog.png");
	tlo_gl = al_load_bitmap("tlo_gl.png");
	tlo2 = al_load_bitmap("tlo2.png");


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(okno));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);



		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				ostatni_ruch = 1;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				ostatni_ruch = 0;
				break;
			}
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_UP)//esc wylacza okno
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)//X wylacza okno
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{

			if (pos_x<960)
			{
				pos_x -= keys[LEFT] * 5;
				pos_x += keys[RIGHT] * 5;
			}

			else if (kamera_x == 0)
			{
				pos_x = 955;
			}

			if (pos_x >= 960)
			{
				kamera_x -= keys[RIGHT] * 5;
				kamera_x += keys[LEFT] * 5;
			}


			//jak prawda to 1 razy to a jak nie to nie ma
			przerys = true;
		}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


		if (przerys && al_is_event_queue_empty(event_queue))//unika ghostow
		{
			przerys = false;


			al_draw_bitmap(tlo_gl, 0+kamera_x/3, 0, 0);
			al_draw_bitmap(tlo2, (0+kamera_x*2)/3, 0, 0);


			//al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255, 0, 255));
			if (ostatni_ruch == 0)
			{
				al_draw_bitmap(bohater, pos_x, pos_y, 0);
			}
			else
			{
				al_draw_bitmap(bohater, pos_x, pos_y, ALLEGRO_FLIP_HORIZONTAL);
			}

			al_draw_bitmap(grunt1, grunt1_x + kamera_x, grunt1_y, 0);
			al_draw_bitmap(grunt1, grunt1_x + 850 + kamera_x, grunt1_y, 0);

			al_draw_bitmap(wrog1, grunt1_x + 1000 + kamera_x, grunt1_y - 80, 0);
			al_draw_bitmap(wrog2, grunt1_x + 1300 + kamera_x, grunt1_y - 80, 0);

			al_draw_textf(font18, al_map_rgb(50, 0, 255), 350, 50, ALLEGRO_ALIGN_LEFT, "%i", pos_x);
			al_draw_textf(font18, al_map_rgb(200, 0, 255), 150, 50, ALLEGRO_ALIGN_LEFT, "%i", kamera_x);


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

	}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	al_destroy_display(okno);
	al_destroy_bitmap(bohater);
	al_destroy_bitmap(grunt1);
	al_destroy_bitmap(wrog1);
	al_destroy_bitmap(wrog2);
	al_destroy_bitmap(tlo2);
	al_destroy_bitmap(tlo_gl);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);



	return 0;
}